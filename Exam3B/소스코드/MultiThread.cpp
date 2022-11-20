#include "MultiThread.h"
#include "HeapPrioQueue.h"
#include "T_Array.h"
#include "SimParam.h"

using namespace std;
using std::this_thread::sleep_for;

void Thread_DataGen(ThreadParam* pParam)
{
	//get paramater-----------------------------------------------
	HeapPrioQueue<int>* pPriQ = pParam->pPriQ; //event pointer
	int myAddr = pParam->myAddr;
	int max_round = pParam->maxRound;
	int targetDataGen = pParam->targetGenData;
	int* pDataArray;
	ThreadMon* pThrdMon = pParam->pThrdMon; //monitering
	//------------------------------------------------------------
	int genDataCount = 0;
	int genData = 0;


	pParam->pThrdMon->mtx_console.lock();
	cout << "Thread_DataGen[" << myAddr << "] is activated now ..." << endl;
	pParam->pThrdMon->mtx_console.unlock();
	for (int round = 0; round < max_round; round++)
	{
		if (genDataCount >= targetDataGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				sleep_for(std::chrono::milliseconds(500));
				continue;
			}
		}
		genData = TOTAL_NUM_DATA - (round * NUM_DATA_GEN + myAddr + 1);
		while (pPriQ->insert(genData) == NULL)
		{
			sleep_for(std::chrono::milliseconds(100));
		}
		pParam->pThrdMon->mtx_thrd_mon.lock();
		pThrdMon->numGenData[myAddr]++;
		pThrdMon->genDataArray[myAddr][round] = genData;
		pThrdMon->totalNumGenData++;
		pParam->pThrdMon->mtx_thrd_mon.unlock();

		genDataCount++;
		sleep_for(std::chrono::milliseconds(10 + rand() % 10));
	}

}

void Thread_DataProc(ThreadParam* pParam)
{
	//get paramater-----------------------------------------------
	HeapPrioQueue<int>* pPriQ = pParam->pPriQ; //event pointer
	int myAddr = pParam->myAddr;
	int max_round = pParam->maxRound;
	int targetDataGen = pParam->targetGenData;
	int* pDataArray;
	ThreadMon* pThrdMon = pParam->pThrdMon; //monitering

	// function parameter
	int* pDeQ_data = NULL;
	int procData = 0;

	pThrdMon->mtx_console.lock();
	cout << "Thread_DataProc[" << myAddr << "] is activated now ..." << endl;
	pThrdMon->mtx_console.unlock();

	for (int round = 0; round < max_round; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)			// Thread가 TERMINATE 되면 
			break;
		if (!pPriQ->isEmpty())
		{
			while ((pDeQ_data = pPriQ->removeHeapMin()) == NULL)		// 이벤트 처리
			{
				sleep_for(std::chrono::milliseconds(10));
				continue;
			}

			procData = *pDeQ_data;

			// 값을 thrdMon에 집어넣음
			pThrdMon->mtx_thrd_mon.lock();
			pThrdMon->numProcData[myAddr]++;
			pThrdMon->procDataArray[myAddr][round] = *pDeQ_data;
			pThrdMon->totalNumProcData++;
			pThrdMon->mtx_thrd_mon.unlock();
		}

		sleep_for(std::chrono::milliseconds(10 + rand() % 10));
	}
}