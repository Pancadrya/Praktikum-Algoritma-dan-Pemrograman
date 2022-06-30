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
char tembok = 254;
char jalan = 32;
char tambahanNyawa = 3;
char jebakan = 35;
char daerahMusuh = 120;
char air = 126;
char tandaMusuhTerkuat = 6;
char tandaMenang = 127;
char tandaHadiahAcak = 63;
char pohon = 30;
char tandaKarakter = 36;

char peta[lebarPeta][panjangPeta] = {
        {tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok},
        {tembok, tambahanNyawa, jalan, jalan, jebakan, jebakan, jalan, jalan, jalan, jalan, jebakan, jebakan, jalan, jalan, jalan, jalan, jebakan, jebakan, tandaMusuhTerkuat, tandaMenang},
        {tembok, jebakan, jebakan, jalan, jalan, jalan, jalan, jebakan, jebakan, jalan, jalan, jalan, jalan, jebakan, jebakan, jalan, jalan, jalan, jalan, tembok},
        {tembok, tembok, tembok, tembok, daerahMusuh, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok},
        {tembok, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, tembok},
        {tembok, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, air, tembok},
        {tembok, tembok, tembok, tembok, daerahMusuh, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, pohon, pohon, pohon, pohon, pohon, pohon, pohon},
        {tembok, tandaHadiahAcak, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, jalan, daerahMusuh, daerahMusuh, daerahMusuh, tambahanNyawa, pohon},
        {tembok, tembok, tembok, tembok, jalan, tembok, tembok, tembok, jalan, jalan, tembok, tembok, tembok, pohon, pohon, pohon, pohon, pohon, pohon, pohon},
        {tembok, tembok, tembok, tembok, jalan, tembok, tembok, tembok, jalan, jalan, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok},
        {tembok, jalan, jalan, jalan, jalan, tembok, tembok, tembok, jalan, jalan, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok},
        {tembok, jalan, pohon, pohon, pohon, pohon, pohon, pohon, daerahMusuh, daerahMusuh, jalan, air, air, air, air, air, air, air, air, tembok},
        {tembok, jalan, jalan, jalan, jalan, pohon, tambahanNyawa, pohon, daerahMusuh, daerahMusuh, pohon, air, air, air, air, air, air, air, air, tembok},
        {tembok, pohon, pohon, pohon, jalan, pohon, tandaHadiahAcak, jalan, daerahMusuh, daerahMusuh, pohon, air, air, air, air, air, air, air, air, tembok},
        {tembok, jalan, jalan, jalan, jalan, pohon, pohon, pohon, pohon, pohon, pohon, air, air, air, air, air, air, air, tandaHadiahAcak, tembok},
        {pohon, pohon, pohon, pohon, pohon, pohon, pohon, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok, tembok}
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
        cout << "1. Ruhi   | Kekuatan: 25 | Pertahanan: 10 (default)\n";
        cout << "2. Zira   | Kekuatan: 20 | Pertahanan: 15\n";
        cout << "3. Aksaka | Kekuatan: 15 | Pertahahan: 20\n";
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
        cout << "Berhasil menyerang, nyawa " << nama << " -" << kerusakan << "\n";
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
        cout << "Berhasil menyerang, nyawa " << nama << " -" << kerusakan << "\n";
    }
};

// Pendeklarasian variabel dengan "tipe data" karakter
karakter k;

struct musuh {
    string nama;
    string dialog;
    string foto;
    int muncul;
    int nyawa;
    int level;
    int kekuatan = 20;
    int pertahanan = 20;
    int kalah;
    int menang;

