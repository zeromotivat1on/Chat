#include "Chat.h"

/*char clear_client_message(char *str) {
    for(int i = 0; i < 2000; i++)
        client_message[i] ='\0';
}*/

void mx_registration(int sock) {
    char client_message[2000];
    for(int i = 0; i < 2000; i++)
        client_message[i] ='\0';

    int read_size;
    write(sock, "Do you have an account?\nIf yes please input 'yes' else input 'no'", 
    strlen("Do you have an account?\nIf yes please input 'yes' else input 'no'"));

	if((read_size = recv(sock , client_message , 2000 , 0)) > 0){
		if(strcmp(client_message, "no") == 0){

            while(1) {
                for(int i = 0; i < 2000; i++)
                    client_message[i] ='\0';

                write(sock, "Pleas input unique login", 
                strlen("Pleas input unique login"));

                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                    char *user_name = strdup(client_message);
                    for(int i = 0; i < 2000; i++)
                        client_message[i] ='\0';

                    
                        if( db_get_user_password(user_name, db) == NULL ) {
                            while(1) {
                                write(sock, "Pleas input password", 
                                strlen("Pleas input password"));
                                char *pass1;
                                char *pass2;
                                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                                    pass1 = strdup(client_message);
                                    for(int i = 0; i < 2000; i++)
                                        client_message[i] ='\0';
                                }
                                write(sock, "Pleas input the same password", 
                                strlen("Pleas input the same password"));
                                if((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
                                    pass2 = strdup(client_message);
                                    for(int i = 0; i < 2000; i++)
                                        client_message[i] ='\0';
                                }
                                if(strcmp(pass1, pass2) == 0) {
                                    db_add_user(user_name, pass1);
                                    return;
                                }
                                else {
                                    write(sock, "Passwords not the same", 
                                    strlen("Passwords not the same"));
                                }
                            }
                        }
                }
                write(sock, "This login alredy exist\nTry again", 
                strlen("This login already exist\nTry again"));
            }
		}
	}
}
