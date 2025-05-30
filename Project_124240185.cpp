#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

string username = "admin";
string password = "123456";

struct Buku
{
  int id;
  char judul[50];
  int harga;
  int stok;
  Buku *kanan;
  Buku *kiri;
};

struct Transaksi
{
  int id_buku;
  char judul[50];
  int harga;
  int jumlah;
  int total;
};

struct Buku *buatNode(int id, const char *judul, int harga, int stok)
{
  Buku *NB = new Buku;
  NB->id = id;
  strcpy(NB->judul, judul);
  NB->harga = harga;
  NB->stok = stok;
  NB->kanan = nullptr;
  NB->kiri = nullptr;
  return NB;
};

bool login()
{
  string user, pass;
  while (true)
  {
    system("cls");
    cout << "===== Login Pegawai =====" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == username && pass == password)
    {
      cout << "\nLogin berhasil!" << endl;
      system("pause");
      return true;
    }
    else
    {
      cout << "\nLogin gagal! Silakan coba lagi" << endl;
      system("pause");
    }
  }
}

void tambah_buku(Buku *&head, int id, const char *judul, int harga, int stok)
{
  Buku *NB = buatNode(id, judul, harga, stok);
  if (head == nullptr)
  {
    head = NB;
    return;
  }
  Buku *bantu = head;
  while (bantu->kanan != nullptr)
  {
    bantu = bantu->kanan;
  }
  bantu->kanan = NB;
  NB->kiri = bantu;
  cout << "\nBuku berhasil ditambahkan!" << endl;
}

void bubble_sort_ID(Buku *head)
{
  if (head == nullptr)
    return;

  bool swap;
  Buku *bantu;
  Buku *last = nullptr;

  do
  {
    swap = false;
    bantu = head;

    while (bantu->kanan != last)
    {
      if (bantu->id > bantu->kanan->id)
      {

        int bantu_id = bantu->id;
        char bantu_judul[50];
        strcpy(bantu_judul, bantu->judul);
        int bantu_harga = bantu->harga;
        int bantu_stok = bantu->stok;

        bantu->id = bantu->kanan->id;
        strcpy(bantu->judul, bantu->kanan->judul);
        bantu->harga = bantu->kanan->harga;
        bantu->stok = bantu->kanan->stok;

        bantu->kanan->id = bantu_id;
        strcpy(bantu->kanan->judul, bantu_judul);
        bantu->kanan->harga = bantu_harga;
        bantu->kanan->stok = bantu_stok;

        swap = true;
      }
      bantu = bantu->kanan;
    }
    last = bantu;
  } while (swap);
}

void tampilkan_buku(Buku *head)
{
  if (head == nullptr)
  {
    cout << "Daftar buku kosong" << endl;
    return;
  }

  cout << left
       << setw(8) << "ID"
       << setw(30) << "Judul"
       << setw(10) << "Harga"
       << setw(8) << "Stok" << endl;
  cout << setfill('-') << setw(56) << "-" << setfill(' ') << endl;

  Buku *bantu = head;
  while (bantu)
  {
    cout << left
         << setw(8) << bantu->id
         << setw(30) << bantu->judul
         << setw(10) << bantu->harga
         << setw(8) << bantu->stok << endl;
    bantu = bantu->kanan;
  }
}

Buku *cari_buku(Buku *head, int id_cari)
{
  Buku *bantu = head;
  while (bantu != nullptr)
  {
    if (bantu->id == id_cari)
    {
      return bantu;
    }
    bantu = bantu->kanan;
  }
  return nullptr;
}

void baca_buku_dari_file(Buku *&head)
{
  FILE *file = fopen("buku.dat", "rb");
  if (file == nullptr)
  {
    cout << "File tidak ditemukan, mulai dengan data kosong" << endl;
    return;
  }

  while (head != nullptr)
  {
    Buku *hapus = head;
    head = head->kanan;
    delete hapus;
  }

  int id, harga, stok;
  char judul[50];
  while (true)
  {
    if (fread(&id, sizeof(int), 1, file) != 1)
      break;
    if (fread(judul, sizeof(char), 50, file) != 50)
      break;
    if (fread(&harga, sizeof(int), 1, file) != 1)
      break;
    if (fread(&stok, sizeof(int), 1, file) != 1)
      break;

    Buku *NB = buatNode(id, judul, harga, stok);
    if (head == nullptr)
    {
      head = NB;
    }
    else
    {
      Buku *bantu = head;
      while (bantu->kanan != nullptr)
        bantu = bantu->kanan;
      bantu->kanan = NB;
      NB->kiri = bantu;
    }
  }
  fclose(file);
}

