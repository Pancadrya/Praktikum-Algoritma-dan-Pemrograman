#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

// Mendefinisikan masukkan panah keyboard
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// Mendefinisikan ukuran peta
const int panjangPeta = 20; // x
const int lebarPeta = 16; // y

// Membuat variabel global
char arrowKey;
char pilihan;
int warna;
int kesempatanSuit;

string peta[lebarPeta][panjangPeta] = {
        {"=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","=","="},
        {"=","H"," "," ","#","#"," "," "," "," ","#","#"," "," "," "," ","#","#","#","="},
        {"=","#","#"," "," "," "," ","#","#"," "," "," "," ","#","#"," "," ","!"," ","W"},
        {"=","=","=","=","x","=","=","=","=","=","=","=","=","=","=","=","#","#","#","="},
        {"=","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","="},
        {"=","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","~","="},
        {"=","=","=","="," ","=","=","=","=","=","=","=","=","=","^","^","^","^","^","^"},
        {"=","?"," "," "," "," "," "," "," "," "," "," "," "," "," "," ","x","x","x","^"},
        {"=","=","=","="," ","=","=","="," "," ","=","=","=","=","^","^","^","^","^","^"},
        {"=","=","=","="," ","=","=","="," "," ","=","=","=","=","=","=","=","=","=","="},
        {"="," "," "," "," "," "," ","="," "," "," "," "," "," ","=","=","=","=","=","="},
        {"="," ","^","^","^","^"," ","=","x","x","^","^","^"," ","=","=","=","=","=","="},
        {"="," "," "," ","^","^"," ","=","x","x","^","^","^","~","~","~","~","~","~","="},
        {"=","=","="," ","x","x","x","?","x","x","^","^","^","~","~","~","~","~","?","="},
        {"="," "," "," ","^","^","H","^"," "," "," ","?","^","~","~","~","~","~","~","="},
        {"^","^","^","^","^","^","^","^","^","^","^","^","^","=","=","=","=","=","=","="},
};

struct karakter {
    string nama;
    int level;
    int nyawa;
    int kekuatan;
    int pertahanan;
    int posisiX;
    int posisiY;
    bool kabur;

    void pilihKarakter() {
        system("cls");
        cout << "---------------------------------------------------\n";
        cout << "                Daftar Karakter\n";
        cout << "---------------------------------------------------\n";
        cout << "1. Ruhi   -> Kekuatan: 25; Pertahanan: 10 (default)\n";
        cout << "2. Zira   -> Kekuatan: 20; Pertahanan: 15\n";
        cout << "3. Aksaka -> Kekuatan: 15; Pertahahan: 20\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Karakter: ";
        pilihan = _getche();

        // Ruhi
        if (pilihan == 49) {
            ruhi:
            this->nama = "Ruhi";
            this->kekuatan = 25;
            this->pertahanan = 10;
        }

        // Zira
        else if (pilihan == 50) {
            this->nama = "Zira";
            this->kekuatan = 20;
            this->pertahanan = 15;
        }

        // Aksaka
        else if (pilihan == 51) {
            this->nama = "Aksaka";
            this->kekuatan = 15;
            this->pertahanan = 20;
        }
        else {
            goto ruhi;
        }
    }

    void serang(string nama, int* nyawa, int* pertahanan, int* levelMusuh) {
        int kerusakan;
        int serangan;
        int pertahananMusuh;
        serangan = kekuatan + (5 * this->level);
        pertahananMusuh = *pertahanan + (5 * (*levelMusuh));
        kerusakan = serangan - pertahananMusuh;
        if (kerusakan <= 0) {
            kerusakan = 0;
        }
        *nyawa -= kerusakan;
        cout << "Behasil menyerang, nyawa " << nama << " -" << kerusakan << "\n";
    }

    void jurus(string nama, int* nyawa, int* pertahanan, int* levelMusuh) {
        int kerusakan;
        int serangan;
        int pertahananMusuh;
        serangan = kekuatan + (5 * this->level);
        pertahananMusuh = *pertahanan + (5 * (*levelMusuh));
        kerusakan = (2 * serangan) - pertahananMusuh;
        ;
        cout << "Mengeluarkan jurus sakti!\n";
        cout << "Nyawa " << this->nama << " -10\n";
        cout << "Kekuatan serangan++\n\n";
        if (kerusakan <= 0) {
            kerusakan = 0;
        }
        this->nyawa -= 10;
        *nyawa -= kerusakan;
        cout << "Behasil menyerang, nyawa " << nama << " -" << kerusakan << "\n";
    }
};

