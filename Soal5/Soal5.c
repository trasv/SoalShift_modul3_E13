#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<termios.h>

pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10;
int status;

int *value;
char nama[100];
int health = 300;
int hunger = 200;
int hygiene = 100;
int food = 0;
int foodstock = 0;
int bathcd = 0;
int bathcooldown = 0;
int enemyhealth = 100;
int state = 0;
int kalah=0;
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

void* mulai(void *arg)
{
    printf("Masukkan Nama monster yang diinginkan : ");
    scanf("%s",nama);
    //while(1)
    //    {
		while(1)
                {
			//standby
			state = 1; //decrement standby mode
			status = 1; //ngeprint
                	char action;

                        //scanf("%d",&action);
			action=getch();
                        if(action=='1')
                        {
				food--;
				hunger+=15;
                        }
   			else if(action=='2' && bathcooldown==0)
                        {
				hygiene+=30;
				bathcooldown=1;
                        }
                        else if(action=='3')
                        {
				//battle mode
				enemyhealth = 100;
				while(1)
                        	{
                         		char action;
					state = 0;
					status = 2;
                                	//scanf("%d",&action);
					action=getch();

                                	if(action=='1')
                                	{
                                        	health-=20;
                                        	enemyhealth-=20;
                                	}
                                	else if(action=='2')
                                	{
                                        	break;
                                	}
                                	if(enemyhealth<=0)
                                	{
                                        	printf("NPC Telah Kalah\n");
                                        	break;
                                	}
                        	}
                        }
                        else if(action=='4')
                        {
				//shop mode
				key_t key = 6969;
				int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
				value = shmat(shmid, NULL, 0);
				//foodstock=*value;

				while(1)
                        	{
					//foodstock=value;
					status = 3;
					state=0;
                                	char action;
                                	//scanf("%d",&action);
					action=getch();

                                	if(action=='1')
                                	{
                                        	if((*value)<=0)
						{
							printf("Stok toko habis\n");
						}
						else
						{
							food++;
                                                	(*value)--;
						}
                                	}
                                	else if(action=='2')
                                	{
                                	        break;
                                	}
                                	system("clear");
                        	}
				shmdt(value);
				shmctl(shmid, IPC_RMID, NULL);

                        }
                        else if(action=='5')
                        {
				keluar=1;
                                break;
                        }
                        //system("clear");
                }
	//}
        //system("clear");

    return NULL;
}

void* hungerstatus(void *arg)
{
    while(1)
    {
	if(state==1)
	{
		sleep(10);
		if(state==1)
		{
			hunger-=5;
		}
	}
    }
}

void* hygienestatus(void *arg)
{
    while(1)
    {
        if(state==1)
        {
                sleep(30);
		if(state==1)
		{
                	hygiene-=10;
		}
        }
    }
}

void* healthstatus(void *arg)
{
    while(1)
    {
        if(state==1)
        {
                sleep(10);
		if(state==1)
		{
			health+=5;
		}
        }
    }
}

void* th_bathcooldown(void *arg)
{
    while(1)
    {
        if(bathcooldown==1)
        {
		bathcd=20;
                sleep(20);
                bathcooldown=0;
		bathcd=1;
        }
    }
}

void* hitung_bathcooldown(void *arg)
{
    while(1)
    {
        while(bathcooldown==1)
        {
                sleep(1);
                bathcd--;
        }
    }
}

void* print_standby(void *arg)
{
    while(1)
    {
	if(status==1)
	{
		printf("Standby Mode\n");
		printf("Nama : %s\n",nama);
        	printf("Health : %d\n",health);
        	printf("Hunger : %d\n",hunger);
        	printf("Hygiene : %d\n",hygiene);
        	printf("Food left : %d\n",food);
        	printf("Bath will be ready in %ds\n",bathcd);
        	printf("Choices\n");
        	printf("1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
		sleep(1);
		system("clear");
    	}
    }
}

void* print_battle(void *arg)
{
    while(1)
    {
        if(status==2)
        {
                printf("Battle Mode\n");
		printf("Nama : %s\n",nama);
                printf("Monster's Health : %d\n",health);
                printf("Enemy's Health : %d\n",enemyhealth);
                printf("Choices\n");
                printf("1. Attack\n2. Run\n");
                sleep(1);
                system("clear");
        }
    }
}

void* print_shop(void *arg)
{
    while(1)
    {
        if(status==3)
        {
		printf("Shop Mode\n");
		printf("Nama : %s\n",nama);
                printf("Shop food stock : %d\n",*value);
                printf("Your food stock : %d\n",food);
                printf("Choices\n");
                printf("1. Buy\n2. Back\n");
                sleep(1);
                system("clear");
        }
    }
}

void* selesai(void *arg)
{
    while(1)
    {
	if(hunger<=0 || hygiene<=0 || keluar==1)
	{
		break;
	}
    }

    if(keluar==1)
    {
	printf("Anda Telah Keluar dari permainan\n");
    }
    else
    {
	printf("Monster Anda Kalah\n");
    }
    pthread_kill(tid1, SIGKILL);
    pthread_kill(tid2, SIGKILL);
    pthread_kill(tid3, SIGKILL);
    pthread_kill(tid4, SIGKILL);
    pthread_kill(tid5, SIGKILL);
    pthread_kill(tid6, SIGKILL);
    pthread_kill(tid7, SIGKILL);
    pthread_kill(tid8, SIGKILL);
    pthread_kill(tid9, SIGKILL);

}

int main()
{

    pthread_create(&(tid1), NULL, mulai, NULL);
    pthread_create(&(tid2), NULL, hungerstatus, NULL);
    pthread_create(&(tid3), NULL, hygienestatus, NULL);
    pthread_create(&(tid4), NULL, healthstatus, NULL);
    pthread_create(&(tid5), NULL, th_bathcooldown, NULL);
    pthread_create(&(tid6), NULL, hitung_bathcooldown, NULL);
    pthread_create(&(tid7), NULL, print_standby, NULL);
    pthread_create(&(tid8), NULL, print_battle, NULL);
    pthread_create(&(tid9), NULL, print_shop, NULL);
    pthread_create(&(tid10), NULL, selesai, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);
    pthread_join(tid7, NULL);
    pthread_join(tid8, NULL);
    pthread_join(tid9, NULL);
    pthread_join(tid10, NULL);

    return 0;
}
