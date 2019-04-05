#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <netinet/in.h>
#define PORT 1235

int main(){
	int server_fd, new_socket, valread, err;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[20] = {0};
    char gagal[20] = "transaksi gagal";
    char berhasil[20] = "transaksi berhasil";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) { // diubah jadi 1
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    key_t key = 1234;
	int *stok;

	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	stok = shmat(shmid, NULL, 0);
	
    while(1){		
		valread = read(new_socket, buffer, 20);
		if(!valread)
			break;
		printf("%s\n",buffer );
		if(strcmp(buffer, "beli") == 0){
			if(*stok == 0){
				send(new_socket, gagal, strlen(gagal) , 0 );
			}
			else {
				(*stok) = (*stok)-1;
				send(new_socket, berhasil, strlen(berhasil) , 0 );
			}	
		}
	}
	
	shmdt(stok);
	shmctl(shmid, IPC_RMID, NULL);
	
	return 0;
}
