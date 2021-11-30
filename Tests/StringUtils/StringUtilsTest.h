#pragma once

#include "BaseTestTemplate.h"
#include <StringUtils.h>

static const char TEST_STRING[] = "0,CONNECT\n 1,CONNECT\n\n +IPD,1,497:GET /api/test HTTP/1.1\nHost: 192.168.53.117\nConnection: keep-alive\n";
static const char TEST_STRING_LOWER[] = "0,connect\n 1,connect\n\n +ipd,1,497:get /api/test http/1.1\nhost: 192.168.53.117\nconnection: keep-alive\n";
static const char TEST_STRING_UPPER[] = "0,CONNECT\n 1,CONNECT\n\n +IPD,1,497:GET /API/TEST HTTP/1.1\nHOST: 192.168.53.117\nCONNECTION: KEEP-ALIVE\n";

static void *stringSetup(const MunitParameter params[], void *userData) {
    char *sourceString = malloc(sizeof(char) * strlen(TEST_STRING) + 1);
    assert_not_null(sourceString);
    memset(sourceString, 0, strlen(sourceString));
    strcpy(sourceString, TEST_STRING);
    return sourceString;
}

static MunitResult testStringBlank(const MunitParameter params[], void *testData) {
    char *testStr1 = "";
    char *testStr2 = "acvd";
    char *testStr3 = "     ";
    char *testStr4 = "   t  ";
    char *testStr5 = "\n\t\r";
    char *testStr6 = NULL;

    assert_true(isStringBlank(testStr1));
    assert_false(isStringBlank(testStr2));
    assert_true(isStringBlank(testStr3));
    assert_false(isStringBlank(testStr4));
    assert_true(isStringBlank(testStr5));
    assert_true(isStringBlank(testStr6));

    return MUNIT_OK;
}

static MunitResult testStringEmpty(const MunitParameter params[], void *testData) {
    char *testStr1 = "";
    char *testStr2 = "acvd";
    char *testStr3 = "     ";
    char *testStr4 = "   t  ";
    char *testStr5 = "\n\t\r";
    char *testStr6 = NULL;

    assert_true(isStringEmpty(testStr1));
    assert_false(isStringEmpty(testStr2));
    assert_false(isStringEmpty(testStr3));
    assert_false(isStringEmpty(testStr4));
    assert_false(isStringEmpty(testStr5));
    assert_true(isStringEmpty(testStr6));

    return MUNIT_OK;
}

static MunitResult testStringReplace(const MunitParameter params[], void *testString) {
    replaceString(testString, "+IPD,", "");
    int replaced = strcmp(testString, "0,CONNECT\n 1,CONNECT\n\n 1,497:GET /api/test HTTP/1.1\nHost: 192.168.53.117\nConnection: keep-alive\n");
    assert_int(replaced, ==, 0);
    return MUNIT_OK;
}

static MunitResult testStringSubstring(const MunitParameter params[], void *testString) {
    char buffer[10] = {0};
    assert_true(substringString("+IPD,", ":", testString, buffer));
    assert_string_equal(buffer, "1,497");

    memset(buffer, 0, 10);
    assert_false(substringString("HTTPS,", ":", testString, buffer));
    return MUNIT_OK;
}

static MunitResult testLowerCaseString(const MunitParameter params[], void *testString) {
    toLowerCaseString(testString);
    assert_string_equal(testString, TEST_STRING_LOWER);
    return MUNIT_OK;
}

static MunitResult testUpperCaseString(const MunitParameter params[], void *testString) {
    toUpperCaseString(testString);
    assert_string_equal(testString, TEST_STRING_UPPER);
    return MUNIT_OK;
}

static MunitResult testContainsString(const MunitParameter params[], void *testString) {
    assert_true(containsString(testString, "Host"));
    assert_false(containsString(testString, "HosT"));
    return MUNIT_OK;
}

static MunitResult testStringOccurrencesOf(const MunitParameter params[], void *testString) {
    char *testParametersString = "/api/test/json?product=1234&utm_source=google&value=string#access_token=test";
    assert_int(countStringOccurrencesOf(testParametersString, "&"), ==, 2);
    assert_int(countStringOccurrencesOf(testParametersString, "utm"), ==, 1);
    assert_int(countStringOccurrencesOf(testParametersString, "?"), ==, 1);
    assert_int(countStringOccurrencesOf(testParametersString, "test"), ==, 2);
    assert_int(countStringOccurrencesOf(testParametersString, "err"), ==, 0);
    assert_int(countStringOccurrencesOf(testParametersString, "12345"), ==, 0);
    return MUNIT_OK;
}