    void fotoPencuri() {
        system("cls");
        cout << "                                                  " << "\n";
        cout << "                                                  " << "\n";
        cout << "    !5PBB#&@@G:                                   " << "\n";
        cout << "    :&@@@@@@@@@?                                  " << "\n";
        cout << "   :P@@@@@@@@@@G                                  " << "\n";
        cout << "   ^?J@@@@@@@@@G                                  " << "\n";
        cout << "      ?#@@@@@&P:     ..:^!7JY5PGBB#####BBP5?~:  .." << "\n";
        cout << "       .~?J?7??JY?^.7P#@@@@@@@@@@@@@@@@@@@@@@#5~  " << "\n";
        cout << "           !B@@@@@@BY7?P@@@@@@@@@@@@@@@@@@@@@@@@Y." << "\n";
        cout << "      ~YPP5@@@@@@@@@@@P!^Y&@@@@@@@@@@@@JP@@@@@@@@Y   JANGAN GANGGU URUSANKU" << "\n";
        cout << "     ~@@@@@@@@@@@@@@@@@@P^:5@@@@@@@@@5!.^!G@@@@@@&   URUS SAJA URUSANMU SENDIRI" << "\n";
        cout << " ^?J?Y&@@@@@@@@@@@@@@@@@@&7 7&@@@@@@#  5BB&@@@@@@@" << "\n";
        cout << "  ^Y&@B?&@@@@@@@@@@@@@@@@@@? !@@@@@@@G?~^!G@@@@@@B" << "\n";
        cout << "     ?5 :?G#&@&G&@@@@@@@@@@@~ 5@@@@@&PB#J ~@@@@@@7" << "\n";
        cout << "           .::. ~&@@@@@@@@@@P ?@@@@@#?! ^J#@@@@@5 " << "\n";
        cout << "           .:^~~~G@@@@@@@@@@#.P@@@@@@@&YG@@@@@@Y  " << "\n";
        cout << "         :YB&@@@@@@@@@@@@@@@B.#@@@@@@@@@@@@@@&?   " << "\n";
        cout << "        :#@@@@@@@@@@@@@@@@@@&:?@@@@@@@@@@@@@P^    " << "\n";
        cout << "        7@@@@@&P555PPB#&@@@@@P !G&@@@@@@@BY^      " << "\n";
        cout << "        !@@@@@&:     ..~&@@@@@J  :!?JJ?!^.        " << "\n";
        cout << "        .G@@@@@G:       !@@@@@@Y.                 " << "\n";
        cout << "         :B@@@@@#7       !&@@@@@G^                " << "\n";
        cout << "          .5@@@@@@P.      ~B@@@@@&J:              " << "\n";
        cout << "            !#@@@@B:       .Y@@@@@@#?             " << "\n";
        cout << "              !??~.          ~P@@@@@B.            " << "\n";
        cout << "                               !P#B5^             " << "\n\n";
    }

    void fotoBegal() {
        system("cls");
        cout << "                                                  " << "\n";
        cout << "                                                  " << "\n";
        cout << "                  .::.                            " << "\n";
        cout << "                .75!~~~:.                  .      " << "\n";
        cout << "                !B#J~~!7~^:.            :75G57.   " << "\n";
        cout << "               :P#Y7~7GP7~!~.        .~JJPB&&&G^  " << "\n";
        cout << "              .J##G5!~!??7~~^      :7Y?: 7PB##G7  " << "\n";
        cout << "             .7PPYJY?7J7!Y5Y7^   ^J57. ~JPB#BP7^  " << "\n";
        cout << "             ~JPGG##GPGBBB#&BY!!J?~:^JG#&&&GJ~.   " << "\n";
        cout << "            ~P#######&######&#57~^7P#&&#GJ~.      " << "\n";
        cout << "      .:::.:!5##############P~^7YB&&#GY~.         JANGAN BERANI-BERANI MELAWAN KAMI" << "\n";
        cout << "    :~7!!!7!!~Y###########B#P?G#&&GJ~.            ATAU KAU AKAN TAHU SENDIRI AKIBATNYA" << "\n";
        cout << "   .!~!7JJJJ7Y~5&######&BG5#&&#GJ~.               " << "\n";
        cout << "   :!~~~!!75Y?!~5B#######B&#GY7!^                 " << "\n";
        cout << "   ~77~~~~75GP5!7!J###&#BPY??~7J7~                " << "\n";
        cout << "  .?G7~775P7^^77YG#&#B5??~77~~YY?P:               " << "\n";
        cout << "  .7??J?55^.:.~B&&BY7~^~5G?7~~PJ77!.              " << "\n";
        cout << "   :757GY:::^::?5!!~^!J~!J?!~YJ?7~!^              " << "\n";
        cout << "    .:~JYJ!^^~~^~~!~?GJ~~!?~?#!?7~~!.             " << "\n";
        cout << "      :!J#PY7!!~~!?7&&7~~77~P&777~~!^             " << "\n";
        cout << "      .^~!~~^^^^^^^^!!^::^^^7J?~~^^^^             " << "\n\n";
    }

