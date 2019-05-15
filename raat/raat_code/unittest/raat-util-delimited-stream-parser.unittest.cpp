#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "raat-util.hpp"
#include "raat-util-delimited-stream-parser.hpp"

static char buffer[9];
static raat_string_buffer s_raat_buffer = {buffer, 9};

static char sp_parsed_string[9];

void on_string_parsed(char * s)
{
    strcpy(sp_parsed_string, s);
}

static void run_through_parser(DelimitedStreamParser& parser, char const * s)
{
    while (*s)
    {
        parser.run(*s);
        s++;
    }
}

class DelimitedStreamParserTest : public CppUnit::TestFixture { 

    char * p_result;
    
    CPPUNIT_TEST_SUITE(DelimitedStreamParserTest);

    CPPUNIT_TEST(testParserDoesNotAcceptNullEndDelimiter);
    CPPUNIT_TEST(testParserAcceptsNullStartDelimiter);
    CPPUNIT_TEST(testParserAcceptsNonNullStartDelimiter);
    CPPUNIT_TEST(testParserDoesNotParseBeyondEndOfBuffer);
    CPPUNIT_TEST(testParserParsesWithoutStartChar);
    CPPUNIT_TEST(testParserParsesMultipleStringsWithoutStartChar);
    CPPUNIT_TEST(testParserParsesWithStartChar);
    CPPUNIT_TEST(testParserParsesMultipleStringsWithStartChar);

    CPPUNIT_TEST_SUITE_END();

    void testParserDoesNotAcceptNullEndDelimiter()
    {
        DelimitedStreamParser parser(',', '\0', s_raat_buffer, on_string_parsed);
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_ERROR, parser.state());
    }

    void testParserAcceptsNullStartDelimiter()
    {
        DelimitedStreamParser parser('\0', ',', s_raat_buffer, on_string_parsed);
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_PARSING, parser.state());
    }

    void testParserAcceptsNonNullStartDelimiter()
    {
        DelimitedStreamParser parser('>', ',', s_raat_buffer, on_string_parsed);
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_WAITING, parser.state());
    }

    void testParserDoesNotParseBeyondEndOfBuffer()
    {
        DelimitedStreamParser parser('\0', ',', s_raat_buffer, on_string_parsed);
        run_through_parser(parser, "THISSTRINGISTOOLONG");
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_OVERFLOW, parser.state());
    }

    void testParserParsesWithoutStartChar()
    {
        DelimitedStreamParser parser('\0', ',', s_raat_buffer, on_string_parsed);
        run_through_parser(parser, "FIELD1,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD1"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_PARSING, parser.state());
    }

    void testParserParsesMultipleStringsWithoutStartChar()
    {
        DelimitedStreamParser parser('\0', ',', s_raat_buffer, on_string_parsed);
        run_through_parser(parser, "FIELD1,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD1"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_PARSING, parser.state());
        run_through_parser(parser, "FIELD2,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD2"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_PARSING, parser.state());
        run_through_parser(parser, "FIELD3,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD3"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_PARSING, parser.state());
    }

    void testParserParsesWithStartChar()
    {
        DelimitedStreamParser parser('>', ',', s_raat_buffer, on_string_parsed);
        run_through_parser(parser, ">FIELD1,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD1"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_WAITING, parser.state());
    }

    void testParserParsesMultipleStringsWithStartChar()
    {
        DelimitedStreamParser parser('>', ',', s_raat_buffer, on_string_parsed);
        run_through_parser(parser, ">FIELD1,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD1"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_WAITING, parser.state());
        run_through_parser(parser, ">FIELD2,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD2"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_WAITING, parser.state());
        run_through_parser(parser, ">FIELD3,");
        CPPUNIT_ASSERT_EQUAL(std::string("FIELD3"), std::string(sp_parsed_string));
        CPPUNIT_ASSERT_EQUAL(PARSER_STATE_WAITING, parser.state());
    }

public:
    void setUp()
    {
        sp_parsed_string[0] = '\0';
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(DelimitedStreamParserTest);