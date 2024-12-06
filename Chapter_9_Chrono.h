#pragma once
/*
*This is the date class provided in chapter 9. This has errors in it due to not being defined.
*The Chrono.cpp file contains the implementation.
*/

namespace Chrono {

	class Date {
	public:
		enum Month {
			jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
		};

		class Invalid{}; //to throw as exception.

		Date(int y, Month m, int d); //Check for valid date and initialize.
		Date(); //default constructor.
		//The default copy operations are fine.

		//Nonmodifying operations:
		int day() const { return d;}
		Month month() const { return m; }
		int year() const { return y; }

		//Modifying operations:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int y;
		Month m;
		int d;
	};

	bool is_date(int y, Date::Month m, int d);  //true for valid date.

	bool leapyear(int y); //True is y is a leap year.

	bool operator==(const Date& a, const Date& b);

	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& dd);

	istream& operator>>(istream& is, Date& dd);
}//Chrono
