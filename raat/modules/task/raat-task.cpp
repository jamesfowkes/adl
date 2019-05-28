/*
 * C/C++ Includes
 */

#include <stdlib.h>
#include <stdint.h>

/*
 * RAAT Includes
 */

#include "raat.hpp"

#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"
#include "raat-task.hpp"

/*
 * Private Module Functions
 */

/*
 * Class Functions
 */

RAATTask::RAATTask(uint16_t period, TaskFn pfnTask) :
    m_task(period, NULL, NULL), m_pfn_task(pfnTask), m_p_data(NULL)
{
    m_task.start();
}

RAATTask::RAATTask(uint16_t period, TaskFn pfnTask, void * pData) : 
    m_task(period, NULL, NULL), m_pfn_task(pfnTask), m_p_data(pData)
{
    m_task.start();
}

void RAATTask::start()
{
    m_task.start();
}

bool RAATTask::run(void * pData)
{
    bool triggered = !m_task.run();

    if (triggered)
    {
        if (m_pfn_task)
        {
            m_pfn_task(*this, pData ? pData : m_p_data);
        }
        m_task.start();
    }
    return triggered;
}

bool RAATTask::is_running()
{
    return m_task.is_running();
}

void RAATTask::reset()
{
    m_task.reset();
}

void RAATTask::set_period(uint16_t period)
{
    m_task.set_period(period);
}
