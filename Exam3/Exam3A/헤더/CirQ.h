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
	if (this->t_array == NULL)		// ���� t_array�� �����Ҵ� ���� �ʾ����� Error�� ���
	{
		cout << "Error in t_array" << endl;
	}
	front = back = 0;				// ��, �ڸ� �������� ���� front�� back�� ���� ��ġ�� ����
}

template<typename E>
inline E* TA_CirQ<E>::dequeue()		 // ���� ���� ( �� ó�� �� ) 
{
	this->mtx_cirQ.lock();
	if (this->isEmpty())		// ���� ť�� ����ִٸ�
	{
		this->mtx_cirQ.unlock();
		return NULL;			// NULL�� ��ȯ

	}
	else
	{
		E* pE;

		pE = &(this->t_array[this->front]);		// �Ǿ��� ���� ����
		this->front++;							// front �� ����
		this->num_elements--;					// ���� ť�� �� �̺�Ʈ�� ���� ����
		if (this->front >= this->capacity)		// ���� front�� �迭�� ���� �����ߴٸ�
			this->front = this->front % this->capacity;		// ��ġ�� �ٽ� ó������ ������
		this->mtx_cirQ.unlock();
		return pE;								// ��ȯ
	}
}

template<typename E>
inline E* TA_CirQ<E>::enqueue(E& element)		// ���� ���� ( �� �ڿ� )
{
	this->mtx_cirQ.lock();
	if (this->isFull())				// ���� ť�� ���� á�ٸ� NULL�� ��ȯ
	{
		cout << "Queue is full !!" << endl;	
		this->mtx_cirQ.unlock();
		return NULL;
	}

	E* pE;				
	this->t_array[this->back] = element;		// ť�� �� �ڿ� ���� ����ְ�
	pE = &(this->t_array[this->back]);			// ��ȯ���� pE�� ����
	back++;										// back ����, ���� �迭�� ���� ���������� ó������ back�� ����
	if (this->back >= this->capacity)
		this->back = this->back % this->capacity;
	this->num_elements++;						// ť �ȿ� �ִ� �̺�Ʈ ���� ����
	this->mtx_cirQ.unlock();

	return pE;
}

template<typename E>
inline void TA_CirQ<E>::fprint(ostream& fout, int elements_per_line)		// ��¹� (�̿ϼ� )
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
