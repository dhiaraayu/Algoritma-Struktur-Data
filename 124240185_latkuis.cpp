#include <iostream>
using namespace std;

struct Pegawai
{
  int id;
  char nama[50];
  int gaji;
};

int baca_file(Pegawai data_pegawai[]);
void tambah_data(Pegawai data_pegawai[], int &jumlah);
void tampilkan_data(Pegawai data_pegawai[], int &jumlah);
void bubble_sort(Pegawai data_pegawai[], int jumlah);
void cari_data(Pegawai data_pegawai[], int jumlah, int cari);
void update_gaji(Pegawai data_pegawai[], int jumlah, int cari);

int main()
{
  Pegawai data_pegawai[1000];
  int menu;
  int jumlah = baca_file(data_pegawai);
  int cari;
  do
  {
    cout << "\n=== SI Kepegawaian  ===\n";
    cout << "[1] Tambah data pegawai\n";
    cout << "[2] Lihat data pegawai\n";
    cout << "[3] Cari data pegawai\n";
    cout << "[4] Perbarui gaji\n";
    cout << "[0] Keluar\n";
    cout << "Pilih menu: ";
    cin >> menu;

    switch (menu)
    {
    case 1:
      system("cls");
      cout << "=== Tambah Data Pegawai ===\n";
      cout << "Masukkan jumlah data: ";
      cin >> jumlah;
      for (int i = 0; i < jumlah; i++)
      {
        tambah_data(data_pegawai, jumlah);
      }
      break;
    case 2:
      system("cls");
      tampilkan_data(data_pegawai, jumlah);
      break;
    case 3:
      system("cls");
      cari_data(data_pegawai, jumlah, cari);
      break;
    case 4:
      system("cls");
      update_gaji(data_pegawai, jumlah, cari);
      break;
    case 0:
      cout << "Keluar dari program" << endl;
    default:
      cout << "Pilih menu yang tersedia.." << endl;
      break;
    }
  } while (menu != 0);
}

void bubble_sort(Pegawai data_pegawai[], int jumlah)
{
  for (int i = 0; i < jumlah; i++)
  {
    for (int j = 0; j < jumlah - 1 - i; j++)
    {
      if (data_pegawai[j].id > data_pegawai[j + 1].id)
      {
        swap(data_pegawai[j], data_pegawai[j + 1]);
      }
    }
  }
}

int baca_file(Pegawai data_pegawai[])
{
  FILE *file = fopen("pegawai.dat", "rb");
  if (!file)
  {
    cout << "File tidak ditemukan!" << endl;
    return 0;
  }

  int count = 0;
  while (fread(&data_pegawai[count], sizeof(Pegawai), 1, file))
  {
    count++;
  }

  fclose(file);
  return count;
}

void tambah_data(Pegawai data_pegawai[], int &jumlah)
{
  FILE *file = fopen("pegawai.dat", "ab");
  if (!file)
  {
    cout << "Gagal membuka file!" << endl;
    return;
  }

  int tambah;
  cout << "=== Tambah Data Pegawai ===\n";
  cout << "Masukkan jumlah data: ";
  cin >> tambah;
  for (int i = 0; i < jumlah; i++)
  {
    cout << "Masukkan ID: ";
    cin >> data_pegawai[jumlah].id;
    cout << "Masukkan nama: ";
    cin >> data_pegawai[jumlah].nama;
    cout << "Masukkan gaji: ";
    cin >> data_pegawai[jumlah].gaji;

    fwrite(&data_pegawai[jumlah], sizeof(Pegawai), 1, file);
  }

  fclose(file);
  cout << "Data berhasil ditambahkan!" << endl;
}

void tampilkan_data(Pegawai data_pegawai[], int &jumlah)
{
  FILE *file = fopen("pegawai.dat", "rb");
  if (!file)
  {
    cout << "Gagal membuka file!" << endl;
    return;
  }

  jumlah = 0;
  while (fread(&data_pegawai[jumlah], sizeof(Pegawai), 1, file))
  {
    jumlah++;
  }
  fclose(file);

  bubble_sort(data_pegawai, jumlah);

  cout << "\n=== Daftar Pegawai ===\n";
  for (int i = 0; i < jumlah; i++)
  {
    cout << "\nID Pegawai: " << data_pegawai[i].id << endl;
    cout << "Nama: " << data_pegawai[i].nama << endl;
    cout << "Gaji: " << data_pegawai[i].gaji << endl;
  }
}

void cari_data(Pegawai data_pegawai[], int jumlah, int cari)
{
  FILE *file = fopen("pegawai.dat", "rb");
  if (!file)
  {
    cout << "Gagal membuka file!" << endl;
    return;
  }

  cout << "Masukkan ID pegawai yang dicari: ";
  cin >> cari;

  int i = 0;
  bool found = false;
  while (fread(&data_pegawai[jumlah], sizeof(Pegawai), 1, file))
  {
    if (data_pegawai[i].id == cari)
    {
      cout << "\nData pegawai ditemukan:\n";
      cout << "ID Pegawai: " << data_pegawai[i].id << endl;
      cout << "Nama: " << data_pegawai[i].nama << endl;
      cout << "Gaji: " << data_pegawai[i].gaji << endl;
      found = true;
      break;
    }
  }

  fclose(file);

  if (!found)
  {
    cout << "Pegawai dengan ID " << cari << " tidak ditemukan" << endl;
  }
}

void update_gaji(Pegawai data_pegawai[], int jumlah, int cari)
{
  FILE *file = fopen("pegawai.dat", "rb+");
  if (!file)
  {
    cout << "Gagal membuka file!" << endl;
    return;
  }

  cout << "Masukkan ID pegawai: ";
  cin >> cari;

  int i = 0;
  int gaji_baru;
  bool found = false;
  while (fread(&data_pegawai[jumlah], sizeof(Pegawai), 1, file) && i < jumlah)
  {
    if (data_pegawai[i].id == cari)
    {
      cout << "ID Pegawai: " << data_Pegawai[i].id << endl;
      cout << "Nama Pegawai: " << data_pegawai[i].nama << endl;
      cout << "Gaji Pegawai: " << data_pegawai[i].gaji << endl;
      cout << "Masukkan gaji baru: ";
      cin >> gaji_baru;
      data_pegawai[i].gaji = gaji_baru;
      found = true;
      break;
    }
    i++;
  }
  fclose(file);

  if (found)
  {
    file = fopen("pegawai.dat", "wb");
    for (int i = 0; i < jumlah; i++)
    {
      fwrite(&data_pegawai[i], sizeof(Pegawai), 1, file);
    }
    fclose(file);
    cout << "Gaji pegawai berhasil diupdate!" << endl;
  }
  else
  {
    cout << "Data tidak ditemukan!" << endl;
  }
}
