#include <assert.h>
#include "test_gpu.cuh"
#include "Search.h"
#include "Board.h"

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}

__device__ int simple_example(int* temp, int n) {
	printf("Testing");
	return n;
}

__global__ void test_kernel(void) {
}

__device__ int CountMovesGPU(int* squares, int size) {
	int counter = 0;
	//printf("CountMovesGPU\n %d  %d  %d\n %d  %d  %d\n %d  %d  %d\n", squares[0], squares[1], squares[2], squares[3], squares[4], squares[5], squares[6], squares[7], squares[8]);
	//printf(" %d  %d  %d\n", squares[3], squares[4], squares[5]);
	//printf(" %d  %d  %d\n", squares[6], squares[7], squares[8]);
	for (int i = 0; i < size * size; ++i) {
		if (squares[i] != 0) {
			++counter;
		}
	}
	return counter;
}

__device__ int* GenerateValidMovesGPU(int* squares, int board_size) {
	int count_moves = CountMovesGPU(squares, board_size);
	int* free_cells = new int[board_size * board_size - count_moves + 1];
	int counter = 0;
	//printf("Counted moves %d\n", count_moves);

	free_cells[0] = 0;
	for (int i = 0; i < board_size * board_size; ++i) {
		if (IsMoveValidGPU(squares, board_size, i)) {
			counter = counter + 1;
			free_cells[counter] = i;
		}
	}
	free_cells[0] = counter;

	return free_cells;
}

__device__ bool IsMoveValidGPU(int* squares, int board_size, int move) {
	if (IsGameFinishedGPU(squares, board_size) == 0) {
		if (move < board_size * board_size) {
			if (squares[move] == 0) {
				return true;
			}
		}
	}
	return false;
}

