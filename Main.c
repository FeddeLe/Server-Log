#include "Server_Header.h"

int main (void)
{   
	char server_message[256] = "Welcome to the Server!\n1. LogIn\n2. Create user\n\n";
	char user[20];
	char password[20];
	char *usr,*pass;
	usr = user;
	pass = password;


	////////CREATE SOCKET////////
	int server_socket;
	int client_socket;
	int client_input;
	int test;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);



	///////DEFINE SERVER ADDRESS, STRUCT OF TYPE "sockaddr_in"//////////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	///////ASSIGNING A NAME TO A SOCKET//////////
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));


	///////WAIT FOR A CONNECTION/////////
	listen(server_socket,10);


	///////ACCEPT THE CONNECTION/////////
 	client_socket = accept(server_socket,NULL,NULL);


 	//////SEND AND RECEIVE DATA///////
 	send(client_socket, server_message, sizeof(server_message), 0);
 	recv(client_socket, &client_input, sizeof(client_input), 0);

 	switch (client_input)
 	{
 		case 1:
 		recv(client_socket, &user, sizeof(user), 0);
 		recv(client_socket, &password, sizeof(password), 0);
 		test = Log_In(usr,pass);
 		send(client_socket, &test, sizeof(test), 0); ////test = 1 -> OK, test = 0 -> ERROR////
 		break;

 		case 2:
 		recv(client_socket, &user, sizeof(user), 0);
 		recv(client_socket, &password, sizeof(password), 0);
 		test = Create_User(usr,pass);
 		send(client_socket, &test, sizeof(test), 0);
 		break;
 	}


 	//////CLOSE THE CONNECTION, CLOSE THE SOCKET//////
 	close(server_socket);

	return 0;
}
