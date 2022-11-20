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
	// 멤버 초기화 리스트를 통해 간단하게 작성

// destructor
	void clear();											// Binary Search Tree를 삭제

	// getter
	string Name() const { return name; }					// 이름
	int Size() const { return num_entry; }					// 현재 들어있는 노드의 개수
	bool empty() const { return num_entry == 0; }			// 현재 트리가 비어있는가?
	T_BSTN<E>* Root() const { return _root; }			// root노드(최상위노드)의 값을 반환
	T_BSTN<E>** RootAddr() { return &_root; }		// root노드의 주소 반환
	E* RootEntry() const { return _root->Entry(); }		// root노드의  Entry를 반환

	// member functions (interfaces)
	T_BSTN<E>* eraseBSTN(T_BSTN<E>** pp);				// 노드를 삭제
	void insertinOrder(const E entry);			// 노드를 집어넣음
	void insertAndReBal(E e);					// 노드를 집어넣고 리밸런싱함
	void print_with_Depth(ostream& ostr);					// BST의 출력 ( 깊이에 따른 )
	void print_inOrder(ostream& ostr);						// BST의 출력 ( 순서에 따른 )

protected:						// public에 있는 함수들이 실행하는 알고리즘이 담긴 소스들template<typename E>
	T_BSTN<E>* _insertInOrder(T_BSTN<E>** p, T_BSTN<E>* prPos, const E e);	// insertInOrder
	T_BSTN<E>* _insertAndRebal(T_BSTN<E>** ppTN, T_BSTN<E>* pPr, E e);		// insertAndRebal
	T_BSTN<E>* _rotate_LL(T_BSTN<E>* pCurSubRoot);				// 왼쪽-왼쪽 노드의 자리바꾸기 
	T_BSTN<E>* _rotate_RR(T_BSTN<E>* pCurSubRoot);				// 오른-오른 노드의 자리바꾸기
	T_BSTN<E>* _rotate_RL(T_BSTN<E>* pCurSubRoot);				// 오른-왼쪽 노드의 자리바꾸기
	T_BSTN<E>* _rotate_LR(T_BSTN<E>* pCurSubRoot);				// 왼쪽-오른 노드의 자리바꾸기
	int _Height(T_BSTN<E>* pTN);							// BST의 높이
	int _HeightDiff(T_BSTN<E>* pTN);						// BST의 높이(현재위치?)
	T_BSTN<E>* _reBalance(T_BSTN<E>** ppTN);			// 리밸런싱 함수
	void _print_with_Depth(T_BSTN<E>* pTN, ostream& ostr, int depth);		// 출력 함수
	void _print_inOrder(T_BSTN<E>* pTN, ostream& ostr);						// 출력 함수 2

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

	if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() == NULL))			// 자식노드들이 없다면
		newSubRoot = NULL;

	else if ((tobeErased->pLc() != NULL) && (tobeErased->pRc() == NULL))	// 왼쪽 자식노드만 있다면
	{
		newSubRoot = tobeErased->pLc();										// 지울 노드의 왼쪽노드를 가져와서
		newSubRoot->SetpPr(tobeErased->pPr());								// 지워질 노드의 부모노드와 이어줌
	}
	else if ((tobeErased->pLc() == NULL) && (tobeErased->pRc() != NULL))	// 오른쪽 자식노드만 있다면
	{
		newSubRoot = tobeErased->pRc();										// 지울 노드의 오른쪽노드를 가져와서
		newSubRoot->SetpPr(tobeErased->pPr());								// 지워질 노드의 부모노드와 이어줌
	}
	else
	{
		int h_diff = _HeightDiff(tobeErased);			// 자식노드의 크기를 비교함.

		T_BSTN<E>* parDel = tobeErased->pPr();
		T_BSTN<E>* lChild = tobeErased->pLc();
		T_BSTN<E>* rChild = tobeErased->pRc();
		T_BSTN<E>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<E>* ioPd = NULL, * lcIoPd, * parIoPd;

		if (h_diff > 0)			// 왼쪽 노드 트리가 더 크다면, 지워진 노드를 대체할 노드를 ioPd로 집어넣음
		{
			ioPd = _maxBSTN(lChild);			// 지워진 노드의 왼쪽 자식노드 트리중 가장 큰 값
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
			ioSs = _minBSTN(rChild); // 지워지는 노드의 오른쪽 자식노드 트리 중 가장 작은 값
			rcIoSs = ioSs->pRc(); parIoSs = ioSs->pPr();
			newSubRoot = ioSs;
			if (ioSs->pPr() != tobeErased)			// 만약 그 노드의 부모노드가 지워야할 노드가 아니라면
			{
				newSubRoot->SetpRc(rChild);			// ioSs의 오른쪽 노드를 지워야할 노드의 오른쪽 자식노드로 설정
				parIoSs->SetpLc(rcIoSs);			// ioSs의 부모노드의 왼쪽자식노드의 값을 ioSs의 오른쪽 자식노드로 설정
				if (rcIoSs != NULL)
					rcIoSs->SetpPr(parIoSs);		// 만약 rcIoSs의 부모노드를 ioSs의 부모노드로 설정
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
		// insert 함수 ( 이진탐색트리에 값을 집어넣음 )
// 1. 순서에 따른 값 집어넣기
// 2. 값을 집어넣고 리밸런싱을 함
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


// 출력 함수 인터페이스
// 1. 깊이에 따른 출력
// 2. 순서에 따른 출력 
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

	// 만약 받은 노드가 없다면
	if (pos == NULL)
	{
		pos = new T_BSTN<E>(e);			// 노드를 동적할당
		if (prPos == NULL)
			this->_root = pos;					// pos가 root노드가 된다. 
		pos->SetpPr(prPos);						// 부모노드로 설정
		*p = pos;
		num_entry++;							// 엔트리의 개수 1개 증가
		return pos;								// 반환
	}

	ent = **pos;

	// 받은 노드의 entry가 부모의 entry보다 더 작다면 왼쪽노드에 집어넣음 
	if (e < ent)
	{
		pChildPos = pos->ppLc();					// 위치는 왼쪽노드 (주소)
		newPos = _insertInOrder(pChildPos, pos, e);	// 한번더 체크 ( 더 밑으로 이어지는지 )
		if (newPos != NULL)
			pos->SetpLc(newPos);					// 만약 더이상 밑으로 내려갈 노드가 없다면 그 노드를 왼쪽으로 세팅
		return NULL;								// 반환
	}

	// 받은 노드의 entry가 부모의 entry보다 더 크다면 왼쪽노드에 집어넣음 
	else if (e >= ent)
	{
		pChildPos = pos->ppRc();					// 위치는 오른쪽노드 (주소)
		newPos = _insertInOrder(pChildPos, pos, e);		// 체크 ( 더 밑으로 이어지는가 ) 
		if (newPos != NULL)
			pos->SetpRc(newPos);					// 더이상 밑으로 내려가지 않는다면 오른쪽 노드에 세팅함
		return NULL;								// 반환
	}
}
template<typename E>
inline T_BSTN<E>* T_BST<E>::_insertAndRebal(T_BSTN<E>** ppTN, T_BSTN<E>* pPr, E e)
{
	T_BSTN<E>* pTN = NULL, ** ppLc = NULL, ** ppRc = NULL;
	E bstn_entry;

	// 현재 외부 노드를 새 트리노드에 연결함
	if (*ppTN == NULL)
	{
		pTN = new T_BSTN<E>(e);
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->SetpPr(pPr);				// 부모노드 설정
		(*ppTN)->SetpLc(NULL);				// 자식노드는 없으므로 NULL로 설정
		(*ppTN)->SetpRc(NULL);
		num_entry++;
		return *ppTN;						// 넣은 노드 반환
	}


	bstn_entry = **(*ppTN);				// 엔트리를 가져옴
	if (e < bstn_entry)
	{
		ppLc = (*ppTN)->ppLc();					// 만약 부모노드보다 엔트리값이 더 작다면 왼쪽 노드 주소를 가져오고 
		pTN = _insertAndRebal(ppLc, *ppTN, e);	// 더 밑으로 내려가면서 계속 넣을 곳을 찾는다
		if (ppTN != NULL)						// 만약 더 내려갈 곳이 없다면 
		{
			(*ppTN)->SetpLc(pTN);				// 노드를 넣음 
			*ppTN = _reBalance(ppTN);			// 위치 리밸런싱 한다.
		}
	}
	else
	{
		ppRc = (*ppTN)->ppRc();					// 부모노드 엔트리 값보다 크거나 같으면 오른쪽 노드 주소를 가져옴
		pTN = _insertAndRebal(ppRc, *ppTN, e);	// 계속 밑으로 내려간다.
		if (ppTN != NULL)						// 더 내려갈 곳이 없다면 
		{
			(*ppTN)->SetpRc(pTN);				// 오른쪽 노등에 세팅하고
			*ppTN = _reBalance(ppTN);			// 리밸런싱 함
		}
	}
	return *ppTN;
}


// rebalance
template<typename E>
inline T_BSTN<E>* T_BST<E>::_reBalance(T_BSTN<E>** ppTN)
{
	int heightDiff = 0;

	heightDiff = _HeightDiff(*ppTN);				// 높이 차이를 계산
	if (heightDiff > 1)								// 만약 1보다 크다면 
	{
		if (_HeightDiff((*ppTN)->pLc()) > 0)		// 왼쪽노드도 계산해서 높이차이가 양수라면
			*ppTN = _rotate_LL(*ppTN);				// 왼-왼 로테이션
		else
			*ppTN = _rotate_LR(*ppTN);				// 아니면 왼-오 로테이션
	}
	else if (heightDiff < -1)						// -1보다 작다면 오른쪽이다.
	{
		if (_HeightDiff((*ppTN)->pRc()) < 0)		// 오른쪽 자식노드도 계산하여 차이가 음수라면
			*ppTN = _rotate_RR(*ppTN);				// 오-오 로테이션
		else
			*ppTN = _rotate_RL(*ppTN);				// 오-왼 로테이션
	}
	return *ppTN;									// 반환
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
		h_Lc = _Height(pTN->pLc()); h_Rc = _Height(pTN->pRc());		// 재귀를 통해 자식노드들의 위치를 판별
		if (h_Lc > h_Rc)
			height = 1 + h_Lc;
		else
			height = 1 + h_Rc;
	}
	// 왼쪽, 오른쪽 중 가장 더 밑으로 내려간 노드를 기준으로 + 1한다.
	return height;
}
template<typename E>
inline int T_BST<E>::_HeightDiff(T_BSTN<E>* pTN)
{
	int h_diff = 0;
	if (pTN == NULL)
		return 0;
	h_diff = _Height(pTN->pLc()) - _Height(pTN->pRc());

	// 구한 왼쪽 노드의 높이와 오른쪽 노드의 높이를 구해 차를 계산
	return h_diff;
}

// print function 
template<typename E>
inline void T_BST<E>::_print_with_Depth(T_BSTN<E>* pTN, ostream& ostr, int depth)
{
	T_BSTN<E>* pRc, * pLc;

	if ((pRc = pTN->pRc()) != NULL)
		_print_with_Depth(pRc, ostr, depth + 1);				// 오른쪽 노드 출력
	for (int i = 0; i < depth; i++)
	{
		ostr << "    ";										// 탭 키로 간격 벌리기
	}
	ostr << **pTN << endl;
	if ((pLc = pTN->pLc()) != NULL)							// 왼쪽 노드 출력
		_print_with_Depth(pLc, ostr, depth + 1);
}
template<typename E>
inline void T_BST<E>::_print_inOrder(T_BSTN<E>* pTN, ostream& ostr)
{
	T_BSTN<E>* pRc, * pLc;
	if ((pLc = pTN->pLc()) != NULL)
		_print_inOrder(pLc, ostr);						// 왼쪽 노드 출력
	ostr << **pTN << " ";						// 중간 노드 출력
	if ((pRc = pTN->pRc()) != NULL)
		_print_inOrder(pRc, ostr);						// 오른쪽 노드 출력
}


#endif // !T_BST_H


