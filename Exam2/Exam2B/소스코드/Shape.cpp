#include "Shape.h"

/*				constructor ( 생성자 )
		1. default constructor ( 디폴트 생성자 )
		2. name만 인수를 받는 constructor			*/

Shape::Shape()
{

	name = "no_name";							// 이름도 없음
}
Shape::Shape(string name)
{
	NameSet(name);								// 이름 세팅
}

/*				destructor ( 소멸자 )				*/
Shape::~Shape()
{
	// cout << "Shape class terminated!" << endl;
}

/*				member functions ( 멤버 함수들 )
		1. draw(ConsolePixelFrame cp_frame)
		  (virtual로 정의하였고, sub-class에서 재정의용도로 만듦)
		2. fprint(ostream&) const ( 출력 함수 )				*/
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
	// 출력 순서 : 좌표 - 각도 - 색깔(선, 브러시)
	out << right <<setw(15) << this->Name() << ": ";
}

/*				operator Overloading ( 연산자 오버로드 )
		1. 대입 연산자 ( = )
		2. 출력 연산자 ( << )										*/
Shape& Shape::operator=(const Shape& s)
{
	this->NameSet(s.Name());

	return *this;
	// TODO: 여기에 return 문을 삽입합니다.
}
ostream& operator<<(ostream& out, const Shape s)
{
	s.print(out);

	return out;
	// TODO: 여기에 return 문을 삽입합니다.
}