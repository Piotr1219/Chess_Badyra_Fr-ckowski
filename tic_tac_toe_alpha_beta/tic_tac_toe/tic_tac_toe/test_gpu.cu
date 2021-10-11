#include "test_gpu.cuh"
#include "Search.h"
#include "Board.h"

__device__ int simple_example(int* temp, int n) {
	printf("Testing");
	return n;
}

__global__ void test_kernel(void) {
}


// Only first kernel launch compiles correctly


__global__ void generate_tree(int* board, int& depth, int board_size, Node* root, pointFunctionGenerateValidMoves GenerateValidMovesPointer, pointFunctionCountMoves CountMovesPointer, int* d_result) {

	int index = threadIdx.x;

	printf("Testing kernel\n");
	// from defaut x starts each game, need to specify that everywhere

	// generate all possible moves from given position, where first element of pointer is moves count


	//int* possible_moves = (*GenerateValidMovesPointer)(board, board_size);
	int* possible_moves = new int[5];
	possible_moves[0] = 1;
	const int len = possible_moves[0];

	printf("Generated possible moves\n");

	// allocate space for all root's children and declare child_count

	root->children = new Node * [len];
	root->children_count = len;

	// check which symbol should be drawn next and declare symbol value: 1 = 'x', -1 = 'o'
	int move_count = (*CountMovesPointer)(root->squares, board_size);
	int symbol = 0;
	if (move_count % 2 == 0) {
		symbol = 1;
	}
	else {
		symbol = -1;
	}

	printf("Calculated symbol\n");

	// for each possible position we need to create new child and add it to root->children array

	Node* child = new Node;
	child->squares = new int[board_size * board_size];

	// we need to copy squares, so root squares will not be changed
	//std::copy(root->squares, root->squares + int(board_size * board_size), child->squares);

	child->squares = root->squares;	// VERY TEMP 

	// adding 1 to array index, because [0] element is moves count, not index of squares array
	child->squares[possible_moves[index + 1]] = symbol;
	child->score = 0;
	child->parent = root;
	root->children[index] = child;
	child->children_count = 0;

	delete[] possible_moves;

	// in small board_size values depth is not needed, we can evaluate all positions, but might be usefull in future implementations

	int* left_cells = (*GenerateValidMovesPointer)(root->children[index]->squares, board_size);
	if (left_cells[0] != 0) {

		// increasing value of depth, because we are going deeper into tree
		depth = depth + 1;
		//generate_tree<<<1, root->children_count>>>(root->children[index]->squares, depth, board_size, child, GenerateValidMovesPointer, CountMovesPointer);
	}

	//std::cout << "Try to delete left_cells" << std::endl;
	delete[] left_cells;

	// std::cout << "Try to delete possible_moves" << std::endl;

	// decreasing depth, because we are returning from recursive algorithm, which means we are going up
	depth = depth - 1;
	*d_result = root->children_count;

	printf("Exiting kernel, childcout: %d\n", root->children_count);
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

		printf("Generate tree device function\n");

		pointFunctionGenerateValidMoves host_GenerateValidMovesPointer;
		pointFunctionGenerateValidMoves GenerateValidMovesPointer = Board::GenerateValidMoves;

		pointFunctionCountMoves host_CountMovesPointer;
		pointFunctionCountMoves CountMovesPointer = Board::CountMoves;

		cudaMemcpyFromSymbol(&host_GenerateValidMovesPointer, GenerateValidMovesPointer, sizeof(pointFunctionGenerateValidMoves));
		cudaMemcpyFromSymbol(&host_CountMovesPointer, CountMovesPointer, sizeof(pointFunctionCountMoves));

		int* d_board;
		int *result; 
		int *d_result;
		Node* d_root;

		cudaMalloc(&d_board, board_size * sizeof(int));
		cudaMalloc(&d_root, sizeof(Node));
		cudaMalloc(&d_result, sizeof(int));
		cudaMalloc(&result, sizeof(int));

		printf("Result before kernel: %d\n", result);

		cudaMemcpy(d_board, board, board_size * sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(d_root, root, sizeof(Node), cudaMemcpyHostToDevice);

		generate_tree << <1, 1 >> > (d_board, depth, board_size, d_root, host_GenerateValidMovesPointer, host_CountMovesPointer, d_result);

		cudaMemcpy(result, d_result, sizeof(int), cudaMemcpyDeviceToHost);

		printf("Exiting device function\n");
		printf("Children count: %d\n", result);
	}
}