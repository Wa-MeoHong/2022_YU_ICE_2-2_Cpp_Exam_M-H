#ifndef T_ARRAY_H
#define T_ARRAY_H

#include "Student.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ��������, ��������
enum SortingOrder { INCREASING = 0, DECREASING = 1 };

template <typename T, typename K>			// Ŭ������ ���ø����� ������
class T_Array
{
public:
	// constructor
	T_Array();								// �⺻ ������
	T_Array(int capa, string n);			// ���ڸ� ���� ������

	// destructor
	~T_Array();

	// getter
	int size() { return num_elements; }		// num_elements ��ȯ
	string Name() { return name; }			// �̸�
	bool empty() { return num_elements == 0; } // ����ִ��� Ȯ��

	// member functions
	void reserve(int new_capacity);			// �뷮 �缳�� �Լ�
	void insert(int i, T element);			// �� ���� �Լ�
	void remove(int i);						// �� ���� �Լ�
	T& at(int i);							// �迭 ���� ��ȯ
	void set(int i, T& element);			// �迭 ���� 
	T& Min(int begin, int end, string KeyName);				// �迭�� �ּҰ�
	T& Max(int begin, int end, string KeyName);				// �迭�� �ִ밪 
	void print(int elements_per_line);	// �迭 ���
	bool isValidIndex(int index);			// �ε�����ȣ ��ȿ�� �˻�
	int sequential_Search(string KeyName, K& search_key);	// ���� Ž��
	int binary_Search(string KeyName, K& search_key);		// ���� Ž��

	// Sorting
	void shuffle();							// �迭 �ڼ���
	void selection_sort(string KeyName, SortingOrder order = INCREASING);	// ��������
	void merge_sort(string KeyName, SortingOrder order = INCREASING);		// ��������
	void quick_sort(string KeyName, SortingOrder order = INCREASING);		// ������

