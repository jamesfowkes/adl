#ifndef _RAAT_TASK_H_
#define _RAAT_TASK_H_

class RAATTask;

typedef void (*TaskFn)(RAATTask& task, void * pTaskData);

class RAATTask
{
public:
    RAATTask(uint16_t period, TaskFn pfnTask);
    RAATTask(uint16_t period, TaskFn pfnTask, void * pData);
    void start();
    void stop();
    bool run(void * pData = NULL);
    bool is_running();
    void reset();
    void set_period(uint16_t period);
    uint16_t period();

private:
    RAATOneShotTask m_task;
    TaskFn m_pfn_task;
    void * m_p_data;
};

#endif
