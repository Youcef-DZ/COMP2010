/*
* File:   main.c
* Author: Youcef Laidi
* COMP2010 - Computing 3
* Day 1 Assignment
*
* This C++ program  asks the user to input two integer values, a starting point and an ending point.
* The program will print out, one per line, all of the prime numbers between start and end including
* the end points (if they are prime). At the end of the list the program output the sum of all the
* printed numbers
*
* Created on September 9, 2016, 8:35 AM
* Modified on September 22, 2016, 3:45 PM - Added a prototype to isPrime function
*/

#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int number); // prototype 

int main(void) {

	bool isPrime(int number);
	int first;
	int last;
	int sum = 0;
	vector<int> v;    // declares a vector of integers

	cout << "Enter starting value:";
	cin >> first;
	cout << "Enter ending value:";
	cin >> last;

	for (int i = first; i < last; i++) {
		if (isPrime(i))
			v.push_back(i);
	}

	for (auto i = v.begin(); i != v.end(); ++i) {
		cout << *i << endl;
		sum += *i;
	}

	cout << "The sum of all the numbers is: ";
	cout << sum << endl;

	system("pause");
	return 0;
}

bool isPrime(int number) {
	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; i * i <= number; i += 2)
		if (number % i == 0) return false;
	return true;
}