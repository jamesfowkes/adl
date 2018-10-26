#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Arduino.h"

#include "adl.h"

#include "adl-oneshot-timer.h"
#include "adl-oneshot-task.h"
#include "adl-task.h"

static int s_call_count;

static void test_task(ADLTask& task, void * pData)
{
    (void)task;
    (void)pData;
    s_call_count++;
}

static bool runTaskAtTime(ADLTask& task, unsigned long _millis)
{
    millis_set(_millis);
    return task.run();
}

class ADLModuleTaskTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(ADLModuleTaskTest);

    CPPUNIT_TEST(testTaskInitsCorrectly);
    CPPUNIT_TEST(testTaskRunsAtCorrectTime);
    CPPUNIT_TEST(testTaskIsStillRunningAfterExpiry);
    CPPUNIT_TEST(testTaskOperatesCorrectlyWithTimerOverflow);
    CPPUNIT_TEST(testTaskPeriodCanBeChanged);

    CPPUNIT_TEST_SUITE_END();

    void testTaskInitsCorrectly()
    {
        ADLTask task(1000, test_task);
        CPPUNIT_ASSERT(task.is_running());
    }

    void testTaskRunsAtCorrectTime()
    {
        ADLTask task(1000, test_task);
        task.start();
        runTaskAtTime(task, 999);
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        millis_set(1000);
        task.run();
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        millis_set(1001);
        task.run();
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        millis_set(1999);
        task.run();
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        millis_set(2000);
        task.run();
        CPPUNIT_ASSERT_EQUAL(2, s_call_count);
    }

    void testTaskIsStillRunningAfterExpiry()
    {
        ADLTask task(1000, test_task);
        task.start();
        CPPUNIT_ASSERT(runTaskAtTime(task, 1000));
        CPPUNIT_ASSERT(task.is_running());
    }

    void testTaskOperatesCorrectlyWithTimerOverflow()
    {
        ADLTask task(1000, test_task);
        millis_set(ULONG_MAX);
        task.start();

        CPPUNIT_ASSERT(!runTaskAtTime(task, 0));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(!runTaskAtTime(task, 998));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(runTaskAtTime(task, 999));
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
    }

    void testTaskPeriodCanBeChanged()
    {
        ADLTask task(1000, test_task);
        task.set_period(500);
        task.start();
        millis_set(0);

        CPPUNIT_ASSERT(!runTaskAtTime(task, 499));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(runTaskAtTime(task, 500));
        CPPUNIT_ASSERT_EQUAL(1, s_call_count); 
    }

public:
    void setUp()
    {
        millis_set(0);
        s_call_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ADLModuleTaskTest);
