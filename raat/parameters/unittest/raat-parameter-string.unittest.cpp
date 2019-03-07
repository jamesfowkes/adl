#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat.hpp"
#include "string-param.hpp"

#include "raat-mock.hpp"

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
    CPPUNIT_TEST(testStringParameterCorrectlyWorksWithMultipleNonvolatiles);
    CPPUNIT_TEST(testStringParameterCorrectlyLoadsFromNonvolatile);
    CPPUNIT_TEST(testStringParameterChangeIsNotSetOnInit);
    CPPUNIT_TEST(testStringParameterChangeIsSetOnSetup);
    CPPUNIT_TEST(testStringParameterChangeIsSetOnSet);
    CPPUNIT_TEST(testStringParameterChangeIsSetOnReset);
    CPPUNIT_TEST(testStringParameterStrncmp);

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
        param.setup();
        param.set("TEST");
        CPPUNIT_ASSERT_EQUAL(std::string("TEST"), std::string((char*)raat_mock_nonvolatile_get_last_write()));
    }

    void testStringParameterCorrectlyWorksWithMultipleNonvolatiles()
    {
        StringParam param1 = StringParam("RESET", 32, true);
        param1.setup();
        StringParam param2 = StringParam("RESET", 32, true);
        param2.setup();
        param1.set("TEST1");
        CPPUNIT_ASSERT_EQUAL(std::string("TEST1"), std::string((char*)raat_mock_nonvolatile_get_last_write()));
        param2.set("TEST2");
        CPPUNIT_ASSERT_EQUAL(std::string("TEST2"), std::string((char*)raat_mock_nonvolatile_get_last_write()));
    }

    void testStringParameterCorrectlyLoadsFromNonvolatile()
    {
        char data[] = "TO LOAD";
        raat_mock_nonvolatile_set(0, sizeof(data), &data);
        
        StringParam param = StringParam("RESET", 32, true);
        param.setup();
        param.get(scratchpad);
        CPPUNIT_ASSERT_EQUAL(std::string("TO LOAD"), std::string(scratchpad));
    }

    void testStringParameterChangeIsNotSetOnInit()
    {
        StringParam param = StringParam("RESET", 32, true);
        CPPUNIT_ASSERT(!param.has_changed());
    }

    void testStringParameterChangeIsSetOnSetup()
    {
        StringParam param = StringParam("RESET", 32, true);
        param.setup();
        CPPUNIT_ASSERT(param.has_changed());
    }

    void testStringParameterChangeIsSetOnSet()
    {
        StringParam param = StringParam("RESET", 32, true);
        param.set("TEST");
        CPPUNIT_ASSERT(param.has_changed());
        param.reset();
    }

    void testStringParameterChangeIsSetOnReset()
    {
        StringParam param = StringParam("RESET", 32, true);
        param.set("TEST");
        (void)param.has_changed();
        param.reset();
        CPPUNIT_ASSERT(param.has_changed());
    }

    void testStringParameterStrncmp()
    {
        StringParam param = StringParam("RESET", 32, true);
        CPPUNIT_ASSERT(param.strncmp(NULL, 0) == 0);
        CPPUNIT_ASSERT(param.strncmp(NULL, sizeof("RESET")) == 0);
        CPPUNIT_ASSERT(param.strncmp("RESET", 0) == 0);
        CPPUNIT_ASSERT(param.strncmp("RESETAAAAA", sizeof("RESET")) != 0);
        CPPUNIT_ASSERT(param.strncmp("RE", sizeof("RESET")) != 0);
        CPPUNIT_ASSERT(param.strncmp("RESET", sizeof("RESET")) == 0);
    }

public:
    void setUp()
    {
        memset(scratchpad, 0, 64);
        raat_mock_nonvolatile_reset();
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringTest);

