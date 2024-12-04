#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>


/*
* This is the drill part 3. The code works per the instructions. 
*
*
*
*/

namespace X {
	int var;

	void print() {
		std::cout << "Print from X: " << var << std::endl;
	};

};

namespace Y {
	int var;
	
	void print() {
		std::cout << "Print from Y: " << var << std::endl;
	}

};


namespace Z {
	int var;
	
	void print() {
		std::cout << "Print from Z: " << var << std::endl;
	}

};

int main() {
	X::var = 7;
	X::print(); //Prints Xs var
	using namespace Y;
	var = 9;
	print(); 
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();  //Print Zs var
	};
	print();     //Print Ys var
	X::print();  //Print Xs var

};
