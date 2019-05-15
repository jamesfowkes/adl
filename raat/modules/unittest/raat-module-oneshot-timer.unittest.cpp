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
#include "raat-oneshot-timer.hpp"

class RAATModuleOneShotTimerTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(RAATModuleOneShotTimerTest);

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
    CPPUNIT_TEST(testOneShotTimerPeriodCanBeSetAtStart);

    CPPUNIT_TEST_SUITE_END();

    void testOneShotTimerInitsCorrectly()
    {
        RAATOneShotTimer timer(1000);
        CPPUNIT_ASSERT(!timer.check());
    }

    void testOneShotTimerInitsCorrectlyAfterTimerWouldHaveElapsed()
    {
        millis_set(1001);
        RAATOneShotTimer timer(1000);
        CPPUNIT_ASSERT(!timer.check());
    }

    void testOneShotTimerRunningAfterStart()
    {
        RAATOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerExpiresAtCorrectTime()
    {
        RAATOneShotTimer timer(1000);
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
        RAATOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerNotRunningAfterReset()
    {
        RAATOneShotTimer timer(1000);
        timer.start();
        timer.reset();
        CPPUNIT_ASSERT(!timer.is_running());
    }

    void testOneShotTimerCheckAndResetIsFalseAndDoesNotResetIfNotExpired()
    {
        RAATOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(!timer.check_and_reset());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCheckAndResetIsTrueAndDoesResetIfExpired()
    {
        RAATOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_reset());
        CPPUNIT_ASSERT(!timer.is_running());
    }

    void testOneShotTimerCanBeRestarted()
    {
        RAATOneShotTimer timer(1000);
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
        RAATOneShotTimer timer(1000);
        timer.start();
        CPPUNIT_ASSERT(!timer.check_and_restart());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCheckAndRestartIsTrueAndRestartsIfExpired()
    {
        RAATOneShotTimer timer(1000);
        timer.start();
        millis_set(1000);
        CPPUNIT_ASSERT(timer.check_and_restart());
        CPPUNIT_ASSERT(timer.is_running());
    }

    void testOneShotTimerCanBeRestartedWithCheckAndRestart()
    {
        RAATOneShotTimer timer(1000);
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
        RAATOneShotTimer timer(1000);
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
        RAATOneShotTimer timer(1000);
        timer.set_period(500);
        timer.start();
        millis_set(0);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(499);
        CPPUNIT_ASSERT(!timer.check());
        millis_set(500);
        CPPUNIT_ASSERT(timer.check());   
    }

    void testOneShotTimerPeriodCanBeSetAtStart()
    {
        RAATOneShotTimer timer(1000);
        timer.start(500);
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

CPPUNIT_TEST_SUITE_REGISTRATION(RAATModuleOneShotTimerTest);
