/****************************************************************************
 *   DATE :21/10/2024
 *   OWNER : Group-04
 *   FILENAME: server_searchForString.h
 *   DESCRIPTION: This header file contains the declarations of functions
 *                used for searching a specific string within files located
 *                in a directory and its subdirectories. The functions
 *                facilitate recursive searching, enabling the program to
 *                navigate through directories effectively. Results are
 *                logged and stored in a designated buffer for further
 *                processing. The declared functions include:
 *                - searchForString: Initiates a search for a specified
 *                  string across the filesystem.
 *                - searchInDirectory: Searches for the specified string
 *                  in files within a given directory.
 *                - searchInFile: Searches for the specified string in
 *                  a specific file.
 ****************************************************************************/


#ifndef SF_SEARCH_FOR_STRING_H
#define SF_SEARCH_FOR_STRING_H

void searchForString(const char* searchString, char* result);
void searchInDirectory(const char* dirPath, const char* searchString, char* result);
void searchInFile(const char* filePath, const char* searchString, char* result);

#endif

