#ifndef T_BST_H
#define T_BST_H

#include <iostream>
#include <iomanip>
#include <string>
#include "T_BSTN.h"

using namespace std;

template<typename E>
class T_BST
{
public:
	// constructor
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {}
	// ��� �ʱ�ȭ ����Ʈ�� ���� �����ϰ� �ۼ�

// destructor
	void clear();											// Binary Search Tree�� ����

	// getter
	string Name() const { return name; }					// �̸�
	int Size() const { return num_entry; }					// ���� ����ִ� ����� ����
	bool empty() const { return num_entry == 0; }			// ���� Ʈ���� ����ִ°�?
	T_BSTN<E>* Root() const { return _root; }			// root���(�ֻ������)�� ���� ��ȯ
	T_BSTN<E>** RootAddr() { return &_root; }		// root����� �ּ� ��ȯ
	E* RootEntry() const { return _root->Entry(); }		// root�����  Entry�� ��ȯ

	// member functions (interfaces)
	T_BSTN<E>* eraseBSTN(T_BSTN<E>** pp);				// ��带 ����
	void insertinOrder(const E entry);			// ��带 �������
	void insertAndReBal(E e);					// ��带 ����ְ� ���뷱����
	void print_with_Depth(ostream& ostr);					// BST�� ��� ( ���̿� ���� )
	void print_inOrder(ostream& ostr);						// BST�� ��� ( ������ ���� )

protected:						// public�� �ִ� �Լ����� �����ϴ� �˰����� ��� �ҽ���template<typename E>
	T_BSTN<E>* _insertInOrder(T_BSTN<E>** p, T_BSTN<E>* prPos, const E e);	// insertInOrder
	T_BSTN<E>* _insertAndRebal(T_BSTN<E>** ppTN, T_BSTN<E>* pPr, E e);		// insertAndRebal
	T_BSTN<E>* _rotate_LL(T_BSTN<E>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ� 
	T_BSTN<E>* _rotate_RR(T_BSTN<E>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	T_BSTN<E>* _rotate_RL(T_BSTN<E>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	T_BSTN<E>* _rotate_LR(T_BSTN<E>* pCurSubRoot);				// ����-���� ����� �ڸ��ٲٱ�
	int _Height(T_BSTN<E>* pTN);							// BST�� ����
	int _HeightDiff(T_BSTN<E>* pTN);						// BST�� ����(������ġ?)
	T_BSTN<E>* _reBalance(T_BSTN<E>** ppTN);			// ���뷱�� �Լ�
	void _print_with_Depth(T_BSTN<E>* pTN, ostream& ostr, int depth);		// ��� �Լ�
	void _print_inOrder(T_BSTN<E>* pTN, ostream& ostr);						// ��� �Լ� 2

private:
	T_BSTN<E>* _root;
	int num_entry;	// number of Nodes
	string name;
};

/*					destructor					*/
template<typename E>
inline void T_BST<E>::clear()
{
	this->_root = NULL;
	this->num_entry = 0;
}

/*			member functions interface			*/
template<typename E>
inline T_BSTN<E>* T_BST<E>::eraseBSTN(T_BSTN<E>** pp)		// remove node and rebalanced
{
	T_BSTN<E>* newSubRoot;
	T_BSTN<E>* tobeErased;

	tobeErased = *pp;
	if (tobeErased == NULL)
		return NULL;

	if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() == NULL))			// �ڽĳ����� ���ٸ�
		newSubRoot = NULL;

	else if ((tobeErased->pLc() != NULL) && (tobeErased->pRc() == NULL))	// ���� �ڽĳ�常 �ִٸ�
	{
		newSubRoot = tobeErased->pLc();										// ���� ����� ���ʳ�带 �����ͼ�
		newSubRoot->SetpPr(tobeErased->pPr());								// ������ ����� �θ���� �̾���
	}
	else if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() != NULL))	// ������ �ڽĳ�常 �ִٸ�
	{
		newSubRoot = tobeErased->pRc();										// ���� ����� �����ʳ�带 �����ͼ�
		newSubRoot->SetpPr(tobeErased->pPr());								// ������ ����� �θ���� �̾���
	}
	else
	{
		int h_diff = _HeightDiff(tobeErased);			// �ڽĳ���� ũ�⸦ ����.

		T_BSTN<E>* parDel = tobeErased->pPr();
		T_BSTN<E>* lChild = tobeErased->pLc();
		T_BSTN<E>* rChild = tobeErased->pRc();
		T_BSTN<E>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<E>* ioPd = NULL, * lcIoPd, * parIoPd;

		if (h_diff > 0)			// ���� ��� Ʈ���� �� ũ�ٸ�, ������ ��带 ��ü�� ��带 ioPd�� �������
		{
			ioPd = _maxBSTN(lChild);			// ������ ����� ���� �ڽĳ�� Ʈ���� ���� ū ��
			lcIoPd = ioPd->pLc();
			parIoPd = ioPd->pPr();
			newSubRoot = ioPd;
			if (ioPd->pPr() != tobeErased)
			{
				newSubRoot->SetpLc(lChild);
				parIoPd->SetpRc(lcIoPd);
				if (lcIoPd != NULL)
					lcIoPd->SetpPr(parIoPd);
			}

			newSubRoot->SetpRc(rChild);
			newSubRoot->SetpPr(tobeErased->pPr());
		}
		else
		{
			ioSs = _minBSTN(rChild); // �������� ����� ������ �ڽĳ�� Ʈ�� �� ���� ���� ��
			rcIoSs = ioSs->pRc(); parIoSs = ioSs->pPr();
			newSubRoot = ioSs;
			if (ioSs->pPr() != tobeErased)			// ���� �� ����� �θ��尡 �������� ��尡 �ƴ϶��
			{
				newSubRoot->SetpRc(rChild);			// ioSs�� ������ ��带 �������� ����� ������ �ڽĳ��� ����
				parIoSs->SetpLc(rcIoSs);			// ioSs�� �θ����� �����ڽĳ���� ���� ioSs�� ������ �ڽĳ��� ����
				if (rcIoSs != NULL)
					rcIoSs->SetpPr(parIoSs);		// ���� rcIoSs�� �θ��带 ioSs�� �θ���� ����
			}
			newSubRoot->SetpLc(lChild);
			newSubRoot->SetpPr(tobeErased->pPr());
		}

		if (lChild != ioPd)
			lChild->SetpPr(newSubRoot);
		if (rChild != ioSs)
			rChild->SetpPr(newSubRoot);
	}
	if (tobeErased == _root)
		_root = newSubRoot;
	num_entry--;
	free(tobeErased);
	*pp = newSubRoot;
	return newSubRoot;
}

