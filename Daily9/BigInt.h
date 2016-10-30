#include<iostream>
#include<string>
#include<vector>

#ifndef BIGINT_H
#define BIGINT_H

using namespace std;

class BigInt
{
public:
	BigInt(); // Initializes the BigInt to zero.
	BigInt(int x); //Initializes the BigInt to have the same value as x
	explicit BigInt(string x); //Initalizes the BigInt to have the value of the given string BUT
	friend BigInt operator+(const BigInt &a, const BigInt &b);
	friend BigInt operator-(const BigInt &a, const BigInt &b);
	friend BigInt operator*(const BigInt &a, const BigInt &b);
	friend bool operator<(const BigInt &a, const BigInt &b);
	friend bool operator>(const BigInt &a, const BigInt &b);
	friend bool operator==(const BigInt &a, const BigInt &b);

	friend ostream& operator<<(ostream& out, const BigInt& right);
	void setDigits(string x, size_t s);
	bool is_digits(const string &str);
private:
	string data;
	bool isNegative;
	vector<int> allDigits; // vector of all digits
	int numDigits; // number of digits in data string
};
#endif
