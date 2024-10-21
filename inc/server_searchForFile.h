/****************************************************************************
*   DATE:21/10/2024
*   OWNER :Group-04
*   FILENAME: server_searchForFile.h
*   DESCRIPTION: This header file contains the declaration of the function
*                searchForFile, which is responsible for searching for a
*                specific file in the filesystem based on a provided file
*                path. The function checks for the existence of the file 
*                and appends the appropriate confirmation message to a 
*                result buffer. It is designed to assist with file 
*                management tasks in a client-server application.
 ****************************************************************************/


#ifndef SF_SEARCH_FOR_FILE_H
#define SF_SEARCH_FOR_FILE_H

void searchForFile(char* filePath, char* result);

#endif

