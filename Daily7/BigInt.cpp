#include"BigInt.h"

int main()
{
	BigInt x;
	cout << x << endl;
	x = BigInt(42);
	cout << x << endl;
	x = BigInt(" -123456789012345678901234567890 and more stuff");
	cout << x << endl;
	x = BigInt("+-4848484848484848");
	cout << x << endl;

	cout << "Exiting.." << endl;

	system("pause");
	return 0;
}

BigInt::BigInt()
{
	data = "0";
}

BigInt::BigInt(int x)
{
	this->data = to_string(x);
}

BigInt::BigInt(string x)
{
	while (x[0] == ' ' || x[0] == 't') {
		x.erase(x.begin()); // erase beggining whitespaces
	}

	unsigned first = x.find(" ");
	x = x.substr(0, first);  // erase everything after first whitespace

	if (!is_digits(x.substr(1, x.size()))) { // check if the string is not all digits
		cout << "Tried to construct an invalid BigInt from string: " << endl;
	}
	else if (isdigit(x[0]) || x[0] == '+'){ // set the sign
		this->isNegative = true;
	}
	else if (x[0] == '-') {
		this->isNegative = false;
	}
	else{
		cout << "Tried to construct an invalid BigInt from string: " << endl;
	}
	
	this->data = x;
}

ostream& operator<<(ostream& out, const BigInt& right)
{
	out << right.data;
	return out;
}

bool BigInt::is_digits(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}
