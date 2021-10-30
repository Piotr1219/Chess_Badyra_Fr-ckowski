#pragma once
#include <iostream>
#include "device_launch_parameters.h"


class Test_class {

public:

	int shape;
	//constructor
	__device__ __host__ Test_class();

	__device__ __host__ Test_class(int shape1);

};
