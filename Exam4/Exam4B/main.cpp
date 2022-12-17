/* 이름 : 신대홍 학번 : 21912193
	날짜 : 2022. 12. 16 (금)
	제목 : Exam4B_21912193_신대홍
	내용 : Trie을 이용하여 문자 출력
	- 비고 : 시험 후, 오타 수정으로 완성
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "Trie.h"
#include "TrieNode.h"

using namespace std;
#define NUM_SAMPLE_TEXTS 100
#define NUM_TEST_PREFIX 3

void main()
{
	Trie_pStr trie_PredictText("Trie_PredictiveText");
	TrieNode_pStr* pTN;
	int word_count;
	string keyStr, prefixStr;
	List_pStr predictTexts;
	List_pStr_Iter itr;

	cout << "2022-2 객체지향 프로그래밍과 자료구조 기말고사 학번:21912193 성명:신대홍" << endl;
	/* Testing Basic Operation in trie */
	string sample_texts[] =
	{
		"abcd", "abc", "ab", "a", "alpha", "WXYZ", "WXY", "WX", "W", "bcd", "bc", "binary", "bit", "bravo",
		"-1"
	};
	cout << "Inserting keywords (texts) into " << trie_PredictText.getName() << " ..... " << endl;

	for (int i = 0; i < NUM_SAMPLE_TEXTS; i++)
	{
		keyStr = sample_texts[i];
		if (keyStr == "-1")
			break;
		trie_PredictText.insert(keyStr, &sample_texts[i]);
	}
	trie_PredictText.fprintTrie(cout);

	/* testing keyWord search in trie */
	string testPrefix[NUM_TEST_PREFIX] = { "W", "a", "b" };
	for (int i = 0; i < NUM_TEST_PREFIX; i++)
	{
		predictTexts.clear();
		prefixStr = testPrefix[i];
		trie_PredictText.findPrefixMatch(prefixStr, predictTexts);
		cout << "Predictive words that starts with with (" << prefixStr << ") : ";
		itr = predictTexts.begin();
		for (int i = 0; i < predictTexts.size(); i++)
		{
			keyStr = *(*itr);
			cout << keyStr << ", ";
			++itr;
		}
		cout << endl;
	}
}
