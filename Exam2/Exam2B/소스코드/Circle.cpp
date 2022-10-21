#include "Circle.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
Circle::Circle()
{
	setRadius(0);
}
Circle::Circle(string name)
	: Shape(name)
{
	setRadius(0);
}
Circle::Circle(string name, int r)
	: Shape(name)
{
	setRadius(r);
}
Circle::Circle(const Circle& cir)
	: Shape( cir.Name())
{
	setRadius(cir.Radius());
}

/*				destructor ( �Ҹ��� )				*/
Circle::~Circle()
{
	// cout << "Circle class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame) ( �׸� �׸��� �Լ� )
		2. fprint(ostream&) const ( ��� �Լ� )
		3. Area() const			( ���� ���ϴ� �Լ�)*/
void Circle::print(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// ���� �Ҽ��� 2�ڸ������� ���
	out.precision(2);

	// ��� ���� : ��ǥ - ������ - ���� - ����(��, �귯��)
	this->Shape::print(out);
	out << ", radius (" << setw(3) << this->Radius() << ")";
	out << ", circumference (" << setw(5) << this->Circumference() << ")";
	out << ", area (" << setw(4) << this->Area() << ")";
}
double Circle::Circumference() const
{
	return 2 * PI * Radius();
}
double Circle::Area() const
{
	return (PI * pow(double(Radius()), 2));
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Circle& Circle::operator=(const Circle& cir)
{
	this->Shape::operator=(cir);
	this->setRadius(cir.Radius());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Circle& cir)
{
	cir.print(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}