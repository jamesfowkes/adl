#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat.hpp"

#include "Arduino.h"
#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"

static int s_call_count;

static void test_task(RAATOneShotTask& task, void * pData)
{
    (void)task;
    (void)pData;
    s_call_count++;
}

static bool runTaskAtTime(RAATOneShotTask& task, unsigned long _millis)
{
    millis_set(_millis);
    task.run();
    return task.is_running();
}

class RAATModuleOneShotTaskTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(RAATModuleOneShotTaskTest);

    CPPUNIT_TEST(testOneShotTaskInitsCorrectly);
    CPPUNIT_TEST(testOneShotTaskInitsCorrectlyAfterTimerWouldHaveElapsed);
    CPPUNIT_TEST(testOneShotTaskRunsAtCorrectTime);
    CPPUNIT_TEST(testOneShotTaskIsNotRunningAfterExpiry);
    CPPUNIT_TEST(testOneShotTaskNotRunningAfterReset);
    CPPUNIT_TEST(testOneShotTaskCanBeRestarted);
    CPPUNIT_TEST(testOneShotTaskOperatesCorrectlyWithTimerOverflow);
    CPPUNIT_TEST(testOneShotTaskPeriodCanBeChanged);

    CPPUNIT_TEST_SUITE_END();

    void testOneShotTaskInitsCorrectly()
    {
        RAATOneShotTask task(1000, test_task);
        CPPUNIT_ASSERT(!task.is_running());
    }

    void testOneShotTaskInitsCorrectlyAfterTimerWouldHaveElapsed()
    {
        millis_set(1001);
        RAATOneShotTask task(1000, test_task);
        CPPUNIT_ASSERT(!task.is_running());
    }

    void testOneShotTaskRunsAtCorrectTime()
    {
        RAATOneShotTask task(1000, test_task);
        task.start();
        runTaskAtTime(task, 999);
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        millis_set(1000);
        task.run();
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        millis_set(1001);
        task.run();
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
    }

    void testOneShotTaskIsNotRunningAfterExpiry()
    {
        RAATOneShotTask task(1000, test_task);
        task.start();
        runTaskAtTime(task, 1000);
        CPPUNIT_ASSERT(!task.is_running());
    }

    void testOneShotTaskNotRunningAfterReset()
    {
        RAATOneShotTask task(1000, test_task);
        task.start();
        task.reset();
        CPPUNIT_ASSERT(!task.is_running());
    }

    void testOneShotTaskCanBeRestarted()
    {
        RAATOneShotTask task(1000, test_task);
        task.start();
        runTaskAtTime(task, 1000);

        task.start();
        task.run();
        CPPUNIT_ASSERT(task.is_running());
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        CPPUNIT_ASSERT(runTaskAtTime(task, 1999));
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
        CPPUNIT_ASSERT(!runTaskAtTime(task, 2000));
        CPPUNIT_ASSERT_EQUAL(2, s_call_count);
    }

    void testOneShotTaskOperatesCorrectlyWithTimerOverflow()
    {
        RAATOneShotTask task(1000, test_task);
        millis_set(ULONG_MAX);
        task.start();

        CPPUNIT_ASSERT(runTaskAtTime(task, 0));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(runTaskAtTime(task, 998));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(!runTaskAtTime(task, 999));
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
    }

    void testOneShotTaskPeriodCanBeChanged()
    {
        RAATOneShotTask task(1000, test_task);
        task.start();
        task.set_period(500);

        CPPUNIT_ASSERT(runTaskAtTime(task, 499));
        CPPUNIT_ASSERT_EQUAL(0, s_call_count);
        CPPUNIT_ASSERT(!runTaskAtTime(task, 500));
        CPPUNIT_ASSERT_EQUAL(1, s_call_count);
    }

public:
    void setUp()
    {
        millis_set(0);
        s_call_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(RAATModuleOneShotTaskTest);
