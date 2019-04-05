#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

pthread_t tid1, tid2, tid3, tid4, tid5;
int status, flag;
int aws = 0;
int iss = 100;
int flagaws = 0;
int flagiss = 0;
int statusaws = 1;
int statusiss = 1;
int threadaws = 0;
int threadiss = 0;
int keluar = 0;

void* awal(void *arg)
{
    status = 0;

    while(1)
    {
        int menu;
        printf("1. All Status\n2. Agmal Ayo Bangun\n3. Iraj Ayo Tidur\n\nPilih angka untuk memilih menu!\n");
        scanf("%d",&menu);
        printf("\n");

        if(menu==1)
        {
                printf("Agmal WakeUp Status = %d\nIraj Spirit Satus = %d\n\n",aws,iss);
        }
        else if(menu==2)
        {
                if(statusiss==0)
                {
                        printf("Agmal Ayo Bangun disabled 10s\n\n");

                }
                else if(statusiss==1)
                {
                        aws+=15;
                        flagaws+=1;
                }
        }
        else if(menu==3)
        {
                if(statusaws==0)
                {
                        printf("Fitur Iraj Ayo Tidur disabled 10s\n\n");
                }
                else if(statusiss==1)
                {
                        iss-=20;
                        flagiss+=1;
                }
        }

        if(flagaws==3)
        {
                threadaws = 1;
        }
        if(flagaws==6)
        {
                threadaws = 2;
        }
        if(flagiss==3)
        {
                threadiss = 1;
        }


        if(aws >= 100)
        {
                flag = 1;
                break;
        }
        if(iss <= 0)
        {
                flag = 2;
                break;
        }


    }

    status = 1;

    return 0;
}

void* th_aws(void *arg)
{
    int tanda = 0;
    while(threadaws != 1)
    {
        if(keluar==1)
        {
                tanda = 1;
                break;
        }
    }
    if(tanda!=1)
    {
    statusaws = 0;
    sleep(10);
    statusaws = 1;
    }

    return 0;
}

void* th_aws2(void *arg)
{
    int tanda = 0;
    while(threadaws != 2)
    {
        if(keluar==1)
        {
                tanda = 1;
                break;
        }

    }
    if(tanda!=1)
    {
    statusaws = 0;
    sleep(10);
    statusaws = 1;
    }

    return 0;
}

void* th_iss(void *arg)
{
    int tanda = 0;
    while(threadiss != 1)
    {
        if(keluar==1)
        {
                tanda = 1;
                break;
        }
    }

    if(tanda!=1)
    {
    statusiss = 0;
    sleep(10);
    statusiss = 1;
    }

    return 0;
}

void* akhir(void *arg)
{
    while(status != 1)
    {

    }

    if(flag==1)
    {
        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
        keluar = 1;
    }
    else if (flag==2)
    {
        printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
        keluar = 1;
    }
    pthread_kill(tid2, SIGKILL);
    pthread_kill(tid3, SIGKILL);
    pthread_kill(tid4, SIGKILL);

    return NULL;
}

int main(void)
{

    pthread_create(&(tid1), NULL, awal, NULL);
    pthread_create(&(tid2), NULL, th_aws, NULL);
    pthread_create(&(tid3), NULL, th_aws2, NULL);
    pthread_create(&(tid4), NULL, th_iss, NULL);
    pthread_create(&(tid5), NULL, akhir, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    return 0;
}
