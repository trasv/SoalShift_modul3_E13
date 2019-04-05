#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;
int status_ketxt1 = 0;
int status_ketxt2 = 0;
int status2 = 0;
int statusprint = 0;
int statusprint1 = 0;
int statusprint2 = 0;


void* ketxt1(void *arg)
{
    system("ps -aux | tail -n10 > /home/trasv/Documents/FolderProses1/SimpanProses1.txt");
    status_ketxt1 = 1;

}

void* ketxt2(void *arg)
{
    system("ps -aux | tail -n10 > /home/trasv/Documents/FolderProses2/SimpanProses2.txt");
    status_ketxt2 = 1;

}


void* ngezip1(void *arg)
{
    while(status_ketxt1 != 1)
    {

    }

    system("zip -m -j /home/trasv/Documents/FolderProses1/KompresProses1.zip /home/trasv/Documents/FolderProses1/SimpanProses1.txt");

    statusprint1 = 1;
}

void* ngezip2(void *arg)
{
    while(status_ketxt2 != 1)
    {

    }

    system("zip -m -j /home/trasv/Documents/FolderProses2/KompresProses2.zip /home/trasv/Documents/FolderProses2/SimpanProses2.txt");

    statusprint2 = 1;
}

void* nunggu(void *arg)
{
    //printf("tes\n");
    while(statusprint1 != 1 && statusprint2 != 1)
    {

    }

    //printf("test\n");

    statusprint = 1;

}

void* ngeprint(void *arg)
{
    while(statusprint != 1)
    {

    }

    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    status2 = 1;

}

void* ngeunzip1(void *arg)
{
    while(status2 != 1)
    {

    }

    system("unzip /home/trasv/Documents/FolderProses1/KompresProses1.zip");
    system("mv /home/trasv/Timo/Sisop/3/SimpanProses1.txt /home/trasv/Documents/FolderProses1/");
}

void* ngeunzip2(void *arg)
{
    while(status2 != 1)
    {

    }

    system("unzip /home/trasv/Documents/FolderProses2/KompresProses2.zip");
    system("mv /home/trasv/Timo/Sisop/3/SimpanProses2.txt /home/trasv/Documents/FolderProses2/");

}

int main(void)
{

    pthread_create(&(tid1), NULL, ketxt1, NULL);
    pthread_create(&(tid2), NULL, ketxt2, NULL);
    pthread_create(&(tid3), NULL, ngezip1, NULL);
    pthread_create(&(tid4), NULL, ngezip2, NULL);
    pthread_create(&(tid5), NULL, nunggu, NULL);
    pthread_create(&(tid6), NULL, ngeprint, NULL);
    pthread_create(&(tid7), NULL, ngeunzip1, NULL);
    pthread_create(&(tid8), NULL, ngeunzip2, NULL);


    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);
    pthread_join(tid7, NULL);
    pthread_join(tid8, NULL);


    return 0;
}
