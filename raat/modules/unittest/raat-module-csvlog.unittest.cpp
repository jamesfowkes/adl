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
    CPPUNIT_TEST(testCSVLogPrintsU8WithDefaultFormatter);
    CPPUNIT_TEST(testCSVLogPrintsU16WithDefaultFormatter);

    CPPUNIT_TEST_SUITE_END();

    void testCSVLogDoesNotPrintWithNoFields()
    {
        CSVLog_PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string(""), std::string(s_test_buffer));
        CPPUNIT_ASSERT_EQUAL(s_call_count, 0U);
    }

    void testCSVLogPrintsU8WithDefaultFormatter()
    {
        uint8_t u8Value = 0xFF;
        CSVLog_AddField(&u8Value, eCSVDataType_u8, NULL);
        CSVLog_PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("255\n"), std::string(s_test_buffer));
    }

    void testCSVLogPrintsU16WithDefaultFormatter()
    {
        uint16_t u16Value = 0xFFFF;
        CSVLog_AddField(&u16Value, eCSVDataType_u16, NULL);
        CSVLog_PrintNow();
        CPPUNIT_ASSERT_EQUAL(std::string("65535\n"), std::string(s_test_buffer));
    }

public:
    void setUp()
    {
        CSVLog_Init(test_printer);
        s_test_buffer[0] = '\0';
        s_call_count = 0;
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CSVLogTest);
