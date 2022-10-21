#include "PolygonPiller.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor ( 헤더에 정의 )
		3. 모든 인자를 받는 constructor
		4. Copy Constructor		( 복제 생성자 )			*/
PolygonPiller::PolygonPiller()
{
	this->Set_Height(0);
}
PolygonPiller::PolygonPiller(string n, int r, int num_poly, int h)
	: PolyGon(n, r, num_poly)				// Funtion initialize로 이름을 집어넣음
{
	this->Set_Height(h);					// 높이 세팅
}
PolygonPiller::PolygonPiller(const PolygonPiller& cyl)
	: PolyGon(cyl.Name(), cyl.Radius() , cyl.NumPoly())
	// Funtion initialize로 집어넣음, 생성자 호출
{
	this->Set_Height(cyl.Height());			// 높이
}

/*				destructor ( 소멸자 )				*/
PolygonPiller::~PolygonPiller()
{
	// destruct Shape object
}

/*				member functions ( 멤버 함수들 )
		1. draw(ostream& ostr)	(virtual로 정의하였고, sub-class에서 재정의용도로 만듦)
		2. Sur_Area() ( 원기둥의 겉넓이  )
		3. Volume() ( 원기둥의 부피 )					*/
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
	// 원기둥 겉넓이 = 2 * 밑면 넓이 + 옆면 넓이
	return ((2.0 * PolyGon::Area()) + ( PolyGon::get_perimeter() * (double)Height()));
}
double PolygonPiller::Volume() const
{
	// 원기둥 부피 = 밑면 넓이 * 높이
	return Area() * (double)Height();
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
PolygonPiller& PolygonPiller::operator=(const PolygonPiller& cyl)
{
	this->PolyGon::operator=(cyl);				// 대입연산자 호출
	this->Set_Height(cyl.Height());				// 높이 대입

	return *this;								// 자기자신 반환
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& ostr, const PolygonPiller& cyl)
{
	// 출력 
	cyl.print(ostr);

	return ostr;
}