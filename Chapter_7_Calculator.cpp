#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

/*
* This program is buggy. Will need to make updates. 
*
*/

const char number = '8';  //t.kind==number means that t is a number Token.
const char quit = 'q';    //t.kind==quit means that t is a quit Token.
const char print = ';';    //t.kind==print means that t is a print Token.
const string prompt = "> ";
const string result = "= "; //used to indicate that what follows is a result.

inline void keep_window_open() {
	char ch; cin >> ch;
}

inline void error(string s) {
	throw runtime_error(s);
}






class Token{
public:
	char kind;        //What kind of token.
	double value;     //For numbers: a value.
	
	Token(char ch):kind(ch),value(0){} //Make a token from a char, constructor.
	Token(char ch, double val):kind(ch),value(val){} //Make a token from a char and a double constructor.

};

Token get_token()    // read a token from cin
{
	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
		//not yet   case ';':    // for "print"
		//not yet   case 'q':    // for "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
	}
};



class Token_stream{
public:
	Token_stream();    //Make a token stream that reads cin
	Token get();       //get a token (get() is defined in 6.8.2)
	void putback(Token t); //put a token back
	void ignore(char c);
private:
	bool full;             //Is there a Token in the buffer?
	Token buffer;          //Here is wher we keep a Token put back using putback()
};
Token_stream::Token_stream() :full(false), buffer(0) {};



void Token_stream::putback(Token t) {
	if(full)error("putback() into a full buffer");
	buffer = t;  //copy t to buffer
	full = true; //buffer is now full
};

void Token_stream::ignore(char c) {
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c)return;
};


Token Token_stream::get() {
	//Read characters from cin and compose a Token.
	if (full) { //Do we already have a token ready?
		//Remove token from buffer.
		full = false;
		return buffer;
}
	char ch;
	cin >> ch; //Note that >> skips whitespace (space, newline, tab, etc)

	switch (ch) {
	case quit:  //For "print"
	case print:  //For "quit"
	case '(': 
	case ')': 
	case '+': 
	case '-': 
	case '*': 
	case '/':
	case '%':
		return Token(ch);  //Let each character represent itself.
	case '.':
	case '0': 
	case '1': 
	case '2': 
	case '3': 
	case '4': 
	case '5': 
	case '6': 
	case '7': 
	case '8': 
	case '9':
	{
		cin.putback(ch);   //Put digit back into the input stream
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		error("Bad token");
	}


};

Token_stream ts;          //Provides get() and putback()
double expression();     //declaration so that primary() can call expression()

void clean_up_mess() {
	ts.ignore(print);
}

double primary(){
	
	Token t = get_token();
	switch (t.kind) {
	case '(':   //handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')error("')'expected");
		return d;
	}
	case number:              //We use 8 to represent a number.
		return t.value;    //Return the numbers value.
	case '-':
		return -primary();
	case '+':
		return primary();
	default:
		error("primary expected");
	}
}       //deal with numbers and parentheses


double term() {
	double left = primary();
	Token t = ts.get();   //get the Token from teh Token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/': {
			double d = primary();
			if (d == 0)error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			int i1 = int(left);
			if (i1 != left)error("left-hand operand of % not int");
			int i2 = int(d);
			if (i2 != d)error("right-hand operand of % not int");
			if (i2 == 0)error("%: divide by zero");
			left = i1 % i2;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);   //put t back into the Token stream
			return left;
		}

	}

};//deal with * and /




double expression() {
	double left = term();   //Read and evaluate a Term
	Token t = ts.get();     //Get the next Token from the Token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();   //Evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);  //put t back into the token stream
			return left;
		}
	}

};  //deal with + and -

void calculate() {
	while(cin)
	try {
	cout << prompt;
	Token t = ts.get();
	while (t.kind == print)t = ts.get();
	if (t.kind == quit)return;
	ts.putback(t);
	cout << result << expression() << '\n';
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		clean_up_mess();

	}
}

int main() {             //main loop and deal with errors

	try {
		calculate();
		keep_window_open();
		return 0;
		}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		keep_window_open(); //Keep the window open.
		cout << "Please enter the character~to close the window\n";
		char ch;
		while (cin >> ch) //Keep reading until we find a ~
			if (ch == '~')return 1;
		return 1;
	}
	catch (...) {
		cerr << "exception \n";
		keep_window_open();
		return 2;
	}

	return EXIT_SUCCESS;
}


