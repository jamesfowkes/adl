/*
 * C/C++ Includes
 */

#include <stdlib.h>
#include <stdint.h>

/*
 * ADL Includes
 */

#include "adl.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"
#include "adl-task.h"

/*
 * Private Module Functions
 */

/*
 * Class Functions
 */

ADLTask::ADLTask(uint16_t period, TaskFn pfnTask) :
    m_task(period, NULL, NULL), m_pfn_task(pfnTask), m_p_data(NULL)
{
    m_task.start();
}

ADLTask::ADLTask(uint16_t period, TaskFn pfnTask, void * pData) : 
    m_task(period, NULL, NULL), m_pfn_task(pfnTask), m_p_data(pData)
{
    m_task.start();
}

void ADLTask::start()
{
    m_task.start();
}

bool ADLTask::run()
{
    bool triggered = !m_task.run();

    if (triggered)
    {
        if (m_pfn_task)
        {
            m_pfn_task(*this, m_p_data) ;
        }
        m_task.start();
    }
    return triggered;
}

bool ADLTask::is_running()
{
    return m_task.is_running();
}

void ADLTask::reset()
{
    m_task.reset();
}

void ADLTask::set_period(uint16_t period)
{
    m_task.set_period(period);
}
