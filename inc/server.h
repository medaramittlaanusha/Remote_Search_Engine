/****************************************************************************
 *   DATE:21/10/2024
 *   OWNER : Group-04
 *   FILENAME: server.h
 *   DESCRIPTION: This header file declares the prototypes of core server-side 
 *                functions used for socket programming. The functions include:
 *                searching for files, locating strings within files, recursively 
 *                navigating directories, and displaying file contents. These 
 *                functions enable efficient handling of client requests related 
 *                to file operations and string searches . Including this header
 *                 ensures  modularity, code reuse, and smooth compilation.
 *****************************************************************************/


#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

void searchForFile(char*, char*);
void searchInFile(const char*, const char*, char*);
void searchInDirectory(const char*, const char*, char*);
void searchForString(const char*, char*);
void displayFileContent(char*, char*);

#endif
