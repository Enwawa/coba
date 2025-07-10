#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BUKU = 100;

class Buku {
private:
    int nomor;
    string judul;
    string penulis;
    int stok;

public:
    Buku() : nomor(0), judul(""), penulis(""), stok(0) {}

    void set(int no, string jdl, string pns, int st) {
        nomor = no;
        judul = jdl;
        penulis = pns;
        stok = st;
    }

    int getNomor() const { return nomor; }
    string getJudul() const { return judul; }
    string getPenulis() const { return penulis; }
    int getStok() const { return stok; }

    void tampil() const {
        cout << nomor << " | " << judul << " | " << penulis << " | Stok: " << stok << endl;
    }

    string toString() const {
        return to_string(nomor) + ";" + judul + ";" + penulis + ";" + to_string(stok);
    }
};

class Perpustakaan {
private:
    Buku daftar[MAX_BUKU];
    int jumlah;

public:
    Perpustakaan() {
        jumlah = 0;
    }

    void bacaData(const string& fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "Gagal membuka file.\n";
            return;
        }

        jumlah = 0;
        string baris;
        while (getline(file, baris) && jumlah < MAX_BUKU) {
            size_t p1 = baris.find(';');
            size_t p2 = baris.find(';', p1 + 1);
            size_t p3 = baris.find(';', p2 + 1);

            if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue;

            int nomor = stoi(baris.substr(0, p1));
            string judul = baris.substr(p1 + 1, p2 - p1 - 1);
            string penulis = baris.substr(p2 + 1, p3 - p2 - 1);
            int stok = stoi(baris.substr(p3 + 1));

            daftar[jumlah++].set(nomor, judul, penulis, stok);
        }

        file.close();
    }

    void tampilkanSemua() {
        for (int i = 0; i < jumlah; i++) {
            daftar[i].tampil();
        }
    }

    void tambahBukuDariInput() {
        if (jumlah >= MAX_BUKU) {
            cout << "Kapasitas penuh!" << endl;
            return;
        }

        int nomor, stok;
        string judul, penulis;

        cout << "Masukkan nomor buku  : ";
        cin >> nomor;
        cin.ignore();

        cout << "Masukkan judul buku  : ";
        getline(cin, judul);

        cout << "Masukkan nama penulis: ";
        getline(cin, penulis);

        cout << "Masukkan stok buku   : ";
        cin >> stok;
        cin.ignore();

        daftar[jumlah].set(nomor, judul, penulis, stok);
        jumlah++;

        ofstream file("data_buku.txt", ios::app);
        if (file) {
            file << nomor << ";" << judul << ";" << penulis << ";" << stok << endl;
            file.close();
            cout << "Data buku berhasil disimpan ke file.\n";
        } else {
            cout << "Gagal menyimpan ke file.\n";
        }
    }

    void cariJudul(const string& kata) {
        ofstream out("hasil_cari_judul.txt");
        bool ditemukan = false;
        for (int i = 0; i < jumlah; i++) {
            if (daftar[i].getJudul().find(kata) != string::npos) {
                daftar[i].tampil();
                out << daftar[i].toString() << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) cout << "Tidak ditemukan.\n";
        out.close();
    }

    void cariPenulis(const string& kata) {
        ofstream out("hasil_cari_penulis.txt");
        bool ditemukan = false;
        for (int i = 0; i < jumlah; i++) {
            if (daftar[i].getPenulis().find(kata) != string::npos) {
                daftar[i].tampil();
                out << daftar[i].toString() << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) cout << "Tidak ditemukan.\n";
        out.close();
    }

    void cariStokKurangDari(int batas) {
        bool ditemukan = false;
        for (int i = 0; i < jumlah; i++) {
            if (daftar[i].getStok() < batas) {
                daftar[i].tampil();
                ditemukan = true;
            }
        }
        if (!ditemukan)
            cout << "Tidak ada buku dengan stok < " << batas << endl;
    }

    void cariStokTerbanyak() {
        if (jumlah == 0) return;

        int maxStok = daftar[0].getStok();
        for (int i = 1; i < jumlah; i++) {
            if (daftar[i].getStok() > maxStok) {
                maxStok = daftar[i].getStok();
            }
        }

        for (int i = 0; i < jumlah; i++) {
            if (daftar[i].getStok() == maxStok) {
                daftar[i].tampil();
            }
        }
    }

    void urutkanAZ() {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = i + 1; j < jumlah; j++) {
                if (daftar[i].getJudul() > daftar[j].getJudul()) {
                    swap(daftar[i], daftar[j]);
                }
            }
        }
        tampilkanSemua();
    }

    void urutkanZA() {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = i + 1; j < jumlah; j++) {
                if (daftar[i].getJudul() < daftar[j].getJudul()) {
                    swap(daftar[i], daftar[j]);
                }
            }
        }
        tampilkanSemua();
    }
};

// === MAIN PROGRAM ===
int main() {
    Perpustakaan p;
    p.bacaData("data_buku.txt");

    int pilihan;
    string kata;

    do {
        cout << "\n=== MENU INVENTARIS PERPUSTAKAAN ===\n";
        cout << "1. Tambah data buku (input manual)\n";
        cout << "2. Cari berdasarkan judul\n";
        cout << "3. Cari berdasarkan penulis\n";
        cout << "4. Cari stok < 5\n";
        cout << "5. Buku dengan stok terbanyak\n";
        cout << "6. Urutkan A-Z berdasarkan judul\n";
        cout << "7. Urutkan Z-A berdasarkan judul\n";
        cout << "8. Tampilkan semua buku\n";
        cout << "9. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: p.tambahBukuDariInput(); break;
            case 2:
                cout << "Masukkan kata kunci judul: ";
                getline(cin, kata);
                p.cariJudul(kata);
                break;
            case 3:
                cout << "Masukkan kata kunci penulis: ";
                getline(cin, kata);
                p.cariPenulis(kata);
                break;
            case 4:
                p.cariStokKurangDari(5);
                break;
            case 5:
                p.cariStokTerbanyak();
                break;
            case 6:
                p.urutkanAZ();
                break;
            case 7:
                p.urutkanZA();
                break;
            case 8:
                p.tampilkanSemua();
                break;
            case 9:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 9);

    return 0;
}
