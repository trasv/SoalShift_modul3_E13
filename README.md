# SoalShift_modul3_E13
Jawaban Soal Praktikum Modul 3 Sisop

1. Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:

   ./faktorial 5 3 4
   
   3! = 6
   
   4! = 24
   
   5! = 120
   
   Jawab:
   ```
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
   ```
   #### Pengambilan angka
   Karena angka yang akan dihitung diambil dari parameter linux bash saat menjalankan program, maka untuk mendapatkannya didalam `int main()` dimasukkan `int argc, const char * argv[]`, dimana akan secara otomatis akan menghitung jumlah parameter dan menyimpannya ke dalam array. Data `argc` ini dapat digunakan untuk mengetahui jumlah elemen array yang berikutnya disalin ke array int agar bisa dilakukan penghitungan dengan fungsi `atoi` ke masing-masing elemen, sebagai berikut.
   ```
   int main(int argc, const char * argv[]){
	int a[argc], err;
	for(int j=1; j<argc; j++){
		a[j] = atoi(argv[j]);
	}
	return 0;
   }
   ```
   #### Pengurutan angka
   Karena hasil output adalah berupa hasil faktorial dari setiap angka parameter, maka harus dilakukan pengurutan angka pada array tersebut. Di sini digunakan algoritma Insertion Sort untuk mengurutkannya. Seperti dalam fungsi berikut.
   ```
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
   ```
   #### Penghitungan faktorial
   Setelah diurutkan dengan insertion sort, berikutnya langsung dihitung hasil faktorial. Karena hasil untuk setiap angka dihitung secara paralel, dibuat thread sebanyak `argc-1` (banyak parameter) untuk menghitungnya. Di sini digunakan perulangan untuk masing-masing iterasi membuat thread yang dijalankan untuk fungsi faktorial, dengan parameter utut dari array ke 1 sampai argc-1. Seperti berikut.
   ```
   for(int i=1; i<argc; i++){
	err = pthread_create(&(tid[i]), NULL, factorial, &a[i]);
	if(err!=0) {
		printf("\n can't create thread : [%s]",strerror(err));
	}
	pthread_join(tid[i], NULL);
   }
   ```
   dan fungsi faktorial sebagai berikut.
   ```
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
   ```
   Fungsi faktorial tersebut hanya dijalankan dengan perulangan dengan angka tersebut dikurang satu selama angka tersebut > 0. Hasilnya akan seperti berikut.

2. Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

   a. Terdapat 2 server: server penjual dan server pembeli
   
   b. 1 server hanya bisa terkoneksi dengan 1 client
   
   c. Server penjual dan server pembeli memiliki stok barang yang selalu sama
   
   d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
      - Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
      
   e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
      - Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
      
   f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
      - Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
      - Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
      
   g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali
   
   h. Menggunakan thread, socket, shared memory


3. Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

   a.	Terdapat 2 karakter Agmal dan Iraj
   
   b.	Kedua karakter memiliki status yang unik
   
   ■	Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
   
   ■	Iraj memiliki Spirit_Status, di awal program memiliki status 100
   
   ■	Terdapat 3 Fitur utama

   ●	All Status, yaitu menampilkan status kedua sahabat
   
   Ex: Agmal WakeUp_Status = 75 
   
   Iraj Spirit_Status = 30

   ●	“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point

   ●	“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point

   ■	Terdapat Kasus yang unik dimana:

   ●	Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)

   ●	Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)

   ■	Program akan berhenti jika Salah Satu :

   ●	WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)

   ●	Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

   ■	Syarat Menggunakan Lebih dari 1 Thread

Jawab :

Kami menggunakan 5 thread, untuk menu awal, untuk sleep 3 thread, dan terakhir untuk menyeesaikan semua, ngeprint dan kill thread. di thread menu terdapat 3 menu yang sudah disuruh di soal. terdapat counter saat menjalankan agmal ayo bangun dan iraj ayo tidur mencapai 3 kali, masing masing akan saling mengeblok. saat iraj sudah 0 atau agmal sudah 100, program akan selesai.

```
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
                else if(statusaws==1)
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
```

4. Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 

   ➔	Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama

   ➔	Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama

   ➔	Ketika Mengekstrak file .zip juga harus secara bersama-sama

   ➔	Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”

   ➔	Wajib Menggunakan Multithreading

   ➔	Boleh menggunakan system

Jawab :
   
Kami menggunakan 7 thread dimana 2 thread untuk memasukkan 10 proses ke file, 2 thread untuk menzip masing masing file, 1 proses untuk menunggu, dan 2 thread terakhir untuk mengunzip masing masing zip tadi. terdapat banyak flag yang digunakan untuk tanda agar masing masing thread berjalan bersama-sama/bergantian tergantung soal misalnya 2 thread untuk memasukkan file berjalan bersama lalu flag berganti lalu 2 thread untuk zip berjalan, dan seterusnya.

```
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
```


5.	Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 

   a.	Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.

   b.	Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.

   c.	Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).

   d.	Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.

   e.	Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 

   f.	Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.

   ■	Pembeli (terintegrasi dengan game)

   ●	Dapat mengecek stok makanan yang ada di toko.

   ●	Jika stok ada, pembeli dapat membeli makanan.

   ■	Penjual (terpisah)

   ●	Bisa mengecek stok makanan yang ada di toko

   ●	Penjual dapat menambah stok makanan.

Spesifikasi program:

A.	Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)

B.	Program terdiri dari 3 scene yaitu standby, battle, dan shop.

C.	Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode

Health : [health status]

Hunger : [hunger status]

Hygiene : [hygiene status]

Food left : [your food stock]

Bath will be ready in [cooldown]s

Choices

1.	Eat

2.	Bath

3.	Battle

4.	Shop

5.	Exit

D.	Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode

Monster’s Health : [health status]

Enemy’s Health : [enemy health status]

Choices

1.	Attack

2.	Run

E.	Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode

Shop food stock : [shop food stock]

Your food stock : [your food stock]

Choices

1.	Buy

2.	Back

F.	Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop

Food stock : [shop food stock]

Choices

1.	Restock

2.	Exit

G.	Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))


   Jawab :
   
   Terdapat 2 program dimana satunya adalah gamenya dan satunya adalah program penjual
   karena disuruh untuk auto detect input keyboard tanpa enter, dan karena getch tidak bisa digunakan di c linux, maka kami menggunakan template dari getch itu sendiri dari internet
   di program game terdapat 10 thread dimana ada yang untuk menu awal, ada yang untuk mengeprint menu di state sekarang, untuk mendecrement variabel tertentu, dan terakhir untuk mengakhiri program
   di program penjual hanya ada 3 thread dimana ada thread untuk menu toko, untuk mengeprint menu tiap detik dan terakhir untuk mengakhiri program.

Program Game

```
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
```

Program shop

```
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
```
