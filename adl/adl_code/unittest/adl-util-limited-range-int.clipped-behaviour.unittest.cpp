#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "adl-util-limited-range-int.h"
#include "adl-util.h"

class LimitedRangeIntClippedTest : public CppUnit::TestFixture { 

    char * p_result;
    
    CPPUNIT_TEST_SUITE(LimitedRangeIntClippedTest);

    CPPUNIT_TEST(testLimitedRangeIntInitsIfInRange);
    CPPUNIT_TEST(testLimitedRangeIntInitClipsIfOutOfRange);
    CPPUNIT_TEST(testLimitedRangeIntSetReturnsTrueForInRangeValuesAndSetsValue);
    CPPUNIT_TEST(testLimitedRangeIntSetReturnsFalseForOutOfRangeValuesAndClipsValue);
    CPPUNIT_TEST(testLimitedRangeIntIncrementGoesUpToMaxValue);
    CPPUNIT_TEST(testLimitedRangeIntAdditionGoesUpToMaxValue);
    CPPUNIT_TEST(testLimitedRangeIntAdditionDoesNotOverflow);
    CPPUNIT_TEST(testLimitedRangeIntDecrementGoesDownToMinValue);
    CPPUNIT_TEST(testLimitedRangeIntSubtractionGoesDownToMinValue);
    CPPUNIT_TEST(testLimitedRangeIntSubtractionDoesNotUnderflow);
    CPPUNIT_TEST(testLimitedRangeCheckReturnsTrueForValuesInsideRange);
    CPPUNIT_TEST(testLimitedRangeCheckReturnsFalseForValuesOutsideRange);

    CPPUNIT_TEST_SUITE_END();

    void testLimitedRangeIntInitsIfInRange()
    {
        LimitedRangeInt limited1(-100,-100,100, true);
        CPPUNIT_ASSERT_EQUAL(-100, limited1.value());

        LimitedRangeInt limited2(100,-100,100, true);
        CPPUNIT_ASSERT_EQUAL(100, limited2.value());
    }

    void testLimitedRangeIntInitClipsIfOutOfRange()
    {
        LimitedRangeInt limited1(-101,-100,100, true);
        CPPUNIT_ASSERT_EQUAL(-100, limited1.value());

        LimitedRangeInt limited2(101,-100,100, true);
        CPPUNIT_ASSERT_EQUAL(100, limited2.value());
    }

    void testLimitedRangeIntSetReturnsTrueForInRangeValuesAndSetsValue()
    {
        LimitedRangeInt limited(0,-100,100, true);
        CPPUNIT_ASSERT(limited.set(-100));
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
    
        CPPUNIT_ASSERT(limited.set(100));
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
    }

    void testLimitedRangeIntSetReturnsFalseForOutOfRangeValuesAndClipsValue()
    {
        LimitedRangeInt limited(0,-100,100, true);
        CPPUNIT_ASSERT(!limited.set(-101));
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
    
        CPPUNIT_ASSERT(!limited.set(101));
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
    }

    void testLimitedRangeIntIncrementGoesUpToMaxValue()
    {
        LimitedRangeInt limited(99,-100,100, true);
        limited++;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
        limited++;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
    }

    void testLimitedRangeIntAdditionGoesUpToMaxValue()
    {
        LimitedRangeInt limited(95,-100,100, true);
        limited += 5;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
        limited += 1;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());

        limited.set(95);
        limited = limited + 5;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
        limited = limited + 1;
        CPPUNIT_ASSERT_EQUAL(100, limited.value());
    }

    void testLimitedRangeIntAdditionDoesNotOverflow()
    {
        LimitedRangeInt limited(INT32_MAX,0,INT32_MAX, true);
        limited++;
        CPPUNIT_ASSERT_EQUAL(INT32_MAX, limited.value());
        limited += 1;
        CPPUNIT_ASSERT_EQUAL(INT32_MAX, limited.value());
        limited = limited + 1;
        CPPUNIT_ASSERT_EQUAL(INT32_MAX, limited.value());
    }

    void testLimitedRangeIntDecrementGoesDownToMinValue()
    {
        LimitedRangeInt limited(-99,-100,100, true);
        limited--;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
        limited--;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
    }

    void testLimitedRangeIntSubtractionGoesDownToMinValue()
    {
        LimitedRangeInt limited(-95,-100,100, true);
        limited -= 5;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
        limited -= 1;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());

        limited.set(-95);
        limited = limited - 5;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
        limited = limited - 1;
        CPPUNIT_ASSERT_EQUAL(-100, limited.value());
    }

    void testLimitedRangeIntSubtractionDoesNotUnderflow()
    {
        LimitedRangeInt limited(INT32_MIN,INT32_MIN,0, true);
        limited--;
        CPPUNIT_ASSERT_EQUAL(INT32_MIN, limited.value());
        limited -= 1;
        CPPUNIT_ASSERT_EQUAL(INT32_MIN, limited.value());
        limited = limited - 1;
        CPPUNIT_ASSERT_EQUAL(INT32_MIN, limited.value());
    }

    void testLimitedRangeCheckReturnsTrueForValuesInsideRange()
    {
        LimitedRangeInt limited(0, -10, 10, true);
        CPPUNIT_ASSERT(limited.check(-10));
        CPPUNIT_ASSERT(limited.check(-9));
        CPPUNIT_ASSERT(limited.check(0));
        CPPUNIT_ASSERT(limited.check(9));
        CPPUNIT_ASSERT(limited.check(10));
    }

    void testLimitedRangeCheckReturnsFalseForValuesOutsideRange()
    {
        LimitedRangeInt limited(0, -10, 10, true);
        CPPUNIT_ASSERT(!limited.check(-11));
        CPPUNIT_ASSERT(!limited.check(11));
        CPPUNIT_ASSERT(!limited.check(INT32_MIN));
        CPPUNIT_ASSERT(!limited.check(INT32_MAX));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(LimitedRangeIntClippedTest);
