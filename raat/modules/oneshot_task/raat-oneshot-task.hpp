#ifndef _RAAT_ONESHOT_TASK_H_
#define _RAAT_ONESHOT_TASK_H_

class RAATOneShotTask;

typedef void (*OneShotTaskFn)(RAATOneShotTask& Task, void * pTaskData);

class RAATOneShotTask
{
public:
    RAATOneShotTask(uint16_t period, OneShotTaskFn pfnTask);
    RAATOneShotTask(uint16_t period, OneShotTaskFn pfnTask, void * pData);
    void start();
    bool run();
    bool is_running();
    void reset();
    void set_period(uint16_t period);

private:
    RAATOneShotTimer m_timer;
    OneShotTaskFn m_pfn_task;
    void * m_p_data;
};

#endif
