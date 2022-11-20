#ifndef CBT_H
#define CBT_H

#include "T_Array.h"
#include <iostream>
#include <iomanip>
#include "SimParam.h"

#define EVENT_PER_LINE 20
#define CBT_ROOT 1
using namespace std;

template <typename E>
class CompleteBinaryTree : public T_Array<E>
{
public:
	// constructor ( ������ )
	CompleteBinaryTree(int capa, string nm);				// CBT �ʱ� ������

	int add_at_end(E& elem);					// ��� ���� elem�� �߰���

	// getter 
	E& EndElement() { return this->t_array[end]; }		// Leap��� ��ȯ
	E& RootElement() { return this->t_array[CBT_ROOT]; }	// Root��� ��ȯ
	int EndIndex() { return this->end; }					// Leap����� �ε��� ��ȯ

	// member functions ( ��� �Լ� ) 
	void removeCBTEnd();								// ���� ����Ʈ���� Leap��� ����
	void fprintCBT(ostream& ostr);						// ���� ����Ʈ�� ���
	void fprintCBT_byLevel(ostream& ostr);				// ������ ���� ��������Ʈ�� ���

protected:
	void _printCBT_byLevel(ostream& ostr, int index, int level);		// ��������Ʈ�� �� ����Լ�
	int parentIndex(int index) const { return index / 2; }				// �θ����� �ε���
	int leftChildIndex(int index) const { return index * 2; }			// ���� �ڽĳ�� �ε���
	int rightChildIndex(int index) const { return index * 2 + 1; }		// ������ �ڽĳ�� �ε���
	bool hasLeftChild(int index) const { return ((index * 2) <= end); }	// �����ڽĳ�尡 �ִ���? ��ȿ���˻�
	bool hasRightChild(int index) const { return ((index * 2 + 1) <= end); } // �������ڽĳ�尡 �ִ���? ��ȿ���˻�
	int end;
};

/*					constructor ( ������ )					*/
template <typename E>
inline CompleteBinaryTree<E>::CompleteBinaryTree(int capa, string nm)
	: T_Array<E>(capa, nm)
{
	end = 0;		// empty ( num_elements = 0 )
}

/*				member functions ( ��� �Լ� )
		1. add_at_end(elem) ( ���� element�� ���� )
		2. removeCBTEnd() ( ���� ���� �ִ� ��带 ������ )
		3. fprintCBT(ostr) ( CBT�� �ܼ��� �迭�� ���·� ��� )
		4. fprintCBT_byLevel(ostr) ( CBT�� �������·� ��� )
		5. _printCBT_byLevel(ostr) ( ���Լ�)					*/
template <typename E>
inline int CompleteBinaryTree<E>::add_at_end(E& elem)
{
	// ���� capacity���� �� á�ٸ� �ٷ� end�� ��ȯ.
	if (this->end >= this->capacity)
	{
		cout << this->name << "is Full now !!" << endl;
		return end;
	}
	// �� ���� �ʾҴٸ� end�� +1 �� ��, elem�� �߰��� �� ��ȯ�Ѵ�.
	this->end++;
	this->t_array[this->end] = elem;

	return end;
}
template <typename E>
inline void CompleteBinaryTree<E>::removeCBTEnd()		// remove end point
{
	// ����� end�� num_elements�� ���δ�. 
	this->end--;
	this->num_elements--;
}
template <typename E>
inline void CompleteBinaryTree<E>::fprintCBT(ostream& ostr)
{
	// ���� ����� CBT ��尡 ������, ����ִٰ� ���
	if (this->end <= 0)
	{
		ostr << this->Name() << "is empty now !!" << endl;
		return;
	}

	// �ƴϸ� �ϳ��� ��� 
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		if ((i - 1) % EVENT_PER_LINE == 0)
			cout << endl;
		ostr << setw(3) << this->t_array[i];
		count++;
	}
}
template <typename E>
inline void CompleteBinaryTree<E>::fprintCBT_byLevel(ostream& ostr)
{
	// ���� ��尡 ������ ������� �ʰ� Ż��
	if (this->end <= 0)
	{
		ostr << "CBT is Empty now !! " << endl;
		return;
	}
	// ���
	_printCBT_byLevel(ostr, CBT_ROOT, 0);
}
template <typename E>
inline void CompleteBinaryTree<E>::_printCBT_byLevel(ostream& ostr, int index, int level)
{
	int index_child;				// �ڽ� ���

	// ������ �ڽĳ�尡 �� ���� ������ ������ ����Լ��� ������ ���� level�� ������ ���
	if (this->hasRightChild(index))
	{
		index_child = rightChildIndex(index);
		this->_printCBT_byLevel(ostr, index_child, level + 1);
	}

	// �� ��� �ڵ�
	for (int i = 0; i < level; i++)
	{
		ostr << "\t";
	}
	this->t_array[index].fprint(ostr);
	ostr << endl;

	// ���� �ڽ� ��� ��� �κ�. �굵 ��͸� ���� level�� �����
	if (this->hasLeftChild(index))
	{
		index_child = leftChildIndex(index);
		this->_printCBT_byLevel(ostr, index_child, level + 1);
	}

}


#endif // !CBT_H

