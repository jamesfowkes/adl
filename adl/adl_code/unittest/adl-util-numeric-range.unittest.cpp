#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "adl-util.h"

char s_test_string[32];
bool b_result;
char * p_result;
int32_t min;
int32_t max;

static void test_range_conversion_with_string(char const * string)
{
    if (string)
    {
        strcpy(s_test_string, string);
        b_result = adl_convert_numeric_range(s_test_string, min, max, &p_result);        
    }
    else
    {
        b_result = adl_convert_numeric_range(NULL, min, max, &p_result);
    }
}

class NumericRangeTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(NumericRangeTest);

    CPPUNIT_TEST(testConvertNumericRangeWithNullReturnsNull);
    CPPUNIT_TEST(testConvertNumericRangeWithEmptyStringReturnsNull);
    CPPUNIT_TEST(testConvertNumericRangeWithNonNumericStringReturnsNull);
    CPPUNIT_TEST(testConvertNumericRangeWithNonNumericRangeReturnsNull);
    
    CPPUNIT_TEST(testConvertNumericRangeWithSingleDigitBelowZero);
    CPPUNIT_TEST(testConvertNumericRangeWithSingleDigitZero);
    CPPUNIT_TEST(testConvertNumericRangeWithSingleDigitAboveZero);
    CPPUNIT_TEST(testConvertNumericRangeWithBothNumbersTheSame);
    CPPUNIT_TEST(testConvertNumericRangeWithBothNumbersPositive);
    CPPUNIT_TEST(testConvertNumericRangeWithBothNumbersNegative);
    CPPUNIT_TEST(testConvertNumericRangeWithNegativeAndPositive);

    CPPUNIT_TEST_SUITE_END();
 
    void testConvertNumericRangeWithNullReturnsNull() {

        test_range_conversion_with_string(NULL);
        CPPUNIT_ASSERT(NULL == p_result);
    }

    void testConvertNumericRangeWithEmptyStringReturnsNull() {
        test_range_conversion_with_string("");
        CPPUNIT_ASSERT(NULL == p_result);
    }

    void testConvertNumericRangeWithNonNumericStringReturnsNull() {
        test_range_conversion_with_string("A");
        CPPUNIT_ASSERT(NULL == p_result);
    }

    void testConvertNumericRangeWithNonNumericRangeReturnsNull() {
        test_range_conversion_with_string("0:A");
        CPPUNIT_ASSERT(NULL == p_result);
        test_range_conversion_with_string("A:0");
        CPPUNIT_ASSERT(NULL == p_result);
        test_range_conversion_with_string("A:A");
        CPPUNIT_ASSERT(NULL == p_result);
    }

    void testConvertNumericRangeWithSingleDigitBelowZero() {
        test_range_conversion_with_string("-1");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+2), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(-1, min);
        CPPUNIT_ASSERT_EQUAL(-1, max);
    }

    void testConvertNumericRangeWithSingleDigitZero() {
        test_range_conversion_with_string("0");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+1), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(0, min);
        CPPUNIT_ASSERT_EQUAL(0, max);
    }
    
    void testConvertNumericRangeWithSingleDigitAboveZero() {    
        test_range_conversion_with_string("1");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+1), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(1, min);
        CPPUNIT_ASSERT_EQUAL(1, max);
    }

    void testConvertNumericRangeWithBothNumbersTheSame() {
        test_range_conversion_with_string("0:0");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+3), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(0, min);
        CPPUNIT_ASSERT_EQUAL(0, max);
    }

    void testConvertNumericRangeWithBothNumbersPositive() {
        test_range_conversion_with_string("1:10");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+4), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(1, min);
        CPPUNIT_ASSERT_EQUAL(10, max);
    }

    void testConvertNumericRangeWithBothNumbersNegative() {
        test_range_conversion_with_string("-10:-1");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+6), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(-10, min);
        CPPUNIT_ASSERT_EQUAL(-1, max);
    }

    void testConvertNumericRangeWithNegativeAndPositive()
    {
        test_range_conversion_with_string("-10:10");
        CPPUNIT_ASSERT_EQUAL((void*)(s_test_string+6), (void*)p_result);
        CPPUNIT_ASSERT_EQUAL(-10, min);
        CPPUNIT_ASSERT_EQUAL(10, max);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( NumericRangeTest );