void simpan_buku_ke_file(Buku *head)
{
  FILE *file = fopen("buku.dat", "wb");
  if (file == nullptr)
  {
    cout << "Gagal membuka file untuk menyimpan data!" << endl;
    return;
  }

  Buku *bantu = head;
  while (bantu != nullptr)
  {
    fwrite(&bantu->id, sizeof(int), 1, file);
    fwrite(bantu->judul, sizeof(char), 50, file);
    fwrite(&bantu->harga, sizeof(int), 1, file);
    fwrite(&bantu->stok, sizeof(int), 1, file);
    bantu = bantu->kanan;
  }
  fclose(file);
}

void hapus_buku(Buku *&head, int id)
{
  Buku *hapus = cari_buku(head, id);
  if (hapus == nullptr)
  {
    cout << "Buku dengan ID " << id << " tidak ditemukan" << endl;
    return;
  }

  if (hapus->kiri)
    hapus->kiri->kanan = hapus->kanan;
  else
    head = hapus->kanan;

  if (hapus->kanan)
    hapus->kanan->kiri = hapus->kiri;

  delete hapus;
  cout << "\nBuku berhasil dihapus" << endl;
}

void update_buku(Buku *head, int id_cari)
{
  Buku *buku = cari_buku(head, id_cari);
  if (buku == nullptr)
  {
    cout << "Buku dengan ID " << id_cari << " tidak ditemukan" << endl;
    return;
  }
  cout << "\nBuku ditemukan:" << endl;
  cout << "Kode   : " << buku->id << endl;
  cout << "Judul  : " << buku->judul << endl;
  cout << "Harga  : " << buku->harga << endl;
  cout << "Stok   : " << buku->stok << endl;

  int pilihan_update;
  cout << "\nPilih yang ingin diupdate:\n";
  cout << "[1] Harga\n[2] Stok\n[3] Harga dan Stok\n[4] Hapus Buku\nPilih: ";
  cin >> pilihan_update;

  switch (pilihan_update)
  {
  case 1:
    cout << "Masukkan harga baru: ";
    cin >> buku->harga;
    cout << "\nHarga berhasil diupdate" << endl;
    break;
  case 2:
    cout << "Masukkan stok baru: ";
    cin >> buku->stok;
    cout << "\nStok berhasil diupdate" << endl;
    break;
  case 3:
    cout << "Masukkan harga baru: ";
    cin >> buku->harga;
    cout << "Masukkan stok baru: ";
    cin >> buku->stok;
    cout << "\nHarga dan stok berhasil diupdate" << endl;
    break;
  case 4:
    hapus_buku(head, id_cari);
    break;
  default:
    cout << "Pilihan tidak valid" << endl;
    break;
  }
}

void transaksi_pembelian(Buku *head)
{
  int id_beli, jumlah;
  cout << "ID buku yang ingin dibeli: ";
  cin >> id_beli;

  Buku *buku = cari_buku(head, id_beli);
  if (buku == nullptr)
  {
    cout << "\nBuku tidak ditemukan" << endl;
    return;
  }

  cout << "\nJudul  : " << buku->judul << endl;
  cout << "Harga  : " << buku->harga << endl;
  cout << "Stok   : " << buku->stok << endl;

  cout << "\nJumlah yang ingin dibeli: ";
  cin >> jumlah;

  if (jumlah > buku->stok)
  {
    cout << "\nStok tidak mencukupi!" << endl;
  }
  else
  {
    int total = jumlah * buku->harga;
    buku->stok -= jumlah;
    cout << "Transaksi berhasil!\n";
    cout << "Total harga: Rp " << total << endl;

    Transaksi trx;
    trx.id_buku = buku->id;
    strcpy(trx.judul, buku->judul);
    trx.harga = buku->harga;
    trx.jumlah = jumlah;
    trx.total = total;

    FILE *file = fopen("transaksi.dat", "ab");
    if (file != nullptr)
    {
      fwrite(&trx, sizeof(Transaksi), 1, file);
      fclose(file);
    }
    else
    {
      cout << "Gagal menyimpan transaksi ke file!" << endl;
    }

    simpan_buku_ke_file(head);
  }
}

