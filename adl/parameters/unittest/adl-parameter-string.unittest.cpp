#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "adl.h"
#include "string-param.h"

#include "adl-mock.h"

static char scratchpad[64];

class StringTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(StringTest);

    CPPUNIT_TEST(testStringParameterInitsToResetValue);
    CPPUNIT_TEST(testStringParameterValidSetCorrectlySetsValue);
    CPPUNIT_TEST(testStringParameterInitWithNullResetResetsToBlankString);
    CPPUNIT_TEST(testStringParameterResetsToResetValue);
    CPPUNIT_TEST(testStringParameterWillSetAtMaxLength);
    CPPUNIT_TEST(testStringParameterWillNotSetOverMaxLength);
    CPPUNIT_TEST(testStringParameterCorrectlyWorksWithNonvolatile);

    CPPUNIT_TEST_SUITE_END();

    void testStringParameterInitsToResetValue()
    {
        StringParam param = StringParam("RESET", 32, false);
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("RESET"), std::string(scratchpad));
    }

    void testStringParameterValidSetCorrectlySetsValue()
    {
        StringParam param = StringParam("RESET", 32, false);
        CPPUNIT_ASSERT(param.set("TEST"));
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("TEST"), std::string(scratchpad));
    }

    void testStringParameterInitWithNullResetResetsToBlankString()
    {
        StringParam param = StringParam(NULL, 32, false);
        CPPUNIT_ASSERT(param.set("TEST"));
        param.reset();
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string(""), std::string(scratchpad));
    }

    void testStringParameterResetsToResetValue()
    {
        StringParam param = StringParam("RESET", 32, false);
        CPPUNIT_ASSERT(param.set("TEST"));
        param.reset();
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("RESET"), std::string(scratchpad));
    }

    void testStringParameterWillSetAtMaxLength()
    {
        StringParam param = StringParam("RESET", 8, false);
        CPPUNIT_ASSERT(param.set("TESTTEST"));
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("TESTTEST"), std::string(scratchpad));
    }

    void testStringParameterWillNotSetOverMaxLength()
    {
        StringParam param = StringParam("RESET", 7, false);
        CPPUNIT_ASSERT(!param.set("TESTTEST"));
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("RESET"), std::string(scratchpad));
    }

    void testStringParameterCorrectlyWorksWithNonvolatile()
    {
        StringParam param = StringParam("RESET", 32, true);
        param.set("TEST");
        CPPUNIT_ASSERT_EQUAL(std::string("TEST"), std::string((char*)adl_mock_nonvolatile_get_last_write()));
    }

public:
    void setUp()
    {
        memset(scratchpad, 0, 64);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);
