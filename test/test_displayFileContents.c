/************************************************************************************
 *   DATE: 21/10/2024
 *   OWNER: Group-04
 *   FILENAME: test_displayFileContent.c
 *   DESCRIPTION: This file contains unit tests for the `displayFileContent` function, 
 *                which displays the contents of a given file or reports if the file 
 *                does not exist. The tests are implemented using the CUnit testing 
 *                framework. Mock files are created to simulate different scenarios such 
 *                as a valid file with content, a non-existent file, and an empty file. 
 *                These tests ensure that `displayFileContent` works as expected under 
 *                various conditions.
 ***************************************************************************************/


#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../INC/sf_displayFileContents.h"  // Adjusted path based on your structure
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Helper function to create test files
void create_test_file(const char* path, const char* content) {
    // Create the directory if it doesn't exist
    mkdir("test_files", 0755); // This will not fail if the directory already exists
    
    FILE* file = fopen(path, "w");
    if (file != NULL) {
        if (content) {
            fputs(content, file);
        }
        fclose(file);
    }
}

// Test Case 1: Valid file with content
void test_valid_file() {
    char result[2048];
    char* filePath = "test_files/sample.txt";

    create_test_file(filePath, "Hello, World!\n");

    displayFileContent(filePath, result);

    CU_ASSERT_TRUE(strstr(result, "File exists, content of file:\n") != NULL);
    CU_ASSERT_TRUE(strstr(result, "Hello, World!") != NULL);
}

// Test Case 2: Non-existent file
void test_non_existent_file() {
    char result[2048];
    char* filePath = "test_files/nonexistent.txt";

    displayFileContent(filePath, result);

    CU_ASSERT_STRING_EQUAL(result, "File does not exist\n");
}

// Test Case 3: Empty file
void test_empty_file() {
    char result[2048];
    char* filePath = "test_files/empty.txt";

    create_test_file(filePath, NULL);

    displayFileContent(filePath, result);

    CU_ASSERT_STRING_EQUAL(result, "File exists, content of file:\n");
}

// Test Suite Setup
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Create a test suite
    CU_pSuite suite = CU_add_suite("displayFileContent Test Suite", init_suite, clean_suite);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test cases to the suite
    if ((NULL == CU_add_test(suite, "Test valid file", test_valid_file)) ||
        (NULL == CU_add_test(suite, "Test non-existent file", test_non_existent_file)) ||
        (NULL == CU_add_test(suite, "Test empty file", test_empty_file))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up and return
    CU_cleanup_registry();
    return CU_get_error();
}