// interface 
		// insert �Լ� ( ����Ž��Ʈ���� ���� ������� )
// 1. ������ ���� �� ����ֱ�
// 2. ���� ����ְ� ���뷱���� ��
template<typename E>
inline void T_BST<E>::insertinOrder(const E entry)
{
	_insertInOrder(&_root, NULL, entry);
}
template<typename E>
inline void T_BST<E>::insertAndReBal(E e)
{
	_insertAndRebal(&_root, NULL, e);
}


// ��� �Լ� �������̽�
// 1. ���̿� ���� ���
// 2. ������ ���� ��� 
template<typename E>
inline void T_BST<E>::print_with_Depth(ostream& ostr)
{
	T_BSTN<E>* root = this->Root();
	if (this->num_entry == 0)
	{
		ostr << this->Name() << " is empty now !!" << endl;
		return;
	}
	_print_with_Depth(this->Root(), ostr, 0);

}
template<typename E>
inline void T_BST<E>::print_inOrder(ostream& ostr)
{
	T_BSTN<E>* root = this->Root();
	if (this->num_entry == 0)
	{
		ostr << this->Name() << " is empty now !!" << endl;
		return;
	}
	_print_inOrder(this->Root(), ostr);
}


/*			protected functions			*/

				//	insert function 
		// 1. insertInOrder
		// 2. insertAndRebalance 
