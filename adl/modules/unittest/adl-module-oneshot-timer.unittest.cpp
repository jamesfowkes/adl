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
#include "adl-oneshot-timer.h"

class ADLModuleOneShotTimerTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(ADLModuleOneShotTimerTest);

    CPPUNIT_TEST(testOneShotTimerInitsCorrectly);
    CPPUNIT_TEST(testOneShotTimerInitsCorrectlyAfterTimerWouldHaveElapsed);
    CPPUNIT_TEST(testOneShotTimerRunningAfterStart);
    CPPUNIT_TEST(testOneShotTimerExpiresAtCorrectTime);
    CPPUNIT_TEST(testOneShotTimerStillRunningAfterExpiry);
    CPPUNIT_TEST(testOneShotTimerNotRunningAfterReset);
    CPPUNIT_TEST(testOneShotTimerCheckAndResetIsFalseAndDoesNotResetIfNotExpired);
    CPPUNIT_TEST(testOneShotTimerCheckAndResetIsTrueAndDoesResetIfExpired);
    CPPUNIT_TEST(testOneShotTimerCanBeRestarted);
    CPPUNIT_TEST(testOneShotTimerCheckAndRestartIsFalseAndDoesNotRestartIfNotExpired);
    CPPUNIT_TEST(testOneShotTimerCheckAndRestartIsTrueAndRestartsIfExpired);
    CPPUNIT_TEST(testOneShotTimerCanBeRestartedWithCheckAndRestart);
    CPPUNIT_TEST(testOneShotTimerOperatesCorrectlyWithTimerOverflow);
    CPPUNIT_TEST(testOneShotTimerPeriodCanBeChanged);

    CPPUNIT_TEST_SUITE_END();

    void testOneShotTimerInitsCorrectly()
    {
        ADLOneShotTimer timer(1000);
        CPPUNIT_ASSERT(!timer.check());
    }

    void testOneShotTimerInitsCorrectlyAfterTimerWouldHaveElapsed()
    {
        millis_set(1001);
        ADLOneShotTimer timer(1000);
        CPPUNIT_ASSERT(!timer.check());
    }

    void testOneShotTimerRunningAfterStart()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerExpiresAtCorrectTime()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(999);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check());
        millis_set(1001);
        CPPUNIT_ASSERT(timer.check());
    }

    void testOneShotTimerStillRunningAfterExpiry()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerNotRunningAfterReset()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        timer.reset();
        CPPUNIT_ASSERT(!timer.is_running());
    }

    void testOneShotTimerCheckAndResetIsFalseAndDoesNotResetIfNotExpired()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(!timer.check_and_reset());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCheckAndResetIsTrueAndDoesResetIfExpired()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_reset());
        CPPUNIT_ASSERT(!timer.is_running());
    }

    void testOneShotTimerCanBeRestarted()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_reset());
        timer.start();
        CPPUNIT_ASSERT(timer.is_running());
        CPPUNIT_ASSERT(!timer.check());
        millis_set(1999);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(2000);
        CPPUNIT_ASSERT(timer.check());
    }

    void testOneShotTimerCheckAndRestartIsFalseAndDoesNotRestartIfNotExpired()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(!timer.check_and_restart());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCheckAndRestartIsTrueAndRestartsIfExpired()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_restart());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCanBeRestartedWithCheckAndRestart()
    {
        ADLOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_restart());
        CPPUNIT_ASSERT(timer.is_running());
        CPPUNIT_ASSERT(!timer.check());
        millis_set(1999);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(2000);
        CPPUNIT_ASSERT(timer.check());
    }

    void testOneShotTimerOperatesCorrectlyWithTimerOverflow()
    {
        ADLOneShotTimer timer(1000);
        millis_set(ULONG_MAX);
        timer.start();
        millis_set(0);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(998);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(999);
        CPPUNIT_ASSERT(timer.check());
    }

    void testOneShotTimerPeriodCanBeChanged()
    {
        ADLOneShotTimer timer(1000);
        timer.set_period(500);
        timer.start();
        millis_set(0);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(499);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(500);
        CPPUNIT_ASSERT(timer.check());   
    }

public:
    void setUp()
    {
        millis_set(0);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ADLModuleOneShotTimerTest);
