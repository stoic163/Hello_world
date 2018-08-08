#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/types.h>
#include<stddef.h>
#define UDS_PATH "uds_test"

int main(void)
{
	int socket_client = -1;
	int data_len = 0;
	int addr_size = 0;

	struct sockaddr_un addr_srv;
	char str[100];
	memset(str, 0, sizeof(char)*100);
	strcpy(str, "This is a test for UDS");

	if ((socket_client = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	addr_srv.sun_family = AF_UNIX;
	strcpy(addr_srv.sun_path, UDS_PATH);
	addr_size = offsetof(struct sockaddr_un, sun_path) + strlen(addr_srv.sun_path);
	if (connect(socket_client, (struct sockaddr *)&addr_srv, addr_size) < 0) {
		return -1;
	}

	if (send(socket_client, str, strlen(str), 0) < 0) {
		close(socket_client);
		return -1;
	}

	if ((data_len = recv(socket_client, str, 100, 0)) > 0) {
		str[data_len] = '\0';
		printf("echo from server:%s", str);
	} else {
		close(socket_client);
		return -1;
	}
	close(socket_client);
	return 0;
}
