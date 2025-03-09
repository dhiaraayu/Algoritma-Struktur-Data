#include <iostream>
#include <iomanip>
using namespace std;

struct Film
{
  string judul;
  string kode;
  float rating;
};

Film list_film[] = {
    {"Exhuma", "A112", 9.5},
    {"Wicked", "A113", 8.8},
    {"Inside Out 2", "A114", 9.2},
    {"Moana 2", "A115", 8.0},
    {"The Nun", "A116", 8.5}};

int jml_film = sizeof(list_film) / sizeof(list_film[0]);

void tampilkan_film()
{
  Film *ptr_film = list_film;
  cout << "\n====================================\n";
  cout << "Judul               Kode     Rating\n";
  cout << "====================================\n";
  for (int i = 0; i < jml_film; i++)
    cout << left << setw(20) << (ptr_film + i)->judul
         << setw(10) << (ptr_film + i)->kode
         << setw(10) << fixed << setprecision(1) << (ptr_film + i)->rating << endl;
  cout << "====================================\n";
}

void cari_kode()
{
  string kode;
  cout << "Masukkan Kode: ";
  cin.ignore();
  getline(cin, kode);

  bool found = false;
  int i = 0;

  while (i < jml_film && found == false)
  {
    if (list_film[i].kode == kode)
    {
      found = true;
      cout << "Judul: " << list_film[i].judul << ", Kode: " << list_film[i].kode << ", Rating: " << list_film[i].rating << endl;
    }
    else
      i++;
  }
  if (!found)
  {
    cout << "Film dengan kode " << kode << " tidak ditemukan\n";
  }
}

int cari_judul(string judul)
{
  int i = 0, j = jml_film - 1, k;
  bool found = false;
  while ((!found) && (i <= j))
  {
    k = (i + j) / 2;
    if (judul == list_film[k].judul)
    {
      found = true;
    }
    else
    {
      if (judul < list_film[k].judul)
        j = k - 1;
      else
        i = k + 1;
    }
  }
  if (found)
    cout << "Judul: " << list_film[k].judul << ", Kode: " << list_film[k].kode << ", Rating: " << list_film[k].rating << endl;
  else
  {
    cout << "Film dengan judul \"" << judul << "\" tidak ditemukan\n";
  }

  if (found)
    return k;
  else
    return -1;
}

void quick_sort(Film *ptr_film, int awal, int akhir)
{
  int low = awal, high = akhir;
  float pivot = ptr_film[(awal + akhir) / 2].rating;

  do
  {
    while (ptr_film[low].rating < pivot)
      low++;
    while (ptr_film[high].rating > pivot)
      high--;
    if (low <= high)
    {
      swap(ptr_film[low], ptr_film[high]);
      low++;
      high--;
    }
  } while (low <= high);

  if (awal < high)
    quick_sort(ptr_film, awal, high);
  if (low < akhir)
    quick_sort(ptr_film, low, akhir);
}

void bubble_sort()
{
  for (int i = 0; i < jml_film - 1; i++)
  {
    for (int j = 0; j < jml_film - 1 - i; j++)
    {
      if (list_film[j].rating < list_film[j + 1].rating)
      {
        swap(list_film[j], list_film[j + 1]);
      }
    }
  }
}

int main()
{
  system("cls");
  int pilihan;

  do
  {
    cout << "\n=== Menu ===\n";
    cout << "1. Tampilkan Data Film\n";
    cout << "2. Cari berdasarkan Kode\n";
    cout << "3. Cari berdasarkan Judul\n";
    cout << "4. Sort Rating Film (asc)\n";
    cout << "5. Sort Rating Film (desc)\n";
    cout << "6. Keluar\n";
    cout << "Pilihan menu: ";
    cin >> pilihan;

    switch (pilihan)
    {
    case 1:
      tampilkan_film();
      break;
    case 2:
    {
      cari_kode();
      break;
    }
    case 3:
    {
      string judul;
      cout << "Masukkan Judul: ";
      cin.ignore();
      getline(cin, judul);
      cari_judul(judul);
      break;
    }
    break;
    case 4:
      quick_sort(list_film, 0, jml_film - 1);
      tampilkan_film();
      break;
    case 5:
      bubble_sort();
      tampilkan_film();
      break;
    case 6:
      cout << "Keluar dari program" << endl;
      return 0;
    default:
      cout << "Pilihan tidak tersedia" << endl;
      break;
    }
  } while (pilihan != 6);

  return 0;
}