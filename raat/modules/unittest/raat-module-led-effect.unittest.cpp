#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "led-effect.hpp"

static void shiftRightOnce(uint8_t * p, uint8_t n)
{
    int8_t max_index = (n*3)-1;
    for (int8_t i=max_index; i>=0; i--)
    {
        p[i] = p[i-1];
    }
    p[0] = 0;
}

static void shiftRightValues(uint8_t * p, uint8_t n)
{
    shiftRightOnce(p,n);
    shiftRightOnce(p,n);
    shiftRightOnce(p,n);
}

class LEDEffectTest : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(LEDEffectTest);

    CPPUNIT_TEST(testLarsonScanner);
    
    CPPUNIT_TEST_SUITE_END();

    void testLarsonScanner()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF, 0xFF, 0xFF},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0, 0, 0}
        };

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5);
        s_larson.start(255,255,255);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));

        shiftRightValues((uint8_t*)expected, 20);
        s_larson.print((uint8_t*)expected, 0, 6);
        s_larson.update();
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(LEDEffectTest);
