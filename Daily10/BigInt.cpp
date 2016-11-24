#include"BigInt.h"

/*
int main()
{
	BigInt a("2205");
	BigInt b("0");
	cout << a << " / " << b << endl <<
		"Expecting 10\n      got " << a / b << endl;

	system("pause");
	return 0;
}
*/
BigInt::BigInt()
{
	data = "0";
}

BigInt::BigInt(int x)
{
	BigInt(to_string(x));
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
		unsigned int i, it, j, k;
		int n, carry = 0;
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
		unsigned int i, it, j, k;
		int n = 0, carry = 0;
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

	for (unsigned int x = 1; x <= a.numDigits; ++x) {
		for (unsigned int y = 1; y <= b.numDigits; ++y) {
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

BigInt operator/(const BigInt & a, const BigInt & b)
{
	BigInt temp1 = a; temp1.isNegative = false;
	BigInt temp2 = b; temp2.isNegative = false;

	if (b == BigInt("0")) {
		int intMax = numeric_limits<int>::max(); // dividing by zero will return the max value of int
		if (a < BigInt("0")) { intMax = numeric_limits<int>::min(); }
		return BigInt(to_string(intMax));
	}
	else if (a.numDigits < b.numDigits) { return BigInt("0"); }
	else if (a == b) { return BigInt("1"); }
	else if (temp1 == temp2) { return BigInt("-1"); }
	else {

		BigInt result = BigInt("1");
		do {
			temp1 = temp1 - temp2;
			if (temp1 > BigInt("0") || temp1 == BigInt("0")) {
				result = result + BigInt("1");
			}
		} while (temp1 > temp2 || temp1 == BigInt("0"));

		result.isNegative = (a.isNegative && !b.isNegative) || (!a.isNegative && b.isNegative);
		return result;
	}
}

bool operator<(const BigInt & a, const BigInt & b)
{
	string str1 = a.data, str2 = b.data;

	if (a.isNegative && !b.isNegative) { return true; }  // a<b
	else if (!a.isNegative && b.isNegative) { return false; } // a>b
	else if (a.isNegative && b.isNegative) { 	// both negative
		if (str1.size() < str2.size()) { return false; }
		else if (str2.size() < str1.size()) { return true; }
		else {
			if (str1 == str2) { return true; } // strings are equal
			else {
				for (unsigned int i = 0; i < str1.size(); ++i) {
					return str2[i] < str1[i];
				}
			}
		}
	}

	// both positive
	else if (str1.size() < str2.size()) { return true; }
	else if (str2.size() < str1.size()) { return false; }
	else { // same size 
		if (str1 == str2) { return false; } // strings are equal
		else {
			for (unsigned int i = 0; i < str1.size(); ++i) {
				return str1[i] < str2[i];
			}
		}
	}
}

bool operator>(const BigInt & a, const BigInt & b)
{
	return b < a; // using previous operator '<'
}

bool operator==(const BigInt & a, const BigInt & b)
{
	return (a.data == b.data) && (a.isNegative == b.isNegative);
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
	numDigits = x.size();			// set number of digits
	data = x;				// set string

<<<<<<< HEAD
	for (unsigned int i = 0; i < numDigits; i++) {
		allDigits.push_back(x[i]);		// push each digit to vector
=======
	for (int i = 0; i < numDigits; i++) {
		allDigits.push_back(x[i]);	// push each digit to vector
>>>>>>> origin/master
	}
}

bool BigInt::is_digits(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}
