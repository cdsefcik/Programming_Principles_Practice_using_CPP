#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>

using namespace std;

/*
*Program is from the Drill exercise for chapter 10, input and output streams.
*Start a program to work with points, dicussed in 10.4. Begin by defining the data type Point that has two coordinate members x and y.
*Using the code and discussion in 10.4, prompt the user to input seven (x,y) pairs. As teh data is entered, store it in a vector of Points called original_points.
*Print the data in original_points to see what it looks like.
* 
* 
* Notes: The program is setup to input doubles however there is precision differences during input output and throws off the comparison. Use integers as the point of the excerise is to demonstrate file io operations.
* Also, I developed the program to do input output operations on data, like it would from a csv file, a real world application.
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
	vector<Point> return_points;

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
			original_points.push_back(Point(stod(x), stod(y)));

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
		catch (Error) {
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
	ifstream inputFile("MyData.txt");
	try {
		if (!inputFile) {
			throw ErrorOpenFile();
		}
		else {
			cout << "File was opened successfully: " << endl;
			vector<string> linestotal;
			string lines;
			while (getline(inputFile, lines)) {
				cout << lines << endl;
				linestotal.push_back(lines);
			}

			//Tokenize the lines and insert into the return vector
			for (int i = 0; i < linestotal.size(); i++) {
				if (i == 0) {
					continue;
				}
				else {
					string numbers = linestotal[i];
					stringstream ss(numbers);
					string token;
					vector<double> tokens;
					
					while (getline(ss, token, ',')) {
						//cout << token << endl;
						//number = number.substr(0, number.size() - 1);
						//Start from here, need to import into tokens vector!!
						tokens.push_back(stod(token));
					}

					//Push the tokens into the return_points vector
					for (int i = 0; i < tokens.size(); i += 2) {
						return_points.push_back(Point(tokens.at(i), tokens.at(i + 1)));
					}
					
					
				}
			}

			inputFile.close();
		}
	}
		catch (ErrorOpenFile) {
			cerr << "Can not open the input file";
		}
	
		cout << "These are the points that were read from the file: " << endl;
		for (int i = 0; i < return_points.size(); i++) {
			cout << "Point " << i + 1 << ": " << "X Value: " << return_points[i].getPointx() << "   Y Value: " << return_points[i].getPointy() << endl;
		}



		//Check all the points between the two vectors:
		for (int i = 0; i < original_points.size(); i++) {

			if ((original_points[i].getPointx() != return_points[i].getPointx()) || (original_points[i].getPointy() != return_points[i].getPointy())) {
				cout << "Point " << i + 1 << ": " << "X Value Original: " << original_points[i].getPointx() << " Y Value Original: " << original_points[i].getPointy() << endl;
				cout << "Point " << i + 1 << ": " << "X Value Return: " << return_points[i].getPointx() << "   Y Value Return: " << return_points[i].getPointy() << endl;
			}
			else {
				continue;
			}
		}


	return EXIT_SUCCESS;
};


