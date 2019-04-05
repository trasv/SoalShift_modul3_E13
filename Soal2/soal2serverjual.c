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
#define PORT 1234

pthread_t tid[2];

/*void *tambah(void *ptr){
	int *n = (int*) ptr;
	*n = *n + 1;
}*/

void *print(void *ptr){
	while(1){
		printf("Stok sekarang: %d\n", *((int*) ptr));
		sleep(5);
	}
}

int main(){
	int server_fd, new_socket, valread, err;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[20] = {0};
      
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
	
	*stok = 0;
	//printf("Stok awal: %d\n", *stok);
	
	err = pthread_create(&(tid[1]), NULL, print, stok);
	if(err!=0) {
		printf("\n can't create thread : [%s]", strerror(err));
	}
	
    while(1){
		/*err = pthread_create(&(tid[0]), NULL, tambah, &stok);
		if(err!=0) {
			printf("\n can't create thread : [%s]", strerror(err));
		}*/
		memset(buffer, '\0', sizeof(buffer));
		valread = read(new_socket, buffer, 20);
		if(!valread)
			break;
		printf("%s\n",buffer );
		if(strcmp(buffer, "tambah") == 0){
			(*stok) = (*stok) + 1;
		}
	}
    
    //send(new_socket , hello , strlen(hello) , 0 );
    //printf("Hello message sent\n");
    shmdt(stok);
	shmctl(shmid, IPC_RMID, NULL);
	pthread_join(tid[1], NULL);
	
	return 0;
}
