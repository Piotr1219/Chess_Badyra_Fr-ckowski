#include "test_gpu.cuh"

__global__ void test_kernel(void) {
}

namespace Test {
	void test(void)
	{
		test_kernel <<<1, 1>>> ();
		printf("Hello, CUDA is here!");
	}
}