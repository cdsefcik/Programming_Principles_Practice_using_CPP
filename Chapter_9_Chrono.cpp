#include "Chrono.h"


/*
*This is the date class provided in chapter 9. This has errors in it due to not being defined.
*The Chrono.h files contains the headers.
*/


namespace Chrono {
	//Member function definitions.
	Date::Date(int yy, Month mm, int dd) :y(yy), m(mm), d(dd) {
		if (!is_date(yy, mm, dd))throw invalid();
	}

	const Date& default_date() {
		static Date dd(2001, Date::jan, 1); //Start of 21st century.
		return dd;
	}

	Date::Date() :y(default_date().year()),m(default_date().month()) ,d(default_date().day()) {

	}

	void Date::add_day(int n) {
		//........
	}

	void Date::add_month(int n) {
		//....
	}

	void Date::add_year(int n) {
		if (m == feb && d == 29 && !leapyear(y + n)) { //Beware of leap years!
			m = mar;
			d = 1;
		}
		y += n;
	} //helper functions:

	bool is_date(int y, Date::Month m, int d) {
		//assume that y is valid

		if (d <= 0) return false;
		if (m < Date::jan || Date::dec < m) return false;

		int days_in_month = 31; //most months have 31 days.

		switch (m) {
		case Date::feb:  //The length of February varies.
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Date::apr: 
		case Date::jun: 
		case Date::sep:
		case Date::nov:
			days_in_month = 30; //The rest have 30 days.
			break;
		}
		if (days_in_month < d)return false;
		return true;
	}

	bool leapyear(int y) {
		//see exercise 10
	}

	bool operator==(const Date& a, const Date& b) {
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b) {
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d) {
		return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd) {
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { //Oops: format error.
			is.clear(ios_base::failbit); //Set the fail bit.
			return is;
		}

		dd = Date(y, Date::Month(m), d);
		return is;
	}

	enum Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	Day day_of_week(const Date& d) {
		//...
	}

	Date next_Sunday(const Date& d) {
		//......
	}

	Date next_weekday(const Date& d) {
		//....
	}
}//Chrono
