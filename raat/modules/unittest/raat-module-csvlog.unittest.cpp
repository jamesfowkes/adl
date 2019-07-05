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
    CPPUNIT_TEST(testCSVLogPrintsStringWithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsFloatWithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsDoubleWithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsPointerWithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsIntegerWithCustomFormatter);
    CPPUNIT_TEST(testCSVLogPrintsStringWithCustomFormatter);
    CPPUNIT_TEST(testCSVLogPrintsMultipleFields);
    CPPUNIT_TEST(testCSVLogAddsPrefixIfSet);
    
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

    void testCSVLogPrintsStringWithDefaultFormatter()
    {
        char cString[] = "Test String";
        CSVLog testLogger(test_printer);
        testLogger.AddField(cString, eCSVDataType_str, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("Test String\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsFloatWithDefaultFormatter()
    {
        float fFloat = 3.141592f;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&fFloat, eCSVDataType_float, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("3.141592\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsDoubleWithDefaultFormatter()
    {
        double fDouble = 3.141592f;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&fDouble, eCSVDataType_double, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("3.141592\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsPointerWithDefaultFormatter()
    {
        void * pPointer = (void*)0xDEADBEEF;
        CSVLog testLogger(test_printer);
        testLogger.AddField(pPointer, eCSVDataType_ptr, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("0xdeadbeef\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsIntegerWithCustomFormatter()
    {
        uint32_t toPrintWithHexFormat = 0x3141;
        CSVLog testLogger(test_printer);
        testLogger.AddField(&toPrintWithHexFormat, eCSVDataType_u32, "0x%08X");
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("0x00003141\n"), std::string(s_test_buffer));   
    }

    void testCSVLogPrintsStringWithCustomFormatter()
    {
        char toPrintWithLeadingSpaces[] = "ABC";
        CSVLog testLogger(test_printer);
        testLogger.AddField(toPrintWithLeadingSpaces, eCSVDataType_str, "%6s");
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("   ABC\n"), std::string(s_test_buffer));   
    }

    void testCSVLogPrintsMultipleFields()
    {
        char field1 = 'Z';
        uint8_t field2 = 100;
        int32_t field3 = -12345678;
        float field4 = 1.141f;
        char field5[] = "Hello!";

        CSVLog testLogger(test_printer);
        testLogger.AddField(&field1, eCSVDataType_char, NULL);
        testLogger.AddField(&field2, eCSVDataType_u8, NULL);
        testLogger.AddField(&field3, eCSVDataType_s32, NULL);
        testLogger.AddField(&field4, eCSVDataType_float, NULL);
        testLogger.AddField(field5, eCSVDataType_str, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("Z,100,-12345678,1.141000,Hello!\n"), std::string(s_test_buffer));
    }

    void testCSVLogAddsPrefixIfSet()
    {
        char str[] = "Hello!";
        CSVLog testLogger(test_printer, "PREFIX");
        testLogger.AddField(str, eCSVDataType_str, NULL);
        testLogger.PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("PREFIX, Hello!\n"), std::string(s_test_buffer));
    }

public:
    void setUp()
    {
        s_test_buffer[0] = '\0';
        s_call_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CSVLogTest);
