/*************************************************************************************
 *   DATE: 21/10/2024
 *   OWNER: Group-04
 *   FILENAME: test_search_for_String.c
 *   DESCRIPTION: This file contains unit tests for the `searchForString` function using 
 *                 the CUnit testing framework. The tests validate the functionality 
 *                under various conditions, such as when the search string is found in 
 *                a file, not found, or when searching in an empty directory. 
 *                Each test case ensures that the `searchForString` function behaves 
 *                correctly and returns expected outputs.
 ******************************************************************************/


#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../INC/hdr.h"
#include "../INC/sf_searchForString.h" // Include the header
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // For rmdir
#include <sys/stat.h> // For mkdir

// Function prototypes for test cases
void test_search_found(void);
void test_search_not_found(void);
void test_search_empty_directory(void);

int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Create a test suite within the registry
    CU_pSuite suite = CU_add_suite("searchForString_test_suite", 0, 0);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test cases to the suite
    if ((CU_add_test(suite, "test_search_found", test_search_found) == NULL) ||
        (CU_add_test(suite, "test_search_not_found", test_search_not_found) == NULL) ||
        (CU_add_test(suite, "test_search_empty_directory", test_search_empty_directory) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

// Test case 1: String found in file
void test_search_found(void) {
    char result[1024] = "";  // Buffer for result
    const char *expectedSubstring = "test_file.txt"; // Adjust according to your setup

    // Ensure test_file.txt exists and contains "testString"
    printf("Checking if test_file.txt exists and contains 'testString'.\n");
    searchForString("testString", result);
    printf("Result from searchForString: %s\n", result);

    // Assert that the result contains the expected file path or substring
    CU_ASSERT(strstr(result, expectedSubstring) != NULL);
}

// Test case 2: String not found in any file
void test_search_not_found(void) {
    char result[1024] = "";  // Buffer for result
    searchForString("non_existent_string", result);
    
    // Debug output
    printf("Result from searchForString: %s\n", result);

    // Assert that the result does not contain the non-existent string
    CU_ASSERT(strstr(result, "non_existent_string") == NULL);
}

// Test case 3: Search in an empty directory
void test_search_empty_directory(void) {
    char result[1024] = "";  // Buffer for result
    const char *emptyDirPath = "./empty_test_dir";

    // Create an empty directory for testing
    if (mkdir(emptyDirPath, 0700) == 0) {
        printf("Empty directory created: %s\n", emptyDirPath);
    }

    // Search in the empty directory
    searchInDirectory(emptyDirPath, "testString", result);
    printf("Result from searchInDirectory: %s\n", result);

    // Assert that the result is empty
    CU_ASSERT_STRING_EQUAL(result, "");

    // Cleanup: Remove the empty directory
    rmdir(emptyDirPath);
}

