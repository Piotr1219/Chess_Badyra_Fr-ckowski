#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Search.h"

#include <stdio.h>

namespace Test {
	void test(void);
	void GenerateTree(int* board, int& depth, int board_size, Node* root);
}