__device__ int IsGameFinishedGPU(int* squares, int board_size) {
	int test_sum_row = 0;
	
	// look for win in rows
	for (int i = 0; i < board_size; ++i) {
		test_sum_row = 0;
		for (int j = 0; j < board_size; ++j) {
			if (squares[i * board_size + j] == 1 && test_sum_row >= 0) {
				++test_sum_row;
			}
			else if (squares[i * board_size + j] == -1 && test_sum_row <= 0) {
				--test_sum_row;
			}
			else {
				test_sum_row = 0;
			}

			if (test_sum_row == 3 || test_sum_row == -3) {
				return test_sum_row;
			}
		}
	}
	
	int test_sum_col = 0;

	// look for win in columns
	for (int j = 0; j < board_size; ++j) {
		test_sum_col = 0;
		for (int i = 0; i < board_size; ++i) {
			if (squares[i * board_size + j] == 1 && test_sum_col >= 0) {
				++test_sum_col;
			}
			else if (squares[i * board_size + j] == -1 && test_sum_col <= 0) {
				--test_sum_col;
			}
			else {
				test_sum_col = 0;
			}

			if (test_sum_col == 3 || test_sum_col == -3) {
				return test_sum_col;
			}
		}
	}

	int test_sum_diagonal = 0;

	// look for win in diagonals
	// for now only support 3x3 boards and their main diagonals
	for (int i = 0; i < board_size; ++i) {
		if (squares[i * board_size + i] == 1 && test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (squares[i * board_size + i] == -1 && test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return test_sum_diagonal;
		}
	}

	test_sum_diagonal = 0;

	for (int i = 0; i < board_size; ++i) {
		if (squares[i * board_size + (board_size - 1 - i)] == 1 && test_sum_diagonal >= 0) {
			++test_sum_diagonal;
		}
		else if (squares[i * board_size + (board_size - 1 - i)] == -1 && test_sum_diagonal <= 0) {
			--test_sum_diagonal;
		}
		else {
			test_sum_diagonal = 0;
		}

		if (test_sum_diagonal == 3 || test_sum_diagonal == -3) {
			return test_sum_diagonal;
		}
	}


	int test_draw = 1;
	for (int i = 0; i < board_size * board_size; ++i) {
		test_draw = test_draw * squares[i];
	}

	return test_draw;
}


__device__ void GenerateTreeParrarel(int* board, int& depth, int board_size, Node* root) {

	// from defaut x starts each game, need to specify that everywhere
	//printf("Depth: %d\n", depth);
	// generate all possible moves from given position, where first element of pointer is moves count
	int* possible_moves = GenerateValidMovesGPU(board, board_size);
	const int len = possible_moves[0];

	// allocate space for all root's children and declare child_count

	root->children = new Node * [len];
	root->children_count = len;

	// check which symbol should be drawn next and declare symbol value: 1 = 'x', -1 = 'o'
	int move_count = CountMovesGPU(root->squares, board_size);
	int symbol = 0;
	if (move_count % 2 == 0) {
		symbol = 1;
	}
	else {
		symbol = -1;
	}

	// for each possible position we need to create new child and add it to root->children array
	for (int i = 0; i < len; ++i) {

		Node* child = new Node;
		child->squares = new int[board_size * board_size];

		// we need to copy squares, so root squares will not be changed
		//std::copy(root->squares, root->squares + int(board_size * board_size), child->squares);
		memcpy(child->squares, root->squares, board_size * board_size * sizeof(int));

		// adding 1 to array index, because [0] element is moves count, not index of squares array
		child->squares[possible_moves[i + 1]] = symbol;
		child->score = 0;
		child->parent = root;
		root->children[i] = child;
		child->children_count = 0;

		// in small board_size values depth is not needed, we can evaluate all positions, but might be usefull in future implementations

		int* left_cells = GenerateValidMovesGPU(child->squares, board_size);
		if (left_cells[0] != 0) {

			// increasing value of depth, because we are going deeper into tree
			depth = depth + 1;
			GenerateTreeParrarel(child->squares, depth, board_size, child);
		}

		//std::cout << "Try to delete left_cells" << std::endl;
		delete[] left_cells;
	}

	//std::cout << "Try to delete possible_moves" << std::endl;
	delete[] possible_moves;

	// decreasing depth, because we are returning from recursive algorithm, which means we are going up
	depth = depth - 1;
}

__device__ pointFunctionGenerateValidMoves GenerateValidMovesPointer = GenerateValidMovesGPU;
__device__ pointFunctionCountMoves CountMovesPointer = CountMovesGPU;
__device__ pointFunctionGenerateTreeParrarel GenerateTreeParrarelPointer = GenerateTreeParrarel;

// Only first kernel launch compiles correctly
// There is issue with GenerateValidMovesPointer, propably it needs device word in initialization, propably same problem with CountMovesPointer


__global__ void generate_tree(int* board, int depth, int board_size, Node* root, int* root_squares, Node* root_parent, int root_score, pointFunctionGenerateValidMoves GenerateValidMovesPointer, pointFunctionCountMoves CountMovesPointer, int* d_result) {

	int index = threadIdx.x;

	root->score = root_score;
	root->squares = root_squares;
	root->parent = root_parent;

	//printf("Testing kernel, depth: %d, pos:\n", depth);
	//printf(" %d  %d  %d\n %d  %d  %d\n %d  %d  %d\n", root->squares[0], root->squares[1], root->squares[2], root->squares[3], root->squares[4], root->squares[5], root->squares[6], root->squares[7], root->squares[8]);
		//printf(" %d  %d  %d\n", root->squares[3], root->squares[4], root->squares[5]);
		//printf(" %d  %d  %d\n", root->squares[6], root->squares[7], root->squares[8]);

	// from defaut x starts each game, need to specify that everywhere

	// generate all possible moves from given position, where first element of pointer is moves count


	int* possible_moves = (*GenerateValidMovesPointer)(board, board_size);
	const int len = possible_moves[0];

	// allocate space for all root's children and declare child_count

	root->children = new Node * [len];
	root->children_count = len;

	//printf("Children count: %d, index: %d, depth: %d\n", root->children_count, index, depth);

	// check which symbol should be drawn next and declare symbol value: 1 = 'x', -1 = 'o'
	//printf("Before counting moves, index: %d, depth: %d, pos\n", index, depth);
	//printf(" %d  %d  %d\n", root->squares[0], root->squares[1], root->squares[2]);
	//printf(" %d  %d  %d\n", root->squares[3], root->squares[4], root->squares[5]);
	//printf(" %d  %d  %d\n", root->squares[6], root->squares[7], root->squares[8]);
	int move_count = (*CountMovesPointer)(root->squares, board_size);
	int symbol = 0;
	if (move_count % 2 == 0) {
		symbol = 1;
	}
	else {
		symbol = -1;
	}

	//printf("Calculated symbol: %d\n", symbol);

	// for each possible position we need to create new child and add it to root->children array

	Node* child = new Node;
	child->squares = new int[board_size * board_size];

	// we need to copy squares, so root squares will not be changed
	//std::copy(root->squares, root->squares + int(board_size * board_size), child->squares);


	// GOTTA SOMEHOW COPY POSITION
	//child->squares = root->squares;	// VERY TEMP 

	memcpy(child->squares, root->squares, board_size*board_size*sizeof(int));

	/*
	printf("After assigning pos to children[index], index: %d, depth: %d, pos\n", index, depth);
	printf(" %d  %d  %d\n", child->squares[0], child->squares[1], child->squares[2]);
	printf(" %d  %d  %d\n", child->squares[3], child->squares[4], child->squares[5]);
	printf(" %d  %d  %d\n", child->squares[6], child->squares[7], child->squares[8]);

	printf("Addres of child: %d\n", child->squares);
	*/

	// adding 1 to array index, because [0] element is moves count, not index of squares array
	child->squares[possible_moves[index + 1]] = symbol;
	/*
	printf("After adding move to children[index], index: %d, depth: %d, pos\n", index, depth);
	printf(" %d  %d  %d\n", child->squares[0], child->squares[1], child->squares[2]);
	printf(" %d  %d  %d\n", child->squares[3], child->squares[4], child->squares[5]);
	printf(" %d  %d  %d\n", child->squares[6], child->squares[7], child->squares[8]);
	*/
	child->score = 0;
	child->parent = root;
	root->children[index] = child;
	child->children_count = 0;

	delete[] possible_moves;

	//printf("Created children\n");

	// in small board_size values depth is not needed, we can evaluate all positions, but might be usefull in future implementations

	//int** left_cells = new int* [index];

	//printf("Generating left_cells\n");

	int* left_cells = (*GenerateValidMovesPointer)(root->children[index]->squares, board_size);

	//printf("Generated next len: %d, index: %d, depth: %d\n", left_cells[0], index, depth);


	//printf("Index %d, depth %d, %d %d %d %d %d %d %d %d\n", index, depth, left_cells[1], left_cells[2], left_cells[3], left_cells[4], left_cells[5], left_cells[6], left_cells[7], left_cells[8]);


	if (left_cells[0] != 0) {
	//if (depth<6){
		//printf("In if\n");
		// increasing value of depth, because we are going deeper into tree
		depth = depth + 1;
		generate_tree<<<1, left_cells[0]>>>(root->children[index]->squares, depth, board_size, root->children[index], root->children[index]->squares, root->children[index]->parent, root->children[index]->score, GenerateValidMovesPointer, CountMovesPointer, d_result);
		//printf("Exiting depth %d\n", depth);
		cudaDeviceSynchronize();
		depth = depth - 1;
	}
	//printf("After if\n");

	//std::cout << "Try to delete left_cells" << std::endl;
	delete[] left_cells;

	// std::cout << "Try to delete possible_moves" << std::endl;

	// decreasing depth, because we are returning from recursive algorithm, which means we are going up
	*d_result = root->children_count;

	//printf("Exiting kernel, child_count: %d, index: %d, depth: %d\n", *d_result, index, depth);
	if (depth == 1 && index == 0) {
		printf("root->children[0]->children[0]->children_count %d:\n", root->children[0]->children[0]->children_count);
	}
}

__global__ void generate_tree_parrarel(int* board, int depth, int board_size, Node* root, int* root_squares, Node* root_parent, int root_score, pointFunctionGenerateValidMoves GenerateValidMovesPointer, pointFunctionCountMoves CountMovesPointer, pointFunctionGenerateTreeParrarel GenerateTreeParrarelPointer, int* d_result) {
	root->score = root_score;
	root->squares = root_squares;
	root->parent = root_parent;
	printf("Running recursive func\n");
	(*GenerateTreeParrarel)(board, depth, board_size, root);
	printf("End recursive func\n");
}

namespace Test {

	__device__ pointFunctionCountMoves Pointer_d = simple_example;
	pointFunctionCountMoves Pointer_h;

	void test(void)
	{
		test_kernel <<<1, 1>>> ();
		printf("Hello, CUDA is here!");
	}

	void GenerateTree(int* board, int& depth, int board_size, Node* root) {

		cudaDeviceSetLimit(cudaLimitMallocHeapSize, 100000000);
		printf("Generate tree device function\n");

		pointFunctionGenerateValidMoves host_GenerateValidMovesPointer;
		pointFunctionCountMoves host_CountMovesPointer;
		pointFunctionGenerateTreeParrarel host_GenerateTreeParrarelPointer;

		cudaMemcpyFromSymbol(&host_GenerateValidMovesPointer, GenerateValidMovesPointer, sizeof(pointFunctionGenerateValidMoves));
		cudaMemcpyFromSymbol(&host_CountMovesPointer, CountMovesPointer, sizeof(pointFunctionCountMoves));
		cudaMemcpyFromSymbol(&host_GenerateTreeParrarelPointer, GenerateTreeParrarelPointer, sizeof(pointFunctionGenerateTreeParrarel));

		int* d_board;
		int *result = (int*)malloc(sizeof(int)); 
		int *d_result;
		int* root_squares;
		Node* root_parent;
		Node* d_root;

		gpuErrchk(cudaMalloc(&d_board, board_size * board_size * sizeof(int)));
		gpuErrchk(cudaMalloc(&d_result, sizeof(int)));
		gpuErrchk(cudaMalloc(&root_squares, board_size * board_size * sizeof(int)));
		gpuErrchk(cudaMalloc(&root_parent, sizeof(Node)));
		gpuErrchk(cudaMalloc(&d_root, sizeof(Node)));

		cudaMemcpy(d_board, board, board_size * board_size * sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(d_root, root, sizeof(Node), cudaMemcpyHostToDevice);
		cudaMemcpy(root_squares, root->squares, board_size * board_size * sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(root_parent, root->parent, sizeof(Node), cudaMemcpyHostToDevice);
		cudaMemcpy(d_root, root, sizeof(Node), cudaMemcpyHostToDevice);

		printf("Testowanie generowania na karcie nie w kernelu:\n");

		generate_tree_parrarel << <1, 1 >> > (d_board, depth, board_size, d_root, root_squares, root_parent, root->score, host_GenerateValidMovesPointer, host_CountMovesPointer, host_GenerateTreeParrarelPointer, d_result);
		cudaDeviceSynchronize();

		printf("Wygenerowano cale drzewo, teraz w kernelu testy zaczac czas:\n");

		generate_tree << <1, 8 >> > (d_board, depth, board_size, d_root, root_squares, root_parent, root->score, host_GenerateValidMovesPointer, host_CountMovesPointer, d_result);
		//gpuErrchk(cudaPeekAtLastError());
		gpuErrchk(cudaDeviceSynchronize());

		printf("Exited kernel\n");

		cudaMemcpy(result, d_result, sizeof(int), cudaMemcpyDeviceToHost);

		printf("Exiting device function\n");
		printf("Children count: %d\n", *result);
	}
}