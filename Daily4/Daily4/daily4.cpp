#include <iostream>
#include <string>

using namespace std;

enum Months {
	UKN, JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

string FullMonths[12] = { "January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

class Month {
public:
	Month(); // Default constructor
	Month(Months m);
	Month(int n);
	void setMonth(int n);
	void outputInt();
	void output3Char();
	void outputFull();
	void nextMonth();
	inline const char* toString(int m);
private:
	int month;
};

int main() {
	Month m = Month(); // set month to January using default constructor
	m.outputInt(); // output month in diffrent formats
	m.output3Char();
	m.outputFull();
	m.nextMonth();

	cout << "--------------------------------------------------------------------" << endl;
	m = Month(FEB); // set month to February using Months type variable as argument
	m.outputInt();
	m.output3Char();
	m.outputFull();
	m.nextMonth();

	cout << "--------------------------------------------------------------------" << endl;
	m = Month(3); // set month to March using int type variable as argument
	m.outputInt();
	m.output3Char();
	m.outputFull();
	m.nextMonth();

	cout << "--------------------------------------------------------------------" << endl;
	m.setMonth(4); // set month to April using SetMonth function
	m.outputInt();
	m.output3Char();
	m.outputFull();
	m.nextMonth();

	cout << "--------------------------------------------------------------------" << endl;
	m.setMonth(12); // show that if current month is December next month would be January
	m.outputInt();
	m.output3Char();
	m.outputFull();
	m.nextMonth();

	system("pause");
	return 0;
}

Month::Month(Months m) {
	month = m;
}

Month::Month(int n) {
	month = n;
}

Month::Month() {
	month = 1;
}

void Month::setMonth(int n) {
	month = n;
}

void Month::outputInt() {
	cout << "Int= " << month << endl;
}

void Month::output3Char() {
	cout << "3 Char= " << toString(month) << endl;
}

void Month::outputFull() {
	cout << "Full= " << FullMonths[month - 1] << endl;
}

void Month::nextMonth() {
	if (month > 0 && month < 12) {
		cout << "Next Month= " << FullMonths[month] << endl;
	}
	else if (month == 12) {
		cout << "Next Month= " << FullMonths[0] << endl;
	}
}

inline const char* Month::toString(int m) {
	switch (m) {
	case JAN: return "JAN";
	case FEB: return "FEB";
	case MAR: return "MAR";
	case APR: return "APR";
	case MAY: return "MAY";
	case JUN: return "JUN";
	case JUL: return "JUL";
	case AUG: return "AUG";
	case SEP: return "SEP";
	case OCT: return "OCT";
	case NOV: return "NOV";
	case DEC: return "DEC";
	default: return "[Unknown Month]";
	}
}


