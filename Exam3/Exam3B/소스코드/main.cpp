/*
  파일명 : "Exam3B_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Heap Priority Queue를 구성하고, 데이터를 관리함
  프로그램 작성자 : 신대홍(2022년 11월 19일)
  최종 Update : Version 1.0.0, 2022년 11월 19일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/19		v1.0.0		  최초작성
	신대홍		 2022/11/20		v1.1.0		  최종완성, 시험 종료후 완성
===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <Windows.h>
#include "CBT.h"
#include "HeapPrioQueue.h"
#include "MultiThread.h"

#define INITIAL_CBT_CAPA 100

using namespace std;

int main(void)
{
	ThreadMon thrdMon;
	ThreadParam thrdParam_Gen[NUM_DATA_GEN]; // thrdPram for each data generator
	ThreadParam thrdParam_Proc[NUM_DATA_PROC]; // thrdPram for each data processor
	THREAD_FLAG thrd_flag = RUN;
	thrdMon.pFlagThreadTerminate = &thrd_flag;
	thrdMon.totalNumGenData = thrdMon.totalNumProcData = 0;
	thread thrd_dataProc[NUM_DATA_PROC];
	thread thrd_dataGen[NUM_DATA_GEN];
	HeapPrioQueue<int> HeapPriQ_int(INITIAL_CBT_CAPA, string("Heap_Priority_Queue_Int"));


	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		for (int i = 0; i < TOTAL_NUM_DATA; i++)
			thrdMon.genDataArray[g][i] = -1;
		thrdMon.numGenData[g] = 0;
		//thrdParam_Gen[g].dataList = dataList;
		thrdParam_Gen[g].myAddr = g;
		thrdParam_Gen[g].pPriQ = &HeapPriQ_int;
		thrdParam_Gen[g].targetGenData = NUM_DATA_PER_GEN;
		thrdParam_Gen[g].maxRound = MAX_ROUNDS;
		thrdParam_Gen[g].pThrdMon = &thrdMon;
		thrd_dataGen[g] = thread(Thread_DataGen, &thrdParam_Gen[g]);
	}
	for (int p = 0; p < NUM_DATA_PROC; p++)
	{
		for (int i = 0; i < TOTAL_NUM_DATA; i++)
			thrdMon.procDataArray[p][i] = -1;
		thrdMon.numProcData[p] = 0;
		thrdParam_Proc[p].myAddr = p;
		thrdParam_Proc[p].pPriQ = &HeapPriQ_int;
		thrdParam_Proc[p].targetGenData = NUM_DATA_PER_GEN;
		thrdParam_Proc[p].maxRound = MAX_ROUNDS;
		thrdParam_Proc[p].pThrdMon = &thrdMon;
		thrd_dataProc[p] = thread(Thread_DataProc, &thrdParam_Proc[p]);
	}

	Sleep(100);
	thrdMon.mtx_console.lock();
	cout << "Testing " << HeapPriQ_int.Name() << "with " << NUM_DATA_GEN << " data generators and ";
	cout << NUM_DATA_PROC << " data processors" << endl;
	thrdMon.mtx_console.unlock();
	for (int round = 0; round < MAX_ROUNDS; round++)
	{
		thrdMon.mtx_console.lock();
		cout << "Round (" << setw(3) << round << ") : totalDataGenerated = " << setw(3) << thrdMon.totalNumGenData;
		cout << ", totalDataProcessed = " << setw(3) << thrdMon.totalNumProcData << endl;
		for (int g = 0; g < NUM_DATA_GEN; g++)
		{
			//cout << "thrdDataGen[" << g << "] generated " << thrdMon.numGenData[g] << " data" << endl;
		}
		for (int p = 0; p < NUM_DATA_PROC; p++)
		{
			//cout << "thrdDataProc[" << p << "] processed " << thrdMon.numProcData[p] << " data" << endl;
		}
		thrdMon.mtx_console.unlock();
		if (thrdMon.totalNumProcData >= TOTAL_NUM_DATA)
		{
			thrd_flag = TERMINATE;
			break;
		}
		Sleep(100);
	}

	cout << endl;
	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		// TERMINATED 된 쓰레드 JOIN하기
		cout << "Thread_DataGen[" << g << "] is joined !!" << endl;
		thrd_dataGen[g].join();
	}
	for (int p = 0; p < NUM_DATA_PROC; p++)
	{
		// TERMINATED 된 쓰레드 JOIN하기
		cout << "Thread_DataProc[" << p << "] is joined !!" << endl;
		thrd_dataProc[p].join();
	}
	cout << endl;

	// 생성된/ 처리된 이벤트 출력하기
	int count = 0;
	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		cout << "Thread_Gen[" << g << "] generated " << thrdMon.numGenData[g] << " data :" << endl;
		count = 0;
		for (int i = 0; i < thrdMon.numGenData[g]; i++)
		{
			cout << setw(5) << thrdMon.genDataArray[g][i];
			count++;
			if ((count % 20) == 0)
				cout << endl;
		}
		cout << endl;
	}
	for (int p = 0; p < NUM_DATA_PROC; p++)
	{
		cout << "Thread_Proc[" << p << "] processed " << thrdMon.numProcData[p] << " data :" << endl;
		count = 0;
		for (int i = 0; i < thrdMon.numProcData[p]; i++)
		{
			cout << setw(5) << thrdMon.procDataArray[p][i];
			count++;
			if ((count % 20) == 0)
				cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	return 0;


}