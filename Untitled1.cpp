#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int MAX_BUKU = 100;

struct Buku {
    int nomor;
    string judul;
    string penulis;
    int stok;
};

Buku daftar[MAX_BUKU];
int jumlah = 0;

// Konversi string angka ke integer (manual, tanpa stoi)
int konversiKeInt(const string& str) {
    int hasil = 0;
    for (char c : str) {
        hasil = hasil * 10 + (c - '0');
    }
    return hasil;
}

// Baca file txt dengan parsing string manual (tidak pakai substr atau stoi)
void bacaDataDariFile(const string& namaFile) {
    ifstream file(namaFile);
    jumlah = 0;

    if (!file) {
        cout << "Gagal membuka file." << endl;
        return;
    }

    string baris;
    while (getline(file, baris) && jumlah < MAX_BUKU) {
        string strNomor, strJudul, strPenulis, strStok;
        stringstream ss(baris);

        getline(ss, strNomor, ';');
        getline(ss, strJudul, ';');
        getline(ss, strPenulis, ';');
        getline(ss, strStok, ';');

        daftar[jumlah].nomor = konversiKeInt(strNomor);
        daftar[jumlah].judul = strJudul;
        daftar[jumlah].penulis = strPenulis;
        daftar[jumlah].stok = konversiKeInt(strStok);

        jumlah++;
    }

    file.close();
}

// Cocokkan string (pencarian linear manual)
bool cocok(const string& sumber, const string& kataKunci) {
    int lenSumber = sumber.length();
    int lenCari = kataKunci.length();

    for (int i = 0; i <= lenSumber - lenCari; ++i) {
        int j = 0;
        while (j < lenCari && sumber[i + j] == kataKunci[j]) {
            j++;
        }
        if (j == lenCari) return true;
    }
    return false;
}

// Simpan hasil pencarian ke file
void simpanKeFile(Buku hasil[], int n, const string& namaFile) {
    ofstream file(namaFile);
    for (int i = 0; i < n; ++i) {
        file << hasil[i].nomor << ";" << hasil[i].judul << ";" << hasil[i].penulis << ";" << hasil[i].stok << endl;
    }
    file.close();
}

// Tampilkan semua data
void tampilkan(Buku data[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << data[i].nomor << " | " << data[i].judul << " | " << data[i].penulis << " | Stok: " << data[i].stok << endl;
    }
}

// Cari berdasarkan judul
void cariBerdasarkanJudul(const string& kata) {
    Buku hasil[MAX_BUKU];
    int n = 0;
    for (int i = 0; i < jumlah; ++i) {
        if (cocok(daftar[i].judul, kata)) {
            hasil[n++] = daftar[i];
        }
    }

    if (n > 0) {
        cout << "\nHasil pencarian berdasarkan judul:\n";
        tampilkan(hasil, n);
        simpanKeFile(hasil, n, "hasil_cari_judul.txt");
    } else {
        cout << "Tidak ditemukan.\n";
    }
}

// Cari berdasarkan penulis
void cariBerdasarkanPenulis(const string& kata) {
    Buku hasil[MAX_BUKU];
    int n = 0;
    for (int i = 0; i < jumlah; ++i) {
        if (cocok(daftar[i].penulis, kata)) {
            hasil[n++] = daftar[i];
        }
    }

    if (n > 0) {
        cout << "\nHasil pencarian berdasarkan penulis:\n";
        tampilkan(hasil, n);
        simpanKeFile(hasil, n, "hasil_cari_penulis.txt");
    } else {
        cout << "Tidak ditemukan.\n";
    }
}

// Cari stok kurang dari nilai tertentu
void cariStokKurangDari(int batas) {
    cout << "\nBuku dengan stok kurang dari " << batas << ":\n";
    for (int i = 0; i < jumlah; ++i) {
        if (daftar[i].stok < batas) {
            cout << daftar[i].judul << " | Stok: " << daftar[i].stok << endl;
        }
    }
}

// Cari buku dengan stok terbanyak
void cariStokTerbanyak() {
    if (jumlah == 0) return;
    int maxStok = daftar[0].stok;
    for (int i = 1; i < jumlah; ++i) {
        if (daftar[i].stok > maxStok) {
            maxStok = daftar[i].stok;
        }
    }

    cout << "\nBuku dengan stok terbanyak:\n";
    for (int i = 0; i < jumlah; ++i) {
        if (daftar[i].stok == maxStok) {
            cout << daftar[i].judul << " | Stok: " << daftar[i].stok << endl;
        }
    }
}

// Urutkan A-Z berdasarkan judul
void urutkanAZ() {
    for (int i = 0; i < jumlah - 1; ++i) {
        for (int j = i + 1; j < jumlah; ++j) {
            if (daftar[i].judul > daftar[j].judul) {
                swap(daftar[i], daftar[j]);
            }
        }
    }

    cout << "\nBuku urut A-Z:\n";
    tampilkan(daftar, jumlah);
}

// Urutkan Z-A berdasarkan judul
void urutkanZA() {
    for (int i = 0; i < jumlah - 1; ++i) {
        for (int j = i + 1; j < jumlah; ++j) {
            if (daftar[i].judul < daftar[j].judul) {
                swap(daftar[i], daftar[j]);
            }
        }
    }

    cout << "\nBuku urut Z-A:\n";
    tampilkan(daftar, jumlah);
}

// MAIN PROGRAM
int main() {
    int pilihan;
    string kata;

    bacaDataDariFile("data_buku.txt");

    do {
        cout << "\n=== MENU INVENTARIS PERPUSTAKAAN ===\n";
        cout << "1. Tampilkan semua data buku\n";
        cout << "2. Cari berdasarkan judul\n";
        cout << "3. Cari berdasarkan penulis\n";
        cout << "4. Cari stok < 5\n";
        cout << "5. Buku dengan stok terbanyak\n";
        cout << "6. Urutkan A-Z berdasarkan judul\n";
        cout << "7. Urutkan Z-A berdasarkan judul\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkan(daftar, jumlah);
                break;
            case 2:
                cout << "Masukkan kata kunci judul: ";
                getline(cin, kata);
                cariBerdasarkanJudul(kata);
                break;
            case 3:
                cout << "Masukkan kata kunci penulis: ";
                getline(cin, kata);
                cariBerdasarkanPenulis(kata);
                break;
            case 4:
                cariStokKurangDari(5);
                break;
            case 5:
                cariStokTerbanyak();
                break;
            case 6:
                urutkanAZ();
                break;
            case 7:
                urutkanZA();
                break;
            case 8:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 8);

    return 0;
}