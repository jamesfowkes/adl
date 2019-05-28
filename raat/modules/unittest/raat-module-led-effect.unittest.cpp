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

class LarsonScannerTest : public CppUnit::TestFixture { 

    int32_t numbers[16];

    CPPUNIT_TEST_SUITE(LarsonScannerTest);

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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

        LarsonScanner<uint8_t> s_larson = LarsonScanner<uint8_t>((uint8_t*)actual, 20, 5, larson_value_callback);
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

class LEDFaderTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(LEDFaderTest);

    CPPUNIT_TEST(testLEDFaderZeroAfterDirectionUpStart);
    CPPUNIT_TEST(testLEDFaderMaxAfterDirectionDownStart);
    CPPUNIT_TEST(testLEDFaderMaxAfterDirectionDownStartWithDifferentRGBValues);
    CPPUNIT_TEST(testLEDFaderLinearlyIncreasingUpdates);
    CPPUNIT_TEST(testLEDFaderLinearlyDecreasingUpdates);

    CPPUNIT_TEST_SUITE_END();

    void testLEDFaderZeroAfterDirectionUpStart()
    {
        uint8_t actual[20][3];
        memset(actual, 0xFF, 60);

        uint8_t expected[20][3];
        
        LEDFader<uint8_t> s_fader = LEDFader<uint8_t>((uint8_t*)actual, 20, LEDFaderType_Linear);
        s_fader.start(true, 255, 255, 255, 255);
        memset(expected, 0x00, 60);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLEDFaderMaxAfterDirectionDownStart()
    {
        uint8_t actual[20][3];
        memset(actual, 0xFF, 60);

        uint8_t expected[20][3];
        
        LEDFader<uint8_t> s_fader = LEDFader<uint8_t>((uint8_t*)actual, 20, LEDFaderType_Linear);
        s_fader.start(false, 50, 100, 200, 255);
        for (uint8_t i = 0; i < 20; i++)
        {
            expected[i][0] = 50;
            expected[i][1] = 100;
            expected[i][2] = 200;
        }
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLEDFaderMaxAfterDirectionDownStartWithDifferentRGBValues()
    {
        uint8_t actual[20][3];
        memset(actual, 0xFF, 60);

        uint8_t expected[20][3];
        
        LEDFader<uint8_t> s_fader = LEDFader<uint8_t>((uint8_t*)actual, 20, LEDFaderType_Linear);
        s_fader.start(false, 255, 255, 255, 255);
        memset(expected, 255, 60);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }


    void testLEDFaderLinearlyIncreasingUpdates()
    {
        uint8_t actual[20][3];
        memset(actual, 0xFF, 60);

        uint8_t expected[20][3];

        LEDFader<uint8_t> s_fader = LEDFader<uint8_t>((uint8_t*)actual, 20, LEDFaderType_Linear);
        s_fader.start(true, 255, 255, 255, 255);

        for (uint16_t i = 0; i<254; i++)
        {
            CPPUNIT_ASSERT(s_fader.update());
            memset(expected, i+1, 60);
            CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
        }
        CPPUNIT_ASSERT(!s_fader.update());
        memset(expected, 255, 60);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

    void testLEDFaderLinearlyDecreasingUpdates()
    {
        uint8_t actual[20][3];
        memset(actual, 0xFF, 60);

        uint8_t expected[20][3];

        LEDFader<uint8_t> s_fader = LEDFader<uint8_t>((uint8_t*)actual, 20, LEDFaderType_Linear);
        s_fader.start(false, 255, 255, 255, 255);

        for (uint16_t i = 0; i<254; i++)
        {
            CPPUNIT_ASSERT(s_fader.update());
            memset(expected, 255-i-1, 60);
            CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
        }
        CPPUNIT_ASSERT(!s_fader.update());
        memset(expected, 0, 60);
        CPPUNIT_ASSERT_EQUAL(0, memcmp(actual, expected, 60));
    }

public:
    void setUp()
    {
        s_callback_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(LarsonScannerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(LEDFaderTest);
