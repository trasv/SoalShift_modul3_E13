# SoalShift_modul3_E13
Jawaban Soal Praktikum Modul 3 Sisop

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
