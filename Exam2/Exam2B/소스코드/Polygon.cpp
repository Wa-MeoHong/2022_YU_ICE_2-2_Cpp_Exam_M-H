
#include "Polygon.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
PolyGon::PolyGon()
{
	radius = 0;						// 반지름
	num_poly = 0;					// 각의 개수
}
PolyGon::PolyGon(string name)
	: Shape(name)
{
	radius = 0;						// 반지름
	num_poly = 0;					// 각의 개수
}
PolyGon::PolyGon(string name,int r, int n_poly )
	: Shape(name)
{
	this->setRadius(r);							// 반지름 대입
	this->setNumPoly(n_poly);					// 각의 개수 대입
}
PolyGon::PolyGon(const PolyGon& poly)
	:Shape(poly.Name())
{
	this->setRadius(poly.Radius());			// 반지름 대입
	this->setNumPoly(poly.NumPoly());		// 각의 개수 대입
}

/*				destructor ( 소멸자 )				*/
PolyGon::~PolyGon()
{
	// cout << "Star class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. print(ostream&) const ( 출력 함수 )		
		2. get_base_length() (다각형 한변 길이)
		3. get_perimeter () 정다각형 둘레			
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
double PolyGon::get_base_length() const		// 변의 길이를 구하는 함수
{
	double base = 0.0;
	// 각도를 라디안값으로 수정
	double angle = (PI / 180.0) * (360.0 / NumPoly());
	
	// 외접원의 반지름 R일때, 정다각형의 변의 길이 = 2 * R * sin(변의 맞닿은 꼭지점각)
	base = 2 * Radius() * sin(angle / 2);

	return base;
}
double PolyGon::get_perimeter() const		// 둘레를 구하는 함수
{
	// 정다각형의 둘레 = 변의 길이 * 각의 개수

	return this->get_base_length() * NumPoly();

}
double PolyGon::Area() const				// 넓이를 구하는 함수
{
	double angle = (PI / 180.0) * (360.0 / NumPoly());
	double height = Radius() * cos(angle/2);
	double base = get_base_length();

	double Tri_area = 0.0;

	Tri_area = height * base * 0.5;

	return Tri_area * NumPoly();
}


/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
PolyGon& PolyGon::operator=(const PolyGon& poly)
{
	this->Shape::operator=(poly);
	this->setRadius(poly.Radius());			// 반지름 대입
	this->setNumPoly(poly.NumPoly());		// 각의 개수 대입

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const PolyGon& poly)
{
	out << poly.Name() << " : ";	poly.print(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}