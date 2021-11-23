# StringUtils
**STM32** Utilities and tools for working with Strings.

### Features
- No dynamic memory allocation

### Add as CPM project dependency
How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)
```cmake
CPMAddPackage(
        NAME StringUtils
        GITHUB_REPOSITORY ximtech/StringUtils
        GIT_TAG origin/main)

target_link_libraries(${PROJECT_NAME} StringUtils)
```

### Usage
Example of usage:
```C
printf("Is string empty: %s\n", isStringEmpty("") ? "Yes" : "No");  // Yes
printf("Is string empty: %s\n", isStringNotEmpty(" ") ? "Yes" : "No");  // Yes
printf("Is string empty: %s\n\n", isStringEmpty(NULL) ? "Yes" : "No");  // Yes

printf("Is string blank: %s\n", isStringBlank("   ") ? "Yes" : "No");  // Yes
printf("Is string blank: %s\n", isStringBlank("\t  \r") ? "Yes" : "No");  // Yes
printf("Is string blank: %s\n", isStringBlank(NULL) ? "Yes" : "No");  // Yes
printf("Is string blank: %s\n\n", isStringNotBlank("   t") ? "Yes" : "No");  // Yes

printf("Have substring: %s\n\n", containsString("Hello world!", "world") ? "Yes" : "No");  // Yes

char buffer[50] = {0};
strcpy(buffer, "HeLlO WoRlD!");
toLowerCaseString(buffer);
printf("To lower case: %s\n", buffer);   // hello world!

toUpperCaseString(buffer);
printf("To upper case: %s\n\n", buffer);   // HELLO WORLD!

memset(buffer, 0, 50);
substringString("Start: ", " :End", "Some string Start: test :End", buffer);
printf("Substring: %s\n", buffer);  // test

memset(buffer, 0, 50);
strcpy(buffer, "Hello world!");
replaceString(buffer, "world", "all");  // Hello all!
printf("Replaced string: %s\n", buffer);

printf("Occurrences of 'ab' in string: %d\n", countStringOccurrencesOf("Test ab some other abab", "a"));  // 3

memset(buffer, 0, 50);
strcpy(buffer, "   test   ");
printf("Trimmed string: %s\n\n", trimString(buffer));   // test

printf("Is string equals: %s\n", isStringEquals("", "") ? "Yes" : "No");  // Yes
printf("Is string equals: %s\n", isStringEquals("aaB", "aaB") ? "Yes" : "No");  // Yes
printf("Is string not equals: %s\n", isStringNotEquals("a", "") ? "Yes" : "No");  // Yes
printf("Is string not equals: %s\n", isStringNotEquals("a", NULL) ? "Yes" : "No");  // Yes
```