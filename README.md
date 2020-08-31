
# discordCLI
Header only library for setting up and using Discord's webhooks for sending messages through CLI.  

**Requirements:**  
 - Having cURL installed

**Usage:**
 - To use the library just include the header file.
 
**sendMessage**
Sends a simple message with a custom username and profile image. Returns `0` as success code and `1` as error.

    int returnCode = sendMessage(const char *webHook, // Server's webhook
				     const char *userName, // Username to be used in message
		                     const char *profileImage, // URL to the image to be used as profile in message
	                             const char *message) // Message to be sent
    

**setupDiscord**
Sets up a config file with a set of server webhook, username and profile image (given by a URL), for sending messages through.

    setupDiscord(const char *webHook, // Configured server's webhook
		     const char *userName, // Username for messaging
		     const char *profileImage); // Profile image's URL
**sendMessageData**
Sends a simple message with username and profile image given by the config file. Returns `0` as success code and `1` as error.

    int returnCode = sendMessage(const char *message) // Message to be sent

