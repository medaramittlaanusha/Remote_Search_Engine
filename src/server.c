/*********************************************************************************&********
 *   DATE: 21/10/2024
 *   OWNER : Group-04
 *   FILENAME : server.c
 *   DESCRIPTION:  This file contains the server-side code for a multi-threaded server 
 *                 that supports concurrent client connections. The server provides
 *                  functionalities  like searching for files, searching for strings
 *				   within files, and displaying file contents.  It manages multiple
 *				   client requests using threads and ensures thread safety with mutex locks.
 *******************************************************************************************/


#include "../inc/hdr.h"
#include "../inc/server.h"
#include "../inc/loggers.h"
#include "../inc/server_displayFileContents.h"
#include "../inc/server_searchForFile.h"
#include "../inc/server_searchForString.h"
#include <pthread.h>

#define MAX_CLIENTS 10
#define MAX_BUFFER_SIZE 1024

pthread_mutex_t client_count_lock;
int active_clients = 0;

// Function to handle each client in a separate thread
void* handleClient(void* clientSocketPtr) {
    int clientSocket = *(int*)clientSocketPtr;
    free(clientSocketPtr);  // Free the pointer after use

    char buffer[MAX_BUFFER_SIZE] = {0};
    char result[MAX_BUFFER_SIZE] = {0};

    while (1) {
        int choice;

        // Receive client choice
        ssize_t recvBytes = recv(clientSocket, &choice, sizeof(choice), 0);
        if (recvBytes <= 0) {
            LOG_WARN("Client disconnected %s", "");
            break;
        }

        LOG_INFO("Client's choice: %d", choice);

        switch (choice) {
            case 1:  // Search for a file
                memset(buffer, 0, sizeof(buffer));  // Clear buffer before receiving data
                recv(clientSocket, buffer, sizeof(buffer), 0);

                memset(result, 0, sizeof(result));  // Clear result before use
                searchForFile(buffer, result);

                send(clientSocket, result, sizeof(result), 0);
                break;

            case 2:  // Search for a string in the filesystem
                memset(buffer, 0, sizeof(buffer));  // Clear buffer before receiving data
                recv(clientSocket, buffer, sizeof(buffer), 0);
                
                memset(result, 0, sizeof(result));  // Clear result before use
                searchForString(buffer, result);
                
                // Send back the search results
                send(clientSocket, result, sizeof(result), 0);
                
                // Check if the result is empty (no files found) and exit early if so
                if (strcmp(result, "") == 0) {
                    break;
                }

                // Clear buffers again before proceeding to display file content
                memset(buffer, 0, sizeof(buffer));
                memset(result, 0, sizeof(result));

                // Receive the file path from the client
                recv(clientSocket, buffer, sizeof(buffer), 0);
                
                // If no valid file path is provided, exit
                if (strcmp(buffer, "") == 0) {
                    break;
                }

                // Display the file content and send it back to the client
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;

            case 3:  // Display file content
                recv(clientSocket, buffer, sizeof(buffer), 0);
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;

            case 4:  // Client exit
                LOG_INFO("Client exiting %s", "");
                close(clientSocket);
                pthread_mutex_lock(&client_count_lock);
                active_clients--;
                pthread_mutex_unlock(&client_count_lock);
                pthread_exit(NULL);

            default:
                LOG_WARN("Invalid choice received from client %s", "");
        }
    }

    close(clientSocket);
    pthread_mutex_lock(&client_count_lock);
    active_clients--;
    pthread_mutex_unlock(&client_count_lock);
    pthread_exit(NULL);
}

int main() {
    LOG_INFO("Creating Socket %s", "");
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        LOG_FATAL("Socket creation failed %s\n", "");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Binding to port %s", "");
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5680);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        LOG_FATAL("Bind failed %s", "");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Listening for incoming connections %s", "");
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        LOG_FATAL("Listen failed %s", "");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Server listening on port %s...", "5680");

    pthread_mutex_init(&client_count_lock, NULL);

    while (1) {
        pthread_mutex_lock(&client_count_lock);
        if (active_clients >= MAX_CLIENTS) {
            pthread_mutex_unlock(&client_count_lock);
            LOG_WARN("Maximum clients reached, waiting for a slot %s", "");
            sleep(1);
            continue;
        }
        pthread_mutex_unlock(&client_count_lock);

        int* clientSocket = malloc(sizeof(int));
        if (clientSocket == NULL) {
            LOG_FATAL("Memory allocation failed %s", "");
            continue;
        }

        *clientSocket = accept(serverSocket, NULL, NULL);
        if (*clientSocket == -1) {
            LOG_FATAL("Accept failed %s", "");
            free(clientSocket);
            continue;
        }

        LOG_INFO("Client connected %s", "");

        pthread_mutex_lock(&client_count_lock);
        active_clients++;
        pthread_mutex_unlock(&client_count_lock);

        pthread_t clientThread;
        if (pthread_create(&clientThread, NULL, handleClient, clientSocket) != 0) {
            LOG_FATAL("Failed to create thread %s", "");
            close(*clientSocket);
            free(clientSocket);

            pthread_mutex_lock(&client_count_lock);
            active_clients--;
            pthread_mutex_unlock(&client_count_lock);
        } else {
            pthread_detach(clientThread);
        }
    }

    LOG_INFO("Closing server socket now %s", "");
    close(serverSocket);
    pthread_mutex_destroy(&client_count_lock);
    return 0;
}

