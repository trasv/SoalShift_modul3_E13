#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_t tid[100];

void insertionSort(int a[], int n){
	
	int key, i;
	for(int j=2; j<n; j++){
		key = a[j];
		i = j-1;
		while(i>0 && a[i] > key){
			a[i+1] = a[i];
			i--;
		}
    a[i+1] = key;
	}
}

void *factorial(void *ptr){
	int n = *((int*) ptr);
	int temp = n;
	unsigned long long hasil = 1;
	if(n == 0 || n == 1){
		hasil = 1;
	} else{
		for(n; n >=1; n--){
			hasil *= n;
		}
	}
	printf("%d! = %llu\n", temp, hasil);
}

int main(int argc, const char * argv[]){
	int a[argc], err;
	for(int j=1; j<argc; j++){
		a[j] = atoi(argv[j]);
	}
	
	insertionSort(a, argc);

	for(int i=1; i<argc; i++){
		err = pthread_create(&(tid[i]), NULL, factorial, &a[i]);
		if(err!=0) {
			printf("\n can't create thread : [%s]",strerror(err));
		}
		pthread_join(tid[i], NULL);
	}

  return 0;
}
