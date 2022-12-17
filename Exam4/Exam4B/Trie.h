/* Exam2B - Trie.h */

#ifndef Trie_H
#define Trie_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#define MAX_STR_LEN 50

#define SIMPLIFIED

//#define DEBUG
using namespace std;

typedef list<string*> List_pStr;
typedef list<string*>::iterator List_pStr_Iter;
enum SearchMode { FULL_MATCH, PREFIX_MATCH };
class Trie_pStr
{
public:
	Trie_pStr(string name) // constructor
	{
		trie_name = name;
		_root = new TrieNode_pStr('\0', NULL);
		_root->setKeyChar('\0');
		_root->setPrev(NULL);
		_root->setNext(NULL);
		_root->setParent(NULL);
		_root->setChild(NULL);
		num_keyWords = 0;
	}
	int size() { return num_keyWords; }
	string getName() { return trie_name; }
	void insert(string keyStr, string* value);
	void insertExternalTN(TrieNode_pStr* pTN, string keyStr, string* value);
	TrieNode_pStr* find(string keyStr);
	void findPrefixMatch(string prefix, List_pStr& predictVocas);
	//void deleteKeyStr(string keyStr);
	//void eraseTrie();
	void fprintTrie(ostream& fout);
protected:
	TrieNode_pStr* _find(string keyStr, SearchMode sm = FULL_MATCH);
	void _traverse(TrieNode_pStr* pTN, List_pStr& list_keywords);
private:
	TrieNode_pStr* _root; // _root trie node
	int num_keyWords;
	string trie_name;
};

inline void Trie_pStr::insert(string keyStr, string* value)
{
	TrieNode_pStr* pTN = NULL, * pTN_New = NULL;
	char* keyPtr = (char*)keyStr.c_str();

	if (keyPtr == NULL)
		return; // 받은 키가 없다면 바로 탈출

	if (this->find(keyStr) != NULL)
	{
		return; // 받은 키가 있지만 완전일치하는 키가 없는 경우에도 탈출
	}
	pTN = this->_root;
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		if (pTN->getKeyChar() < *keyPtr && pTN->getNext() == NULL && *keyPtr != '\0')
			break;
		while (pTN->getKeyChar() < *keyPtr && pTN->getNext() != NULL)
			pTN = pTN->getNext();
		while (pTN != NULL && pTN->getKeyChar() == *keyPtr && *keyPtr != '\0')
		{
			pTN = pTN->getChild();
			keyPtr++;
		}

		if (pTN->getKeyChar() > *keyPtr && *keyPtr != '\0')
			break;
	}
	// insert 진행
	// 이미 들어간 단어 끝에 더 들어가는 경우
	if (pTN->getKeyChar() != '\0' && *keyPtr == '\0')
	{
		pTN_New = new TrieNode_pStr('\0', value);
		pTN_New->setParent(pTN->getParent());
		(pTN->getParent())->setChild(pTN_New);
		pTN_New->setNext(pTN);
		this->num_keyWords++;
		return;
	}

	else if (pTN->getKeyChar() < *keyPtr && pTN->getNext() == NULL && *keyPtr != '\0')
	{
		pTN_New = new TrieNode_pStr(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setParent(pTN->getParent());
		pTN_New->setPrev(pTN);
		pTN->setNext(pTN_New);
		pTN = pTN_New;
		keyPtr++;

		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode_pStr(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}

		if (*keyPtr == '\0')
		{
			this->insertExternalTN(pTN, keyStr, value);
			this->num_keyWords++;
			return;
		}

	}
	else if (pTN->getKeyChar() > *keyPtr && *keyPtr != '\0')
	{
		pTN_New = new TrieNode_pStr(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setNext(pTN);
		pTN_New->setParent(pTN->getParent());

		if (pTN->getPrev() == NULL)
		{
			if (pTN->getParent() != NULL)
				(pTN->getParent())->setChild(pTN_New);
		}
		else
			(pTN->getPrev())->setNext(pTN_New);
		pTN_New->setPrev(pTN->getPrev());
		pTN->setPrev(pTN_New);
		pTN = pTN_New;

		keyPtr++;
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode_pStr(*keyPtr, VALUE_INTERNAL_NODE);
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')
		{
			this->insertExternalTN(pTN, keyStr, value);
			this->num_keyWords++;
			return;
		}
	}
}

inline void Trie_pStr::insertExternalTN(TrieNode_pStr* pTN, string keyStr, string* value)
{
	TrieNode_pStr* pTN_New = NULL;

	pTN_New = new TrieNode_pStr('\0', NULL);
	pTN->setChild(pTN_New);
	(pTN->getChild())->setParent(pTN);
	pTN_New->setValue(value);
}

inline TrieNode_pStr* Trie_pStr::find(string keyStr)
{
	return nullptr;
}

inline void Trie_pStr::findPrefixMatch(string prefix, List_pStr& predictVocas)
{
	TrieNode_pStr* pPtr = NULL, * pTN = NULL;
	string keyPtr;

	TrieNode_pStr* found = NULL;
	keyPtr = prefix;

	if (prefix.empty())
		return;
	pTN = this->_root;
	pTN = _find(prefix, PREFIX_MATCH);
	this->_traverse(pTN, predictVocas);
}

inline void Trie_pStr::fprintTrie(ostream& fout)
{
	TrieNode_pStr* pTN;
	int line = 1, indent = 0;

	fout << "Trie (" << getName() << ") with " <<
		this->num_keyWords << " trie_nodes\n";

	if (this->num_keyWords == 0)
	{
		fout << "empty!!";
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}

inline TrieNode_pStr* Trie_pStr::_find(string keyStr, SearchMode sm)
{
	const char* keyPtr;
	TrieNode_pStr* pTN = NULL, * found = NULL;

	if (keyStr.empty())
	{
		return NULL;
	}
	keyPtr = (char*)keyStr.c_str();
	pTN = this->_root;

	while (pTN != NULL && *keyPtr != '\0')
	{
		while (pTN != NULL && pTN->getKeyChar() < *keyPtr)
		{
			if (pTN->getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();


		}

		if (pTN != NULL && pTN->getKeyChar() > *keyPtr)
			return NULL;
		else if (pTN->getKeyChar() == NULL && *keyPtr != '\0')
			return NULL;
		else if (pTN->getKeyChar() == *keyPtr && *keyPtr != '\0')
		{
			pTN = pTN->getChild();
			keyPtr++;
			if (*keyPtr == '\0')
			{
				if (sm == FULL_MATCH)
				{
					if (pTN->getKeyChar() == '\0')
						return pTN;
					else
						return NULL;
				}
				else if (sm == PREFIX_MATCH)
				{
					return pTN;
				}
			}
			else if (pTN->getKeyChar() == '\0' && *keyPtr != '\0')
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext();
					continue;
				}
				else
					return NULL;
			}
			else
				continue;
		}
	}
}

inline void Trie_pStr::_traverse(TrieNode_pStr* pTN, List_pStr& list_keywords)
{
	if (pTN == NULL)
		return;
	if (pTN->getChild() == NULL)
		list_keywords.push_back(pTN->getValue());
	else
		this->_traverse(pTN->getChild(), list_keywords);
	if (pTN->getNext() != NULL)
		this->_traverse(pTN->getNext(), list_keywords);

}


#endif