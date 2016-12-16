/*
* File:   daily2.cpp
* Author: Youcef Laidi
* COMP2010 - Computing 3
* Day 2 Assignment
*
* This program asks the user to enter a length given in feet and inches and Convert it to meters and
* centimeters. The program uses three functions; getInput, conversion and output.
*
* Created on September 11, 2016, 8:35 AM
* Modified on September 22, 2016, 3:56 PM
*			* Reduced obvious comments
*			* Progrem will end after conversion
*			* Only variables that need to be changed will be passed by refrence
*			* constant numbers have been set to const
*/

#include <iostream>
#include <cmath>
using namespace std;

void getInput(int &feet, double &inches);										//prototype
void conversion(int feet, double inches, int &meters, double &centimeters);     //prototype
void output(int feet, double inches, int meters, double centimeters);		//prototype

int main(void) {

	int feet, meters;									// declare variables name
	double inches, centimeters;

	getInput(feet, inches);
	conversion(feet, inches, meters, centimeters);
	output(feet, inches, meters, centimeters);

	system("pause");
	return 0;
} // end main

void getInput(int &feet, double &inches) {
	cout << "Please enter the number of feet: ";
	cin >> feet;
	cout << "Please enter the number of inches: ";
	cin >> inches;
} // end getInput

void conversion(int feet, double inches, int &meters, double &centimeters)
{
	const double feet_to_inch = 12;
	const double inch_to_centi = 2.54;

	double total_inches = feet * feet_to_inch + inches;
	double total_centi = total_inches * inch_to_centi;

	if (total_centi >= 100) {
		meters = (int)total_centi / 100;
	}
	centimeters = total_centi - (meters * 100);
} // end conversion

void output(int feet, double inches, int meters, double centimeters)
{
	cout.setf(ios::fixed);						 // Fixed number, normal notation
	cout.setf(ios::showpoint);					 // Dsiplay a decimal and extra zeros
	cout.precision(8);							 // Set precision to be 8 numebrs after decimal point

	cout << feet << " feet and " << inches << " inches converts to" << endl;
	cout << meters << " meters and " << centimeters << " centimeters." << endl;
} // end output