	T& operator[](int index);				// �迭�� ��ȯ

private:
	void _mergeSort(T* arr, T* tmp_array, int left, int right, string KeyName, SortingOrder order);
	T* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename T, typename K>
int _partition(T* array, int size, int left, int right, int PivotIndex, string KeyName, SortingOrder order);
template<typename T, typename K>
void _quickSort(T* array, int size, int left, int right, string KeyName, SortingOrder order);

/*				constructor ( ������ )
		1. default constructor ( ����Ʈ ������ )
		2. �뷮, �̸��� ���� constructor				*/
template<typename T, typename K>
inline T_Array<T, K>::T_Array()
{
	// t_array�� NULL, �������� 0���� �ʱ�ȭ
	t_array = NULL;
	num_elements = 0;
	capacity = 0;
	name = "";
}
template<typename T, typename K>
inline T_Array<T, K>::T_Array(int capa, string n)
{
	capacity = capa;						// �뷮 ����
	t_array = new T[capacity];				// �迭 �����Ҵ�
	if (t_array == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	num_elements = 0;
	name = n;
}

/*				destructor ( �Ҹ��� )				*/
template<typename T, typename K>
inline T_Array<T, K>::~T_Array()
{
	if (t_array != NULL)			// ���� �迭�� �����Ѵٸ� delete
		delete[] t_array;
}

/*					���� ���� �Լ�
		1. isValidIndex(index) : �ε�����ȣ ��ȿ�� �˻�
		2. reserve (new_capacity) : �뷮 ����
		3. insert (i, element) : ���ڸ� ����
		4. remove (i) : i��° ���ڸ� ����
		5. at(i) : �迭�� ���� ��ȯ��
		6. set(i, element) : �迭�� ���� ������
		7. Min(), Max() : �ּҰ�, �ִ밪
		8. fprint(fout, elemnets_per_line) : �迭 ���
		7. ����Ž��, ����Ž��							*/

template<typename T, typename K>
inline bool T_Array<T, K>::isValidIndex(int index)
{
	// �ε�����ȣ�� 0 ~ capacity - 1���̿� �ִٸ� true, �ƴϸ� false
	if (index >= 0 && index < capacity)
		return true;
	else
		return false;
}
template<typename T, typename K>
inline void T_Array<T, K>::reserve(int new_capacity)
{

	if (capacity >= new_capacity)
		return;						// �뷮�� ����ϹǷ� �ʿ����

	T* old_array = this->t_array;						// �õ��� �ڷḦ ����
	this->t_array = new T[new_capacity];				// ���ο� �뷮�� �迭 ����
	if (t_array == NULL)								// �迭 ���� ���н� ����
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	cout << this->Name() << " expands capacity to " << new_capacity << endl;

	// ������ ������ ��� ����
	for (int i = 0; i < this->num_elements; i++)
		t_array[i] = old_array[i];

	delete[] old_array;			// ������ �迭�� delete
	capacity = new_capacity;	// ���ο� �뷮���� ���� 
}
template<typename T, typename K>
inline void T_Array<T, K>::insert(int i, T element)
{
	// ���� �뷮�� ���� �� ���� ���� ���ٸ�
	if (num_elements >= capacity)
	{
		int new_capa;
		new_capa = 2 * capacity;	// ���Ӱ� �뷮�� 2��� �ø� ��, �ٽ� ����
		reserve(new_capa);			// reserve �Լ� ȣ��
	}

	if (isValidIndex(i))			// �뷮�� �ø���(����) �ε��� ��ȣ �˻�
	{
		for (int j = this->num_elements - 1; j >= i; j--)	// i��° ������ ������ ���� ��ĭ�� �о���
			t_array[j + 1] = t_array[j];
		t_array[i] = element;			// ����ִ� i��°�� ���� ����
		num_elements++;						// num_elements�� ����
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::remove(int i)
{
	// ��ȿ�� ������ Ȯ�� ��
	if (isValidIndex(i))
	{
		// i��° ���� ���� ��� ��ܼ� i��°�� ���� ����
		for (int j = i + 1; j < num_elements; j++)
			t_array[j - 1] = t_array[j];
		num_elements--;			// ���� ����
	}
	// ���� �迭�� ������ 2���� 1���϶�� �뷮�� ����.
	if (num_elements < (capacity / 2))
	{
		int new_capa = capacity / 2;	// 2���� 1���� �뷮
		T* t_newAR = (T*) new T[new_capa];		// ���Ӱ� �迭 ����
		if (t_newAR == NULL)
		{
			cout << "Error in realloc new array!!" << endl;
			return;
		}

		// �迭�� ���� ���ο� �迭�� ����
		for (int i = 0; i < num_elements; i++)
			t_newAR[i] = t_array[i];

		// ������ �迭�� ����
		delete[] t_array;
		t_array = t_newAR;
		capacity = new_capa;
	}
}
template<typename T, typename K>
inline T& T_Array<T, K>::at(int i)
{
	if (isValidIndex(i))
		return t_array[i];			// �ε��� ��ȣ�� ��ȿ�ϸ� �迭�� ���� ��ȯ
	else
		return 0;
}
template<typename T, typename K>
inline void T_Array<T, K>::set(int i, T& element)
{
	if (isValidIndex(i))
	{
		t_array[i] = element;		// �ε��� ��ȣ�� ��ȿ�ϸ� �迭�� ���� ������
	}
	else
		return 0;
}
template<typename T, typename K>
inline T& T_Array<T, K>::Min(int begin, int end, string KeyName)
{
	int index_min;					// �ּҰ� �ε��� ��ȣ
	K minKey, Key;

	// �ʱⰪ ����
	t_array[begin]->getKey(KeyName, &minKey); // �ε��� ��ȣ, Ű���� ȹ��
	index_min = begin;
	for (int i = begin + 1; i < end; i++)
	{
		t_array[i]->getKey(KeyName, &Key);
		// ���� Key�� minKey���� ������
		if (Key < minKey)
		{
			minKey = Key;				// �ּҰ� Ű�� ���Ӱ� ����
			index_min = i;				// �ε�����ȣ�� ����
		}
	}

	return t_array[index_min];			// �ּҰ� ��ȯ
}
template<typename T, typename K>
inline T& T_Array<T, K>::Max(int begin, int end, string KeyName)
{
	int index_max;					// �ִ밪 �ε��� ��ȣ
	K maxKey, Key;					// �ε��� ���� Ű

	// �ʱⰪ ����
	t_array[begin]->getKey(KeyName, &maxKey); // �ε��� ��ȣ, Ű���� ȹ��
	index_max = begin;
	for (int i = begin + 1; i < end; i++)
	{
		t_array[begin]->getKey(KeyName, &Key); // �ε��� ��ȣ, Ű���� ȹ��
		// ���� max_value���� t_array[i]�� ũ��
		if (Key > maxKey)
		{
			maxKey = Key;				// �ִ밪 Ű�� ���Ӱ� ����
			index_max = i;				// �ε�����ȣ�� ����
		}
	}

	return t_array[index_max];			// �ִ밪 ��ȯ
}
template<typename T, typename K>
inline void T_Array<T, K>::print(int elements_per_line)
{
	int count = 0;
	// ��� 
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			// ��ü ���, ���ٿ� �������� ����ϱ� ������ endl�� ���� ����
			cout << *t_array[count] << " ";
			count++;
			// ����, ������ ����� �� �������� endl;�� ����
			if (count % elements_per_line == 0)
				cout << endl;
		}
	}
	cout << endl;
}
template<typename T, typename K>
inline int T_Array<T, K>::sequential_Search(string KeyName, K& search_key)		// ����Ž��
{
	string keytype;
	K key = NULL;

	// �ϳ��ϳ� �� ���캽
	for (int index = 0; index < num_elements; index++)
	{
		t_array[index]->getKey(KeyName, &key);
		if (key == search_key)		// ���� �Ȱ������� ã�� �ȴٸ� index�� ��ȯ
			return index;
	}
	return -1;			// ������ -1 ��ȯ
}
template<typename T, typename K>
inline int T_Array<T, K>::binary_Search(string KeyName, K& search_key)
{
	int low, mid, high;
	int loop = 1;

	// �ʱⰪ ���� (low = 0, high = num_elements - 1)
	low = 0; high = num_elements - 1;
	K mid_key = NULL;

	while (low <= high)					// �ο�� ���̰� ������ ������
	{
		// mid �� ���� 
		mid = (low + high) / 2;

		// Ű ȹ��
		t_array[mid]->getKey(KeyName, &mid_key);
		// ���� search_key�� mid���� �۴ٸ�, high�� ����
		if (mid_key > search_key)
			high = mid - 1;
		// ���� search_key�� mid���� ũ�ٸ�, low�� ����
		else if (mid_key < search_key)
			low = mid + 1;
		else
			return mid;			// ���ٸ� mid ��ȯ
		loop++;
	}

	return -1;
}

/*							���� ���� �Լ�
		1. shuffle() : �迭 ���� �Լ�
		2. selection_sort(order) : ����/���������� ���� ��������
		3. merge_sort()	: ��������
		4. _mergeSort() : �������� ���Լ�
		3. quick_sort(order) : ����/������������ ������
		4. _quicksort() : ������ ���Լ�
		5. _partition()	: �迭 �߰����� �������� ���ǿ� �°� �з�			*/
template<typename T, typename K>
inline void T_Array<T, K>::shuffle()
{
	srand((unsigned int)time(NULL));		// �õ� ����
	int index1, index2;						// �ε��� ��ȣ 1, 2
	T temp;									// �Űܴٴ� ���� temp

	for (int i = 0; i < num_elements; i++)
	{
		// �ε���1 , �ε���2 ����
		index1 = (((unsigned int)rand() << 15) | rand()) % num_elements;
		index2 = (((unsigned int)rand() << 15) | rand()) % num_elements;

		// swaping
		temp = t_array[index1];
		t_array[index1] = t_array[index2];
		t_array[index2] = temp;
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::selection_sort(string KeyName, SortingOrder order)
{
	int In_Min, In_Max;
	T tempElement;
	K minKey, maxKey, Key;

	for (int i = 0; i < num_elements - 1; i++)
	{
		// �������� ����
		if (order == INCREASING)
		{
			// Min �κ� �ʱⰪ ����
			In_Min = i;
			t_array[i]->getKey(KeyName, &Key); // �ε��� ��ȣ, Ű���� ȹ��
			minKey = (K)Key;			// �ּ��� Ű �� ���

			for (int j = i + 1; j < num_elements; j++)
			{
				this->t_array[j]->getKey(KeyName, &Key); // �ε��� ��ȣ, Ű���� ȹ��
				// ���� ���� �� ã��
				if ((K)Key < minKey)			// Ű�� ���Ͽ�, ���ο� ���� ������ ����
				{
					minKey = (K)Key;			// Ű ����
					In_Min = j;
				}
			}
			// Swaping
			if (In_Min != i)
			{
				tempElement = t_array[In_Min];
				t_array[In_Min] = t_array[i];
				t_array[i] = tempElement;
			}
		}

		// �������� ����
		else
		{
			// Max �κ� �ʱⰪ ����
			In_Max = i;
			this->t_array[i]->getKey(KeyName, &Key); // �ε��� ��ȣ, Ű���� ȹ��
			maxKey = (K)Key;			// �ִ��� Ű �� ���

			for (int j = i + 1; j < num_elements; j++)
			{
				this->t_array[j]->getKey(KeyName, &Key); // �ε��� ��ȣ, Ű���� ȹ��
				// ���� ū Ű ã��
				if ((K)Key > maxKey)			// Ű�� ���Ͽ�, ���ο� ���� ũ�� ����
				{
					maxKey = (K)Key;			// Ű ����
					In_Max = j;
				}
			}
			// Swaping
			if (In_Max != i)
			{
				tempElement = t_array[In_Max];
				t_array[In_Max] = t_array[i];
				t_array[i] = tempElement;
			}
		}
	}
}
template<typename T, typename K>
inline void T_Array<T, K>::merge_sort(string KeyName, SortingOrder order)
{
	T* tmp_array = new T[num_elements];
	if (tmp_array == NULL)
	{
		cout << "ERROR in creation tmp_array!!" << endl;
		exit(-1);
	}

	_mergeSort(t_array, tmp_array, 0, size() - 1, KeyName, order);
	delete[] tmp_array;
}
template<typename T, typename K>
inline void T_Array<T, K>::_mergeSort(T* arr, T* tmp_array, int left, int right, string KeyName, SortingOrder order)
{
	K key_i, key_j;

	if (left >= right)				// ���� �迭�� ���Ұ� 1����� ��ġ ��
		return;

	int mid = (left + right) / 2;
	_mergeSort(arr, tmp_array, left, mid, KeyName, order);		// ���� 
	_mergeSort(arr, tmp_array, mid + 1, right, KeyName, order);		// ������ �� 


	for (int i = left; i <= mid; i++)						// ������ ������� �ӽ� �迭�� �־���
		tmp_array[i] = arr[i];
	for (int j = 1; j <= right - mid; j++)					// �������� ����(�߿�)���� �ӽù迭�� �־���
		tmp_array[right - j + 1] = arr[j + mid];

	// [1, 5, 2, 9, ----- ] �� [1, 5, 9, 2, -----]

	for (int i = left, j = right, k = left; k <= right; k++)	// �߰� ��������
	{
		tmp_array[i]->getKey(KeyName, &key_i);
		tmp_array[j]->getKey(KeyName, &key_j);
		// Ű�� ���Ͽ� ���� ���� ���ʺ��� �־���, ū���� �����ʺ��� �־��� (�������� ����)
		if (order == INCREASING)
		{
			if ((K)key_i < (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
		else
		{
			if ((K)key_i > (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
	}

}
template<typename T, typename K>
inline void T_Array<T, K>::quick_sort(string KeyName, SortingOrder order)
{
	_quickSort(t_array, size(), 0, size() - 1, KeyName, order);
}
template<typename T, typename K>
inline void _quickSort(T* array, int size, int left, int right, string KeyName, SortingOrder order)
{
	int P_I, newPI;

	if (left >= right)							// ���� left�� right���� ũ�ų� ���ٸ� newPI��ȯ ����, ���� left�� 1Ȥ�� 0�϶��̴�..
		return;

	else if (left < right)
	{
		P_I = (left + right) / 2;				// �߰���, ���� Ȧ���ΰ�� ���������� ��������ġ�� ����
	}

	newPI = _partition(array, size, left, right, P_I, KeyName, order);

	// �̷��� ����, ������ ������� �������� �� ū����
	if (left < (newPI - 1))									// ���� newPI�������� ���ʺκ�
	{
		_quicksort(array, size, left, newPI - 1, KeyName, order);
		// �ٽ� newPI�� �����ϸ鼭 ũ�������� �����ش�.
	}
	if ((newPI + 1) < right)								// ����, ������ quickSort�� ������, newPI���� ������ �κ�
	{
		_quicksort(array, size, newPI + 1, right, KeyName, order);
		// ���������� newPI����� ũ������� �������ش�.
	}
}
template<typename T, typename K>
inline int _partition(T* array, int size, int left, int right, int PivotIndex, string KeyName, SortingOrder order)
{
	int newPI;
	T PivotValue, temp;							// PivotValue = �ٲٴ� ����
	K key = NULL, key_val = NULL;

	PivotValue = array[PivotIndex];
	PivotValue.getKey(KeyName, &key_val);		// PivotValue Ű ���� ����

	array[PivotIndex] = array[right];
	array[right] = PivotValue;
	// �� ó�� PivotIndex�� �ִ� ���� �� ������(Ȥ�� P_I-1��ġ�� �ִ� ��)�� �ٲ۴�

	newPI = left;						// ���� ���ο� �ǹ���ġ�� �������ִµ� �ʱⰪ�� �� ����(Ȥ�� P_I + 1��ġ)���� ����
	for (int i = left; i <= right - 1; i++)
		// �ǵڷ� ���Ե� PivotValue�� ���� ������ �迭���� ������ ��´�.
	{
		array[i].getKey(KeyName, &key);

		if (order == INCREASING)
		{
			if ((K)key <= (K)key_val)								// ���� key_val���� key ���� �۴ٸ�
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
				newPI += 1;
			}
		}
		else
		{
			if ((K)key > (K)key_val)								// ���� key_val���� key ���� �۴ٸ�
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;							// ����(i)��ġ�� �ִ� ���� newPI�� �ִ� ������ �ٲ��ش�.
				newPI += 1;
			}
		}
	}
	// ��������� ó�� PivotValue���� �������� ������ PivotValue���� ���� ������ �迭, �������� PivotValue���� ū ������ �迭�� �����Ǿ���.
	PivotValue = array[right];
	array[right] = array[newPI];
	array[newPI] = PivotValue;

	return newPI;											// newPI ��ȯ
}

// operator overloading []
template<typename T, typename K>
inline T& T_Array<T, K>::operator[](int index)
{
	// �ε��� ��ȣ�� ��ȿ�ϸ� �� ��ȯ
	if (isValidIndex(index))
		return t_array[index];
	// �ƴϸ� �����ڵ� ����� Ż��
	cout << "Error in index!!" << endl;
	exit(-1);
}

#endif // !T_ARRAY_H