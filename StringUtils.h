#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

bool isStringEmpty(char const *string);

bool isStringNotEmpty(char const *string);

bool isStringBlank(char const *string);

bool isStringNotBlank(char const *string);

bool containsString(const char *string, const char *searchString);

void toLowerCaseString(char *string);

void toUpperCaseString(char *string);

bool substringString(const char *start, const char *end, const char *source, char *dest);

void replaceString(char *source, const char *target, const char *replacement);

uint32_t countStringOccurrencesOf(const char *sourceString, const char *subString);

char *splitStringReentrant(char *source, const char *delimiter, char **nextPointer);    // analog of strtok_r

char *trimString(char *string); // Note: This function modify the string and returns a pointer to a substring of the original string

bool isStringEquals(const char *one, const char *two);

bool isStringNotEquals(const char *one, const char *two);