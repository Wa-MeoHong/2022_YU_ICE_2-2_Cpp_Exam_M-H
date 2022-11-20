#ifndef CIRQ_H
#define CIRQ_H

#include <iostream>
#include <iomanip>
#include <string>
#include <mutex>
#include "T_Array.h"


using namespace  std;

template <typename E>
class TA_CirQ : public T_Array<E>
{
private:
	int front; // index of queue_front
	int back; // index of queue_back
	mutex mtx_cirQ;
public:
	TA_CirQ(int capacity, string nm); // constructor
	~TA_CirQ() {} //destructor
	E* dequeue(); // return the element at front of FIFO queue
	E* enqueue(E& element); // insert an element at the back of the FIFO queue
	bool isEmpty() { return (this->num_elements == 0); }
	bool isFull() { return (this->num_elements >= this->capacity); }
	int size() { return this->num_elements; }
	void fprint(ostream& fout, int elements_per_line);
};

template<typename E>
inline TA_CirQ<E>::TA_CirQ(int capacity, string nm)
	: T_Array<E>(capacity, nm)
{
	if (this->t_array == NULL)		// 만약 t_array가 동적할당 되지 않았으면 Error문 출력
	{
		cout << "Error in t_array" << endl;
	}
	front = back = 0;				// 앞, 뒤를 설정해줌 현재 front와 back이 같은 위치에 있음
}

template<typename E>
inline E* TA_CirQ<E>::dequeue()		 // 값을 빼냄 ( 맨 처음 값 ) 
{
	this->mtx_cirQ.lock();
	if (this->isEmpty())		// 만약 큐가 비어있다면
	{
		this->mtx_cirQ.unlock();
		return NULL;			// NULL값 반환

	}
	else
	{
		E* pE;

		pE = &(this->t_array[this->front]);		// 맨앞의 값을 빼냄
		this->front++;							// front 값 증가
		this->num_elements--;					// 현재 큐에 든 이벤트의 개수 감소
		if (this->front >= this->capacity)		// 만약 front가 배열의 끝에 도달했다면
			this->front = this->front % this->capacity;		// 위치를 다시 처음으로 돌려줌
		this->mtx_cirQ.unlock();
		return pE;								// 반환
	}
}

template<typename E>
inline E* TA_CirQ<E>::enqueue(E& element)		// 값을 삽입 ( 맨 뒤에 )
{
	this->mtx_cirQ.lock();
	if (this->isFull())				// 만약 큐가 가득 찼다면 NULL을 반환
	{
		cout << "Queue is full !!" << endl;	
		this->mtx_cirQ.unlock();
		return NULL;
	}

	E* pE;				
	this->t_array[this->back] = element;		// 큐의 맨 뒤에 값을 집어넣고
	pE = &(this->t_array[this->back]);			// 반환해줄 pE에 복사
	back++;										// back 증가, 만약 배열의 끝에 도달했으면 처음으로 back을 설정
	if (this->back >= this->capacity)
		this->back = this->back % this->capacity;
	this->num_elements++;						// 큐 안에 있는 이벤트 개수 증가
	this->mtx_cirQ.unlock();

	return pE;
}

template<typename E>
inline void TA_CirQ<E>::fprint(ostream& fout, int elements_per_line)		// 출력문 (미완성 )
{
	cout.setf(4);
	for (int i = 0; i < elements_per_line; i++)			
	{
		cout << this->t_array[i];

		if ((i + 1) % elements_per_line == 0)
			cout << endl;
	}
}

#endif CIRQ_H
