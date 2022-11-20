/*
  파일명 : "Exam3A_21912193_신대홍"
  프로그램의 목적 및 기본 기능:
	- Circular Queue를 구성하여 int형의 데이터를 다룬다.
  프로그램 작성자 : 신대홍(2022년 11월 19일)
  최종 Update : Version 1.1.0, 2022년 11월 19일(신대홍)
===========================================================================================================
					프로그램 수정/보완 이력
===========================================================================================================
   수정자	  수정일			버전			     수정/보완내용
-----------------------------------------------------------------------------------------------------------
	신대홍		 2022/11/19		v1.0.0		  최초작성
	신대홍		 2022/11/20		v1.1.0		  최종 완성 및 보완 완료, 시험 종료 후 완성
===========================================================================================================
*/

#include <iostream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <Windows.h>

#include "MultiThread.h"
#include "SimParam.h"
#include "T_Array.h"
#include "CirQ.h"

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

	TA_CirQ<int> TA_CirQ_int(QUEUE_SIZE, string("TA_CirQ of Integer"));

	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		for (int i = 0; i < TOTAL_NUM_DATA; i++)
			thrdMon.genDataArray[g][i] = -1;
		thrdMon.numGenData[g] = 0;
		//thrdParam_Gen[g].dataList = dataList;
		thrdParam_Gen[g].myAddr = g;
		thrdParam_Gen[g].pTA_CirQ = &TA_CirQ_int;
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
		thrdParam_Proc[p].pTA_CirQ = &TA_CirQ_int;
		thrdParam_Proc[p].targetGenData = NUM_DATA_PER_GEN;
		thrdParam_Proc[p].maxRound = MAX_ROUNDS;
		thrdParam_Proc[p].pThrdMon = &thrdMon;
		thrd_dataProc[p] = thread(Thread_DataProc, &thrdParam_Proc[p]);
	}
	
	cout << "Testing " << TA_CirQ_int.Name() << "with " << NUM_DATA_GEN << " data generators and ";
	cout << NUM_DATA_PROC << " data processors" << endl; for (int i = 0; i < MAX_ROUNDS; i++)
	{
		thrdMon.mtx_console.lock();
		cout << "Round (" << setw(3) << i << ") : totalDataGenerated = " << setw(3) << thrdMon.totalNumGenData;
		cout << ", totalDataProcessed = " << setw(3) << thrdMon.totalNumProcData << endl;
		/*
		for (int g = 0; g < NUM_DATA_GEN; g++)
		{
			//cout << "thrdDataGen[" << g << "] generated " << thrdMon.numGenData[g] << " data" << endl;
		}
		for (int p = 0; p < NUM_DATA_PROC; p++)
		{
			//cout << "thrdDataProc[" << p << "] processed " << thrdMon.numProcData[p] << " data" << endl;
		}
		*/
		thrdMon.mtx_console.unlock();

		// 만약 Proccessing 된 데이터가 TOTAL을 넘어섰다면 ( 다했다면 ) Thread들을 TERMINATED 시킴
		if (thrdMon.totalNumProcData >= TOTAL_NUM_DATA)
		{
			thrd_flag = TERMINATE;
			break;
		}

		Sleep(100);
	}

	// Thread joining 
	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		cout << " Thread_DataGen[" << g << "] is join! " << endl;
		thrd_dataGen[g].join();
	}
	for (int p = 0; p < NUM_DATA_PROC; p++)
	{
		cout << " Thread_DataProc[" << p << "] is join! " << endl;
		thrd_dataProc[p].join();
	}

	// Generating and Proccessing result printing
	for (int g = 0; g < NUM_DATA_GEN; g++)
	{
		cout << "Thread_Gen[" << g << "] generated " << thrdMon.numGenData[g] << " data :" << endl;

		thrdMon.mtx_console.lock();
		for (int i = 0; i < NUM_DATA_PER_GEN; i++)
		{
			cout << setw(4) << thrdMon.genDataArray[g][i];
			if ((i + 1) % Elements_per_line == 0)
				cout << endl;
			
		}
		thrdMon.mtx_console.unlock();
		cout << endl;
	}

	for (int p = 0; p < NUM_DATA_PROC; p++)
	{
		cout << "Thread_Proc[" << p << "] processed " << thrdMon.numProcData[p] << " data :" << endl;
		thrdMon.mtx_console.lock();
		for (int i = 0; i < (TOTAL_NUM_DATA / NUM_DATA_PROC); i++)
		{
			cout << setw(4) << thrdMon.procDataArray[p][i];
			if ((i + 1) % Elements_per_line == 0)
				cout << endl;
			
		}
		thrdMon.mtx_console.unlock();
		cout << endl;
	}
	return 0;
}