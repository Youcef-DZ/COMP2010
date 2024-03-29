#include"BigInt.h"

int main()
{
	BigInt a("100");
	BigInt b("100");
	cout << a << " * " << b << endl <<
		"Expecting 10000\n      got " << a*b << endl;

	cout << endl;
	a = BigInt("1234");
	b = BigInt("-678");
	cout << a << " * " << b << endl <<
		"Expecting -836652\n      got "; cout << a*b << endl;

	cout << endl;
	a = BigInt("-123456789012345678901234567890");
	b = BigInt("-987654321");
	cout << a << " * " << b << endl
		<< "Expecting 121932631124828532112482853211126352690\n      got "
		<< a*b << endl;

	cout << endl << "Testing > operator" << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") > BigInt("-1")) << endl;
	cout << "Expecting 1, got: " << (BigInt("30") > BigInt("-1")) << endl;
	cout << "Expecting 0, got: " << (BigInt("30") > BigInt("300")) << endl;
	cout << "Expecting 1, got: " << (BigInt("-30") > BigInt("-300")) << endl;

	cout << endl << "Testing == operator" << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") == BigInt("-1")) << endl;
	cout << "Expecting 1, got: " << (BigInt("30") == BigInt("30")) << endl;
	cout << "Expecting 0, got: " << (BigInt("-30") == BigInt("30")) << endl;
	cout << "Expecting 0, got: " << (BigInt("-300") == BigInt("300")) << endl;

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
	while (x[0] == ' ' || x[0] == 't' || x[0] == '0') {
		x.erase(x.begin()); // erase beggining whitespaces and zeros
	}

	unsigned first = x.find(" ");
	x = x.substr(0, first);  // erase everything after first whitespace

	size_t s = (x[0] == '-' || x[0] == '+') ? x.size() - 1 : x.size(); // number of chars without the sing

	if (!is_digits(x.substr(x.size() - s, s))) { // check if the string is not all digits
		cout << "Tried to construct an invalid BigInt from string: " << endl;
	}

	setDigits(x, s);
}

BigInt operator+(BigInt const & a, BigInt const & b)
{
	BigInt result;
	string resultStr = "";
	if ((!a.isNegative) && (!b.isNegative)) { // if both BigInts are positive
		vector<string> newData;
		int i, it, j, k, n, carry = 0;
		string str1, str2;
		it = (a.numDigits >= b.numDigits) ? a.numDigits : b.numDigits;

		for (i = 1; i <= it; i++) {
			str1 = (a.numDigits < i) ? '0' : a.allDigits.at(a.numDigits - i);
			str2 = (b.numDigits < i) ? '0' : b.allDigits.at(b.numDigits - i);

			j = stoi(str1);
			k = stoi(str2);

			n = j + k + carry;
			if (n >= 10) {
				carry = n / 10;
				n = n - 10;
			}
			else { carry = 0; }
			newData.push_back(to_string(n));
		}
		if (carry >= 1) {
			newData.push_back(to_string(carry));
		}
		reverse(newData.begin(), newData.end());
		for (const auto &piece : newData) resultStr += piece; // array to string
		result = BigInt(resultStr);
	}
	else if ((a.isNegative) && (!b.isNegative)) { // (-a) + (+b) = b-a
		BigInt temp1 = a;
		temp1.isNegative = false;
		result = b - temp1;
	}
	else if ((!a.isNegative) && (b.isNegative)) { // (+a) + (-b) = a-b
		BigInt temp1 = b;
		temp1.isNegative = false;
		result = a - temp1;
		result.isNegative = b < a;
	}
	else if ((a.isNegative) && (b.isNegative)) { // (-a) + (-b) = -(a+b)
		BigInt temp1 = a;
		BigInt temp2 = b;
		temp1.isNegative = false;
		temp2.isNegative = false;
		result = temp1 + temp2;
		result.isNegative = true;
	}

	return result;
}

