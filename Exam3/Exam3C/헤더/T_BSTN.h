#ifndef T_BSTN_H
#define T_BSTN_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template <typename E>
class T_BSTN
{
public:
	// constructor 
	T_BSTN()					// default constructor
		: entry(), pPR(NULL), pLC(NULL), pRC(NULL) {};
	T_BSTN(E e) 	// constructor
		: entry(e), pPR(NULL), pLC(NULL), pRC(NULL) {};

	// setter
	void SetpPr(T_BSTN<E>* pTN) { pPR = pTN; }
	void SetpLc(T_BSTN<E>* pTN) { pLC = pTN; }
	void SetpRc(T_BSTN<E>* pTN) { pRC = pTN; }
	void SetEntry(E e) { entry = e; }

	// getter
	T_BSTN<E>* pPr() const { return pPR; }				// �θ���
	T_BSTN<E>* pLc() const { return pLC; }				// ���� �ڽĳ��
	T_BSTN<E>* pRc() const { return pRC; }				// ������ �ڽĳ��	
	T_BSTN<E>** ppLc() { return &pLC; }			// ���� �ڽĳ���� �ּ�
	T_BSTN<E>** ppRc() { return &pRC; }			// ������ �ڽĳ���� �ּ�

	// operator overloading
	E& operator*() { return entry; }

private:
	E				entry;		// element value  
	T_BSTN<E>*		pPR;		// parent pointer
	T_BSTN<E>*		pLC;		// left child pointer
	T_BSTN<E>*		pRC;		// right child pointer
};
#endif // !T_BST_H