#include "Cylinder.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor ( ����� ���� )
		3. ��� ���ڸ� �޴� constructor
		4. Copy Constructor		( ���� ������ )			*/
Cylinder::Cylinder()
{
	this->Set_Height(0);
}
Cylinder::Cylinder(string n,int r, int h)
	: Circle( n, r)				// Funtion initialize�� �̸��� �������
{
	this->Set_Height(h);					// ���� ����
}
Cylinder::Cylinder(const Cylinder& cyl)
	: Circle( cyl.Name(), cyl.Radius())
	// Funtion initialize�� �������, ������ ȣ��
{
	this->Set_Height(cyl.Height());			// ����
}

/*				destructor ( �Ҹ��� )				*/
Cylinder::~Cylinder()
{
	// destruct Shape object
}

/*				member functions ( ��� �Լ��� )
		1. draw(ostream& ostr)	(virtual�� �����Ͽ���, sub-class���� �����ǿ뵵�� ����)
		2. Sur_Area() ( ������� �ѳ���  )
		3. Volume() ( ������� ���� )					*/
void Cylinder::print(ostream& ostr) const
{
	ostr.setf(ios::fixed);  ostr.setf(ios::showpoint);
	ostr.precision(2);
	//print form : Name : radius, circumference, x_area, height, surface area, volume
	Shape::print(ostr);
	ostr << "radius (" << this->Radius() << ", "
		<< "circumference (" << setw(5) << this->Circumference() << "), "
		<< "x_area (" << setw(5) << Circle::Area() << "), "
		<< "surface area (" << setw(10) << Sur_Area() << "), "
		<< "volume (" << setw(10) << Volume() << ")]";
}
double Cylinder::Sur_Area() const
{
	// ����� �ѳ��� = 2 * �ظ� ���� + ���� ����
	return ((2.0 * Area()) + (2.0 * PI * (double)Radius() * (double)Height()));
}
double Cylinder::Volume() const
{
	// ����� ���� = �ظ� ���� * ����
	return Area() * (double)Height();
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
Cylinder& Cylinder::operator=(const Cylinder& cyl)
{
	this->Circle::operator=(cyl);				// ���Կ����� ȣ��
	this->Set_Height(cyl.Height());				// ���� ����

	return *this;								// �ڱ��ڽ� ��ȯ
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& ostr, const Cylinder& cyl)
{
	// ��� 
	cyl.print(ostr);

	return ostr;
}