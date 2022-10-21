#include "PolygonPiller.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor ( ����� ���� )
		3. ��� ���ڸ� �޴� constructor
		4. Copy Constructor		( ���� ������ )			*/
PolygonPiller::PolygonPiller()
{
	this->Set_Height(0);
}
PolygonPiller::PolygonPiller(string n, int r, int num_poly, int h)
	: PolyGon(n, r, num_poly)				// Funtion initialize�� �̸��� �������
{
	this->Set_Height(h);					// ���� ����
}
PolygonPiller::PolygonPiller(const PolygonPiller& cyl)
	: PolyGon(cyl.Name(), cyl.Radius() , cyl.NumPoly())
	// Funtion initialize�� �������, ������ ȣ��
{
	this->Set_Height(cyl.Height());			// ����
}

/*				destructor ( �Ҹ��� )				*/
PolygonPiller::~PolygonPiller()
{
	// destruct Shape object
}

/*				member functions ( ��� �Լ��� )
		1. draw(ostream& ostr)	(virtual�� �����Ͽ���, sub-class���� �����ǿ뵵�� ����)
		2. Sur_Area() ( ������� �ѳ���  )
		3. Volume() ( ������� ���� )					*/
void PolygonPiller::print(ostream& ostr) const
{
	ostr.setf(ios::fixed);  ostr.setf(ios::showpoint);
	ostr.precision(2);
	//print form : Name : radius, circumference, x_area, height, surface area, volume
	Shape::print(ostr);
	ostr << "radius (" << this->Radius() << ", "
		<< "base_length (" << setw(5) << this->get_base_length() << "), "
		<< "x_perimeter (" << setw(5) << PolyGon::get_perimeter() << "), "
		<< "x_area (" << setw(5) << PolyGon::Area() << "), "
		<< "height (" << this->Height() << "), "
		<< "surface area (" << setw(10) << Sur_Area() << "), "
		<< "volume (" << setw(10) << Volume() << ")]";
}
double PolygonPiller::Sur_Area() const
{
	// ����� �ѳ��� = 2 * �ظ� ���� + ���� ����
	return ((2.0 * PolyGon::Area()) + ( PolyGon::get_perimeter() * (double)Height()));
}
double PolygonPiller::Volume() const
{
	// ����� ���� = �ظ� ���� * ����
	return Area() * (double)Height();
}

/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
PolygonPiller& PolygonPiller::operator=(const PolygonPiller& cyl)
{
	this->PolyGon::operator=(cyl);				// ���Կ����� ȣ��
	this->Set_Height(cyl.Height());				// ���� ����

	return *this;								// �ڱ��ڽ� ��ȯ
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& ostr, const PolygonPiller& cyl)
{
	// ��� 
	cyl.print(ostr);

	return ostr;
}