void tampilkan_transaksi()
{
  FILE *file = fopen("transaksi.dat", "rb");
  if (file == nullptr)
  {
    cout << "Belum ada transaksi tersimpan" << endl;
    return;
  }

  cout << left
       << setw(8) << "ID"
       << setw(30) << "Judul"
       << setw(10) << "Harga"
       << setw(8) << "Jumlah"
       << setw(12) << "Total" << endl;
  cout << setfill('-') << setw(68) << "-" << setfill(' ') << endl;

  Transaksi trx;
  while (fread(&trx, sizeof(Transaksi), 1, file) == 1)
  {
    cout << left
         << setw(8) << trx.id_buku
         << setw(30) << trx.judul
         << setw(10) << trx.harga
         << setw(8) << trx.jumlah
         << setw(12) << trx.total << endl;
  }

  fclose(file);
}

int main()
{
  if (!login())
  {
    return 0;
  }

  Buku *head = nullptr;
  baca_buku_dari_file(head);
  int id, harga, stok;
  char judul[50];
  int pilihan;
  do
  {
    system("cls");
    cout << "======== BOOK STORE ========" << endl;
    cout << "[1] Tambahkan Buku" << endl;
    cout << "[2] Tampilkan Data Buku" << endl;
    cout << "[3] Cari Buku" << endl;
    cout << "[4] Update Buku" << endl;
    cout << "[5] Transaksi Pembelian" << endl;
    cout << "[6] Lihat Riwayat Transaksi" << endl;
    cout << "[0] Keluar" << endl;
    cout << "============================" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
      system("cls");
      cout << "======= Tambah Buku =======" << endl;
      cout << "ID Buku    : ";
      cin >> id;
      cin.ignore();
      cout << "Judul Buku : ";
      cin.getline(judul, 50);
      cout << "Harga Buku : ";
      cin >> harga;
      cout << "Stok Buku  : ";
      cin >> stok;
      tambah_buku(head, id, judul, harga, stok);
      simpan_buku_ke_file(head);
      system("pause");
      break;
    case 2:
      system("cls");
      bubble_sort_ID(head);
      tampilkan_buku(head);
      system("pause");
      break;
    case 3:
      system("cls");
      cout << "======= Cari Buku =======" << endl;
      cout << "ID buku yang dicari: ";
      cin >> id;
      {
        Buku *hasil = cari_buku(head, id);
        if (hasil != nullptr)
        {
          cout << "\nBuku ditemukan:" << endl;
          cout << "Kode   : " << hasil->id << endl;
          cout << "Judul  : " << hasil->judul << endl;
          cout << "Harga  : " << hasil->harga << endl;
          cout << "Stok   : " << hasil->stok << endl;
        }
        else
        {
          cout << "\nBuku dengan ID " << id << " tidak ditemukan." << endl;
        }
      }
      system("pause");
      break;
    case 4:
      system("cls");
      cout << "======== Update Buku ========" << endl;
      cout << "ID buku yang ingin diupdate: ";
      cin >> id;
      update_buku(head, id);
      simpan_buku_ke_file(head);
      system("pause");
      break;
    case 5:
      system("cls");
      cout << "====== Transaksi Pembelian ======" << endl;
      transaksi_pembelian(head);
      system("pause");
      break;
    case 6:
      system("cls");
      tampilkan_transaksi();
      system("pause");
      break;
    case 0:
      cout << "Terima kasih" << endl;
      return 0;
    default:
      cout << "Pilihan tidak valid" << endl;
      system("pause");
      break;
    }
  } while (pilihan != 0);
  simpan_buku_ke_file(head);
  return 0;
}
