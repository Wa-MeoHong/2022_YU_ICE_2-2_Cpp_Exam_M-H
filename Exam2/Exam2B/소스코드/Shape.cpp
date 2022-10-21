#include "Shape.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor			*/

Shape::Shape()
{

	name = "no_name";							// �̸��� ����
}
Shape::Shape(string name)
{
	NameSet(name);								// �̸� ����
}

/*				destructor ( �Ҹ��� )				*/
Shape::~Shape()
{
	// cout << "Shape class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. draw(ConsolePixelFrame cp_frame)
		  (virtual�� �����Ͽ���, sub-class���� �����ǿ뵵�� ����)
		2. fprint(ostream&) const ( ��� �Լ� )				*/
//void Shape::draw()
//{
//	//draw
//}
//void Shape::draw(ConsolePixelFrame cp_frame)
//{
//	/* virtual function that will be late-binded to sub-class's draw() */
//}
void Shape::print(ostream& out) const
{
	// ��� ���� : ��ǥ - ���� - ����(��, �귯��)
	out << right <<setw(15) << this->Name() << ": ";
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Shape& Shape::operator=(const Shape& s)
{
	this->NameSet(s.Name());

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const Shape s)
{
	s.print(out);

	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}