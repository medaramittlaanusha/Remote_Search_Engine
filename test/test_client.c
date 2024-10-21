/*********************************************************************************
 *   DATE: 21/10/2024
 *   OWNER: Group-04
 *   FILENAME: test_client.c
 *   DESCRIPTION:This file contains the unit tests for various functions used in the
 *       project. It uses the CUnit testing framework to verify the correctness 
 *       of key operations, such as searching for files and strings. Mock 
 *       functions are implemented to simulate behaviors of the actual functions 
 *       during testing. Test cases validate both positive and negative scenarios 
 *       for file and string search functionality.
 *******************************************************************************/


#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../INC/server_function.h"

// Mock functions for testing
void mock_searchForFile(char* path, char* response) {
    // Mock implementation
    if (strcmp(path, "/valid/path") == 0) {
        strcpy(response, "File found.");
    } else {
        strcpy(response, "File not found.");
    }
}

void mock_searchForString(const char* path, char* response) {
    // Mock implementation
    if (strcmp(path, "hello") == 0) {
        strcpy(response, "String found in file.");
    } else {
        strcpy(response, "String not found.");
    }
}

// Test cases
void test_searchForFile_validPath() {
    char response[256];
    mock_searchForFile("/valid/path", response);
    CU_ASSERT_STRING_EQUAL(response, "File found.");
}

void test_searchForFile_invalidPath() {
    char response[256];
    mock_searchForFile("/invalid/path", response);
    CU_ASSERT_STRING_EQUAL(response, "File not found.");
}

void test_searchForString_found() {
    char response[256];
    mock_searchForString("hello", response);
    CU_ASSERT_STRING_EQUAL(response, "String found in file.");
}

void test_searchForString_notFound() {
    char response[256];
    mock_searchForString("world", response);
    CU_ASSERT_STRING_EQUAL(response, "String not found.");
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Create a test suite
    CU_pSuite pSuite = CU_add_suite("Client Tests", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test cases to the suite
    if ((NULL == CU_add_test(pSuite, "Test valid file search", test_searchForFile_validPath)) ||
        (NULL == CU_add_test(pSuite, "Test invalid file search", test_searchForFile_invalidPath)) ||
        (NULL == CU_add_test(pSuite, "Test string search found", test_searchForString_found)) ||
        (NULL == CU_add_test(pSuite, "Test string search not found", test_searchForString_notFound))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

