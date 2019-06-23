#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "csvlog.h"

static char s_test_buffer[1024];
static uint32_t s_call_count = 0;

static int test_printer(char const * format, ...)
{
    int n = 0;
    va_list args;
    va_start(args, format);
    n = vsnprintf(s_test_buffer + strlen(s_test_buffer), 1024-strlen(s_test_buffer), format, args);
    va_end(args);
    s_call_count++;
    return n;
}

class CSVLogTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(CSVLogTest);

    CPPUNIT_TEST(testCSVLogDoesNotPrintWithNoFields);
    CPPUNIT_TEST(testCSVLogPrintsCharWithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsU8WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsU16WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsU32WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsU64WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsS8WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsS16WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsS32WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsS64WithDefaultFormatter);

    CPPUNIT_TEST_SUITE_END();

    void testCSVLogDoesNotPrintWithNoFields()
    {
        CSVLog testLogger(test_printer);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string(""), std::string(s_test_buffer));
        CPPUNIT_ASSERT_EQUAL(s_call_count, 0U);
    }

    void testCSVLogPrintsCharWithDefaultFormatter()
    {
        char cValue = 'a';
        CSVLog testLogger(test_printer);
        testLogger.AddField(&cValue, eCSVDataType_char, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("a\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsU8WithDefaultFormatter()
    {
        uint8_t u8Value = 0xFF;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&u8Value, eCSVDataType_u8, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("255\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsU16WithDefaultFormatter()
    {
        uint16_t u16Value = 0xFFFF;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&u16Value, eCSVDataType_u16, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("65535\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsU32WithDefaultFormatter()
    {
        uint32_t u32Value = 0xFFFFFFFF;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&u32Value, eCSVDataType_u32, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("4294967295\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsU64WithDefaultFormatter()
    {
        uint64_t u64Value = 0xFFFFFFFFFFFFFFFF;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&u64Value, eCSVDataType_u64, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("18446744073709551615\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsS8WithDefaultFormatter()
    {
        int8_t s8Value = (int8_t)0x80;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&s8Value, eCSVDataType_s8, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("-128\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsS16WithDefaultFormatter()
    {
        int16_t s16Value = (int16_t)0x8000;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&s16Value, eCSVDataType_s16, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("-32768\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsS32WithDefaultFormatter()
    {
        int32_t s32Value = (int32_t)0x80000000;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&s32Value, eCSVDataType_s32, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("-2147483648\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsS64WithDefaultFormatter()
    {
        int64_t s64Value = (int64_t)0x8000000000000000;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&s64Value, eCSVDataType_s64, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("-9223372036854775808\n"), std::string(s_test_buffer));
    }

public:
    void setUp()
    {
        s_test_buffer[0] = '\0';
        s_call_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CSVLogTest);
