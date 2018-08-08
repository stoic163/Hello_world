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
	int socket_srv = -1;
	int socket_client = -1;
	int t = -1;
	int len = 0;
	struct sockaddr_un addr_srv, addr_client;
	char str[100];
	memset(str, 0 , sizeof(char)*100);

	if ((socket_srv = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	addr_srv.sun_family = AF_UNIX;
	strcpy(addr_srv.sun_path, UDS_PATH);
	if (bind(socket_srv, (struct sockaddr *)&addr_srv, offsetof(struct sockaddr_un, sun_path) + strlen(addr_srv.sun_path)) < 0) {
		return -1;
	}

	if (listen(socket_srv, 10) < 0) {
		return -1;
	}

	while(1) {
		int nRecv;
		int *sz = sizeof(addr_client);
		if ((socket_client  = accept(socket_srv, (struct sockaddr *)&addr_client, *sz)) == -1 ){
		return -1;
		}

		if (nRecv = recv(socket_client, str, 100,0) < 0) {
			close(socket_client);
			break;
		}

		if (send(socket_client, str, nRecv, 0) < 0) {
			close(socket_client);
			break;
		}
		close(socket_client);
	}
	return 0;
}
