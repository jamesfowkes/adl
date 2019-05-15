#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat.hpp"
#include "boolean-param.hpp"

#include "raat-mock.hpp"

class BooleanParameterTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(BooleanParameterTest);

    CPPUNIT_TEST(testBooleanParameterInitsToResetValue);
    CPPUNIT_TEST(testBooleanParameterSetReturnsTrueAndStateIsSet);
    CPPUNIT_TEST(testBooleanParameterResetsToResetValue);
    CPPUNIT_TEST(testBooleanParameterCorrectlyWorksWithNonvolatile);
    CPPUNIT_TEST(testBooleanParameterCorrectlyWorksWithMultipleNonvolatiles);
    CPPUNIT_TEST(testBooleanParameterChangeIsNotSetOnInit);
    CPPUNIT_TEST(testBooleanParameterChangeIsSetOnSetup);
    CPPUNIT_TEST(testBooleanParameterChangeIsSetOnSet);
    CPPUNIT_TEST(testBooleanParameterChangeIsSetOnReset);

    CPPUNIT_TEST_SUITE_END();

    void testBooleanParameterInitsToResetValue()
    {
        BooleanParam param = BooleanParam(false, false);
        CPPUNIT_ASSERT_EQUAL(false, param.get());
        param = BooleanParam(true, false);
        CPPUNIT_ASSERT_EQUAL(true, param.get());
    }

    void testBooleanParameterSetReturnsTrueAndStateIsSet()
    {
        BooleanParam param = BooleanParam(false, false);
        CPPUNIT_ASSERT(param.set(true));
        CPPUNIT_ASSERT_EQUAL(true, param.get());
        CPPUNIT_ASSERT(param.set(false));
        CPPUNIT_ASSERT_EQUAL(false, param.get());
    }

    void testBooleanParameterResetsToResetValue()
    {
        BooleanParam param = BooleanParam(false, false);
        param.set(true);
        param.reset();
        CPPUNIT_ASSERT_EQUAL(false, param.get());
    }

    void testBooleanParameterCorrectlyWorksWithNonvolatile()
    {
        BooleanParam param = BooleanParam(false, true);
        param.setup();
        param.set(true);
        CPPUNIT_ASSERT_EQUAL(true, *(bool*)raat_mock_nonvolatile_get_last_write());
    }

    void testBooleanParameterCorrectlyWorksWithMultipleNonvolatiles()
    {
        BooleanParam param1 = BooleanParam(false, true);
        BooleanParam param2 = BooleanParam(false, true);
        
        param1.set(true);

        param2.set(true);

        param1.set(false);

        CPPUNIT_ASSERT_EQUAL(true, *(bool*)raat_mock_nonvolatile_get_last_write());
    }

    void testBooleanParameterChangeIsNotSetOnInit()
    {
        BooleanParam param = BooleanParam(false, false);
        CPPUNIT_ASSERT(!param.has_changed());
    }

    void testBooleanParameterChangeIsSetOnSetup()
    {
        BooleanParam param = BooleanParam(false, true);
        param.setup();
        CPPUNIT_ASSERT(param.has_changed());
    }

    void testBooleanParameterChangeIsSetOnSet()
    {
        BooleanParam param = BooleanParam(false, false);
        param.set(true);
        CPPUNIT_ASSERT(param.has_changed());
        param.reset();
    }

    void testBooleanParameterChangeIsSetOnReset()
    {
        BooleanParam param = BooleanParam(false, false);
        param.set(true);
        (void)param.has_changed();
        param.reset();
        CPPUNIT_ASSERT(param.has_changed());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(BooleanParameterTest);
