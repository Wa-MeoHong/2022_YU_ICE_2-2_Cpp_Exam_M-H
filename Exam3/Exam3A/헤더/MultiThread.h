
#ifndef MULTI_THREAD
#define MULTI_THREAD

#include <thread>
#include <mutex>
#include <string>
#include "CirQ.h"
#include "SimParam.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };		// 역할 enum 
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };	// thread flag enum

/* ThreadStatusMonitor ( 쓰레드 상태 모니터 구조체 ) */
typedef struct _ThreadStatusMonitor
{
	mutex mtx_thrd_mon;
	mutex mtx_console;
	int numGenData[NUM_DATA_GEN];
	int numProcData[NUM_DATA_PROC];
	int totalNumGenData = 0;
	int totalNumProcData = 0;

	int genDataArray[NUM_DATA_GEN][TOTAL_NUM_DATA]; // used for monitoring only
	int procDataArray[NUM_DATA_PROC][TOTAL_NUM_DATA]; // used for monitoring only
	THREAD_FLAG* pFlagThreadTerminate = NULL;

} ThreadMon;

/* ThreadParameter_Event ( 쓰레드 내의 변수들 구조체 ) */
typedef struct _ThreadParameter_Event
{
	TA_CirQ<int>* pTA_CirQ = NULL;
	int myAddr;
	int maxRound;
	int targetGenData;
	ThreadMon* pThrdMon;

} ThreadParam;

void Thread_DataGen(ThreadParam* pParam);
void Thread_DataProc(ThreadParam* pParam);

#endif // !MULTI_THREAD