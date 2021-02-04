#include "Chat.h"

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void message_synchronization(char *message, int sock) {

	int last_message_id = 0;
	//func to get last message id
	send(sock, mx_itoa(last_message_id), strlen(mx_itoa(last_message_id)));
	
	//number of message
	recv(sock, message, 2000, 0);
	int number_message = atoi(message);

	if (number_message > 0) {
		char **messages = (char **) malloc(sizeof(char *) * (number_message + 1))
		int i = 0;
		recv(sock, message, 2000, 0);
		while(strcmp("@end_synchronization", message) != 0) {
			messages[i] = mx_strdup(message);
			i++;
			recv(sock, message, 2000, 0);
		}
		messages[i] = NULL;
		//func to add new messages to DB
	}
}


void *reader(void *new_sock) {
	int sock = *(int *)new_sock;
	char *server_reply = NULL;
	server_reply = clear_client_message(server_reply);
	for(int i = 0; i < 2000; i++)
			server_reply[i] = '\0';

	while(1) {
		if( recv(sock , server_reply , 2000 , 0) < 0) {
			break;
		}

		if(strcmp(server_reply, "exit") == 0) {
			close(sock);
			break;
		}
		else if(strcmp(server_reply, "@synchronization") == 0) {
			message_synchronization(server_reply, sock);
		}
		else if (strcmp(server_reply, "@file") == 0) {
			read_file(sock);
			server_reply = clear_client_message(server_reply);
			continue;
		}
		
		printf("%s\n", server_reply);
		
		server_reply = clear_client_message(server_reply);
	}
	return 0;
}


int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent *serv;
	char *message = NULL;
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	serv = gethostbyname(SERVERADDR);
    memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	memcpy(&server.sin_addr.s_addr, serv->h_addr_list[0],  serv->h_length);
	server.sin_port = htons(SERVERPORT);
	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}	
	puts("Connected\n");
	
	//keep communicating with server
	
	pthread_t sniffer_thread;
	int *new_sock = malloc(1);
	*new_sock = sock;
	if( pthread_create( &sniffer_thread , NULL ,  reader , (void*) new_sock) < 0) {
		perror("could not create thread");
		return 1;
	}

	while(sniffer_thread) {
		
		message = clear_client_message(message);

		gets(message);

		if (strcmp(message, "@file") == 0) {
			file_sending(sock);
			message = clear_client_message(message);
			continue;
		}
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}

		if(strcmp(message, "exit") == 0) {
			break;
		}
		
	}
	pthread_join(sniffer_thread , NULL);
	close(sock);
	return 0;
}