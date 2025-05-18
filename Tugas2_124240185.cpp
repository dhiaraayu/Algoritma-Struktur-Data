#include <iostream>
using namespace std;

struct Pesanan
{
  string info; // menyimpan variabel nama
  string jenis_roti;
  int total_harga;
  Pesanan *next;
};

struct Stackpesanan
{
  string info;
  string jenis_roti;
  int total_harga;
  Stackpesanan *next;
};

Pesanan *depan, *belakang = NULL;
Stackpesanan *top = NULL;

bool queuekosong()
{
  return (depan == NULL);
}

void enqueue() // fungsi untuk menambahkan pesanan ke antrean
{
  Pesanan *NB = new Pesanan();
  NB->next = NULL;

  cout << "------ Ambil Antrean ------" << endl;
  cout << "Nama        : ";
  cin.ignore();
  getline(cin, NB->info);
  cout << "Jenis Roti  : ";
  getline(cin, NB->jenis_roti);
  cout << "Total Harga : Rp ";
  cin >> NB->total_harga;

  if (depan == NULL)
  {
    depan = NB;
  }
  else
  {
    belakang->next = NB;
  }
  belakang = NB;
}

void push_riwayat(Pesanan *data) // fungsi untuk menyimpan ke riwayat menggunakan stack
{
  Stackpesanan *NS = new Stackpesanan();
  NS->info = data->info;
  NS->jenis_roti = data->jenis_roti;
  NS->total_harga = data->total_harga;
  NS->next = top;
  top = NS;
}

void dequeue() // fungsi untuk melayani pembeli
{
  if (queuekosong())
  {
    cout << "Antrean masih kosong!" << endl;
  }
  else
  {
    Pesanan *hapus = depan;

    cout << "------ Melayani Pesanan ------" << endl;
    cout << "Nama        : " << hapus->info << endl;
    cout << "Jenis Roti  : " << hapus->jenis_roti << endl;
    cout << "Total Harga : Rp " << hapus->total_harga << endl;
    cout << "------------------------------" << endl;

    push_riwayat(hapus);

    depan = depan->next;
    delete hapus;
    cout << "Pesanan berhasil dilayani dan dicatat ke riwayat" << endl;
  }
}

void cetakqueue() // fungsi untuk menampilkan pesanan
{
  Pesanan *bantu = depan;
  int nomor = 1;
  if (bantu == NULL)
  {
    cout << "Antrean masih kosong!" << endl;
    return;
  }
  cout << "----- Daftar Pesanan -----" << endl;
  while (bantu != NULL)
  {
    cout << nomor++ << ". Nama        : " << bantu->info << endl;
    cout << "   Jenis Roti  : " << bantu->jenis_roti << endl;
    cout << "   Total Harga : Rp " << bantu->total_harga << endl;
    cout << "--------------------------" << endl;
    bantu = bantu->next;
  }
  cout << endl;
}

void batalkanpesanan() // fungsi untuk membatalkan pesanan
{
  if (queuekosong())
  {
    cout << "Antrean masih kosong!" << endl;
    return;
  }
  if (depan == belakang)
  {
    cout << "Pesanan atas nama " << belakang->info << " berhasil dibatalkan" << endl;
    delete depan;
    depan = NULL;
    belakang = NULL;
    return;
  }

  Pesanan *bantu = depan;
  while (bantu->next != belakang)
  {
    bantu = bantu->next;
  }
  cout << "Pesanan atas nama " << belakang->info << " berhasil dibatalkan" << endl;
  delete belakang;
  belakang = bantu;
  belakang->next = NULL;
}

void cetakriwayat() // fungsi untuk menampilkan riwayat yg sudah disimpan menggunakan stack
{
  if (top == NULL)
  {
    cout << "History kosong!" << endl;
    return;
  }
  Stackpesanan *bantu = top;
  int nomor = 1;
  cout << "------ History Pesanan ------" << endl;
  while (bantu != NULL)
  {
    cout << nomor++ << ". Nama        : " << bantu->info << endl;
    cout << "   Jenis Roti  : " << bantu->jenis_roti << endl;
    cout << "   Total Harga : Rp " << bantu->total_harga << endl;
    cout << "-----------------------------" << endl;
    bantu = bantu->next;
  }
  cout << endl;
}

int main()
{
  int pilihan;
  char ulang_menu;
  do
  {
    system("cls");
    cout << "===== TOKO ROTI MANIS LEZAT =====\n";
    cout << "[1] Ambil Antrean\n";
    cout << "[2] Layani Pembeli\n";
    cout << "[3] Tampilkan Pesanan\n";
    cout << "[4] Batalkan Pesanan\n";
    cout << "[5] Tampilkan History Pesanan\n";
    cout << "[0] Keluar\n";
    cout << "Pilih Menu: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
      system("cls");
      enqueue();
      break;
    case 2:
      system("cls");
      dequeue();
      break;
    case 3:
      system("cls");
      cetakqueue();
      break;
    case 4:
      system("cls");
      batalkanpesanan();
      break;
    case 5:
      system("cls");
      cetakriwayat();
      break;
    case 0:
      cout << "Have a Good Day! ^_^" << endl;
      return 0;
    default:
      cout << "Pilih menu yang ada..." << endl;
      break;
    }
    cout << "\nKembali ke menu utama? (y/n): ";
    cin >> ulang_menu;
  } while (ulang_menu == 'y' || ulang_menu == 'Y');
  cout << "Terima kasih ^.^" << endl;
  return 0;
}
