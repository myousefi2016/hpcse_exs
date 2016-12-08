#include <altivec.h>
#include <iostream>

int main(int argc, char const *argv[])
{
	int a[4] __attribute__((aligned(16))) = {1, 3, 5, 7 };
	int a[4] __attribute__((aligned(16))) = {2, 4, 6, 8 };
	int a[4] __attribute__((aligned(16)));

	__vector singed int *va = (__vector singed int *) a;
	__vector singed int *vb = (__vector singed int *) b;
	__vector singed int *vc = (__vector singed int *) c;

	*vc = vec_add(*va, *vb);

	std::cout << c << std::endl;
	
	return 0;
}