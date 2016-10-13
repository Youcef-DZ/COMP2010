#include<iostream>
#include<string>

#ifndef BIGINT_H
#define BIGINT_H

using namespace std;

class BigInt
{
public:
	BigInt(); // Initializes the BigInt to zero.
	BigInt(int x); //Initializes the BigInt to have the same value as x
	explicit BigInt(string x); //Initalizes the BigInt to have the value of the given string BUT
	friend ostream& operator<<(ostream& out, const BigInt& right);
	bool is_digits(const string &str);
private:
	string data;
	bool isNegative;
};
#endif
