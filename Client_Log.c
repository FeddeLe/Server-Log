#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main (void)
{
  	char server_data[256];
  	char user[20];
  	char password[20];
  	int user_input;
  	int test;

	///////CREATE A SOCKET/////
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);


	///////SPECIFY AN ADDRESS FOR THE SOCKET///////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	///////CONNECT TO THE SERVER//////
	int connection_status;
	connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	if (connection_status == -1)
	{
		printf("ERROR\n");
	}


	///////IF THE SERVER ACCEPT OUR CONNECTION, RECEIVE AND SEND DATA///////
	recv(network_socket, &server_data, sizeof(server_data), 0);
	printf("%s\n",server_data);
	scanf("%d",&user_input);
	send(network_socket, &user_input, sizeof(user_input), 0);
	
	printf("Enter User and Password\n");
	scanf("%s",user);
	scanf("%s",password);
	send(network_socket, user, sizeof(user), 0);
	send(network_socket, password, sizeof(user), 0);

	recv(network_socket, &test, sizeof(test), 0);

	if (user_input == 1)
	{
		switch (test)
		{
			case 1:
			printf("Succesfully loged!\n");
			break;

			case 0:
			printf("ERROR: Invalid user or password\n");
		}
	}

	if (user_input == 2)
	{
		switch (test)
		{
			case 1:
			printf("Succesfully registered!\n");
			break;

			case 0:
			printf("The user name is unavailable\n");
			break;

			case -1:
			printf("Remember: The password must contain at least one uppercase, one lowercase, one number and must contain 6 to 20 characters\n");
			break;
		}
	}


	return 0;
}
