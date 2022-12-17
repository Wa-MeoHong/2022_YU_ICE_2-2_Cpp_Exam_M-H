/* �̸� : �Ŵ�ȫ �й� : 21912193
	��¥ : 2022. 12. 16 (��)
	���� : Exam4B_21912193_�Ŵ�ȫ
	���� : Trie�� �̿��Ͽ� ���� ���
	- ��� : ���� ��, ��Ÿ �������� �ϼ�
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

	cout << "2022-2 ��ü���� ���α׷��ְ� �ڷᱸ�� �⸻��� �й�:21912193 ����:�Ŵ�ȫ" << endl;
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
