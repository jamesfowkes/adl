#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat-util.h"

class SingleNumericTest : public CppUnit::TestFixture { 

    char * p_result;
    
    CPPUNIT_TEST_SUITE(SingleNumericTest);

    CPPUNIT_TEST(testConvertSingleNumericReturnsFalseForNull);
    CPPUNIT_TEST(testConvertSingleNumericReturnsFalseForEmptyString);
    CPPUNIT_TEST(testConvertSingleNumericReturnsFalseForNonNumericString);
    CPPUNIT_TEST(testConvertSingleNumericReturnsTrueForNumericString);

    CPPUNIT_TEST_SUITE_END();
    void testConvertSingleNumericReturnsFalseForNull()
    {
        int32_t num;
        CPPUNIT_ASSERT(!raat_parse_single_numeric(NULL, num, &p_result));
    }

    void testConvertSingleNumericReturnsFalseForEmptyString()
    {
        int32_t num;
        CPPUNIT_ASSERT(!raat_parse_single_numeric("", num, &p_result));
    }

    void testConvertSingleNumericReturnsFalseForNonNumericString()
    {
        int32_t num;
        CPPUNIT_ASSERT(!raat_parse_single_numeric("A", num, &p_result));
    }

    void testConvertSingleNumericReturnsTrueForNumericString()
    {
        int32_t num;
        CPPUNIT_ASSERT(raat_parse_single_numeric("0", num, &p_result));
        CPPUNIT_ASSERT_EQUAL(num, 0);
        CPPUNIT_ASSERT(raat_parse_single_numeric("1", num, &p_result));
        CPPUNIT_ASSERT_EQUAL(num, 1);
        CPPUNIT_ASSERT(raat_parse_single_numeric("-1", num, &p_result));
        CPPUNIT_ASSERT_EQUAL(num, -1);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(SingleNumericTest);