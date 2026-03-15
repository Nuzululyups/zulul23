#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct barang {
    string kode; 
    string nama;
    int harga;
    int stok;
};

string formatrupiah(int angka) {
    string s = to_string(angka);
    int n = s.length();

    for (int i = n - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }

    return s;
}

int main() {
    barang brg[100] = {
        {"BR01", "Beras 3 kg", 15000, 10},
          {"MG02", "Minyak goreng 1 liter", 20000, 10},
        {"TL03", "Telur 1/4", 5000, 15},
        {"TR04", "Terigu 1/5 kg", 8000, 20},
        {"AC05", "Aci 1/5 kg", 8000, 20},
        {"BM06", "Beras merah 3 kg", 20000, 5},
        {"GJ07", "Gula jawa 1/5 kg", 10000, 10},
        {"DK08", "Dedek 1 kg", 5000, 30},
        {"BW09", "Bawang 1/5 kg", 10000, 15},
        {"BB10", "Brambang 1/5 kg", 10000, 15}
    };

    int jumlahBarang = 10; 
    int total = 0;
    string pil; 

    do {
        cout << "=========================================================\n";
        cout << "                     DAFTAR BARANG                      \n";
        cout << "=========================================================\n";
        cout << left << setw(8) << "Kode" << setw(25) << "Nama Barang" 
             << right << setw(12) << "Harga" << setw(10) << "Stok" << endl;
        cout << "---------------------------------------------------------\n";

        for (int i = 0; i < jumlahBarang; i++) {
            cout << left << setw(8) << brg[i].kode
                 << setw(25) << brg[i].nama
                 << right << setw(12) << formatrupiah(brg[i].harga) 
                 << setw(10) << brg[i].stok << endl;
        }

        cout << "---------------------------------------------------------\n";
        cout << "99  ADMIN (Tambah Barang/Stok)\n";
        cout << "0   SELESAI & BAYAR\n";
        cout << "=========================================================\n";
        cout << "Total Belanja Sementara: Rp. " << formatrupiah(total) << endl;

        cout << "\nMasukkan kode barang : ";
        cin >> pil;

        if (pil == "99") {
            int subPil;
            cout << "\n--- MENU ADMIN ---\n";
            cout << "[1] Tambah Jenis Barang Baru\n";
            cout << "[2] Tambah Stok Barang Lama\n";
            cout << "Pilih: "; cin >> subPil;

            if (subPil == 1) {
                cin.ignore(1000, '\n');
                cout << "Kode barang baru: "; cin >> brg[jumlahBarang].kode;
                cin.ignore(1000, '\n');
                cout << "Nama barang baru: "; getline(cin, brg[jumlahBarang].nama);
                cout << "Harga: "; cin >> brg[jumlahBarang].harga;
                cout << "Stok awal: "; cin >> brg[jumlahBarang].stok;
                jumlahBarang++;
                cout << "Barang berhasil ditambahkan!\n";
            } 
            else if (subPil == 2) {
                string cariKode;
                int tmbh, indeks = -1;
                cout << "Masukkan kode barang yang akan ditambah stoknya: "; cin >> cariKode;
                
                for (int i = 0; i < jumlahBarang; i++) {
                    if (brg[i].kode == cariKode) { indeks = i; break; }
                }

                if (indeks != -1) {
                    cout << "Jumlah stok tambahan: "; cin >> tmbh;
                    brg[indeks].stok += tmbh;
                    cout << "Stok berhasil diupdate!\n";
                } else {
                    cout << "Kode barang tidak ditemukan!\n";
                }
            }
            system("pause");

        } else if (pil != "0") {
            int indeks = -1;
            for (int i = 0; i < jumlahBarang; i++) {
                if (brg[i].kode == pil) {
                    indeks = i;
                    break;
                }
            }

            if (indeks != -1) {
                int jml;
                cout << "Jumlah pembelian " << brg[indeks].nama << " : ";
                cin >> jml;

                if (jml > brg[indeks].stok) {
                    cout << "\n[!] GAGAL: Stok tidak mencukupi! (Sisa: " << brg[indeks].stok << ")\n";
                } else if (jml <= 0) {
                    cout << "[!] Jumlah tidak valid!\n";
                } else {
                    brg[indeks].stok -= jml; 
                    total += (brg[indeks].harga * jml);
                    cout << "Berhasil ditambahkan ke keranjang.\n";
                }
            } else {
                cout << "[!] Kode barang salah atau tidak ditemukan!\n";
            }
            system("pause");
        }
    } while (pil != "0");

    if (total > 0) {
        cout << "=====================================================\n";
        cout << "Total Belanja : Rp. " << formatrupiah(total) << endl;
        
        int persenDiskon;
        cout << "Masukkan diskon (%) : "; cin >> persenDiskon;

        int diskon = total * persenDiskon / 100;
        int totalSetelahDiskon = total - diskon;

        cout << "Diskon (" << persenDiskon << "%) : Rp. " << formatrupiah(diskon) << endl;
        cout << "Total Bayar : Rp. " << formatrupiah(totalSetelahDiskon) << endl;
        cout << "-----------------------------------------------------\n";

        int Bayar;
        do {
            cout << "Bayar : Rp. "; cin >> Bayar;
            if (Bayar < totalSetelahDiskon) {
                cout << "Uang kurang! Harusnya minimal Rp. " << formatrupiah(totalSetelahDiskon) << "\n";
            }
        } while (Bayar < totalSetelahDiskon);

        cout << "Kembalian : Rp. " << formatrupiah(Bayar - totalSetelahDiskon) << endl;
        cout << "=====================================================\n";
    }

    cout << "Terima kasih sudah berbelanja!\n";
    system("pause");
    return 0;
}
