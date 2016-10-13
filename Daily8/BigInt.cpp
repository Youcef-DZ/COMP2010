#include"BigInt.h"

int main()
{
	BigInt a("-1000");
	BigInt b("+999");
	cout << b << "+" << a << endl << "= " << b + a << endl;
	a = BigInt("1000");
	b = BigInt("999");
	cout << a << "-" << b << endl << "= " << a - b << endl;
	a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
	b = BigInt("1");
	cout << " " << a << "+" << b << endl << "= " << a + b << endl;
	cout << "Expecting 1, got: " << (BigInt("-30") < BigInt("-1")) << endl;
	cout << "Expecting 0, got: " << (BigInt("30") < BigInt("-1")) << endl;
	cout << "Expecting 1, got: " << (BigInt("30") < BigInt("300")) << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") < BigInt("-300")) << endl;

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

	size_t s = (x[0] == '-' || x[0] == '+') ? x.size() - 1 : x.size();

	if (!is_digits(x.substr(x.size()-s, s))) { // check if the string is not all digits
			cout << "Tried to construct an invalid BigInt from string: " << endl;
	}
	
	setDigits(x.substr(x.size()-s, s));
}

BigInt operator+(const BigInt & a, const BigInt & b)
{
	int result =0;
	return BigInt(result);
}

BigInt operator-(const BigInt & a, const BigInt & b)
{
	return BigInt();
}

bool operator<(const BigInt & a, const BigInt & b)
{
	return false;
}

ostream& operator<<(ostream& out, const BigInt& right)
{
	out << right.data;
	return out;
}

void BigInt::setDigits(string x)
{
	numDigits = x.size();
	isNegative = x[0] == '-';
	data = x;

	for (int i = 0; i < numDigits; i++) {
		allDigits.push_back(x[i]);
	}
}

bool BigInt::is_digits(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}