static MunitResult testStringSplit(const MunitParameter params[], void *testString) {
    char *testPathString = "/api/test/json/product=1234/utm_source";
    size_t stringLength = strlen(testPathString);
    char *source = malloc(stringLength * sizeof(char) + 1);
    memset(source, 0, stringLength);
    strcpy(source, testPathString);

    char *nextPointer;
    char *token = splitStringReentrant(source, "&", &nextPointer);
    assert_string_equal(token, source); // delimiter is not found, return input string

    token = splitStringReentrant(source, "/", &nextPointer);
    assert_string_equal(token, "api");
    assert_string_equal(nextPointer, "test/json/product=1234/utm_source");

    token = splitStringReentrant(NULL, "/", &nextPointer);
    assert_string_equal(token, "test");
    assert_string_equal(nextPointer, "json/product=1234/utm_source");

    token = splitStringReentrant(NULL, "/", &nextPointer);
    assert_string_equal(token, "json");
    assert_string_equal(nextPointer, "product=1234/utm_source");

    token = splitStringReentrant(NULL, "/", &nextPointer);
    assert_string_equal(token, "product=1234");
    assert_string_equal(nextPointer, "utm_source");

    token = splitStringReentrant(NULL, "/", &nextPointer);
    assert_string_equal(token, "utm_source");
    assert_string_equal(nextPointer, "");

    token = splitStringReentrant(NULL, "/", &nextPointer);
    assert_null(token);
    free(source);
    return MUNIT_OK;
}

static MunitResult testTrimString(const MunitParameter params[], void *testString) {
    char testBuffer[20] = {0};
    const char *stringWithSpaces = munit_parameters_get(params, "stringWithSpaces");
    strcpy(testBuffer, stringWithSpaces);
    assert_string_equal(trimString(testBuffer), "test");
    return MUNIT_OK;
}

static MunitResult testIsStringEquals(const MunitParameter params[], void *testString) {
    assert_true(isStringEquals(NULL, NULL));
    assert_true(isStringEquals("b", "b"));
    assert_true(isStringEquals("123", "123"));
    assert_true(isStringEquals(")", ")"));

    assert_false(isStringEquals("a", NULL));
    assert_false(isStringEquals(NULL, "b"));
    assert_false(isStringEquals("bB", "b"));
    assert_false(isStringEquals("bB", "bb"));
    assert_false(isStringEquals("#@", "@#"));
    return MUNIT_OK;
}

static void stringTearDown(void *string) {
    free(string);
    string = NULL;
    munit_assert_ptr_null(string);
}

static char *stringWithTrailingSpaces[] = {
        "   test   ",
        "test       ",
        "       test",
        "\ttest\t",
        "test\t",
        "\ttest",
        " test ",
        NULL
};

static MunitParameterEnum stringTestParameters1[] = {
        {.name = "stringWithSpaces", .values = stringWithTrailingSpaces},
        END_OF_PARAMETERS
};

static MunitTest stringUtilsTests[] = {
        {.name =  "Test isStringBlank() - should check string blankness", .test = testStringBlank},
        {.name =  "Test testStringEmpty() - should check that string is empty or not", .test = testStringEmpty},
        {.name =  "Test replaceString() - should correctly replace substring from string", .test = testStringReplace, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test substringString() - should correctly substring string from string", .test = testStringSubstring, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test toLowerCaseString() - should set all chars to lower case", .test = testLowerCaseString, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test toUpperCaseString() - should set all chars to upper case", .test = testUpperCaseString, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test containsString() - should find substring in source string", .test = testContainsString, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test countStringOccurrencesOf() - should correctly count substrings", .test = testStringOccurrencesOf, .setup = stringSetup, .tear_down = stringTearDown},
        {.name =  "Test splitStringReentrant() - should correctly split string", .test = testStringSplit},
        {.name =  "Test testTrimString() - should correctly remove trailing whitespaces", .test = testTrimString, .parameters = stringTestParameters1},
        {.name =  "Test isStringEquals() - should correctly check string equality", .test = testIsStringEquals},
        END_OF_TESTS
};

static const MunitSuite stringUtilsTestSuite = {
        .prefix = "String: ",
        .tests = stringUtilsTests,
        .suites = NULL,
        .iterations = 1,
        .options = MUNIT_SUITE_OPTION_NONE
};
