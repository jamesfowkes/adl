#ifndef _ADL_ONESHOT_TASK_H_
#define _ADL_ONESHOT_TASK_H_

class ADLOneShotTask;

typedef void (*OneShotTaskFn)(ADLOneShotTask& Task, void * pTaskData);

class ADLOneShotTask
{
public:
    ADLOneShotTask(uint16_t period, OneShotTaskFn pfnTask);
    ADLOneShotTask(uint16_t period, OneShotTaskFn pfnTask, void * pData);
    void start();
    bool run();
    bool is_running();
    void reset();
    void set_period(uint16_t period);

private:
    ADLOneShotTimer m_timer;
    OneShotTaskFn m_pfn_task;
    void * m_p_data;
};

#endif
