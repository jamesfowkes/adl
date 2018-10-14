#ifndef _ADL_TASK_H_
#define _ADL_TASK_H_

class ADLTask;

typedef void (*TaskFn)(ADLTask& task, void * pTaskData);

class ADLTask
{
public:
	ADLTask(uint16_t period, TaskFn pfnTask);
	ADLTask(uint16_t period, TaskFn pfnTask, void * pData);
	void start();
	void stop();
	bool run();
	bool is_running();
	void reset();
	void set_period(uint16_t period);
private:
	ADLOneShotTask m_task;
	TaskFn m_pfn_task;
	void * m_p_data;
};

#endif
