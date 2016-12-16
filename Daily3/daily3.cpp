#include <iostream>

using namespace std;

class Temperature {
private:
	double degK;
public:
	void set_temp_kelvin(double degK);
	void set_temp_fahrenheit(double degF);
	void set_temp_celsius(double degC);

	double get_temp_kelvin() const;
	double get_temp_fahrenheit() const;
	double get_temp_celsius() const;

	void output() const;
};

int main() {
	Temperature t;

	t.set_temp_celsius(0);							// set the Temperature to 0°C then print the conversions
	t.output();
	t.set_temp_fahrenheit(32);						// set the Temperature to 32°F then print the conversions
	t.output();
	t.set_temp_kelvin(273.15);						// set the Temperature to 273.15°K then print the conversions
	t.output();

	system("pause");
	return 0;
}

void Temperature::output() const {
	cout << get_temp_celsius() << "C " << "is equal to: "
		<< get_temp_fahrenheit() << "F and: "
		<< get_temp_kelvin() << "K." << endl;
}

void Temperature::set_temp_kelvin(double degK) {
	this->degK = degK;
}

void Temperature::set_temp_celsius(double degC) {
	this->degK = degC + 273.15;
}

void Temperature::set_temp_fahrenheit(double degF) {
	this->degK = (5.0 / 9)*(degF - 32) + 273.15;
}

double Temperature::get_temp_kelvin() const {
	return degK;
}

double Temperature::get_temp_fahrenheit() const {
	return (9.0 / 5)*(degK - 273.15) + 32;
}

double Temperature::get_temp_celsius() const {
	return degK - 273.15;
}