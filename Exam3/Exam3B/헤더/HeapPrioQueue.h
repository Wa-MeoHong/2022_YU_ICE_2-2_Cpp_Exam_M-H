#ifndef HEAP_PRIO_QUEUE_H
#define HEAP_PRIO_QUEUE_H

#include "CBT.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <mutex>

using namespace std;

template <typename K>
class HeapPrioQueue : public CompleteBinaryTree<K>
{
public:
	// constructor
	HeapPrioQueue(int capa, string nm);
	
	// destructor
	~HeapPrioQueue();

	// getter 
	bool isEmpty() { return this->size() == 0; }
	bool isFull() { return this->size() == this->capacity; }
	int size() { return this->end; }
	K* HeapMin();

	// member functions
	K* insert(K elem);
	K* removeHeapMin();
	void fprint(ostream& ostr);
private:
	int capacity;
	mutex mtx_priQ;
};

/*					constructor ( ������ )				*/
template<typename K>
inline HeapPrioQueue<K>::HeapPrioQueue(int capa, string nm)
	: CompleteBinaryTree<K>(capa, nm), capacity(capa)
{
}

/*					destructor ( �Ҹ��� )				*/
template<typename K>
inline HeapPrioQueue<K>::~HeapPrioQueue()
{
	cout << "HeapPriority Queue is destructed !" << endl;
}

/*				member function ( ��� �Լ� )
		1. HeapMin() ( Heap Queue�� ���� �켱������ ���� �� ��ȯ )
		2. Insert(elem) ( ť�� */

template<typename K>
inline K* HeapPrioQueue<K>::HeapMin()
{
	K* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	// ROOT��带 �����ؼ� �����ͼ� ��ȯ��
	*pMinElem = this->RootElement();
	return pMinElem;
}

template<typename K>
inline K* HeapPrioQueue<K>::insert(K elem)
{
	int index, ParentIndex;
	K temp;
	K* pRoot = NULL;

	// ���� ����á�ٸ� ť�� �����ʰ� �ٷ� return �Ѵ�.
	this->mtx_priQ.lock();
	if (isFull())			// ���� ť�� ���� á�ٸ�
	{
		cout << "Error! Queue is Full !!" << endl;
		this->mtx_priQ.unlock();
		return NULL;		// NULL�� ��ȯ
	}
	// ť�� �ְ� �� �ε��� ���� ��ȯ���� ( ������ �ϱ� ���� ���� ) 
	index = this->add_at_end(elem);

	while (index != CBT_ROOT)
	{
		ParentIndex = this->parentIndex(index);		// ������ �ε����� �θ� ���
		if (this->t_array[index] >= this->t_array[ParentIndex])		// ���� �ε�����ȣ�� �θ�ͺ��� ũ�ٸ�( �켱������ ���ٸ�) 
			break;									// �״�� ���д�
		else
		{
			// �ƴϸ� �θ���� �ٲ۴�.
			temp = this->t_array[index];
			this->t_array[index] = this->t_array[ParentIndex];
			this->t_array[ParentIndex] = temp;
			index = ParentIndex;
		}
	}
	this->mtx_priQ.unlock();

	pRoot = &(this->t_array[CBT_ROOT]);				// ��Ʈ ��� ��ȯ
	return pRoot;									// ��Ʈ ��� ��ȯ
}

template<typename K>
inline K* HeapPrioQueue<K>::removeHeapMin()
{
	int index_p, index_c, index_rc;
	K* pMinElem = NULL;
	K temp, t_p, t_c;

	// ���� queue�� ũ�Ⱑ 0���϶�� Null ��ȯ
	int HPQ_Size = this->size();
	if (HPQ_Size <= 0)
		return NULL;

	mtx_priQ.lock();
	pMinElem = (K*) new K;
	// ROOT ����� ���� ������ ������
	*pMinElem = this->RootElement();
	if (HPQ_Size == 1)
	{
		this->removeCBTEnd();
	}

	else
	{
		// �θ���� 1, �׸���, �� �������� ������ ���������.
		index_p = CBT_ROOT;
		this->t_array[CBT_ROOT] = this->t_array[this->end];
		this->end--;

		while (this->hasLeftChild(index_p))
		{
			// c = ���� �ڽ�, rc = ������ �ڽ�
			index_c = this->leftChildIndex(index_p);
			index_rc = this->rightChildIndex(index_p);
			// ���� ������ ��尡 �ְ�, �������� �� �켱 ������ ���ٸ�, rc�� ���� ����Ѵ�.
			if (this->hasRightChild(index_p) && (this->t_array[index_c] > this->t_array[index_rc]))
				index_c = index_rc;
			t_p = this->t_array[index_p]; t_c = this->t_array[index_c];
			if (t_p > t_c)
			{
				//swaping
				temp = t_p;
				this->t_array[index_p] = this->t_array[index_c];
				this->t_array[index_c] = temp;
				index_p = index_c;

			}
			else
				break;
		} // end while
	}
	mtx_priQ.unlock();

	return pMinElem;
}

template<typename K>
inline void HeapPrioQueue<K>::fprint(ostream& ostr)
{
	if (this->size() <= 0) // if is empty
	{
		ostr << "Error ! Queue is Empty !! " << endl;
		return;
	}
	else
		CompleteBinaryTree<K>::fprintCBT(ostr);
}

#endif // !HEAP_PRIO_QUEUE_H
