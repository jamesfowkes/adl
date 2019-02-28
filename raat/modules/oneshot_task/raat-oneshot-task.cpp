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

/*
 * Class Functions
 */

RAATOneShotTask::RAATOneShotTask(uint16_t period, OneShotTaskFn pfnTask) :
    m_timer(period), m_pfn_task(pfnTask), m_p_data(NULL)
{

}

RAATOneShotTask::RAATOneShotTask(uint16_t period, OneShotTaskFn pfnTask, void * pData) : 
    m_timer(period), m_pfn_task(pfnTask), m_p_data(pData)
{
    
}

void RAATOneShotTask::start()
{
    m_timer.start();
}

bool RAATOneShotTask::run()
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

bool RAATOneShotTask::is_running()
{
    return m_timer.is_running();
}

void RAATOneShotTask::reset()
{
    m_timer.reset();
}

void RAATOneShotTask::set_period(uint16_t period)
{
    m_timer.set_period(period);
}
