/***************************************************************************
*   DATE:
*   AUTHOR : Group-04
*   FILENAME : client.c
*   DESCRIPTION: Contains code for a client that connects to a server 
*               to perform various file operations, including searching for 
*               a file, searching for a string within files, and displaying 
*               file contents. The client communicates with the server via 
*               socket programming and presents options to the user through 
*               a console interface.
*****************************************************************************/

#include "../inc/hdr.h"
#include "../inc/server.h"
#include "../inc/loggers.h"
#include "../inc/server_displayFileContents.h"
#include "../inc/server_searchForFile.h"
#include "../inc/server_searchForString.h"

// Function to check if the string is numeric
int isNumeric(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;  // Not numeric
        }
    }
    return 1;  // All characters are numeric
}

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    serverAddr.sin_port = htons(5680);                     // Server port

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    int choice;
    char buffer[MAX_BUFFER_SIZE];

    while (1) {
        printf("\n");
        printf("***********************************************************\n");
        printf("                   REMOTE SEARCH ENGINE                    \n");
        printf("***********************************************************\n");
        printf("Choose an Option:\n");
        printf("\n");
        printf("1. Search for a file\n");
        printf("2. Search for a string in the filesystem\n");
        printf("3. Enter the absolute path and Display the content\n");
        printf("4. Exit\n");
        printf("************************************************************\n");
        printf("\n");
        printf("Enter your choice: ");
        
        // Input validation for choice
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter a number: ");
                while (getchar() != '\n'); // Clear the input buffer
            } else if (choice < 1 || choice > 4) {
                printf("Please enter a valid option (1-4): ");
            } else {
                break; // Valid input, break out of the loop
            }
        }

        send(clientSocket, &choice, sizeof(choice), 0);

        switch (choice) {
            case 1:
            case 3:
                // Both options 1 and 3 require absolute path input
                while (1) {
                    printf("Enter the absolute path: ");
                    getchar(); // clear newline from buffer
                    scanf("%[^\n]s", buffer);

                    // Check if the input is purely numeric
                    if (isNumeric(buffer)) {
                        printf("Invalid path. Please enter a correct absolute path (not purely numeric):\n");
                    } else {
                        // Valid path, send it to the server
                        send(clientSocket, buffer, sizeof(buffer), 0);
                        recv(clientSocket, buffer, sizeof(buffer), 0);
                        printf("Server response:\n%s\n", buffer);
                        break;
                    }
                }
                break;

            case 2:
                printf("Enter the word/sentence/pattern: ");
                getchar(); // clear newline from buffer
                scanf("%[^\n]s", buffer);
                send(clientSocket, buffer, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s", buffer);
                if (strcmp(buffer, "") == 0) {
                    printf("This string was not found in any file\n\n");
                    break;
                }
                char case2SubChoice[5];
                printf("\n    View a file\n");
                printf("    Enter YES or NO: ");
                scanf("%s", case2SubChoice);
                getchar(); // clear newline from buffer
                if (strcmp(case2SubChoice, "YES") == 0) {
                    printf("    Enter the path: ");
                    scanf("%[^\n]s", buffer);
                    send(clientSocket, buffer, sizeof(buffer), 0);
                    recv(clientSocket, buffer, sizeof(buffer), 0);
                    printf("Server response:\n%s\n", buffer);
                } else {
                    send(clientSocket, "", sizeof(buffer), 0);
                }
                break;

            case 4:
                close(clientSocket);
                exit(EXIT_SUCCESS);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

