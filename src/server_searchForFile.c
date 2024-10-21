/****************************************************************************
*   DATE : 21/10/2024
*   OWNER : GROUP-04
*	FILENAME: server_searchForFile.c
*	DESCRIPTION: Contains the code to search for a file in the filesystem 
*	            based on the provided file path. If the file exists, 
*	            it appends a confirmation message to the result buffer; 
*	            if not, it logs an error and stores an appropriate message.
*****************************************************************************/



#include "../inc/hdr.h"
#include "../inc/loggers.h"

void searchForFile(char* filePath, char* result) {
    LOG_INFO("Searching for a file in filesystem with filePath - %s", filePath);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        fclose(file);
        strcat(result, "Yes, the file exists!");
        LOG_INFO("File exists - %s", "TRUE");
    } else {
        strcat(result, "No, the file does not exist!");
        LOG_FATAL("File exists - %s", "FALSE");
    }
}
