/* Exam2B - TrieNode.h */

#ifndef TRIE_NODE_H
#define TRIE_NODE_H
#include <iostream>
#include <string>
#include <list>
#define VALUE_INTERNAL_NODE NULL

using namespace std;

class TrieNode_pStr
{
public:
	TrieNode_pStr() {} // default constructor
	TrieNode_pStr(char k, string* v) : keyChar(k), value(v) { prev = next = parent = child = NULL; }
	void setKeyChar(char k) { keyChar = k; }
	void setValue(string* v) { value = v; }
	void setNext(TrieNode_pStr* nxt) { next = nxt; }
	void setPrev(TrieNode_pStr* pv) { prev = pv; }
	void setParent(TrieNode_pStr* pr) { parent = pr; }
	void setChild(TrieNode_pStr* chld) { child = chld; }
	char getKeyChar() { return keyChar; }
	string* getValue() { return value; }
	TrieNode_pStr* getPrev() { return prev; }
	TrieNode_pStr* getNext() { return next; }
	TrieNode_pStr* getParent() { return parent; }
	TrieNode_pStr* getChild() { return child; }
	void _fprint(ostream& fout, TrieNode_pStr* pTN, int indent);

private:
	char keyChar;
	string* value;
	TrieNode_pStr* prev;
	TrieNode_pStr* next;
	TrieNode_pStr* parent;
	TrieNode_pStr* child;
};

inline void TrieNode_pStr::_fprint(ostream& fout, TrieNode_pStr* pTN, int indent)
{
	if (pTN == NULL)
	{
		fout << endl;
		return;

	}
	else
	{
		fout << pTN->getKeyChar();
		this->_fprint(fout, pTN->getChild(), indent + 1); // 자식 노드 출력
		if (pTN->getNext() == NULL)
			return;
		for (int i = 0; i < indent; i++)
			fout << "\t";
		this->_fprint(fout, pTN->getNext(), indent);	// 다음 노드 출력
	}
}
// . . .  필요한 부분은 직접 추가 구현 할 것

#endif