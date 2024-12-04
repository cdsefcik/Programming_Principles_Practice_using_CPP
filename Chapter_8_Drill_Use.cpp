#include "my.h"
#include <iostream>

/*
*The drill from chapter 8 for part 1 and 2. The swap_cr did not compile.
*
*/

int foo = 7;

int main() {

	print_foo();
	print(99);

	int x = 7;
	int y = 9;

	double dx = 7.7;
	double dy = 9.9;

	//swap_r(dx, dy);
	swap_v(dx, dy);

	swap_r(x, y);
	swap_v(7, 9);

	std::cout << x << "\n";
	std::cout << y << "\n";
	std::cout << dx << "\n";
	std::cout << dy << "\n";


	//const int cx = 7;
	//const int cy = 9;

	//swap_cr(cx, cy);
	//swap_cr(7.7, 9.9);

	return 0;
}
