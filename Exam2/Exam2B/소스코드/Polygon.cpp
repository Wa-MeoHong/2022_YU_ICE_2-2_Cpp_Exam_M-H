
#include "Polygon.h"

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. name�� �μ��� �޴� constructor
		3. ��� ���ڸ� �޴� constructor
		4. ����������								*/
PolyGon::PolyGon()
{
	radius = 0;						// ������
	num_poly = 0;					// ���� ����
}
PolyGon::PolyGon(string name)
	: Shape(name)
{
	radius = 0;						// ������
	num_poly = 0;					// ���� ����
}
PolyGon::PolyGon(string name,int r, int n_poly )
	: Shape(name)
{
	this->setRadius(r);							// ������ ����
	this->setNumPoly(n_poly);					// ���� ���� ����
}
PolyGon::PolyGon(const PolyGon& poly)
	:Shape(poly.Name())
{
	this->setRadius(poly.Radius());			// ������ ����
	this->setNumPoly(poly.NumPoly());		// ���� ���� ����
}

/*				destructor ( �Ҹ��� )				*/
PolyGon::~PolyGon()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( ��� �Լ��� )
		1. print(ostream&) const ( ��� �Լ� )		
		2. get_base_length() (�ٰ��� �Ѻ� ����)
		3. get_perimeter () ���ٰ��� �ѷ�			
		4. Area()								*/
void PolyGon::print(ostream& out) const
{
	out.setf(ios::fixed);  out.setf(ios::showpoint);
	out.precision(2);

	this->Shape::print(out);
	out << "radius (" << setw(2) << this->Radius() << "), ";
	out << "num_poly (" << setw(2) << this->NumPoly() << "), "
		<< "perimeter (" << setw(5) << this->get_perimeter() << "), "
		<< "area (" << setw(5) << this->Area() << ")";

}
double PolyGon::get_base_length() const		// ���� ���̸� ���ϴ� �Լ�
{
	double base = 0.0;
	// ������ ���Ȱ����� ����
	double angle = (PI / 180.0) * (360.0 / NumPoly());
	
	// �������� ������ R�϶�, ���ٰ����� ���� ���� = 2 * R * sin(���� �´��� ��������)
	base = 2 * Radius() * sin(angle / 2);

	return base;
}
double PolyGon::get_perimeter() const		// �ѷ��� ���ϴ� �Լ�
{
	// ���ٰ����� �ѷ� = ���� ���� * ���� ����

	return this->get_base_length() * NumPoly();

}
double PolyGon::Area() const				// ���̸� ���ϴ� �Լ�
{
	double angle = (PI / 180.0) * (360.0 / NumPoly());
	double height = Radius() * cos(angle/2);
	double base = get_base_length();

	double Tri_area = 0.0;

	Tri_area = height * base * 0.5;

	return Tri_area * NumPoly();
}


/*				operator Overloading ( ������ �����ε� )
		1. ���� ������ ( = )
		2. ��� ������ ( << )										*/
PolyGon& PolyGon::operator=(const PolyGon& poly)
{
	this->Shape::operator=(poly);
	this->setRadius(poly.Radius());			// ������ ����
	this->setNumPoly(poly.NumPoly());		// ���� ���� ����

	return *this;
	// TODO: ���⿡ return ���� �����մϴ�.
}
ostream& operator<<(ostream& out, const PolyGon& poly)
{
	out << poly.Name() << " : ";	poly.print(out);
	return out;
	// TODO: ���⿡ return ���� �����մϴ�.
}