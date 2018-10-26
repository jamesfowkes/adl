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

/*
 * Class Functions
 */

ADLOneShotTask::ADLOneShotTask(uint16_t period, OneShotTaskFn pfnTask) :
    m_timer(period), m_pfn_task(pfnTask), m_p_data(NULL)
{

}

ADLOneShotTask::ADLOneShotTask(uint16_t period, OneShotTaskFn pfnTask, void * pData) : 
    m_timer(period), m_pfn_task(pfnTask), m_p_data(pData)
{
    
}

void ADLOneShotTask::start()
{
    m_timer.start();
}

bool ADLOneShotTask::run()
{
    if (m_timer.check_and_reset())
    {
        if (m_pfn_task)
        {
            m_pfn_task(*this, m_p_data);
        }
    }
    return m_timer.is_running();
}

bool ADLOneShotTask::is_running()
{
    return m_timer.is_running();
}

void ADLOneShotTask::reset()
{
    m_timer.reset();
}

void ADLOneShotTask::set_period(uint16_t period)
{
    m_timer.set_period(period);
}
