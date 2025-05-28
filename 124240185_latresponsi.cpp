#include <iostream>
#include <cstring>
using namespace std;

struct Spotify_KW
{
  string judul;
  string penyanyi;
  string album;
};

struct Node
{
  Spotify_KW data;
  Node *left;
  Node *right;

  Node(Spotify_KW data)
  {
    this->data = data;
    left = nullptr;
    right = nullptr;
  }
};

struct Queue
{
  string info;
  Queue *next;
};

Queue *depan, *belakang;

void buatqueue()
{
  depan = NULL;
  belakang = NULL;
}

int queuekosong()
{
  return (depan == NULL);
}

void tambah_lagu(Node *&root, Spotify_KW data)
{
  if (root == nullptr)
  {
    root = new Node(data);
    return;
  }
  Node *current = root;
  while (true)
  {
    if (data.judul < current->data.judul)
    {
      if (current->left == nullptr)
      {
        current->left = new Node(data);
        return;
      }
      current = current->left;
    }
    else
    {
      if (current->right == nullptr)
      {
        current->right = new Node(data);
        return;
      }
      current = current->right;
    }
  }
}

Spotify_KW *cari_lagu(Node *root, const string &judul)
{
  Node *current = root;
  while (current != nullptr)
  {
    if (judul == current->data.judul)
    {
      return &current->data;
    }
    else if (judul < current->data.judul)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return nullptr;
}

void daftar_lagu(Node *root)
{
  int nomor = 1;
  if (root == nullptr)
    return;
  daftar_lagu(root->left);
  cout << "Judul    : " << root->data.judul << endl;
  cout << "Penyanyi : " << root->data.penyanyi << endl;
  cout << "Album    : " << root->data.album << endl;
  cout << "-------------------------" << endl;
  daftar_lagu(root->right);
}

void tambah_antrian(string IB)
{
  Queue *NB = new Queue;
  NB->info = IB;
  NB->next = NULL;

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

void putar_lagu()
{
  if (queuekosong())
  {
    cout << "Tidak ada daftar lagu di antrian!" << endl;
  }
  else
  {
    cout << "Memutar lagu: " << depan->info << endl;
    Queue *hapus = depan;
    depan = depan->next;
    delete hapus;
  }
}

Node *minValueNode(Node *node)
{
  Node *current = node;
  while (current && current->left != nullptr)
    current = current->left;
  return current;
}

Node *hapus_lagu(Node *root, const string &judul)
{
  if (root == nullptr)
    return root;

  if (judul < root->data.judul)
  {
    root->left = hapus_lagu(root->left, judul);
  }
  else if (judul > root->data.judul)
  {
    root->right = hapus_lagu(root->right, judul);
  }
  else
  {
    if (root->left == nullptr)
    {
      Node *temp = root->right;
      delete root;
      return temp;
    }
    else if (root->right == nullptr)
    {
      Node *temp = root->left;
      delete root;
      return temp;
    }
    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    root->right = hapus_lagu(root->right, temp->data.judul);
  }
  return root;
}

int main()
{
  Node *root = nullptr;
  int pilihan;
  string judul, penyanyi, album;

  buatqueue();

  do
  {
    system("cls");
    cout << "===== SPOTIFY KW 1000 =====" << endl;
    cout << "[1] Tambah Data Lagu" << endl;
    cout << "[2] Pencarian Lagu" << endl;
    cout << "[3] Lihat Daftar Lagu" << endl;
    cout << "[4] Tambah Antrian Lagu" << endl;
    cout << "[5] Putar Lagu" << endl;
    cout << "[6] Hapus Lagu" << endl;
    cout << "[0] Keluar" << endl;
    cout << "===========================" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan)
    {
    case 1:
      system("cls");
      cout << "------ Tambah Data Lagu ------" << endl;
      cout << "Judul    : ";
      getline(cin, judul);
      cout << "Penyanyi : ";
      getline(cin, penyanyi);
      cout << "Album    : ";
      getline(cin, album);

      tambah_lagu(root, {judul, penyanyi, album});
      cout << "\nLagu berhasil ditambahkan!" << endl;
      system("pause");
      break;

    case 2:
    {
      system("cls");
      cout << "----- Pencarian Lagu -----" << endl;
      cout << "Judul lagu: ";
      getline(cin, judul);

      Spotify_KW *hasil = cari_lagu(root, judul);
      if (hasil != nullptr)
      {
        cout << "\nLagu ditemukan:" << endl;
        cout << "Judul    : " << hasil->judul << endl;
        cout << "Penyanyi : " << hasil->penyanyi << endl;
        cout << "Album    : " << hasil->album << endl;
        cout << "-------------------------" << endl;
      }
      else
      {
        cout << "\nLagu dengan judul \"" << judul << "\" tidak ditemukan" << endl;
      }
      system("pause");
      break;
    }

    case 3:
      system("cls");
      cout << "----- Daftar Lagu -----" << endl;
      if (root == nullptr)
      {
        cout << "\nBelum ada lagu yang tersimpan" << endl;
      }
      else
      {
        daftar_lagu(root);
      }
      system("pause");
      break;

    case 4:
    {
      system("cls");
      cout << "----- Tambah Antrian Lagu -----" << endl;
      cout << "Masukkan judul lagu: ";
      getline(cin, judul);

      Spotify_KW *lagu_antrian = cari_lagu(root, judul);
      if (lagu_antrian != nullptr)
      {
        tambah_antrian(judul);
        cout << "\nLagu berhasil ditambahkan ke antrian!" << endl;
      }
      else
      {
        cout << "\nLagu tidak ditemukan, tidak bisa ditambahkan ke antrian" << endl;
      }
      system("pause");
      break;
    }

    case 5:
      system("cls");
      cout << "------ Putar Lagu ------" << endl;
      putar_lagu();
      cout << "------------------------" << endl;
      system("pause");
      break;

    case 6:
      system("cls");
      cout << "----- Hapus Lagu -----" << endl;
      cout << "Judul lagu yang ingin dihapus: ";
      getline(cin, judul);
      root = hapus_lagu(root, judul);
      cout << "\nLagu berhasil dihapus" << endl;
      system("pause");
      break;

    case 0:
      cout << "Terima kasih telah menggunakan Spotify KW 1000 ^.^" << endl;
      break;

    default:
      cout << "Pilih menu yang tersedia..." << endl;
      system("pause");
      break;
    }

  } while (pilihan != 0);

  return 0;
}
