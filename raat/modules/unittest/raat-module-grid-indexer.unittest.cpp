#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "grid-indexer.hpp"

class GridIndexerTest : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(GridIndexerTest);

    CPPUNIT_TEST(testLength1);
    CPPUNIT_TEST(testLength2);
    CPPUNIT_TEST(testLength3);
    
    CPPUNIT_TEST_SUITE_END();

    void testLength1()
    {
        GridIndexer s_indexer = GridIndexer(1);
        for (int i = 0; i<255; i++)
        { 
            CPPUNIT_ASSERT_EQUAL(i, (int)s_indexer.get(i));
        }
    }

    void testLength2()
    {
        GridIndexer s_indexer = GridIndexer(2);
        CPPUNIT_ASSERT_EQUAL(0, (int)s_indexer.get(0));
        CPPUNIT_ASSERT_EQUAL(1, (int)s_indexer.get(1));
        CPPUNIT_ASSERT_EQUAL(3, (int)s_indexer.get(2));
        CPPUNIT_ASSERT_EQUAL(2, (int)s_indexer.get(3));
        CPPUNIT_ASSERT_EQUAL(4, (int)s_indexer.get(4));
        CPPUNIT_ASSERT_EQUAL(5, (int)s_indexer.get(5));
    }


    void testLength3()
    {
        GridIndexer s_indexer = GridIndexer(3);
        CPPUNIT_ASSERT_EQUAL(0, (int)s_indexer.get(0));
        CPPUNIT_ASSERT_EQUAL(1, (int)s_indexer.get(1));
        CPPUNIT_ASSERT_EQUAL(2, (int)s_indexer.get(2));
        CPPUNIT_ASSERT_EQUAL(5, (int)s_indexer.get(3));
        CPPUNIT_ASSERT_EQUAL(4, (int)s_indexer.get(4));
        CPPUNIT_ASSERT_EQUAL(3, (int)s_indexer.get(5));
        CPPUNIT_ASSERT_EQUAL(6, (int)s_indexer.get(6));
        CPPUNIT_ASSERT_EQUAL(7, (int)s_indexer.get(7));
        CPPUNIT_ASSERT_EQUAL(8, (int)s_indexer.get(8));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(GridIndexerTest);