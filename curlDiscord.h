#ifndef _CURLDISCORD_

#define _CURLDISCORD_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DISCORD_BUFFER 1024

/**
 * Sends 'message' to server with 'webHook' using 'username' and profile image in the given 'profileImage' URL
*/
int sendMessage(const char *webHook, 
                const char *userName, 
                const char *profileImage, 
                const char *message);

/**
 * Sends 'message' to server with webHook, username and profile image defined on data.cfg
*/
int sendMessageData(const char *message);

/**
 * Setup 'data.cfg' user data file
*/
void setupDiscord(const char *webHook, 
                  const char *userName, 
                  const char *profileImage);

/**
 * Message sending function implementation
 */
inline int sendMessage(const char *webHook,      // Server's webhook
                       const char *userName,     // Username to be used in message
                       const char *profileImage, // URL to the image to be used as profile in message
                       const char *message)      // Message to be sent
{
    char *command = (char*) malloc((119 + 
                                    strlen(webHook) + 
                                    strlen(userName)+
                                    strlen(profileImage) + 
                                    strlen(message)) * sizeof(char)); // cURL request memory allocation
    
    // builds cURL request
    strcpy(command, "curl -H \"Content-Type: application/json\" -X POST -d '{\"username\": \"");
    strcpy(command + strlen(command), userName);
    strcpy(command + strlen(command), "\", \"content\": \"");
    strcpy(command + strlen(command), message);
    strcpy(command + strlen(command), "\", \"avatar_url\": \"");
    strcpy(command + strlen(command), profileImage);
    strcpy(command + strlen(command), "\"}' ");
    strcpy(command + strlen(command), webHook);
    
    // executes and evaluates cURL request
    int rValue = system(command);
    free(command);

    return (rValue != 0);
}

inline int sendMessageData(const char *message)
{
    // opens data file
    FILE *dataFile = fopen("data.cfg", "r"); if (!dataFile) { printf("'data.cfg' doesn't exist. Run 'setupDiscord' to create.\n"); return 1; }

    // fetches data
    char *webHook = (char*) calloc(DISCORD_BUFFER, sizeof(char)),
         *userName = (char*) calloc(DISCORD_BUFFER, sizeof(char)),
         *profileImage = (char*) calloc(DISCORD_BUFFER, sizeof(char));
    fgets(webHook, DISCORD_BUFFER, dataFile); webHook[strlen(webHook) - 1] = '\0';
    fgets(userName, DISCORD_BUFFER, dataFile); userName[strlen(userName) - 1] = '\0';
    fgets(profileImage, DISCORD_BUFFER, dataFile); profileImage[strlen(profileImage) - 1] = '\0';

    char *command = (char*) malloc((119 + 
                                    strlen(webHook) + 
                                    strlen(userName)+
                                    strlen(profileImage) + 
                                    strlen(message)) * sizeof(char)); // cURL request memory allocation
    
    // builds cURL request
    strcpy(command, "curl -H \"Content-Type: application/json\" -X POST -d '{\"username\": \"");
    strcpy(command + strlen(command), userName);
    strcpy(command + strlen(command), "\", \"content\": \"");
    strcpy(command + strlen(command), message);
    strcpy(command + strlen(command), "\", \"avatar_url\": \"");
    strcpy(command + strlen(command), profileImage);
    strcpy(command + strlen(command), "\"}' ");
    strcpy(command + strlen(command), webHook);
    
    // executes and evaluates cURL request
    int rValue = system(command);
    free(command);

    return (rValue != 0);
}

inline void setupDiscord(const char *webHook, 
                        const char *userName, 
                        const char *profileImage)
{
    FILE *data = fopen("data.cfg", "w+"); // opens data file for creation

    // stores info
    fputs(webHook, data); fputc('\n', data); 
    fputs(userName, data); fputc('\n', data);
    fputs(profileImage, data); fputc('\n', data);

    // closes file
    fclose(data);
}

#endif