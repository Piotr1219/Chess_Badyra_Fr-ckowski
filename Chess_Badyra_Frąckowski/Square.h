#pragma once
#include <string>
#include <list>
#include <stack>
#include "Piece.h"
#include <iostream>
//#include "cuda_runtime.h"
#include "device_launch_parameters.h"

struct Square
{
    Piece Piece1;

    __device__ __host__ Square(Piece piece);
    __device__ __host__ Square();

};