// Pendeklarasian variabel dengan "tipe data" karakter
karakter k;

struct musuh {
    string nama;
    int muncul;
    int nyawa;
    int level;
    int kekuatan = 20;
    int pertahanan = 20;
    int kalah;
    int menang;
    int suit;
    int poinSuit;

    void acakMusuh() {
        srand(time(0));
        int musuhPilihan = rand() % 3;
        // Begal
        if (musuhPilihan == 0) {
            this->nama = "Begal";
            this->kekuatan = 25;
            this->pertahanan = 15;
        }

        // Pembunuh
        else if (musuhPilihan == 1) {
            this->nama = "Pembunuh";
            this->kekuatan = 20;
            this->pertahanan = 20;
        }

        // Jambret
        else if (musuhPilihan == 2) {
            this->nama = "Jambret";
            this->kekuatan = 15;
            this->pertahanan = 25;
        }
    }

    void serangKarakter(string nama, int* nyawa, int* pertahanan) {
        int kerusakan;
        kerusakan = (kekuatan + (5 * this->level)) - (*pertahanan + (2 * k.level));
        if (kerusakan <= 0) {
            kerusakan = 0;
        }
        *nyawa -= kerusakan;
        cout << this->nama << " menyerang balik, nyawa " << nama << " -" << kerusakan << "\n";
    }

    void acakLevel() {
        srand(time(0));
        if (peta[k.posisiY][k.posisiX] == "x") {
            if (k.level < 6) {
                this->level = rand() % 4;  // Level musuh antara 0 - 4
            }
            else if (k.level < 11) {
                this->level = 8 + (rand() % 3);    // Level musuh antara 8 - 10
            }
            else if (k.level < 21) {
                this->level = 15 + (rand() % 6);   // Level musuh antara 15 - 20
            }
            else if (k.level < 31) {
                this->level = 25 + (rand() % 6);   // level musuh antara 25 - 30
            }
            else if (k.level < 41) {
                this->level = 35 + (rand() % 6);   // level musuh antara 35 - 40
            }
        }
        else if (peta[k.posisiY][k.posisiX] == "!") {
            this->level = 45 + (rand() % 6);   // Level musuh terkuat antara 45 - 50
        }
    }
};

// Pendeklarasian variabel dengan "tipe data" musuh
musuh m;

struct grafik {
    int hadiahAcak;
    int acakX;
    int acakY;
    int jumlahH;
    int jumlahX;
    int munculH;
    int munculX;

    // Membersihkan layar dari kode yang telah dijalankan sebelumnya
    void bersihLayar() {
        system("cls");
    }

    void tampilanAwal() {
        cout << " ============================================================\n";
        cout << "|                     Permainan Tiles 2D                     |\n";
        cout << "|============================================================|\n";
        cout << "|               Capai level setinggi-tingginya               |\n";
        cout << "| Cari siasat untuk mengalahkan musuh dan tingkatkan levelmu |\n";
        cout << "|------------------------------------------------------------|\n";
        cout << "|         Tekan tombol apa saja untuk melanjutkan            |\n";
        cout << " ============================================================\n";
        _getch();

    }

    //Memilih warna tema permainan (khusus saat dijalankan pada aplikasi sode editor laptop/komputer)
    void pilihWarnaTema() {
        this->bersihLayar();
        cout << "--------------------------------------------\n";
        cout << "             Daftar Warna Tema\n";
        cout << "--------------------------------------------\n";
        cout << "1. Teks Putih  |  Background Hitam (default)\n";
        cout << "2. Teks Biru   |  Background Hitam\n";
        cout << "3. Teks Merah  |  Background Hitam\n";
        cout << "4. Teks Hijau  |  Background Hitam\n";
        cout << "5. Teks Kuning |  Background Hitam\n";
        cout << "6. Teks Hitam  |  Background Putih\n";
        cout << "--------------------------------------------\n";
        cout << "Pilih warna tema: ";
        warna = _getche();

        if (warna == 50) {
            system("color 03");
        }
        else if (warna == 51) {
            system("color 0C");
        }
        else if (warna == 52) {
            system("color 0A");
        }
        else if (warna == 53) {
            system("color 06");
        }
        else if (warna == 54) {
            system("color 70");
        }
    }

