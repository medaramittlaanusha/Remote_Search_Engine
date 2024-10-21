/******************************************************************************
 *   DATE: 21/10/2024
 *   OWNER: Group-04
 *   FILENAME: test_searchForFile.c
 *   DESCRIPTION: This file contains unit tests for the `searchForFile` function using 
 *               the CUnit testing framework. The tests validate the functionality 
 *               under various conditions, such as when the file exists, does not exist, 
 *               the result buffer is empty, or an invalid file path is provided. 
 *               Each test case ensures that the `searchForFile` function behaves 
 *               correctly and returns expected outputs.
 *******************************************************************************/


#include "../INC/hdr.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../INC/sf_searchForFile.h"

// Function prototypes for test cases
void test_searchForFile_fileExists(void);
void test_searchForFile_fileDoesNotExist(void);
void test_searchForFile_emptyResultBuffer(void);
void test_searchForFile_invalidPath(void);

// Main function to run tests
int main() {
    // Initialize CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Create a test suite within the registry
    CU_pSuite suite = CU_add_suite("FileSearchTests", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test cases to the suite
    if ((CU_add_test(suite, "Test File Exists", test_searchForFile_fileExists) == NULL) ||
        (CU_add_test(suite, "Test File Does Not Exist", test_searchForFile_fileDoesNotExist) == NULL) ||
        (CU_add_test(suite, "Test Empty Result Buffer", test_searchForFile_emptyResultBuffer) == NULL) ||
        (CU_add_test(suite, "Test Invalid Path", test_searchForFile_invalidPath) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up and exit
    CU_cleanup_registry();
    return CU_get_error();
}

// Implementations of the test cases
void test_searchForFile_fileExists(void) {
    char result[1024];  
    result[0] = '\0';  // Initialize result buffer
    searchForFile("existing_file.txt", result);  // Ensure this file exists with expected content
    CU_ASSERT_STRING_EQUAL(result, "Yes, the file exists!");  // Update with the output of your function
}

void test_searchForFile_fileDoesNotExist(void) {
    char result[1024];  
    result[0] = '\0';  // Initialize result buffer
    searchForFile("non_existing_file.txt", result);  // This file should not exist
    CU_ASSERT_STRING_EQUAL(result, "No, the file does not exist!");  // Expecting this output
}

void test_searchForFile_emptyResultBuffer(void) {
    char result[1024];  
    result[0] = '\0';  // Initialize result buffer
    searchForFile("empty_file.txt", result);  // Ensure this file exists but is empty
    CU_ASSERT_STRING_EQUAL(result, "No, the file does not exist!");  // Expecting this output since your function does not return an empty string for an empty file
}

void test_searchForFile_invalidPath(void) {
    char result[1024];  
    result[0] = '\0';  // Initialize result buffer
    searchForFile("invalid_path/file.txt", result);  // Ensure this path is invalid
    CU_ASSERT_STRING_EQUAL(result, "No, the file does not exist!");  // Expecting this output
}
