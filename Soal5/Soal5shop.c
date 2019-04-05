#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>
#include<termios.h>

pthread_t tid1, tid2, tid3;
int status;

int *value;
int foodstock;
int keluar=0;

int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void* shop(void *arg)
{
    status = 1;
    key_t key = 6969;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    //foodstock=*value;

    while(1)
    {
	char action;
	//scanf("%d",&action);
	action=getch();

	if(action=='1')
	{
		(*value)++;
	}
	else if(action=='2')
	{
		keluar=1;
		break;
	}
    }
    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}

void* print_shop(void *arg)
{
    while(1)
    {
	if(status==1)
	{
		printf("Shop\n");
        	printf("Food stock : %d\n",*value);
        	printf("Choices\n");
        	printf("1. Restock\n2. Exit\n");
        	sleep(1);
        	system("clear");
	}
    }
}

void* selesai(void *arg)
{
    while(1)
    {
        if(keluar==1)
        {
		printf("Anda Telah Keluar dari shop\n");
		break;
        }
    }
    pthread_kill(tid1, SIGKILL);
    pthread_kill(tid2, SIGKILL);
    pthread_kill(tid3, SIGKILL);
}
int main(void)
{

    pthread_create(&(tid1), NULL, shop, NULL);
    pthread_create(&(tid2), NULL, print_shop, NULL);
    pthread_create(&(tid3), NULL, selesai, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    return 0;
}
