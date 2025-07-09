# coba

Deklarasi:
    array buku[100] bertipe struct { judul, penulis }
    integer jumlahBuku
    string kata_kunci
    boolean ditemukan ← false

Prosedur:
1. Baca data dari file "data_buku.txt" ke array buku[]
   jumlahBuku ← jumlah data yang berhasil dibaca

2. Tampilkan: "Masukkan kata kunci pencarian:"
   Input kata_kunci

3. ditemukan ← false

4. Untuk i dari 0 sampai jumlahBuku - 1 lakukan
     Jika kata_kunci ditemukan dalam buku[i].judul ATAU buku[i].penulis maka
         Tampilkan "Judul  : ", buku[i].judul
         Tampilkan "Penulis: ", buku[i].penulis
         Tampilkan "-----------------------"
         ditemukan ← true
     End Jika
   End Untuk

5. Jika ditemukan = false maka
     Tampilkan "Data tidak ditemukan."
   End Jika

Selesai
