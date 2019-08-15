#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat-util.hpp"

static const int32_t EMPTY_ARRAY[16] = {INT16_MAX};

static void make_array_empty(int32_t * array)
{
    for (uint8_t i=0; i<16; i++)
    {
        array[i] = INT16_MAX;
    }
}

static bool array_is_empty(int32_t * array)
{
    bool empty = true;
    for (uint8_t i=0; i<16; i++)
    {
        empty &= (array[i] == INT16_MAX);
    }
    return empty;
}

class CSVNumericsTest : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(CSVNumericsTest);

    CPPUNIT_TEST(testConvertCSVReturnsZeroAndDoesNotFillArrayForNull);
    CPPUNIT_TEST(testConvertCSVReturnsZeroAndDoesNotFillArrayForEmptyString);
    CPPUNIT_TEST(testConvertCSVReturnsZeroAndDoesNotFillArrayForNonNumericString);
    CPPUNIT_TEST(testConvertCSVConvertsSingleNumberWithoutComma);
    CPPUNIT_TEST(testConvertCSVConvertsTwoCSVNumbers);
    CPPUNIT_TEST(testConvertCSVConvertsThreeCSVNumbers);

    CPPUNIT_TEST_SUITE_END();

    void testConvertCSVReturnsZeroAndDoesNotFillArrayForNull()
    {      
        CPPUNIT_ASSERT_EQUAL((uint8_t)0, raat_parse_comma_separated_numerics<int32_t>(NULL, numbers));
        CPPUNIT_ASSERT(array_is_empty(numbers));
        CPPUNIT_ASSERT_EQUAL((uint8_t)0, raat_parse_comma_separated_numerics<int32_t>("1,2,3", NULL));
        CPPUNIT_ASSERT(array_is_empty(numbers));
    }

    void testConvertCSVReturnsZeroAndDoesNotFillArrayForEmptyString()
    {
        CPPUNIT_ASSERT_EQUAL((uint8_t)0, raat_parse_comma_separated_numerics<int32_t>("", numbers));
        CPPUNIT_ASSERT(array_is_empty(numbers));
    }

    void testConvertCSVReturnsZeroAndDoesNotFillArrayForNonNumericString()
    {
        CPPUNIT_ASSERT_EQUAL((uint8_t)0, raat_parse_comma_separated_numerics<int32_t>("A", numbers));
        CPPUNIT_ASSERT_EQUAL((uint8_t)0, raat_parse_comma_separated_numerics<int32_t>("A,A", numbers));
    }

    void testConvertCSVConvertsSingleNumberWithoutComma()
    {
        CPPUNIT_ASSERT_EQUAL((uint8_t)1, raat_parse_comma_separated_numerics<int32_t>("1", numbers));
        CPPUNIT_ASSERT_EQUAL(1, numbers[0]);
    }

    void testConvertCSVConvertsTwoCSVNumbers()
    {
        CPPUNIT_ASSERT_EQUAL((uint8_t)2, raat_parse_comma_separated_numerics<int32_t>("1,2", numbers));
        CPPUNIT_ASSERT_EQUAL(1, numbers[0]);
        CPPUNIT_ASSERT_EQUAL(2, numbers[1]);
    }

    void testConvertCSVConvertsThreeCSVNumbers()
    {
        CPPUNIT_ASSERT_EQUAL((uint8_t)3, raat_parse_comma_separated_numerics<int32_t>("1,2,3", numbers));
        CPPUNIT_ASSERT_EQUAL(1, numbers[0]);
        CPPUNIT_ASSERT_EQUAL(2, numbers[1]);
        CPPUNIT_ASSERT_EQUAL(3, numbers[2]);
    }

public:
    void setUp()
    {
        make_array_empty(numbers);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CSVNumericsTest);