#ifndef _ADL_ONESHOT_TASK_H_
#define _ADL_ONESHOT_TASK_H_

class ADLOneShotTask;

typedef void (*OneShotTask)(ADLOneShotTask* pTask, void * pTaskData);

class ADLOneShotTask
{
public:
	ADLOneShotTask(uint16_t period, OneShotTask pfnTask);
	ADLOneShotTask(uint16_t period, OneShotTask pfnTask, void * pData);
	void start();
	bool run();
	bool is_running();
	void reset();
private:
	ADLOneShotTimer m_timer;
	OneShotTask m_pfn_task;
	void * m_p_data;
};

#endif
