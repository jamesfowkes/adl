#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "led-effect.hpp"

#define N_LARSON_LEDS 5

static uint8_t s_callback_count = 0;

void larson_value_callback(uint8_t index, uint8_t * pMultiplier, uint8_t * pDivisor)
{
    uint8_t multiplier = index+1;
    *pMultiplier = multiplier;
    *pDivisor = (N_LARSON_LEDS + 1) / 2;
    s_callback_count++;
}

class LEDEffectTest : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(LEDEffectTest);

    CPPUNIT_TEST(testLarsonScannerStart);
    CPPUNIT_TEST(testLarsonScannerMoveOnce);
    CPPUNIT_TEST(testLarsonScannerMoveToEnd);
    CPPUNIT_TEST(testLarsonScannerBounceAtRight);
    CPPUNIT_TEST(testLarsonScannerReturnToLeft);
    CPPUNIT_TEST(testLarsonScannerBounceAtLeft);
    CPPUNIT_TEST(testLarsonScannerRunOnce);
    CPPUNIT_TEST(testLarsonScannerRunSeveralTimes);
    CPPUNIT_TEST(testLarsonScannerRunForever);

    CPPUNIT_TEST_SUITE_END();

    void testLarsonScannerStart()
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

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerMoveOnce()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {
            {0, 0, 0},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF, 0xFF, 0xFF},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0, 0, 0}
        };

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        s_larson.update();
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerMoveToEnd()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF, 0xFF, 0xFF},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
        };

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        for (uint8_t i=0; i<15; i++)
        {
            s_larson.update();
        }

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerBounceAtRight()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF, 0xFF, 0xFF},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0, 0, 0},
        };

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        for (uint8_t i=0; i<16; i++)
        {
            s_larson.update();
        }

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerReturnToLeft()
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

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        for (uint8_t i=0; i<30; i++)
        {
            s_larson.update();
        }

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerBounceAtLeft()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {
            {0, 0, 0},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF, 0xFF, 0xFF},
            {0xFF*2/3, 0xFF*2/3, 0xFF*2/3},
            {0xFF*1/3, 0xFF*1/3, 0xFF*1/3},
            {0, 0, 0}
        };

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        for (uint8_t i=0; i<31; i++)
        {
            s_larson.update();
        }

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLarsonScannerRunOnce()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {0};

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255, 1);
        for (uint8_t i=0; i<29; i++)
        {
            CPPUNIT_ASSERT(s_larson.update());
        }

        CPPUNIT_ASSERT(!s_larson.update());

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
        CPPUNIT_ASSERT(s_callback_count > 0);
    }

    void testLarsonScannerRunSeveralTimes()
    {
        uint8_t actual[20][3] = {0xFF};
        uint8_t expected[20][3] = {0};

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255, 3);
        for (uint8_t i=0; i<89; i++)
        {
            CPPUNIT_ASSERT(s_larson.update());
        }

        CPPUNIT_ASSERT(!s_larson.update());

        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
        CPPUNIT_ASSERT(s_callback_count > 0);
    }

    void testLarsonScannerRunForever()
    {
        uint8_t actual[20][3] = {0xFF};

        LarsonScanner s_larson = LarsonScanner((uint8_t*)actual, 20, 5, larson_value_callback);
        s_larson.start(255,255,255);
        for (uint32_t i=0; i<999999; i++)
        {
            CPPUNIT_ASSERT(s_larson.update());
        }
        CPPUNIT_ASSERT(s_callback_count > 0);
    }

public:
    void setUp()
    {
        s_callback_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(LEDEffectTest);
