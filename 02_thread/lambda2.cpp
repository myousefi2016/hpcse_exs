#include <iostream>


int main()
{
	auto lam1 = [] (const int x) {return x+1;};
	std::cout << "amd1(2): " << lam1(2) << std::endl;
	
	int y = 4;
	auto lam2 = [=] (const int x) {return x+y;};
	std::cout << "lam2 " << lam2(2) <<std::endl;
	
}
