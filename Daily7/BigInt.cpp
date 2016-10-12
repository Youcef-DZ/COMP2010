#include"BigInt.h"
using namespace std;

int main()
{
	BigInt x;
	cout << x << endl;
	x = BigInt(42);
	cout << x << endl;
	x = BigInt(" -123456789012345678901234567890 and more stuff");
	cout << x << endl;
	x = BigInt("+-4848484848484848");
	cout << x << endl;
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
	//this->data = x;
}

void proc(BigInt) {

}

ostream & operator<<(ostream & out, const BigInt & right)
{
	// TODO: insert return statement here
}