    void renderGrafik() {
        // Penjelasan controller
        cout << "-------------------------------------------------\n";
        cout << "                    Controller\n";
        cout << "-------------------------------------------------\n";
        cout << "W atau Panah Atas  : karakter geser ke atas\n";
        cout << "S atau Panah Bawah : karakter geser ke bawah\n";
        cout << "A atau Panah Kiri  : karakter geser ke kiri\n";
        cout << "D atau Panah Kanan : karakter geser ke kanan\n";
        cout << "X atau Esc         : untuk keluar dari permainan\n";
        cout << "------------------------------------------------\n\n";

        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (k.posisiX == x && k.posisiY == y) {
                    cout << "$" << " ";
                }
                else {
                    cout << peta[y][x] << " ";
                }
            }
            cout << "\n";
        }

        cout << "Karakter : " << k.nama << " ($)" << "\n";
        cout << "Nyawa    : " << k.nyawa;
        cout << "\nLevel    : " << k.level << "\n";
    }

    void controller() {
        // Aturan menggerakkan karakter ke atas
        if ((arrowKey == 'w' || arrowKey == 'W' || arrowKey == KEY_UP) && (peta[k.posisiY - 1][k.posisiX] != "=" && peta[k.posisiY - 1][k.posisiX] != "^" && k.posisiY >= 1)) {
            // Gerakkan karakter ke atas
            k.posisiY = k.posisiY - 1;
        }

        // Aturan menggerakkan karakter ke bawah
        if ((arrowKey == 's' || arrowKey == 'S' || arrowKey == KEY_DOWN) && (peta[k.posisiY + 1][k.posisiX] != "=" && peta[k.posisiY + 1][k.posisiX] != "^" && k.posisiY < lebarPeta - 1)) {
            // Gerakkan karakter ke atas
            k.posisiY = k.posisiY + 1;
        }

        // Aturan menggerakkan karakter ke kiri
        if ((arrowKey == 'a' || arrowKey == 'A' || arrowKey == KEY_LEFT) && (peta[k.posisiY][k.posisiX - 1] != "=" && peta[k.posisiY][k.posisiX - 1] != "^" && k.posisiX >= 0)) {
            // Gerakkan karakter ke atas
            k.posisiX = k.posisiX - 1;
        }

        // Aturan menggerakkan karakter ke kanan
        if ((arrowKey == 'd' || arrowKey == 'D' || arrowKey == KEY_RIGHT) && (peta[k.posisiY][k.posisiX + 1] != "=" && peta[k.posisiY][k.posisiX + 1] != "^" && k.posisiX < panjangPeta - 1)) {
            // Gerakkan karakter ke atas
            k.posisiX = k.posisiX + 1;
        }

        if (arrowKey == 'x' || arrowKey == 'X' || arrowKey == KEY_ESC) {
            exit(0);
        }
    }

    void menghitungMusuh() {
        grafik::jumlahX = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "x") {
                    grafik::jumlahX++;
                }
            }
        }
    }

    void menghitungTambahanNyawa() {
        this->jumlahH = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == "H") {
                    this->jumlahH++;
                }
            }
        }
    }

    void menangKalah() {
        // Menang
        if (peta[k.posisiY][k.posisiX] == "W") {
            _getch();
            grafik::bersihLayar();
            cout << "-------------------------------------------------------------------------\n";
            cout << "                           PERMAINAN SELESAI                             \n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "Mengalahkan musuh\t: " << m.kalah << " kali" << "\n";
            cout << "Dikalahkan musuh\t: " << m.menang << " kali" << "\n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "               Selamat, Anda menang dalam permainan kali ini!                 \n";
            cout << "-------------------------------------------------------------------------\n";
            _getch();
            exit(0);
        }

        // permainan over atau kalah
        if (k.nyawa <= 0) {
            _getch();
            grafik::bersihLayar();
            cout << "-------------------------------------------------------------------------\n";
            cout << "                           PERMAINAN SELESAI                             \n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "Mengalahkan musuh\t: " << m.kalah << " kali" << "\n";
            cout << "Dikalahkan musuh\t: " << m.menang << " kali" << "\n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "                   Anda kalah dalam permainan kali ini!                      \n";
            cout << "-------------------------------------------------------------------------\n";
            _getch();
            exit(0);
        }
    }
};