BigInt operator-(BigInt const & a, BigInt const & b)
{
	BigInt result, left, right;
	string resultStr = "";

	left = a < b ? b : a;
	right = a < b ? a : b;

	if ((!left.isNegative) && (!right.isNegative)) { // if both BigInts are positive
		vector<string> newData;
		int i, it, j, k, n, carry = 0;
		string str1, str2;
		it = (left.numDigits >= right.numDigits) ? left.numDigits : right.numDigits;

		for (i = 1; i <= it; i++) {
			str1 = (left.numDigits < i) ? '0' : left.allDigits.at(left.numDigits - i);
			str2 = (right.numDigits < i) ? '0' : right.allDigits.at(right.numDigits - i);

			j = stoi(str1) - carry;
			k = stoi(str2);
			n = j - k;

			if (n < 0) {
				carry = 1;
				n = n + 10;
			}
			else { carry = 0; }
			newData.push_back(to_string(n));
		}

		if (n < 0) { result.isNegative = true; }
		reverse(newData.begin(), newData.end());
		for (const auto &piece : newData) resultStr += piece; // array to string
		result = BigInt(resultStr);
	}
	else if ((left.isNegative) && (!right.isNegative)) { // (-a)-(+b) = -(a+b)
		BigInt temp1 = left;
		temp1.isNegative = false;
		result = temp1 + right;
		result.isNegative = true;
	}
	else if ((!left.isNegative) && (right.isNegative)) { // (+a)-(-b) = a+b
		BigInt temp1 = right;
		temp1.isNegative = false;
		result = left + temp1;
	}
	else if ((left.isNegative) && (right.isNegative)) { // (-a)-(-b) = b-a
		BigInt temp2 = right;
		temp2.isNegative = false;
		result = temp2 - left;
	}

	return result;
}

BigInt operator*(const BigInt & a, const BigInt & b)
{
	BigInt result(0);

	for (long long int x = 1; x <= a.numDigits; ++x) {
		for (long long int y = 1; y <= b.numDigits; ++y) {
			int digit1 = a.allDigits[a.numDigits - x] - '0';
			int digit2 = b.allDigits[b.numDigits - y] - '0';
			int mul = digit1*digit2;

			string digitResult = to_string(mul);

			for (long long int n = 2; n < y + x; ++n) {
				digitResult = digitResult + "0";
			}

			BigInt singleResult(digitResult);
			result = result + singleResult;
		}
	}

	result.isNegative = (a.isNegative && !b.isNegative) || (!a.isNegative && b.isNegative);
	return result;
}

bool operator<(const BigInt & a, const BigInt & b)
{
	string str1 = a.data, str2 = b.data;

	if (a.isNegative && !b.isNegative) return true;  // a<b
	else if (!a.isNegative && b.isNegative) return false; // a>b
	else if (a.isNegative && b.isNegative) { 	// both negative
		if (str1.size() < str2.size()) { return false; }
		else if (str2.size() < str1.size()) { return true; }
		else {
			if (str1 == str2) return true; // strings are equal
			for (int i = 0; i < str1.size(); ++i) {
				return str2[i] < str1[i];
			}
		}
	}

	// both positive
	else if (str1.size() < str2.size()) { return true; }
	else if (str2.size() < str1.size()) { return false; }
	else { // same size 
		if (str1 == str2) return false; // strings are equal
		for (int i = 0; i < str1.size(); ++i) {
			return str1[i] < str2[i];
		}
	}
}

bool operator>(const BigInt & a, const BigInt & b)
{
	return b < a; // using previous operator '<'
}

bool operator==(const BigInt & a, const BigInt & b)
{
	if ((a.isNegative && !b.isNegative) || (!a.isNegative && b.isNegative)) return false; // diffrent sign
	if (a.numDigits != b.numDigits) return false; // diffrent size

	if (a.data == b.data) return true;
}

ostream& operator<<(ostream& out, const BigInt& right)
{
	if (right.isNegative) {
		out << "-" << right.data;
	}
	else {
		out << right.data;
	}
	return out;
}

void BigInt::setDigits(string x, size_t s)
{
	isNegative = (x.find("-") == 0);	// set sign boolean
	x = x.substr(x.size() - s, s);		// remove sign from string
	numDigits = x.size();				// set number of digits
	data = x;							// set string

	for (int i = 0; i < numDigits; i++) {
		allDigits.push_back(x[i]);		// push each digit to vector
	}
}

bool BigInt::is_digits(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}
