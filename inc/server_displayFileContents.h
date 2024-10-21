/****************************************************************************
 *   DATE :21/10/2024 
 *   OWNER : Group-04
 *   FILENAME: server_displayFileContent.h
 *   DESCRIPTION: This header file declares the prototype of the 
 *                `displayFileContent` function. This function reads the contents 
 *                of a specified file and stores them in a result buffer. If the 
 *                file exists, its contents are retrieved and appended to the buffer; 
 *                otherwise, an appropriate error message is logged.
 *
 *                Including this header ensures the availability of the function 
 *                for reading and displaying file contents within the server's 
 *                file operations module, contributing to the client-server 
 *                communication process.
 *****************************************************************************/


#ifndef SF_DISPLAY_FILE_CONTENT_H
#define SF_DISPLAY_FILE_CONTENT_H

void displayFileContent (char* filePath, char* result);

#endif