// Pendeklarasian variabel dengan "tipe data" grafik
grafik g;

void aturanMain();
void tarung();

int main() {
    // Elemen Peta permainan
    /*
    "=" adalah tembok (tidak bisa dilalui)
    " " adalah jalan (bisa dilalui)
    "~" adalah air (bisa dilalui)
    "^" adalah pohon (tidak bisa dilalui)
    "#" adalah jebakan (bisa dilalui, tetapi mengurangi 1 nyawa dan langsung kembali ke titik seperti saat permainan baru dimulai)
    "H" adalah tambahan nyawa
    "W" adalah tempat untuk memenangkan permainan
    "x" adalah tempat kemungkinan munculnya musuh
    "?" adalah hadiah acak
    "!" adalah musuh terakhir (terkuat)
    */

    // Aturan permainan
    /*
    1. Saat pemain bertemu musuh, pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan keluar dari jangkauan musuh
       Jika gagal, nyawa pemain akan berkurang 10 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Pemain diberikan 3 pilihan, menyerang dengan serangan biasa, menyerang dengan jurus sakti, atau mencoba kabur
           Jika memilih serangan biasa, maka nyawa musuh akan berkurang berdasarkan daya hancur yang diterima (serangan karakter - pertahanan musuh)
           Jika memilih jurus sakti, maka kekuatan serangan akan bertambah sehingga daya rusak musuh  lebih tinggi dibandingkan dengan serangan biasa
               Konsekuensi dari menggunakan jurus sakti ini adalah nyawa pemain akan berkurang 10 setiap menggunakannya
           Memilih mencoba kabur:
               Jika berhasil, maka pemain akan kembali ke titik awal permainan
               Jika gagal, nyawa pemain akan berkurang 10 dan pemain akan diarahkan untuk memilih menyerang dengan serangan biasa, menyerang dengan jurus sakti, atau mencoba kabur kembali
       Jika nyawa pemain <= 0, maka permainan akan selesai dan pemain dinyatakan kalah
       Jika nyawa musuh <= 0, maka level karakter akan bertambah 1 dan daerah kemungkinan munculnya musuh yang tadi dilawan akan menghilang
    2. Naikkan level dengan mengalahkan musuh (x) atau dapatkan dari hadiah acak (?)
    3. Hadiah acak bisa menambah nyawa pwmain, level pemain, ataupun tidak berpengaruh apa-apa
    4. Saat pemain bertemu musuh terkuat (pejabat kotor), pemain bisa memilih lawan atau kabur
       Memilih kabur:
       Jika berhasil, maka pemain akan kembali ke titik awal permainan dan nyawa pemain tersisa 10
       Jika gagal, nyawa pemain akan berkurang 10 dan pemain akan diarahkan untuk memilih kabur atau lawan kembali
       Memilih lawan:
       Pemain diberikan 3 pilihan, menyerang dengan serangan biasa, menyerang dengan jurus sakti, atau mencoba kabur
           Jika memilih serangan biasa, maka nyawa musuh akan berkurang berdasarkan daya hancur yang diterima (serangan karakter - pertahanan musuh)
           Jika memilih jurus sakti, maka kekuatan serangan akan bertambah sehingga daya rusak musuh  lebih tinggi dibandingkan dengan serangan biasa
               Konsekuensi dari menggunakan jurus sakti ini adalah nyawa pemain akan berkurang 10 setiap menggunakannya
           Memilih mencoba kabur:
               Jika berhasil, maka pemain akan kembali ke titik awal permainan dan nyawa pemain tersisa 10
               Jika gagal, nyawa pemain akan berkurang 10 dan pemain akan diarahkan untuk memilih menyerang dengan serangan biasa, menyerang dengan jurus sakti, atau mencoba kabur kembali
       Jika nyawa pemain <= 0, maka permainan akan selesai dan pemain dinyatakan kalah
       Jika nyawa musuh <= 0, maka karakter dapat menuju titik W untuk memenangkan permainan
    5. Untuk memenangkan permainan, pemain harus berhasil mencapai titik W
    6. permainan akan berakhir jika nyawa pemain <= 0 atau pemain berhasil mencapai titik W atau pemain memekan tombol X/Esc
    */

    // Tampilan awal permainan
    g.tampilanAwal();

    // Memilih Karakter
    k.pilihKarakter();

    // Memmilih tema warna permaainan
    g.pilihWarnaTema();

    // Pengaturan awal karakter
    k.level = 1;
    k.nyawa = 200;
    k.posisiY = 14;
    k.posisiX = 1;

    // Loop permainan
    while (k.nyawa > 0) {
    mulai:
        // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        g.bersihLayar();

        // Menghitung jumlah musuh (x)
        g.menghitungMusuh();

        // Menghitung jumlah tambahan nyawa (H)
        g.menghitungTambahanNyawa();

        // Render grafik
        g.renderGrafik();

        // Aturan main
        aturanMain();

        // Input Keyboard
        arrowKey = _getch();

        // Controller
        g.controller();

        // Hasil akhir permainan
        g.menangKalah();

    }

    return 0;
}

