#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>

using namespace std;

/*
*Program is from the Drill exercise for chapter 10, input and output streams. 
*Start a program to work with points, dicussed in 10.4. Begin by defining the data type Point that has two coordinate members x and y.
*Using the code and discussion in 10.4, prompt the user to input seven (x,y) pairs. As teh data is entered, store it in a vector of Points called original_points.
*Print the data in original_points to see what it looks like.
*/


inline void keep_window_open() {
	char ch; cin >> ch;
}

class Point {
public:

	Point(double x, double y) :x(x), y(y) {
		count++;
	}

	~Point() {
		count--;
	}

	double getPointx() {
		return x;
	}

	double getPointy() {
		return y;
	}

	double getCount() {
		return count;
	}

private:
	double x;
	double y;
	static int count;
};

int Point::count = 0;

class Error {}; //For errors.
class ErrorOpenFile {};//Error for file open;

int main() {
	cout << "Enter the points. " << endl;
	char c = 'Y';
	vector<Point> original_points;
	
	while (c == 'Y') {

		try {

			//Take in the values from the user:
			cout << "Enter the x value: ";
			string x;
			getline(cin, x);
			cout << "" << endl;

			cout << "Enter the y value: ";
			string y;
			getline(cin, y);
			cout << "" << endl;

			//Add the point to the point vector:
			original_points.push_back(Point(stod(x),stod(y)));

			//Ask if the user would like to enter another point:
			cout << "Would you like to enter another point? " << "Enter Y for yes, N for no. ";
			cin >> c;
			if ((c != 'Y') && (c != 'N')) {
				throw Error();
			}
			//Clear the buffer
			cin.clear();
			cin.ignore();

		}
		catch(Error){
			cerr << "Incorrect input, exiting input." << endl;
		}
		
	}

	//Print out the original points to the console to the user:
	cout << "Here are the original points: " << endl;
	for (int i = 0; i < original_points.size(); i++) {
		cout << "Point " << i + 1 << ": " << "X Value: " << original_points[i].getPointx() << "   Y Value: " << original_points[i].getPointy() << endl;
	}

	//Create file and output results
	ofstream ost("MyData.txt");
	try {
		if (!ost) {
			throw ErrorOpenFile();
		}
		else {
			ost << "X Values,Y Values," << endl;
			for (int i = 0; i < original_points.size(); i++) {
				ost << original_points[i].getPointx() << "," << original_points[i].getPointy() << "," << endl;
			}
			ost.close();
		}
	}
	catch (ErrorOpenFile) {
		cerr << "Can not open the file";
	}

	//Input the results from the file.

	return EXIT_SUCCESS;
};
