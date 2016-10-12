#include <iostream>

using namespace std;

class Rational {
private:
	int num;
	int den;
	int gcd(int a, int b);
public:
	Rational();
	Rational(int n);
	Rational(int n, int d);
	friend ostream& operator<<(ostream& os, const Rational& r);
};

int main(void) {
	Rational r1 = Rational();  // defualt constructure
	cout << r1;
	Rational r2 = Rational(5); // set numeratur = 5 and denom = 1
	cout << r2;
	Rational r3 = Rational(6, 36); // this should output 1/6
	cout << r3;

	system("pause");
	return 0;
}

Rational::Rational()
{
	this->num = 0;
	this->den = 1;
}

Rational::Rational(int n)
{
	this->num = n;
	this->den = 1;
}

Rational::Rational(int n, int d)
{
	this->num = n / gcd(n, d);
	this->den = d / gcd(n, d);
}

int Rational::gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

ostream & operator<<(ostream & os, const Rational & r)
{
	os << r.num << " / " << r.den << endl;
	return os;
}
