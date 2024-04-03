#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_BUKU = 100;
const int MAX_PANJANG_JUDUL = 100;
const int MAX_PANJANG_PENGARANG = 100;
const int BATAS_WAKTU_PINJAM = 7; // Batas waktu maksimal peminjaman dalam hari

// Array dua dimensi untuk menyimpan informasi buku
const int MAX_BUKU_INFO = 100;
const int MAX_KOLOM_INFO = 30; // Judul, Pengarang, Tahun Terbit, Kategori, Harga, dan Denda Per Hari
char bukuInfo[MAX_BUKU_INFO][MAX_KOLOM_INFO][100];

// Struktur data untuk menyimpan informasi buku
struct Buku {
    char judul[MAX_PANJANG_JUDUL];
    char pengarang[MAX_PANJANG_PENGARANG];
    int tahun;
    double harga;
    double dendaPerHari;
    char kategori[50]; // Menambahkan kategori buku
};

// Struktur data untuk menyimpan informasi peminjaman buku
struct SimpulPinjam {
    Buku buku;
    SimpulPinjam* next;
};

// Fungsi untuk membuat simpul baru dalam daftar peminjaman
SimpulPinjam* buatSimpulPinjam(Buku buku) {
    SimpulPinjam* newNode = new SimpulPinjam();
    newNode->buku = buku;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk meminjam buku dengan menambahkannya ke daftar peminjaman
void pinjamBuku(SimpulPinjam*& head, Buku buku) {
    SimpulPinjam* newNode = buatSimpulPinjam(buku);
    newNode->next = head;
    head = newNode;
}

// Fungsi untuk mencetak daftar buku yang sedang dipinjam
void cetakDaftarPinjam(SimpulPinjam* head) {
    SimpulPinjam* temp = head;
    double totalHarga = 0;

    cout << "=================================================================================================" << endl;
    cout << "|                           DAFTAR BUKU YANG DIPINJAM                                           |" << endl;
    cout << "=================================================================================================" << endl;
    cout << "| No |     Judul     |    Pengarang    |    Tahun Terbit    |     Kategori      |     Harga     |" << endl;
    cout << "=================================================================================================" << endl;

    int nomor = 1;
    while (temp != nullptr) {
        cout << "| " << setw(2) << nomor << " | " << setw(14) << temp->buku.judul << " | " << setw(15) << temp->buku.pengarang << " | "
             << setw(18) << temp->buku.tahun << " | " << setw(17) << temp->buku.kategori << " | " << setw(13) << temp->buku.harga << " |" << endl;
        totalHarga += temp->buku.harga;
        temp = temp->next;
        nomor++;
    }

    cout << "=================================================================================================" << endl;
    cout << "Total Harga: Rp" << fixed << setprecision(2) << totalHarga << endl;
}

// Fungsi untuk mengembalikan buku yang dipinjam
void kembalikanBuku(SimpulPinjam*& head, const char* judul) {
    SimpulPinjam* temp = head;
    SimpulPinjam* prev = nullptr;

    while (temp != nullptr && strcmp(temp->buku.judul, judul) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != nullptr) {
        if (prev != nullptr) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        delete temp;
        cout << "Buku '" << judul << "' berhasil dikembalikan." << endl;
    } else {
        cout << "Buku dengan judul '" << judul << "' tidak ditemukan dalam daftar peminjaman." << endl;
    }
}

// Meminta input informasi buku
void inputInformasiBuku(Buku& buku, int indeks) {
    cout << "Masukkan informasi buku " << indeks + 1 << ":" << endl;
    cout << "Judul: ";
    cin.getline(buku.judul, MAX_PANJANG_JUDUL);
    cout << "Pengarang: ";
    cin.getline(buku.pengarang, MAX_PANJANG_PENGARANG);
    cout << "Tahun terbit: ";
    cin >> buku.tahun;
    cin.ignore(); // Membersihkan newline dari buffer
    cout << "Kategori buku: "; // Meminta kategori buku
    cin.getline(buku.kategori, 50);
    cout << "Harga buku (dalam rupiah): Rp";
    cin >> buku.harga;
    cout << "Denda per hari terlambat pengembalian (dalam rupiah): Rp";
    cin >> buku.dendaPerHari;
    cin.ignore(); // Membersihkan newline dari buffer
}

int main() {
    Buku buku[MAX_BUKU]; // Array untuk menyimpan informasi buku
    SimpulPinjam* daftarPinjam = nullptr;

    cout << "===============================================================================" << endl;
    cout << "|                         PROGRAM PEMINJAMAN BUKU                              |" << endl;
    cout << "===============================================================================" << endl;
    cout << "Catatan: Semua buku memiliki batas waktu peminjaman maksimal " << BATAS_WAKTU_PINJAM << " hari." << endl;

    int jumlahBuku;
    cout << "Masukkan jumlah buku: ";
    cin >> jumlahBuku;

   // Validasi jumlah buku
    if (jumlahBuku <= 0 || jumlahBuku > MAX_BUKU) {
        cout << "Jumlah buku tidak valid!" << endl;
        return 1; // Keluar dari program dengan kode error
    }

    cin.ignore(); // Membersihkan newline dari buffer

    // Lanjutkan dengan input informasi buku
    cout << "Masukkan informasi buku:" << endl;
    for (int i = 0; i < jumlahBuku; ++i) {
        inputInformasiBuku(buku[i], i);
        // Menambahkan informasi buku ke array dua dimensi bukuInfo
        strcpy(bukuInfo[i][0], buku[i].judul);
        strcpy(bukuInfo[i][1], buku[i].pengarang);
        sprintf(bukuInfo[i][2], "%d", buku[i].tahun);
        strcpy(bukuInfo[i][3], buku[i].kategori);
        sprintf(bukuInfo[i][4], "%.2f", buku[i].harga);
    }


    cout << endl << "Buku-buku di perpustakaan:" << endl;

    cout << "=================================================================================================" << endl;
    cout << "| No |     Judul     |    Pengarang    |    Tahun Terbit    |     Kategori      |     Harga     |" << endl;
    cout << "=================================================================================================" << endl;

    for (int i = 0; i < jumlahBuku; ++i) {
        cout << "| " << setw(2) << i + 1 << " | " << setw(14) << bukuInfo[i][0] << " | " << setw(15) << bukuInfo[i][1] << " | "
             << setw(18) << bukuInfo[i][2] << " | " << setw(17) << bukuInfo[i][3] << " | " << setw(13) << bukuInfo[i][4] << " |" << endl;
    }

    cout << "=================================================================================================" << endl;

    int pilihan;
    do {
        cout << "\nMenu:\n1. Pinjam buku\n2. Lihat daftar peminjaman\n3. Kembalikan buku\n4. Keluar\nMasukkan pilihan Anda: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan newline dari buffer
        switch (pilihan) {
            case 1: {
                int indeksBuku;
                cout << "Masukkan indeks buku yang ingin Anda pinjam (1-" << jumlahBuku << "): ";
                cin >> indeksBuku;
                if (indeksBuku >= 1 && indeksBuku <= jumlahBuku) {
                    pinjamBuku(daftarPinjam, buku[indeksBuku - 1]);
                    cout << "Buku berhasil dipinjam!" << endl;
                } else {
                    cout << "Indeks tidak valid!" << endl;
                }
                break;
            }
            case 2:
                cout << "\nDaftar buku yang dipinjam:" << endl;
                cetakDaftarPinjam(daftarPinjam);
                break;
            case 3: {
            char judul[MAX_PANJANG_JUDUL];
            cout << "Masukkan judul buku yang ingin Anda kembalikan: ";
            cin.getline(judul, MAX_PANJANG_JUDUL); // Menghapus cin.ignore() yang tidak perlu
            kembalikanBuku(daftarPinjam, judul);
            break;
            }
            case 4:
                cout << "Keluar dari program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan masukkan lagi." << endl;
        }
    } while (pilihan != 4);

    SimpulPinjam* sekarang = daftarPinjam;
    while (sekarang != nullptr) {
        SimpulPinjam* temp = sekarang;
        sekarang = sekarang->next;
        delete temp;
    }

    return 0;
}
