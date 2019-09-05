#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat-util.hpp"


class ArrayUtilsParserTest : public CppUnit::TestFixture { 

    char * p_result;
    
    CPPUNIT_TEST_SUITE(ArrayUtilsParserTest);

    CPPUNIT_TEST(testAnyAreNullReturnsFalseForEmptyOrNULLArray);
    CPPUNIT_TEST(testAnyAreNullReturnsFalseForNonNullArray);
    CPPUNIT_TEST(testAnyAreNullReturnsFalseForNonNullArrayWithLimit);
    CPPUNIT_TEST(testAnyAreNullReturnsTrueForArrayWithNulls);
    CPPUNIT_TEST(testAnyAreNullReturnsTrueForArrayWithNullsWithLimit);
    CPPUNIT_TEST(testAllMatchReturnsFalseForEmptyOrNullArray);
    CPPUNIT_TEST(testAllMatchReturnsFalseForNonMatchingArray);
    CPPUNIT_TEST(testAllMatchReturnsTrueForMatchingArray);
    CPPUNIT_TEST(testAllMatchReturnsTrueForMatchingArrayWithLimit);

    CPPUNIT_TEST_SUITE_END();

    void testAnyAreNullReturnsFalseForEmptyOrNULLArray()
    {
        void * array[1];
        CPPUNIT_ASSERT(!any_are_null(NULL, 0));
        CPPUNIT_ASSERT(!any_are_null(NULL, 1));
        CPPUNIT_ASSERT(!any_are_null(array, 0));
    }

    void testAnyAreNullReturnsFalseForNonNullArray()
    {
        void * array[10] = {(void*)1, (void*)2, (void*)3, (void*)4, (void*)5, (void*)6, (void*)7, (void*)8, (void*)9 , (void*)10};
        CPPUNIT_ASSERT(!any_are_null(array, 10));
    }

    void testAnyAreNullReturnsFalseForNonNullArrayWithLimit()
    {
        void * array[10] = {(void*)1, (void*)2, (void*)3, (void*)4, (void*)5, NULL, NULL, NULL, NULL, NULL};
        CPPUNIT_ASSERT(!any_are_null(array, 5));
    }

    void testAnyAreNullReturnsTrueForArrayWithNulls()
    {
        void * array[10] = {(void*)1, (void*)2, (void*)3, (void*)4, (void*)5, (void*)6, (void*)7, (void*)8, (void*)9 , NULL};
        CPPUNIT_ASSERT(any_are_null(array, 10));
    }

    void testAnyAreNullReturnsTrueForArrayWithNullsWithLimit()
    {
        void * array[10] = {(void*)1, (void*)2, (void*)3, (void*)4, NULL, NULL, NULL, NULL, NULL, NULL};
        CPPUNIT_ASSERT(any_are_null(array, 5));
    }

    void testAllMatchReturnsFalseForEmptyOrNullArray()
    {
        char array[1];
        CPPUNIT_ASSERT(!(all_match<char>(NULL, 0)));
        CPPUNIT_ASSERT(!(all_match<char>(NULL, 1)));
        CPPUNIT_ASSERT(!(all_match<char>(array, 0)));
    }

    void testAllMatchReturnsFalseForNonMatchingArray()
    {
        char array[] = "AAAAAAAAAB";
        CPPUNIT_ASSERT(!all_match<char>(array, 10));
    }

    void testAllMatchReturnsTrueForMatchingArray()
    {
        char array[] = "AAAAAAAAAA";
        CPPUNIT_ASSERT(all_match<char>(array, 10));
    }

    void testAllMatchReturnsTrueForMatchingArrayWithLimit()
    {
        char array[] = "AAAAABBBBB";
        CPPUNIT_ASSERT(all_match<char>(array, 5));
    }

public:
    void setUp()
    {
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayUtilsParserTest);