    void fotoPembunuh() {
        system("cls");
        cout << "                                                    " << "\n";
        cout << "  .                   7G&@&#P?^                  .  " << "\n";
        cout << " 5BJ.               ~G@@@@B@@@&G!              .JB5 " << "\n";
        cout << " ^5GP!             ?@@@@@@B&@@@@@J            !PG5~ " << "\n";
        cout << "   7GGY^          ~@@@@@@@@@@@@@@@~         :YGG7   " << "\n";
        cout << "    :5BG?.        7@@@@@@@BPB&@@@@J       .?PGY:    " << "\n";
        cout << "      !GGP!       J@@@#####@&GB@@@5      ~PGP!      " << "\n";
        cout << "       .JGGY^    ~&&B##G5JY@@@#G@@G    :YGGJ.       " << "\n";
        cout << "         ~PGBJ:~.B&G&?: .::!P5G&G@@?^:?BG5^         " << "\n";
        cout << "           J&&#P5@P@@J. 7GP:.~#@&B@@B###?           " << "\n";
        cout << "           ~JY@B@#G@@@5.!??^^#@@@B&#B&J?~           " << "\n";
        cout << "         .^!JB@#GGB@@B##P#GG##&@@#GG&&P!^.          " << "\n";
        cout << "        J#@@&5G@#YP##BGG##&#G##&@P5@#JG@@&G^        KEMATIAN AKAN SELALU MEMBAYANGIMU" << "\n";
        cout << "      .#@@@@@YPBPG#G&@@@@GB@@@&BG#GGB5G@@@@@?       DIMANAPUN KAMU BERADA" << "\n";
        cout << "      7@&&&@YGG#@@@&BPG@@&@@&GP#&@@@BB5B@&&@B.      " << "\n";
        cout << "      7B##@GYBB@@&GBB#GBBB#BBB#BBB@@@G#J@&#BP.      " << "\n";
        cout << "     ^#&&&@P5G@@@&G&@@@&#PGB&@@##G@@@#GY&&&##5      " << "\n";
        cout << "     ^G&&&&@&J&#GG5G###&@@#&###&PPGB&BP@&###&J      " << "\n";
        cout << "     .G@@@@&55GYYGP&&@@@@@@&&BGB&BGG5G5G@@@@&?      " << "\n";
        cout << "     !@@@@B7GBB&G@##@@@@@@@&B#@@@B@#BP#YJ&@@@B      " << "\n";
        cout << "      B@&P!##P@@B#@B##&@@#5#@@#&B@&G@&5@57#&@7      " << "\n";
        cout << "     .#@&!##P@@@@BBBB##B?. !P#&BB#B@@@&P@JY@@J      " << "\n";
        cout << "     .P&YY&5@@&&#&@&B5!      ^YB&@@@@@@&P&~&B7      " << "\n";
        cout << "       Y7PYB#&&@&#57:          .~YB&@@@@BG!5^       " << "\n";
        cout << "       ^^!?7~!7!:                  :~7!!!J^!        " << "\n";
        cout << "       ^7~                                !!        " << "\n";
        cout << "       .?                                 :!        " << "\n\n";
    }

