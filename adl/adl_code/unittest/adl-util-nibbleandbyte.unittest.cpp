#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "adl-util.h"

class NibbleAndByteTests : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(NibbleAndByteTests);

    CPPUNIT_TEST(testNibbleToHex);
    CPPUNIT_TEST(testByteToHex);

    CPPUNIT_TEST_SUITE_END();

    void testNibbleToHex()
    {      
        CPPUNIT_ASSERT_EQUAL('0', nibble_to_hex(0x0));
        CPPUNIT_ASSERT_EQUAL('1', nibble_to_hex(0x1));
        CPPUNIT_ASSERT_EQUAL('2', nibble_to_hex(0x2));
        CPPUNIT_ASSERT_EQUAL('3', nibble_to_hex(0x3));
        CPPUNIT_ASSERT_EQUAL('4', nibble_to_hex(0x4));
        CPPUNIT_ASSERT_EQUAL('5', nibble_to_hex(0x5));
        CPPUNIT_ASSERT_EQUAL('6', nibble_to_hex(0x6));
        CPPUNIT_ASSERT_EQUAL('7', nibble_to_hex(0x7));
        CPPUNIT_ASSERT_EQUAL('8', nibble_to_hex(0x8));
        CPPUNIT_ASSERT_EQUAL('9', nibble_to_hex(0x9));
        CPPUNIT_ASSERT_EQUAL('A', nibble_to_hex(0xA));
        CPPUNIT_ASSERT_EQUAL('B', nibble_to_hex(0xB));
        CPPUNIT_ASSERT_EQUAL('C', nibble_to_hex(0xC));
        CPPUNIT_ASSERT_EQUAL('D', nibble_to_hex(0xD));
        CPPUNIT_ASSERT_EQUAL('E', nibble_to_hex(0xE));
        CPPUNIT_ASSERT_EQUAL('F', nibble_to_hex(0xF));
    }

    void testByteToHex()
    {      
        char expected[3];
        char actual[3];
        for (uint16_t i=0; i<255; i++)
        {
            actual[0] = actual[1] = actual[2] = actual[3] = '\0';
            sprintf(expected, "%02X", i);
            byte_to_hex(actual, i);
            CPPUNIT_ASSERT_EQUAL(std::string(expected), std::string(actual));
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(NibbleAndByteTests);