template<typename E>
inline T_BSTN<E>* T_BST<E>::_insertInOrder(T_BSTN<E>** p, T_BSTN<E>* prPos, const E e)
{
	T_BSTN<E>* newPos, ** pChildPos;
	T_BSTN<E>* pos;
	E ent;

	if (p == NULL)
	{
		cout << "Error !! in creation of Binary Search Tree : \n"
			<< " address of the pointer to the Root Node is NULL !! \n";
		exit(-1);
	}

	pos = *p;

	// ���� ���� ��尡 ���ٸ�
	if (pos == NULL)
	{
		pos = new T_BSTN<E>(e);			// ��带 �����Ҵ�
		if (prPos == NULL)
			this->_root = pos;					// pos�� root��尡 �ȴ�. 
		pos->SetpPr(prPos);						// �θ���� ����
		*p = pos;
		num_entry++;							// ��Ʈ���� ���� 1�� ����
		return pos;								// ��ȯ
	}

	ent = **pos;

	// ���� ����� entry�� �θ��� entry���� �� �۴ٸ� ���ʳ�忡 ������� 
	if (e < ent)
	{
		pChildPos = pos->ppLc();					// ��ġ�� ���ʳ�� (�ּ�)
		newPos = _insertInOrder(pChildPos, pos, e);	// �ѹ��� üũ ( �� ������ �̾������� )
		if (newPos != NULL)
			pos->SetpLc(newPos);					// ���� ���̻� ������ ������ ��尡 ���ٸ� �� ��带 �������� ����
		return NULL;								// ��ȯ
	}

	// ���� ����� entry�� �θ��� entry���� �� ũ�ٸ� ���ʳ�忡 ������� 
	else if (e >= ent)
	{
		pChildPos = pos->ppRc();					// ��ġ�� �����ʳ�� (�ּ�)
		newPos = _insertInOrder(pChildPos, pos, e);		// üũ ( �� ������ �̾����°� ) 
		if (newPos != NULL)
			pos->SetpRc(newPos);					// ���̻� ������ �������� �ʴ´ٸ� ������ ��忡 ������
		return NULL;								// ��ȯ
	}
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_insertAndRebal(T_BSTN<E>** ppTN, T_BSTN<E>* pPr, E e)
{
	T_BSTN<E>* pTN = NULL, ** ppLc = NULL, ** ppRc = NULL;
	E bstn_entry;

	// ���� �ܺ� ��带 �� Ʈ����忡 ������
	if (*ppTN == NULL)
	{
		pTN = new T_BSTN<E>(e);
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->SetpPr(pPr);				// �θ��� ����
		(*ppTN)->SetpLc(NULL);				// �ڽĳ��� �����Ƿ� NULL�� ����
		(*ppTN)->SetpRc(NULL);
		num_entry++;
		return *ppTN;						// ���� ��� ��ȯ
	}


	bstn_entry = **(*ppTN);				// ��Ʈ���� ������
	if (e < bstn_entry)
	{
		ppLc = (*ppTN)->ppLc();					// ���� �θ��庸�� ��Ʈ������ �� �۴ٸ� ���� ��� �ּҸ� �������� 
		pTN = _insertAndRebal(ppLc, *ppTN, e);	// �� ������ �������鼭 ��� ���� ���� ã�´�
		if (ppTN != NULL)						// ���� �� ������ ���� ���ٸ� 
		{
			(*ppTN)->SetpLc(pTN);				// ��带 ���� 
			*ppTN = _reBalance(ppTN);			// ��ġ ���뷱�� �Ѵ�.
		}
	}
	else
	{
		ppRc = (*ppTN)->ppRc();					// �θ��� ��Ʈ�� ������ ũ�ų� ������ ������ ��� �ּҸ� ������
		pTN = _insertAndRebal(ppRc, *ppTN, e);	// ��� ������ ��������.
		if (ppTN != NULL)						// �� ������ ���� ���ٸ� 
		{
			(*ppTN)->SetpRc(pTN);				// ������ �� �����ϰ�
			*ppTN = _reBalance(ppTN);			// ���뷱�� ��
		}
	}
	return *ppTN;
}


// rebalance
template<typename E>
inline T_BSTN<E>* T_BST<E>::_reBalance(T_BSTN<E>** ppTN)
{
	int heightDiff = 0;

	heightDiff = _HeightDiff(*ppTN);				// ���� ���̸� ���
	if (heightDiff > 1)								// ���� 1���� ũ�ٸ� 
	{
		if (_HeightDiff((*ppTN)->pLc()) > 0)		// ���ʳ�嵵 ����ؼ� �������̰� ������
			*ppTN = _rotate_LL(*ppTN);				// ��-�� �����̼�
		else
			*ppTN = _rotate_LR(*ppTN);				// �ƴϸ� ��-�� �����̼�
	}
	else if (heightDiff < -1)						// -1���� �۴ٸ� �������̴�.
	{
		if (_HeightDiff((*ppTN)->pRc()) < 0)		// ������ �ڽĳ�嵵 ����Ͽ� ���̰� �������
			*ppTN = _rotate_RR(*ppTN);				// ��-�� �����̼�
		else
			*ppTN = _rotate_RL(*ppTN);				// ��-�� �����̼�
	}
	return *ppTN;									// ��ȯ
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_rotate_LL(T_BSTN<E>* pCurSubRoot)
{
	T_BSTN<E>* pNewSubRoot, * pBR, * pCurParent;

	pCurParent = pCurSubRoot->pPr();
	pNewSubRoot = pCurSubRoot->pLc();
	pBR = pNewSubRoot->pRc();

	pCurSubRoot->SetpLc(pBR);
	if (pBR != NULL)
		pBR->SetpPr(pCurSubRoot);
	pNewSubRoot->SetpRc(pCurSubRoot);
	pNewSubRoot->SetpPr(pCurParent);
	pCurSubRoot->SetpPr(pNewSubRoot);

	return pNewSubRoot;
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_rotate_RR(T_BSTN<E>* pCurSubRoot)
{
	T_BSTN<E>* pNewSubRoot, * pBL, * pCurParent;

	pCurParent = pCurSubRoot->pPr();
	pNewSubRoot = pCurSubRoot->pRc();
	pBL = pNewSubRoot->pLc();

	pCurSubRoot->SetpRc(pBL);
	if (pBL != NULL)
		pBL->SetpPr(pCurSubRoot);
	pNewSubRoot->SetpLc(pCurSubRoot);
	pNewSubRoot->SetpPr(pCurParent);
	pCurSubRoot->SetpPr(pNewSubRoot);

	return pNewSubRoot;
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_rotate_RL(T_BSTN<E>* pCurSubRoot)
{
	T_BSTN<E>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<E>* pA, * pB, * pC, * pBL, * pBR;

	pA = pCurSubRoot;
	pCurParent = pCurSubRoot->pPr();				// 
	pC = pA->pRc(); pB = pC->pLc();
	pBL = pB->pLc(); pBR = pB->pRc();

	pSubRoot = _rotate_LL(pC);
	pCurSubRoot->SetpRc(pSubRoot);
	pNewSubRoot = _rotate_RR(pA);

	pNewSubRoot->SetpPr(pCurParent);
	pA->SetpPr(pNewSubRoot); pC->SetpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->SetpPr(pA);
	if (pBR != NULL)
		pBR->SetpPr(pC);

	return pNewSubRoot;
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_rotate_LR(T_BSTN<E>* pCurSubRoot)
{
	T_BSTN<E>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<E>* pA, * pB, * pC, * pBL, * pBR;

	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->pPr();
	pA = pC->pLc(); pB = pA->pRc();
	pBL = pB->pLc(); pBR = pB->pRc();

	pSubRoot = _rotate_RR(pA);
	pCurSubRoot->SetpLc(pSubRoot);
	pNewSubRoot = _rotate_LL(pC);

	pNewSubRoot->SetpPr(pCurParent);
	pA->SetpPr(pNewSubRoot); pC->SetpPr(pNewSubRoot);
	if (pBL != NULL)
		pBL->SetpPr(pA);
	if (pBR != NULL)
		pBR->SetpPr(pC);

	return pNewSubRoot;

}

template<typename E>
inline int T_BST<E>::_Height(T_BSTN<E>* pTN)
{
	int height = 0, h_Lc = 0, h_Rc = 0;

	if (pTN != NULL)
	{
		h_Lc = _Height(pTN->pLc()); h_Rc = _Height(pTN->pRc());		// ��͸� ���� �ڽĳ����� ��ġ�� �Ǻ�
		if (h_Lc > h_Rc)
			height = 1 + h_Lc;
		else
			height = 1 + h_Rc;
	}
	// ����, ������ �� ���� �� ������ ������ ��带 �������� + 1�Ѵ�.
	return height;
}
template<typename E>
inline int T_BST<E>::_HeightDiff(T_BSTN<E>* pTN)
{
	int h_diff = 0;
	if (pTN == NULL)
		return 0;
	h_diff = _Height(pTN->pLc()) - _Height(pTN->pRc());

	// ���� ���� ����� ���̿� ������ ����� ���̸� ���� ���� ���
	return h_diff;
}

// print function 
template<typename E>
inline void T_BST<E>::_print_with_Depth(T_BSTN<E>* pTN, ostream& ostr, int depth)
{
	T_BSTN<E>* pRc, * pLc;

	if ((pRc = pTN->pRc()) != NULL)
		_print_with_Depth(pRc, ostr, depth + 1);				// ������ ��� ���
	for (int i = 0; i < depth; i++)
	{
		ostr << "    ";										// �� Ű�� ���� ������
	}
	ostr << **pTN << endl;
	if ((pLc = pTN->pLc()) != NULL)							// ���� ��� ���
		_print_with_Depth(pLc, ostr, depth + 1);
}
template<typename E>
inline void T_BST<E>::_print_inOrder(T_BSTN<E>* pTN, ostream& ostr)
{
	T_BSTN<E>* pRc, * pLc;
	if ((pLc = pTN->pLc()) != NULL)
		_print_inOrder(pLc, ostr);						// ���� ��� ���
	ostr << **pTN << " ";						// �߰� ��� ���
	if ((pRc = pTN->pRc()) != NULL)
		_print_inOrder(pRc, ostr);						// ������ ��� ���
}


#endif // !T_BST_H