    void fotoPejabatKotor() {
        //system("cls");
        cout << "                                                             " << "\n";
        cout << "                             ^?J7                            " << "\n";
        cout << "                            .@@@@?                           " << "\n";
        cout << "                            .@@@@7                           " << "\n";
        cout << "                            .&@@@^                           " << "\n";
        cout << "                         :J#@B@&B&&J:                        " << "\n";
        cout << "                      ^P&&B@@&5?&@@&@&P!.                    " << "\n";
        cout << "                    J@@@@^^@@@?^@@@^!J:?BJ                   " << "\n";
        cout << "                   5@@@@@B!&@#:.?@&75.   &~                  " << "\n";
        cout << "                  .@@@@@@@.~B^.^.7~.@^   ~@:                 " << "\n";
        cout << "                  B@@@@@@@G.P^.:^^^5P:    &&                 JADI KAMU YANG INGIN MENGGANGGU BISNISKU" << "\n";
        cout << "                 5@@@@@@@@@@PPJ??5P.      !@5                LENYAPLAH KAU DARI MUKA BUMI" << "\n";
        cout << "               :B@@@@@@@@@BP##&@B~         J@G:              " << "\n";
        cout << "      .::::!  ?Y::~B@@@@@~   ?@@!         ...:Y7  !::::.     " << "\n";
        cout << "     ~:^..J:&@J!. .^@@@G      5@          :. .~Y@&:?.:^:^    " << "\n";
        cout << "     ~J~:!J5#!^~7!#@@@&       ^B         !@B!?~^!#YJ!:~J^    " << "\n";
        cout << " .:.. ^#&Y~:  :.^P#^^~7.      ~J.     .^~~~#P:.:  :~Y&B^ ..: " << "\n";
        cout << " .^:::~?.  ..::.7&^ ~.:.      .5      .^.~ !&!.::..  :?~:::^." << "\n";
        cout << "  .!!B&Y   ..     ..   .      .?      :   ..     ..   P&G!!. " << "\n";
        cout << "     .P@Y.         .::.        ^       .::.         .5@5.    " << "\n";
        cout << "       :P5?5J?!?PG#B.          :         .##GP7!?Y5?5P:      " << "\n";
        cout << "           .P@@@@J@!           .          ?@Y@@@@P.          " << "\n";
        cout << "             .~: !B                        #~ :~.            " << "\n";
        cout << "                 &:                        ^#                " << "\n\n";
    }

