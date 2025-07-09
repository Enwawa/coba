#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BUKU = 100;

class BukuManager {
private:
    struct Buku {
        string judul;
        string penulis;
    };

    Buku daftar[MAX_BUKU];
    int jumlah;
    string namaFile;

public:
    BukuManager(string file) {
        namaFile = file;
        jumlah = 0;
    }

    void inputData() {
        if (jumlah >= MAX_BUKU) {
            cout << "Data penuh!" << endl;
            return;
        }

        Buku b;
        cout << "Judul   : ";
        getline(cin, b.judul);
        cout << "Penulis : ";
        getline(cin, b.penulis);

        ofstream file(namaFile, ios::app); // simpan langsung
        if (file) {
            file << b.judul << ";" << b.penulis << endl;
            file.close();
            cout << "Data berhasil disimpan." << endl;
        } else {
            cout << "Gagal membuka file!" << endl;
        }
    }

    int bacaDariFile() {
        ifstream file(namaFile);
        jumlah = 0;

        if (!file) {
            cout << "File belum tersedia." << endl;
            return 0;
        }

        string baris;
        while (getline(file, baris) && jumlah < MAX_BUKU) {
            size_t pos = baris.find(';');
            if (pos != string::npos) {
                daftar[jumlah].judul = baris.substr(0, pos);
                daftar[jumlah].penulis = baris.substr(pos + 1);
                jumlah++;
            }
        }

        file.close();
        return jumlah;
    }

    void urutkanAZ() {
        for (int i = 0; i < jumlah - 1; ++i) {
            for (int j = i + 1; j < jumlah; ++j) {
                if (daftar[i].judul > daftar[j].judul) {
                    swap(daftar[i], daftar[j]);
                }
            }
        }
    }

    void urutkanZA() {
        for (int i = 0; i < jumlah - 1; ++i) {
            for (int j = i + 1; j < jumlah; ++j) {
                if (daftar[i].judul < daftar[j].judul) {
                    swap(daftar[i], daftar[j]);
                }
            }
        }
    }

    void tampilkan() {
        if (jumlah == 0) {
            cout << "Belum ada data buku." << endl;
            return;
        }

        for (int i = 0; i < jumlah; ++i) {
            cout << "Judul  : " << daftar[i].judul << endl;
            cout << "Penulis: " << daftar[i].penulis << endl;
            cout << "---------------------------" << endl;
        }
    }

    void cariBerdasarkanJudul(const string& kata) {
        if (bacaDariFile() == 0) return;

        bool ditemukan = false;
        for (int i = 0; i < jumlah; ++i) {
            if (daftar[i].judul.find(kata) != string::npos) {
                cout << "Judul  : " << daftar[i].judul << endl;
                cout << "Penulis: " << daftar[i].penulis << endl;
                cout << "---------------------------" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan)
            cout << "Buku dengan judul mengandung \"" << kata << "\" tidak ditemukan." << endl;
    }

    void cariBerdasarkanPenulis(const string& kata) {
        if (bacaDariFile() == 0) return;

        bool ditemukan = false;
        for (int i = 0; i < jumlah; ++i) {
            if (daftar[i].penulis.find(kata) != string::npos) {
                cout << "Judul  : " << daftar[i].judul << endl;
                cout << "Penulis: " << daftar[i].penulis << endl;
                cout << "---------------------------" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan)
            cout << "Buku dengan penulis mengandung \"" << kata << "\" tidak ditemukan." << endl;
    }
};

// ===== MAIN PROGRAM =====
int main() {
    BukuManager manager("data_buku.txt");
    int pilihan;

    do {
        cout << "\n=== MENU DATA BUKU ===" << endl;
        cout << "1. Isi Data Buku" << endl;
        cout << "2. List Buku dari A-Z" << endl;
        cout << "3. List Buku dari Z-A" << endl;
        cout << "4. Cari Buku berdasarkan Penulis" << endl;
        cout << "5. Cari Buku berdasarkan Judul" << endl;
        cout << "6.  Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); // bersihkan newline

        switch (pilihan) {
            case 1:
                manager.inputData();
                break;
            case 2:
                if (manager.bacaDariFile()) {
                    manager.urutkanAZ();
                    cout << "\n== Daftar Buku A-Z ==" << endl;
                    manager.tampilkan();
                }
                break;
            case 3:
                if (manager.bacaDariFile()) {
                    manager.urutkanZA();
                    cout << "\n== Daftar Buku Z-A ==" << endl;
                    manager.tampilkan();
                }
                break;
            case 4:
                string keyword;
                cout << "Masukkan kata kunci penulis: ";
                getline(cin, keyword);
                manager.cariBerdasarkanPenulis(keyword);
                break;
            case 5: {
                string keyword;
                cout << "Masukkan kata kunci judul: ";
                getline(cin, keyword);
                manager.cariBerdasarkanJudul(keyword);
                break;
            }
            case 6: {
                cout << "Terima kasih!" << endl;
                break;
            }
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 4);

    return 0;
}

