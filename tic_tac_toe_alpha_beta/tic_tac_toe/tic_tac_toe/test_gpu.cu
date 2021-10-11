#include "test_gpu.cuh"
#include "Search.h"
#include "Board.h"

typedef int* (*pointFunctionGenerateValidMoves)(int*, int);
typedef int (*pointFunctionCountMoves)(int*, int);

__device__ int simple_example(int* temp, int n) {
	printf("Testing");
	return n;
}

__global__ void test_kernel(void) {
}

// pointFunctionGenerateValidMoves GenerateValidMovesPointer, pointFunctionCountMoves CountMovesPointer

__global__ void generate_tree(int* board, int& depth, int board_size, Node* root, pointFunctionCountMoves Pointer) {
	
	int index = threadIdx.x;
	int *temp = new int;
	int n = 0;

	n = (*Pointer)(temp, n);

	//printf("Testing generating gametree\n");
	// from defaut x starts each game, need to specify that everywhere

	// generate all possible moves from given position, where first element of pointer is moves count
	
	/*
	int* possible_moves = (*GenerateValidMovesPointer)(board, board_size);
	const int len = possible_moves[0];

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

	*/

	// decreasing depth, because we are returning from recursive algorithm, which means we are going up
	depth = depth - 1;
}

namespace Test {

	//__device__ pointFunctionGenerateValidMoves GenerateValidMovesPointer = Board::GenerateValidMoves;
	//pointFunctionGenerateValidMoves host_GenerateValidMovesPointer;

	//__device__ pointFunctionCountMoves CountMovesPointer = Board::CountMoves;
	//pointFunctionCountMoves host_CountMovesPointer;

	__device__ pointFunctionCountMoves Pointer_d = simple_example;
	pointFunctionCountMoves Pointer_h;

	void test(void)
	{
		test_kernel <<<1, 1>>> ();
		printf("Hello, CUDA is here!");
	}

	void GenerateTree(int* board, int& depth, int board_size, Node* root) {

		//cudaMemcpyFromSymbol(&host_GenerateValidMovesPointer, GenerateValidMovesPointer, sizeof(pointFunctionGenerateValidMoves));
		//cudaMemcpyFromSymbol(&host_CountMovesPointer, CountMovesPointer, sizeof(pointFunctionCountMoves));

		cudaMemcpyFromSymbol(&Pointer_h, Pointer_d, sizeof(pointFunctionCountMoves));


		//generate_tree << <1, 1 >> > (board, depth, board_size, root, host_GenerateValidMovesPointer, host_CountMovesPointer);

		generate_tree << <1, 1 >> > (board, depth, board_size, root, Pointer_h);
	}
}