    void acakMusuh() {
        srand(time(0));
        int musuhPilihan = rand() % 3;
        // Begal
        if (musuhPilihan == 0) {
            this->nama = "Begal";
            this->kekuatan = 25;
            this->pertahanan = 15;
            this->dialog = "Serahkan seluruh harta bendamu, atau kau akan ku bunuh!\n";
            fotoBegal();
        }

        // Pembunuh
        else if (musuhPilihan == 1) {
            this->nama = "Pembunuh";
            this->kekuatan = 20;
            this->pertahanan = 20;
            this->dialog = "Kemana pun kau pergi, kau tak akan selamat!\n";
            fotoPembunuh();
        }

        // Pencuri
        else if (musuhPilihan == 2) {
            this->nama = "Pencuri";
            this->kekuatan = 15;
            this->pertahanan = 25;
            this->dialog = "Baiklah kawan, jika kau ingin bergulat, maju!\n";
            fotoPencuri();
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
        if (peta[k.posisiY][k.posisiX] == daerahMusuh) {
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
        else if (peta[k.posisiY][k.posisiX] == tandaMusuhTerkuat) {
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

    void coverPermainan() {
        cout << "                                                  " << "\n";
        cout << "                     .:^^^^^^:.                   " << "\n";
        cout << "                 .~77!^:.....:~7?!:               " << "\n";
        cout << "               .J?:              .!Y~             " << "\n";
        cout << "              ?Y:                  .?P.           " << "\n";
        cout << "             5?:.                   :~B.          " << "\n";
        cout << "            !P:~                     7~G          " << "\n";
        cout << "            J?~7                    .P.#          " << "\n";
        cout << "            .#7Y.      .^:.^:.      ~J5?          " << "\n";
        cout << "             PB.?5P5YJ!^.:^.^~JY5PPY:!@           " << "\n";
        cout << "             .&.5@@@@@@7G:.57&@@@@@@ B?           " << "\n";
        cout << "              PP!@@@@@@&7.Y^B@@@@@@B^&            " << "\n";
        cout << "              5J .::^^^..&@#.:^^:.: :#.           " << "\n";
        cout << "             .#.  :~~~. @@G@& ^~~^   P?           " << "\n";
        cout << "              .7YPB@~ ..G? YP:  &&P5?^            " << "\n";
        cout << "                !G @B          ~@~^B              " << "\n";
        cout << "                :B:@&?77!!!!!77G@J!Y              " << "\n";
        cout << "                ~P ~BG5JJ?JJ75PB?:^G              " << "\n";
        cout << "                :B:  .^777J?7!.  .YJ              " << "\n";
        cout << "                 .!?7~:       ~!?7:               " << "\n";
        cout << "                     ~G~....:5J.                  " << "\n";
        cout << "                       :^^:^^.                    " << "\n\n";
        cout << "            =============================        " << "\n";
        cout << "            |       KRIMINACITY         |        " << "\n";
        cout << "            =============================        " << "\n";
        _getch();
    }

    void tampilanAwal() {
        this->bersihLayar();
        cout << " ============================================================\n";
        cout << "|                           PROLOG                           |\n";
        cout << "|============================================================|\n";
        cout << "|               Kejahatan terjadi berkali-kali               |\n";
        cout << "|      Ekonomi hingga ambisi pribadi menjadi motivasi        |\n";
        cout << "|                 Meski tak dapat menghabisi                 |\n";
        cout << "|       Setidaknya sudah memerangi hingga mengurangi         |\n";
        cout << "|               Capai level setinggi-tingginya               |\n";
        cout << "|  Cari siasat terbaik serta lakukan dengan apik dan cerdik  |\n";
        cout << "|              Menangkan permainan dengan asik               |\n";
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
                    cout << tandaKarakter << " ";
                }
                else {
                    cout << peta[y][x] << " ";
                }
            }
            cout << "\n";
        }

        cout << "Karakter : " << k.nama << " (" << tandaKarakter << ")" << "\n";
        cout << "Nyawa    : " << k.nyawa;
        cout << "\nLevel    : " << k.level << "\n";
    }

    void controller() {
        // Aturan menggerakkan karakter ke atas
        if ((arrowKey == 'w' || arrowKey == 'W' || arrowKey == KEY_UP) && (peta[k.posisiY - 1][k.posisiX] != tembok && peta[k.posisiY - 1][k.posisiX] != pohon && k.posisiY >= 1)) {
            // Gerakkan karakter ke atas
            k.posisiY = k.posisiY - 1;
        }

        // Aturan menggerakkan karakter ke bawah
        if ((arrowKey == 's' || arrowKey == 'S' || arrowKey == KEY_DOWN) && (peta[k.posisiY + 1][k.posisiX] != tembok && peta[k.posisiY + 1][k.posisiX] != pohon && k.posisiY < lebarPeta - 1)) {
            // Gerakkan karakter ke atas
            k.posisiY = k.posisiY + 1;
        }

        // Aturan menggerakkan karakter ke kiri
        if ((arrowKey == 'a' || arrowKey == 'A' || arrowKey == KEY_LEFT) && (peta[k.posisiY][k.posisiX - 1] != tembok && peta[k.posisiY][k.posisiX - 1] != pohon && k.posisiX >= 0)) {
            // Gerakkan karakter ke atas
            k.posisiX = k.posisiX - 1;
        }

        // Aturan menggerakkan karakter ke kanan
        if ((arrowKey == 'd' || arrowKey == 'D' || arrowKey == KEY_RIGHT) && (peta[k.posisiY][k.posisiX + 1] != tembok && peta[k.posisiY][k.posisiX + 1] != pohon && k.posisiX < panjangPeta - 1)) {
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

                if (peta[y][x] == daerahMusuh) {
                    grafik::jumlahX++;
                }
            }
        }
    }

    void menghitungTambahanNyawa() {
        this->jumlahH = 0;
        for (int y = 0; y < lebarPeta; y++) {
            for (int x = 0; x < panjangPeta; x++) {

                if (peta[y][x] == tambahanNyawa) {
                    this->jumlahH++;
                }
            }
        }
    }

