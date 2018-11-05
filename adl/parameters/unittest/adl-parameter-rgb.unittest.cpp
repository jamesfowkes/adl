#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "adl.h"
#include "adl-util-limited-range-int.h"
#include "rgb-param.h"

class RGBParameterTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(RGBParameterTest);

    CPPUNIT_TEST(testRGBParameterInitsToResetValue);
    CPPUNIT_TEST(testRGBParameterSetReturnsTrueAndStateIsSet);
    CPPUNIT_TEST(testClippedRGBParameterWithLimitsClipsOnOutOfRangeSet);
    CPPUNIT_TEST(testUnclippedRGBParameterWithLimitsDoesNotAllowSetOutsideRange);
    CPPUNIT_TEST(testRGBParameterResetsToResetValue);

    CPPUNIT_TEST_SUITE_END();
    void testRGBParameterInitsToResetValue()
    {
        RGBParam param = RGBParam(255, 10, 20, 30, false, false);
        CPPUNIT_ASSERT_EQUAL((uint16_t)10, param.get(eR));
        CPPUNIT_ASSERT_EQUAL((uint16_t)20, param.get(eG));
        CPPUNIT_ASSERT_EQUAL((uint16_t)30, param.get(eB));
    }

    void testRGBParameterSetReturnsTrueAndStateIsSet()
    {
        uint16_t set_values[3] = {10,20,30};
        uint16_t get_values[3];

        RGBParam param1 = RGBParam(255, 0, 0, 0, false, false);
        CPPUNIT_ASSERT(param1.set(10,20,30));
        CPPUNIT_ASSERT_EQUAL((uint16_t)10, param1.get(eR));
        CPPUNIT_ASSERT_EQUAL((uint16_t)20, param1.get(eG));
        CPPUNIT_ASSERT_EQUAL((uint16_t)30, param1.get(eB));

        RGBParam param2 = RGBParam(255, 0, 0, 0, false, false);

        CPPUNIT_ASSERT(param2.set(set_values));
        param2.get(get_values);
        CPPUNIT_ASSERT_EQUAL((uint16_t)10, get_values[eR]);
        CPPUNIT_ASSERT_EQUAL((uint16_t)20, get_values[eG]);
        CPPUNIT_ASSERT_EQUAL((uint16_t)30, get_values[eB]);
    }

    void testClippedRGBParameterWithLimitsClipsOnOutOfRangeSet()
    {
        RGBParam param = RGBParam(255, 0, 0, 0, true, false);
        CPPUNIT_ASSERT(!param.set(256, 0, 0));
        CPPUNIT_ASSERT_EQUAL((uint16_t)255, param.get(eR));
    }

    void testUnclippedRGBParameterWithLimitsDoesNotAllowSetOutsideRange()
    {
        RGBParam param = RGBParam(255, 0, 0, 0, false, false);
        CPPUNIT_ASSERT(!param.set(256, 0, 0));
        CPPUNIT_ASSERT_EQUAL((uint16_t)0, param.get(eR));
    }

    void testRGBParameterResetsToResetValue()
    {
        RGBParam param = RGBParam(255, 0, 128, 255, false, false);
        param.set(1,1,1);
        param.reset();
        CPPUNIT_ASSERT_EQUAL((uint16_t)0, param.get(eR));
        CPPUNIT_ASSERT_EQUAL((uint16_t)128, param.get(eG));
        CPPUNIT_ASSERT_EQUAL((uint16_t)255, param.get(eB));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(RGBParameterTest);
