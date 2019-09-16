#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat.hpp"
#include "raat-buffer.hpp"

#include "http-get-server.hpp"

class RAATModuleHTTPGetServerTest : public CppUnit::TestFixture { 

    CPPUNIT_TEST_SUITE(RAATModuleHTTPGetServerTest);

    //CPPUNIT_TEST(testOneShotTaskInitsCorrectly);

    CPPUNIT_TEST_SUITE_END();

    //void testOneShotTaskInitsCorrectly()
    //{
    //}


public:
    void setUp()
    {
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(RAATModuleHTTPGetServerTest);