    void menangKalah() {
        // Menang
        if (peta[k.posisiY][k.posisiX] == tandaMenang) {
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
    "lambang kotak" adalah tembok (tidak bisa dilalui)
    " " adalah jalan (bisa dilalui)
    "~" adalah air (bisa dilalui)
    "lambang segitiga" adalah pohon (tidak bisa dilalui)
    "#" adalah jebakan (bisa dilalui, tetapi mengurangi 1 nyawa dan langsung kembali ke titik seperti saat permainan baru dimulai)
    "lambang hati" adalah tambahan nyawa
    "lambang rumah" adalah tempat untuk memenangkan permainan
    "x" adalah tempat kemungkinan munculnya musuh
    "?" adalah hadiah acak
    "lambang daun" adalah musuh terakhir (terkuat)
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
       Jika nyawa musuh <= 0, maka karakter dapat menuju tandaMenang untuk memenangkan permainan
    5. Untuk memenangkan permainan, pemain harus berhasil mencapai titik tandaMenang
    6. permainan akan berakhir jika nyawa pemain <= 0 atau pemain berhasil mencapai titik tandaMenangW atau pemain memekan tombol X/Esc
    */

    // Tampilan awal permainan
    g.coverPermainan();
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

        // Menghitung jumlah tambahan nyawa (tambahan nyawa)
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
    if (peta[k.posisiY][k.posisiX] == daerahMusuh) {
        m.muncul = rand() % 2;
        m.nyawa = 150;

        if (m.muncul == 1) {
        
            g.bersihLayar();

            // Mengacak musuh
            m.acakMusuh();

            // Mengacak level musuh
            m.acakLevel();

            tanding:
            cout << m.dialog;
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
                    if (peta[k.posisiY - 1][k.posisiX] != tembok && peta[k.posisiY - 1][k.posisiX] != pohon) {
                        k.posisiY = k.posisiY - 1;
                    }
                    else if (peta[k.posisiY + 1][k.posisiX] != tembok && peta[k.posisiY + 1][k.posisiX] != pohon) {
                        k.posisiY = k.posisiY + 1;
                    }
                    else if (peta[k.posisiY][k.posisiX - 1] != tembok && peta[k.posisiY][k.posisiX - 1] != pohon) {
                        k.posisiX = k.posisiX - 1;
                    }
                    else if (peta[k.posisiY][k.posisiX + 1] != tembok && peta[k.posisiY][k.posisiX + 1] != pohon) {
                        k.posisiX = k.posisiX + 1;
                    }
                    cout << "\n";
                }
                else {
                    g.bersihLayar();
                    cout << "Gagal kabur\n";
                    cout << "Nyawa " << k.nama << " -10\n";
                    k.nyawa -= 10;

                    if (k.nyawa <= 0) {
                        g.menangKalah();
                    }

                    goto tanding;
                }
            }
        }
    }

    // Aturan menambah nyawa
    if (peta[k.posisiY][k.posisiX] == tambahanNyawa) {
        k.nyawa += 50;
        peta[k.posisiY][k.posisiX] = jalan;
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan menang hadiah acak
    if (peta[k.posisiY][k.posisiX] == tandaHadiahAcak) {
        srand(time(0));
        g.hadiahAcak = rand() % 3;
        if (g.hadiahAcak == 0) {
            peta[k.posisiY][k.posisiX] = jalan;
        }
        else if (g.hadiahAcak == 1) {
            peta[k.posisiY][k.posisiX] = jalan;
            k.level++;
        }
        else if (g.hadiahAcak == 2) {
            peta[k.posisiY][k.posisiX] = jalan;
            k.nyawa += 100;
        }
        g.bersihLayar();
        g.renderGrafik();
    }

    // Aturan memunculkan 1 nyawa secara acak pada peta saat nyawa pemain <= 100 dan jumlah tamba nyawa = 0
    srand(time(0));
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahH == 0) {
        g.munculH = 1;
    }

