#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat.hpp"
#include "raat-util-limited-range-int.hpp"
#include "integer-param.hpp"

#include "raat-mock.hpp"

class IntegerParameterTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(IntegerParameterTest);

    CPPUNIT_TEST(testIntegerParameterInitsToResetValue);
    CPPUNIT_TEST(testIntegerParameterSetReturnsTrueAndStateIsSet);
    CPPUNIT_TEST(testIntegerParameterWithoutLimitsAllowIntegerMinMax);
    CPPUNIT_TEST(testClippedIntegerParameterWithLimitsDoesNotAllowSetOutsideRange);
    CPPUNIT_TEST(testUnclippedIntegerParameterWithLimitsDoesNotAllowSetOutsideRange);
    CPPUNIT_TEST(testIntegerParameterWithLimitsAllowSetInsideRange);
    CPPUNIT_TEST(testIntegerParameterResetsToResetValue);
    CPPUNIT_TEST(testIntegerParameterCorrectlyWorksWithNonvolatile);
    CPPUNIT_TEST(testIntegerParameterCorrectlyWorksWithMultipleNonvolatiles);
    CPPUNIT_TEST(testIntegerParameterChangeIsNotSetOnInit);
    CPPUNIT_TEST(testIntegerParameterChangeIsSetOnSetup);
    CPPUNIT_TEST(testIntegerParameterChangeIsSetOnSet);
    CPPUNIT_TEST(testIntegerParameterChangeIsSetOnReset);

    CPPUNIT_TEST_SUITE_END();
    void testIntegerParameterInitsToResetValue()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(10, INT32_MIN, INT32_MAX, true, false);
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testIntegerParameterSetReturnsTrueAndStateIsSet()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, false);
        CPPUNIT_ASSERT(param.set(10));
    }

    void testIntegerParameterWithoutLimitsAllowIntegerMinMax()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, false);
        CPPUNIT_ASSERT(param.set(INT32_MAX));
        CPPUNIT_ASSERT(param.set(INT32_MIN));
    }

    void testClippedIntegerParameterWithLimitsDoesNotAllowSetOutsideRange()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, -10, 10, true, false);
        CPPUNIT_ASSERT(!param.set(-11));
        CPPUNIT_ASSERT_EQUAL(-10, param.get());
        CPPUNIT_ASSERT(!param.set(11));
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testUnclippedIntegerParameterWithLimitsDoesNotAllowSetOutsideRange()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, -10, 10, false, false);
        CPPUNIT_ASSERT(!param.set(-11));
        CPPUNIT_ASSERT(!param.set(11));
        CPPUNIT_ASSERT_EQUAL(0, param.get());
    }

    void testIntegerParameterWithLimitsAllowSetInsideRange()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, -10, 10, false, false);
        CPPUNIT_ASSERT(param.set(-10));
        CPPUNIT_ASSERT_EQUAL(-10, param.get());
        CPPUNIT_ASSERT(param.set(10));
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testIntegerParameterResetsToResetValue()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(10, INT32_MIN, INT32_MAX, true, true);
        param.setup();
        param.set(0);
        param.reset();
        CPPUNIT_ASSERT_EQUAL(10, param.get());
    }

    void testIntegerParameterCorrectlyWorksWithNonvolatile()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        param.setup();
        param.set(100);
        CPPUNIT_ASSERT_EQUAL(100, *(int32_t*)raat_mock_nonvolatile_get_last_write());
    }

    void testIntegerParameterCorrectlyWorksWithMultipleNonvolatiles()
    {
        IntegerParam<int32_t> param1 = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        IntegerParam<int32_t> param2 = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        
        param1.setup();
        param2.setup();

        param1.set(100);
        CPPUNIT_ASSERT_EQUAL(100, *(int32_t*)raat_mock_nonvolatile_get_last_write());
        param2.set(200);
        CPPUNIT_ASSERT_EQUAL(200, *(int32_t*)raat_mock_nonvolatile_get_last_write());
    }

    void testIntegerParameterChangeIsNotSetOnInit()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        CPPUNIT_ASSERT(!param.has_changed());
    }

    void testIntegerParameterChangeIsSetOnSetup()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        param.setup();
        CPPUNIT_ASSERT(param.has_changed());
    }

    void testIntegerParameterChangeIsSetOnSet()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        param.set(100);
        CPPUNIT_ASSERT(param.has_changed());
        param.reset();
    }

    void testIntegerParameterChangeIsSetOnReset()
    {
        IntegerParam<int32_t> param = IntegerParam<int32_t>(0, INT32_MIN, INT32_MAX, true, true);
        param.set(100);
        (void)param.has_changed();
        param.reset();
        CPPUNIT_ASSERT(param.has_changed());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(IntegerParameterTest);
