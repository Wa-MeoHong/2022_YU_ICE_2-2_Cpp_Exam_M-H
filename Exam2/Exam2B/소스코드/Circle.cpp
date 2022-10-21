#include "Circle.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor
		3. 모든 인자를 받는 constructor
		4. 복제생성자								*/
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

/*				destructor ( 소멸자 )				*/
Circle::~Circle()
{
	// cout << "Circle class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame) ( 그림 그리기 함수 )
		2. fprint(ostream&) const ( 출력 함수 )
		3. Area() const			( 넓이 구하는 함수)*/
void Circle::print(ostream& out) const
{
	out.setf(ios::showpoint); out.setf(ios::fixed);				// 고정 소수점 2자리까지만 출력
	out.precision(2);

	// 출력 순서 : 좌표 - 반지름 - 각도 - 색깔(선, 브러시)
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

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Circle& Circle::operator=(const Circle& cir)
{
	this->Shape::operator=(cir);
	this->setRadius(cir.Radius());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Circle& cir)
{
	cir.print(out);
	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}