    if (k.nyawa <= 100 && g.jumlahH == 0 && g.munculH == 1 && peta[g.acakY][g.acakX] == jalan && peta[g.acakY][g.acakX] != tandaKarakter) {
        peta[g.acakY][g.acakX] = tambahanNyawa;
        g.munculH = 0;
    }

    // Aturan memunculkan 1 musuh (x) secara acak pada peta saat x = 1
    srand(time(0));
    g.acakX = rand() % panjangPeta - 1;
    g.acakY = rand() % lebarPeta - 1;

    if (g.jumlahX <= 1) {
        g.munculX = 1;
    }

    if (g.jumlahX <= 1 && g.munculX > 0 && peta[g.acakY][g.acakX] == jalan) {
        peta[g.acakY][g.acakX] = daerahMusuh;
        g.munculX = 0;
    }

    // Aturan jika terkena jebakan
    if (peta[k.posisiY][k.posisiX] == jebakan) {
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
    if (peta[k.posisiY][k.posisiX] == tandaMusuhTerkuat) {
        m.nama = "Pejabat Kotor";
        m.dialog = "Hadapi kesengsaraan karena ulahmu ini!\n";

        // Mengacak level musuh terkuat
        m.acakLevel();
        m.nyawa = 250;

        g.bersihLayar();
        m.fotoPejabatKotor();

    tandingAkhir:
        cout << m.dialog;
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
                g.bersihLayar();
                cout << "Gagal kabur\n";
                cout << "Nyawa -10\n";
                k.nyawa -= 10;
                if (k.nyawa <= 0) {
                    g.menangKalah();
                }
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
                if (peta[k.posisiY][k.posisiX] == 33) {
                    k.nyawa = 10;
                }
                k.posisiX = 1;
                k.posisiY = 14;
                break;
            }
            else {
                cout << "Gagal kabur\n";
                cout << "Nyawa " << k.nama << " -10\n";
                k.nyawa -= 10;
                if (k.nyawa <= 0) {
                    goto ending;
                }
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
            ending:
            cout << "\nKamu kalah!\n";
            cout << "Tekan tombol apa saja untuk melanjutkan\n";
            m.menang++;
            _getch();
            g.bersihLayar();
            cout << " ============================================================ \n";
            cout << "|                           ENDING                           |\n";
            cout << "|============================================================|\n";
            cout << "|     Sayang sekali Anda gagal dalam kesempatan kali ini     |\n";
            cout << "|                      Jangan menyerah                       |\n";
            cout << "|             Tetap konsisten membela kebenaran              |\n";
            cout << "|       Semoga kebenaran menang di kesempatan lainnya        |\n";
            cout << "|------------------------------------------------------------|\n";
            cout << "|         Tekan tombol apa saja untuk melanjutkan            |\n";
            cout << " ============================================================ \n";
            g.menangKalah();
        }
        else if (m.nyawa <= 0) {
            cout << "\nKamu menang!\n";
            cout << "level " << k.nama << " +1\n";
            m.kalah++;
            k.level++;
            peta[k.posisiY][k.posisiX] = jalan;
            cout << "Tekan tombol apa saja untuk melanjutkan\n";
            if (m.nama == "Pejabat Kotor") {
                _getch();
                g.bersihLayar();
                cout << " ============================================================ \n";
                cout << "|                           ENDING                           |\n";
                cout << "|============================================================|\n";
                cout << "|         Anda telah berhasil menumpas satu kejahatan        |\n";
                cout << "|                       Jangan terlena                       |\n";
                cout << "|             Tetap konsisten membela kebenaran              |\n";
                cout << "|    Semoga dunia ini menjadi lebih damai, aman, dan baik    |\n";
                cout << "|          Pergilah ke tanda " << tandaMenang << " dan jadilah pemenang          |\n";
                cout << "|------------------------------------------------------------|\n";
                cout << "|         Tekan tombol apa saja untuk melanjutkan            |\n";
                cout << " ============================================================ \n";
            }
            break;
        }
    }
}