void aturanMain() {
    // Aturan munculnya musuh
    if (peta[k.posisiY][k.posisiX] == "x") {
        m.muncul = rand() % 2;
        m.nyawa = 150;

        if (m.muncul == 1) {
            // Mengacak musuh
            m.acakMusuh();

            // Mengacak level musuh
            m.acakLevel();

            g.bersihLayar();
        tanding:
            cout << m.nama << " menghadang, lawan (f) atau kabur (r)? ";
            pilihan = _getche();

            if (pilihan == 'f' || pilihan == 'F') {
                // Bertarung untuk menentukan pemenang
                tarung();
            }
            else {
                srand(time(0));
                k.kabur = rand() % 2;
                if (k.kabur == true) {
                    g.bersihLayar();
                    cout << "Berhasil kabur\n";
                    cout << "Tekan tombol apa saja untuk melanjutkan\n";
                    if (peta[k.posisiY - 1][k.posisiX] != "=" && peta[k.posisiY - 1][k.posisiX] != "^") {
                        k.posisiY = k.posisiY - 1;
                    }
                    else if (peta[k.posisiY + 1][k.posisiX] != "=" && peta[k.posisiY + 1][k.posisiX] != "^") {
                        k.posisiY = k.posisiY + 1;
                    }
                    else if (peta[k.posisiY][k.posisiX - 1] != "=" && peta[k.posisiY][k.posisiX - 1] != "^") {
                        k.posisiX = k.posisiX - 1;
                    }
                    else if (peta[k.posisiY][k.posisiX + 1] != "=" && peta[k.posisiY][k.posisiX + 1] != "^") {
                        k.posisiX = k.posisiX + 1;
                    }
                    cout << "\n";
                }
                else {
                    cout << "\nGagal kabur\n";
                    cout << "Nyawa " << k.nama << " - 10\n";
                    k.nyawa -= 10;

                    if (k.nyawa == 0) {
                        g.menangKalah();
                    }

                    goto tanding;
                }
            }
        }
    }

    // Aturan menambah nyawa
    if (peta[k.posisiY][k.posisiX] == "H") {
        k.nyawa += 50;
        peta[k.posisiY][k.posisiX] = " ";
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan menang hadiah acak
    if (peta[k.posisiY][k.posisiX] == "?") {
        srand(time(0));
        g.hadiahAcak = rand() % 3;
        if (g.hadiahAcak == 0) {
            peta[k.posisiY][k.posisiX] = " ";
        }
        else if (g.hadiahAcak == 1) {
            peta[k.posisiY][k.posisiX] = " ";
            k.level++;
        }
        else if (g.hadiahAcak == 2) {
            peta[k.posisiY][k.posisiX] = " ";
            k.nyawa += 100;
        }
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan memunculkan 1 nyawa (H) secara acak pada peta saat nyawa pemain = 1 dan jumlah H = 0
    srand(time(0));
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahH == 0) {
        g.munculH = 1;
    }

    if (k.nyawa <= 100 && g.jumlahH == 0 && g.munculH == 1 && peta[g.acakY][g.acakX] == " " && peta[g.acakY][g.acakX] != "$") {
        peta[g.acakY][g.acakX] = "H";
        g.munculH = 0;
    }

    // Aturan memunculkan 1 musuh (x) secara acak pada peta saat x = 1
    srand(time(0));
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahX <= 1) {
        g.munculX = 1;
    }

    if (g.jumlahX <= 1 && g.munculX > 0 && peta[g.acakY][g.acakX] == " ") {
        peta[g.acakY][g.acakX] = "x";
        g.munculX = 0;
    }

    // Aturan jika terkena jebakan
    if (peta[k.posisiY][k.posisiX] == "#") {
        k.nyawa -= 10;
        k.posisiX = 1;
        k.posisiY = 14;
        g.bersihLayar();
        cout << k.nama << " terkena jebakan, nyawa " << k.nama << " -10\n";
        cout << "Tekan tombol apa saja untuk melanjutkan\n";
        if (k.nyawa <= 0) {
            g.menangKalah();
        }
        _getch();
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan melawan musuh terakhir/terkuat
    if (peta[k.posisiY][k.posisiX] == "!") {
        m.nama = "Pejabat Kotor";
        // Mengacak level musuh terkuat
        m.acakLevel();
        m.nyawa = 250;

        g.bersihLayar();
    tandingAkhir:
        cout << m.nama << " menghadang, lawan (f) atau kabur (r)? ";
        pilihan = _getche();
        if (pilihan == 'f' || pilihan == 'F') {
            tarung();
        }
        else {
            srand(time(0));
            k.kabur = rand() % 2;
            if (k.kabur == true) {
                g.bersihLayar();
                cout << "Berhasil kabur\n";
                cout << "Tekan tombol apa saja untuk melanjutkan\n";
                if (k.nyawa > 1) {
                    k.nyawa = 10;
                }
                else {
                    k.nyawa = 0;
                }
                k.posisiX = 1;
                k.posisiY = 14;
            }
            else {
                cout << "\nGagal kabur\n";
                cout << "Nyawa -10\n";
                k.nyawa -= 10;
                goto tandingAkhir;
            }
        }

        // Pernyataan menang atau kalah
        g.menangKalah();
    }
}

void tarung() {
    int pilihan;
    int serangTidak;
    bool awal = true;

    g.bersihLayar();

    while (true) {
    pertarungan:
        srand(time(0));
        serangTidak = rand() % 2;
        if (awal != true)
            cout << "\n";
        awal = false;
        cout << "Nyawa " << k.nama << " : " << k.nyawa << "\n";
        cout << "Level " << k.nama << " : " << k.level << "\n";
        cout << "Nyawa " << m.nama << " : " << m.nyawa << "\n";
        cout << "Level " << m.nama << " : " << m.level << "\n\n";
        cout << "Pilihan Tindakan\n";
        cout << "1. Serang dengan serangan biasa\n";
        cout << "2. Serang dengan jurus Sakti\n";
        cout << "3. Mencoba kabur\n";
        cout << "Pilih: ";
        pilihan = _getche();

        if (pilihan == 49 && m.nyawa > 0) {
            g.bersihLayar();
            k.serang(m.nama, &m.nyawa, &m.pertahanan, &m.level);
        }
        else if (pilihan == 50 && m.nyawa > 0) {
            g.bersihLayar();
            k.jurus(m.nama, &m.nyawa, &m.pertahanan, &m.level);
        }
        else if (pilihan == 51) {
            g.bersihLayar();
            srand(time(0));
            k.kabur = rand() % 2;
            if (k.kabur == 1) {
                g.bersihLayar();
                cout << "Berhasil kabur\n";
                cout << "Tekan tombol apa saja untuk melanjutkan\n";
                if (peta[k.posisiY][k.posisiX] == "!") {
                    k.nyawa = 10;
                }
                k.posisiX = 1;
                k.posisiY = 14;
                break;
            }
            else {
                cout << "Gagal kabur\n";
                cout << "Nyawa " << k.nama << " - 10\n";
                k.nyawa -= 10;
                goto pertarungan;
            }
        }
        else {
            g.bersihLayar();
            cout << "Invalid input\n";
            goto pertarungan;
        }

        if (serangTidak == 1) {
            m.serangKarakter(k.nama, &k.nyawa, &k.pertahanan);
        }

        if (k.nyawa <= 0) {
            cout << "\nKamu kalah!\n";
            cout << "Tekan tombol apa saja untuk melanjutkan\n";
            m.menang++;
            g.menangKalah();
        }
        else if (m.nyawa <= 0) {
            cout << "\nKamu menang!\n";
            cout << "level " << k.nama << " +1\n";
            m.kalah++;
            k.level++;
            peta[k.posisiY][k.posisiX] = " ";
            cout << "Tekan tombol apa saja untuk melanjutkan\n";
            break;
        }
    }
}
