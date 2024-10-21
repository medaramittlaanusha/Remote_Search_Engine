/****************************************************************************
*   DATE :21/10/2024
*   OWNER :Group-04
*   FILENAME: client.h
*   DESCRIPTION: This header file contains declarations for functions used
*                in the client-side of a client-server application. It includes
*                the declaration of the function connectToServer, which is 
*                responsible for creating a socket and establishing a 
*                connection to the server. Additionally, it provides the 
*                declaration of the handleChoice function, which processes 
*                user input and manages the corresponding actions based 
*                on the user's selections.
 ****************************************************************************/


#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h> // For struct sockaddr_in and related functions

// Function to create a socket and connect to the server
int connectToServer(int* clientSocket, const char* ipAddress, int port);

// Function to handle user choices based on the user's input
void handleChoice(int clientSocket, int choice);

#endif // CLIENT_H

