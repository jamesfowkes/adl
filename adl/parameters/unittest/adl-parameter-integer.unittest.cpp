#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "parameter.h"
#include "integer-param.h"

class IntegerParameterTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(IntegerParameterTest);

    CPPUNIT_TEST(testIntegerParameterInitsToResetValue);
    CPPUNIT_TEST(testIntegerParameterSetReturnsTrueAndStateIsSet);
    CPPUNIT_TEST(testIntegerParameterWithoutLimitsAllowIntegerMinMax);
    CPPUNIT_TEST(testIntegerParameterWithLimitsDoesNotAllowSetOutsideRange);
    CPPUNIT_TEST(testIntegerParameterWithLimitsAllowSetInsideRange);
    CPPUNIT_TEST(testIntegerParameterResetsToResetValue);

    CPPUNIT_TEST_SUITE_END();
    void testIntegerParameterInitsToResetValue()
    {
        IntegerParam param = IntegerParam(10);
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testIntegerParameterSetReturnsTrueAndStateIsSet()
    {
        IntegerParam param = IntegerParam(0);
        CPPUNIT_ASSERT(param.set(10));
    }

    void testIntegerParameterWithoutLimitsAllowIntegerMinMax()
    {
        IntegerParam param = IntegerParam(0);
        CPPUNIT_ASSERT(param.set(INT32_MAX));
        CPPUNIT_ASSERT(param.set(INT32_MIN));
    }

    void testIntegerParameterWithLimitsDoesNotAllowSetOutsideRange()
    {
        IntegerParam param = IntegerParam(0, -10, 10);
        CPPUNIT_ASSERT(!param.set(-11));
        CPPUNIT_ASSERT(!param.set(11));
        CPPUNIT_ASSERT_EQUAL(0, param.get());
    }

    void testIntegerParameterWithLimitsAllowSetInsideRange()
    {
        IntegerParam param = IntegerParam(0, -10, 10);
        CPPUNIT_ASSERT(param.set(-10));
        CPPUNIT_ASSERT_EQUAL(-10, param.get());
        CPPUNIT_ASSERT(param.set(10));
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testIntegerParameterResetsToResetValue()
    {
        IntegerParam param = IntegerParam(10);
        param.set(0);
        param.reset();
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(IntegerParameterTest);
