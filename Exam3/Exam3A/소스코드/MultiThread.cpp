#include <Windows.h>
#include "MultiThread.h"
#include "CirQ.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void Thread_DataGen(ThreadParam* pParam)
{
	// thread parameter 
	int myAddr = pParam->myAddr;
	int maxround = pParam->maxRound;
	TA_CirQ<int>* pCirQ = pParam->pTA_CirQ;
	int targetGenData = pParam->targetGenData;
	ThreadMon* pThrdMon = pParam->pThrdMon;

	// function parameters
	int genData = 0;
	int genDataCount = 0;

	// activated printed
	pParam->pThrdMon->mtx_console.lock();
	cout << "Thread_DataGen[" << myAddr << "] is activated now ..." << endl;
	pParam->pThrdMon->mtx_console.unlock();

	// �ݺ��� ����
	for (int round = 0; round < maxround; round++)
	{
		if (genDataCount >= targetGenData)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				sleep_for(std::chrono::milliseconds(500));
				continue;
			}
		}

		// �̺�Ʈ ����
		genData = round + myAddr * pParam->targetGenData;
		while (pCirQ->enqueue(genData) == NULL)				// �̺�Ʈ�� ������� ���ߴٸ�
			sleep_for(std::chrono::milliseconds(100));		// ��� ����.
		pParam->pThrdMon->mtx_console.lock();
		cout << "Input Success! - Thrd_DataGen[" << myAddr << "] !" << endl;	// ���
		pParam->pThrdMon->mtx_console.unlock();

		// ���� ����͸� ������ �������
		pThrdMon->mtx_thrd_mon.lock();
		pThrdMon->numGenData[myAddr]++;
		pThrdMon->genDataArray[myAddr][round] = genData;
		pThrdMon->totalNumGenData++;
		pThrdMon->mtx_thrd_mon.unlock();

		genDataCount++;

		sleep_for(std::chrono::milliseconds(10));

	}
	
}

void Thread_DataProc(ThreadParam* pParam)
{
	// thread parameter 
	int myAddr = pParam->myAddr;
	int maxround = pParam->maxRound;
	TA_CirQ<int>* pCirQ = pParam->pTA_CirQ;
	int targetGenData = pParam->targetGenData;
	ThreadMon* pThrdMon = pParam->pThrdMon;

	// function parameters
	int* pDeQ_data = NULL;
	int procData = 0;

	// activated printed
	pThrdMon->mtx_console.lock();
	cout << "Thread_DataProc[" << myAddr << "] is activated now ..." << endl;
	pThrdMon->mtx_console.unlock();

	for (int round = 0; round < maxround; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if (!pCirQ->isEmpty())
		{
			while ((pDeQ_data = pCirQ->dequeue()) == NULL)		// Dequeue�� �����ϸ� �ٽ� �ݺ��غ���.
			{
				sleep_for(std::chrono::milliseconds(10));
				continue;
			}
			//pDeQ_data = pCirQ->dequeue();				// �̺�Ʈ ó��
			
			procData = *pDeQ_data;

			// ���� thrdMon�� �������
			pThrdMon->mtx_thrd_mon.lock();
			pThrdMon->numProcData[myAddr]++;
			pThrdMon->procDataArray[myAddr][round] = procData;
			pThrdMon->totalNumProcData++;
			pThrdMon->mtx_thrd_mon.unlock();
		}

		sleep_for(std::chrono::milliseconds(10 + rand() % 10));
	}
}