#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

/*
*
*
*/

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


Token Token_stream::get() {
	if (full) { //Do we already have a token ready?
		//Remove token from buffer.
		full = false;
		return buffer;
}
	char ch;
	cin >> ch; //Note that >> skips whitespace (space, newline, tab, etc)

	switch (ch) {
	case ';':  //For "print"
	case 'q':  //For "quit"
	case '(': case ')': case '+': case '-': case '*': case '/':
		return Token(ch);  //Let each character represent itself.
	case '.':
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);   //Put digit back into the input stream
		double val;
		cin >> val;
		return Token('8', val);
	}
	default:
		error("Bad token");
	}


};

Token_stream ts;          //Provides get() and putback()
double expression();     //declaration so that primary() can call expression()

double primary(){
	Token t = get_token();
	switch (t.kind) {
	case '(':   //handle '(' expression ')'
	{
		double d = expression();
		t = get_token();
		if (t.kind != ')')error("')'expected");
		return d;
	}
	case '8':
		return t.value;
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

int main() {             //main loop and deal with errors

	try {
		while (cin) {
			cout << expression() << '\n';
			keep_window_open();
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "exception \n";
		keep_window_open();
		return 2;
	}

	return EXIT_SUCCESS;
}


