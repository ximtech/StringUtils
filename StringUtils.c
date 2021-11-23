#include "StringUtils.h"


bool isStringEmpty(char const *string) {
    return string == NULL || strlen(string) == 0;
}

bool isStringNotEmpty(char const *string) {
    return !isStringEmpty(string);
}

bool isStringBlank(char const *string) {
    uint32_t stringLength;
    if (string != NULL && (stringLength = strlen(string)) != 0) {
        for (uint32_t i = 0; i < stringLength; i++) {
            if (!isspace(string[i])) {
                return false;
            }
        }
        return true;
    }
    return true;
}

bool isStringNotBlank(char const *string) {
    return !isStringBlank(string);
}

bool containsString(const char *string, const char *searchString) {
    return strstr(string, searchString) != NULL;
}

void toLowerCaseString(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = (char) tolower(string[i]);
    }
}

void toUpperCaseString(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = (char) toupper(string[i]);
    }
}

bool substringString(const char *start, const char *end, const char *source, char *dest) {
    char *startPointer = strstr(source, start);
    if (startPointer != NULL) {  // check that substring start is found
        startPointer += strlen(start);
        size_t substringLength = strcspn(startPointer, end);
        if (substringLength > 0) {  // check that substring end is found
            strncat(dest, startPointer, substringLength);
            return true;
        }
        return false;
    }
    return false;
}

void replaceString(char *source, const char *target, const char *replacement) {
    char *sourcePointer = strstr(source, target);
    if (sourcePointer == NULL) return;

    uint32_t targetLength = strlen(target);
    uint32_t replacementLength = strlen(replacement);
    uint32_t tailLength = strlen(sourcePointer + targetLength);

    memmove(sourcePointer + replacementLength, sourcePointer + targetLength, tailLength + 1);
    memcpy(sourcePointer, replacement, replacementLength);
}

uint32_t countStringOccurrencesOf(const char *sourceString, const char *subString) {
    if (isStringNotEmpty(sourceString) && isStringNotEmpty(subString)) {
        uint32_t count = 0;
        uint32_t sourceStringLength = strlen(sourceString);
        uint32_t subStringLength = strlen(subString);
        if (subStringLength > sourceStringLength) {
            return count;
        }

        for (uint32_t i = 0; i < (sourceStringLength - subStringLength) + 1; i++) {
            if (strstr(sourceString + i, subString) == sourceString + i) {
                count++;
                i += subStringLength - 1;
            }
        }
        return count;
    }
    return 0;
}

char *splitStringReentrant(char *source, const char *delimiter, char **nextPointer) {
    char *returnToken;

    if (source == NULL) {
        source = *nextPointer;
    }
    source += strspn(source, delimiter);

    if (*source == '\0') {
        return NULL;
    }
    returnToken = source;
    source += strcspn(source, delimiter);

    if (*source) {
        *source++ = '\0';
    }
    *nextPointer = source;
    return returnToken;
}

char *trimString(char *string) {
    if (string == NULL) return NULL;

    while (isspace((unsigned char) *string)) {// Trim leading space
        string++;
    }

    if (*string == 0) { // All spaces?
        return string;
    }

    // Trim trailing space
    char * stringEnd = string + strlen(string) - 1;
    while (stringEnd > string && isspace((unsigned char) *stringEnd)) {
        stringEnd--;
    }

    // Write new null terminator character
    stringEnd[1] = '\0';
    return string;
}

bool isStringEquals(const char *one, const char *two) {
    if (one == two) return true;

    if (one != NULL && two != NULL) {
        size_t oneLength = strlen(one);
        if (oneLength == strlen(two)) {
            int i = 0;
            while (oneLength-- != 0) {
                if (one[i] != two[i]) {
                    return false;
                }
                i++;
            }
            return true;
        }
    }
    return false;
}

bool isStringNotEquals(const char *one, const char *two) {
	return !isStringEquals(one, two);
}