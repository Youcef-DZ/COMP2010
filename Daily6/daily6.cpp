#include <iostream>

using namespace std;

int gcd(int a, int b); // gcd prototype

class Rational {
private:
	int num;
	int den;
public:
	Rational();
	Rational(int n);
	Rational(int n, int d);
	
	friend ostream& operator<<(ostream& os, const Rational& r);
	friend Rational operator+(const Rational &r1, const Rational &r2);
	friend Rational operator-(const Rational &r1, const Rational &r2);
	friend Rational operator*(const Rational &r1, const Rational &r2);
	friend Rational operator/(const Rational &r1, const Rational &r2);

	friend bool operator== (const Rational &r1, const Rational &r2);
	friend bool operator!= (const Rational &r1, const Rational &r2);
	friend bool operator> (const Rational &r1, const Rational &r2);
	friend bool operator>= (const Rational &r1, const Rational &r2);
	friend bool operator< (const Rational &r1, const Rational &r2);
	friend bool operator<= (const Rational &r1, const Rational &r2);

	Rational& operator++();       // Prefix increment operator.
	Rational operator++(int);     // Postfix increment operator.
	Rational& operator--();       // Prefix decrement operator.
	Rational operator--(int);     // Postfix decrement operator.
	
	int getNum() { return num; }
	int getDen() { return den; }
};

int main(void) {
	cout << "daily 5: \n";
	Rational r1 = Rational();  // defualt constructure
	cout << "r1= " << r1;
	Rational r2 = Rational(5,2); 
	cout << "r2= " << r2;
	Rational r3 = Rational(7,2);
	cout << "r3= " << r3;

	/// daily 6 starts
	cout << "\nArthemtric op: \n";
	cout << "r2 + r3= " << r2 + r3;
	cout << "r2 - r3= " << r2 - r3;
	cout << "r2 * r3= " << r2 * r3;
	cout << "r2 / r3= " << r2 / r3;

	cout << "\nBooleans op: \n";
	std::cout.setf(std::ios::boolalpha);   // print true/false instead of 0/1
	std::cout << "r2 == r3 ? " << (r2 == r3) << "\n";
	std::cout << "r2 != r3 ? " << (r2 != r3) << "\n";
	std::cout << "r2 > r3 ? " << (r2 > r3) << "\n";
	std::cout << "r2 < r3 ? " << (r2 < r3) << "\n";
	std::cout << "r2 >= r3 ? " << (r2 >= r3) << "\n";
	std::cout << "r2 <= r3 ? " << (r2 <= r3) << "\n";

	cout << "\nIncr & Decr Op: \n";
	cout << "r4 = r5 = r6 = r7 = 2 \n";
	Rational r4 = Rational(2),
		r5 = Rational(2),
		r6 = Rational(2),
		r7 = Rational(2);

	cout << "r4++ is: " << r4++;
	cout << "++r5 is: " << ++r5;
	cout << "r6-- is: " << r6--;
	cout << "--r7 is: " << --r7;

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

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

ostream & operator<<(ostream & os, const Rational & r)
{
	os << r.num << " / " << r.den << endl;
	return os;
}

Rational operator+(const Rational & r1, const Rational & r2)
{
	int n = (r1.num*r2.den) + (r2.num*r1.den);
	int d = r1.den * r2.den;
	return Rational(n, d);
}

Rational operator-(const Rational & r1, const Rational & r2)
{
	int n = (r1.num*r2.den) - (r2.num*r1.den);
	int d = r1.den * r2.den;
	return Rational(n, d);
}


Rational operator*(const Rational & r1, const Rational & r2)
{
	int n = r1.num * r2.num;
	int d = r1.den * r2.den;
	return Rational(n, d);
}

Rational operator/(const Rational & r1, const Rational & r2)
{
	int n = r1.num * r2.den;
	int d = r1.den * r2.num;
	return Rational(n, d);
}

bool operator==(const Rational & r1, const Rational & r2)
{
	return (r1.num == r2.num) && (r1.den == r2.den);
}

bool operator!=(const Rational & r1, const Rational & r2)
{
	return (r1.num != r2.num) || (r1.den != r2.den);
}

bool operator>(const Rational & r1, const Rational & r2)
{
	double n1 = (double)r1.num / r1.den;
	double n2 = (double)r2.num / r2.den;
	return n1 > n2;
}

bool operator>=(const Rational & r1, const Rational & r2)
{
	double n1 = (double)r1.num / r1.den;
	double n2 = (double)r2.num / r2.den;
	return n1 >= n2;
}

bool operator<(const Rational & r1, const Rational & r2)
{
	double n1 = (double)r1.num / r1.den;
	double n2 = (double)r2.num / r2.den;
	return n1 < n2;
}

bool operator<=(const Rational & r1, const Rational & r2)
{
	double n1 = (double)r1.num / r1.den;
	double n2 = (double)r2.num / r2.den;
	return n1 <= n2;
}

// Define prefix increment operator.
Rational& Rational::operator++()
{
	this->num = num + den;
	return *this;
}

// Define postfix increment operator.
Rational Rational::operator++(int)
{
	Rational temp = *this;
	++*this;
	return temp;
}

// Define prefix decrement operator.
Rational& Rational::operator--()
{
	this->num = num - den;
	return *this;
}

// Define postfix decrement operator.
Rational Rational::operator--(int)
{
	Rational temp = *this;
	--*this;
	return temp;
}