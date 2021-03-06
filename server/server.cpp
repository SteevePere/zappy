#include "server.hh"


Server::Server(int port): _port(port) {

}


Server::~Server() {

}


int Server::launch() const {

	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char const* connected = "Connection to Server was successful";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {

		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {

		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {

		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {

		perror("Listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {

		perror("Accept");
		exit(EXIT_FAILURE);
	}

	read(new_socket, buffer, 1024);
	printf("%s\n", buffer);

	send(new_socket, connected, strlen(connected), 0);

	return 0;

}
