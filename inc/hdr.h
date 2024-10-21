/***************************************************************************
*   DATE :21/10/2024 
*   OWNER : Group-04
*	FILENAME : hdr.h
*	DESCRIPTION: Contains utility functions for socket programming, 
*                including handling sockets, directories, and buffers. 
*                The functions in this file are designed to assist 
*                with network communications in a client-server application.
*****************************************************************************/


#include <stdio.h>             // Standard input/output library
#include <stdlib.h>            // Standard library for memory allocation and conversion
#include <string.h>            // String manipulation functions
#include <unistd.h>            // Standard symbolic constants and types
#include <arpa/inet.h>        // Definitions for internet operations
#include <dirent.h>           // Directory entry definitions
#include <sys/socket.h>       // Main structures for sockets
#include <ctype.h>
#define MAX_BUFFER_SIZE 1024   // Define a constant for the maximum buffer size
