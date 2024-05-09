#include "bukumanager.h"

BukuManager::BukuManager(QObject *parent) : QObject(parent), head(nullptr) {
    tambahBeberapaBuku();
}

// Destruktor untuk kelas BukuManager
BukuManager::~BukuManager()
{
    Buku* current = head;
    while (current) {
        Buku* next = current->next;
        delete current;
        current = next;
    }
}

// Metode untuk menambahkan beberapa buku ke dalam manajer buku
void BukuManager::tambahBeberapaBuku() {
    tambahBuku("Harry Potter", "J.K. Rowling", "1997", "100000");
    tambahBuku("To Kill a Mockingbird", "Harper Lee", "1960", "95000");
    tambahBuku("The Great Gatsby", "F. Scott Fitzgerald", "1925", "90000");
    tambahBuku("1984", "George Orwell", "1949", "85000");
    tambahBuku("The Catcher in the Rye", "J.D. Salinger", "1951", "80000");
}

// Metode untuk menambahkan buku baru ke dalam manajer buku
void BukuManager::tambahBuku(const QString& judul, const QString& pengarang, const QString& tahunTerbit, const QString& harga)
{
    // Membuat node buku baru
    Buku* newBuku = new Buku;
    newBuku->judul = judul;
    newBuku->pengarang = pengarang;
    newBuku->tahunTerbit = tahunTerbit;
    newBuku->harga = harga;
    newBuku->next = nullptr;

    // Menambahkan buku baru ke dalam daftar buku
    if (!head) {
        head = newBuku;
    } else {
        Buku* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newBuku;
    }
}

// Metode untuk menampilkan data buku dalam tabel
void BukuManager::tampilkanDataBuku(QTableWidget* tableWidget)
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    Buku* current = head;
    int row = 0;
    while (current) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(current->judul));
        tableWidget->setItem(row, 1, new QTableWidgetItem(current->pengarang));
        tableWidget->setItem(row, 2, new QTableWidgetItem(current->tahunTerbit));
        tableWidget->setItem(row, 3, new QTableWidgetItem(current->harga));
        current = current->next;
        ++row;
    }
}

// Metode untuk menampilkan data buku dalam konsol
void BukuManager::tampilkanDataBuku()
{
    Buku* current = head;
    while (current) {
        qDebug() << "Judul:" << current->judul << ", Pengarang:" << current->pengarang << ", Tahun Terbit:" << current->tahunTerbit << ", Harga:" << current->harga;
        current = current->next;
    }
}

// Metode untuk memperbarui informasi buku
void BukuManager::perbaruiBuku(const QString& judulLama, const QString& judulBaru, const QString& pengarangBaru, const QString& tahunTerbitBaru, const QString& hargaBaru)
{
    Buku* current = head;
    while (current) {
        if (current->judul == judulLama) {
            current->judul = judulBaru;
            current->pengarang = pengarangBaru;
            current->tahunTerbit = tahunTerbitBaru;
            current->harga = hargaBaru;
            break;
        }
        current = current->next;
    }
}

// Metode untuk menghapus buku dari daftar berdasarkan judul
void BukuManager::hapusBuku(const QString& judul)
{
    if (!head) {
        qDebug() << "Tidak ada buku dalam daftar.";
        return;
    }

    if (head->judul == judul) {
        Buku* temp = head;
        head = head->next;
        delete temp;
        qDebug() << "Buku dengan judul" << judul << "telah dihapus.";
        return;
    }

    Buku* current = head;
    while (current->next) {
        if (current->next->judul == judul) {
            Buku* temp = current->next;
            current->next = current->next->next;
            delete temp;
            qDebug() << "Buku dengan judul" << judul << "telah dihapus.";
            return;
        }
        current = current->next;
    }

    qDebug() << "Buku dengan judul" << judul << "tidak ditemukan dalam daftar.";
}

// Metode untuk menampilkan data buku dalam tabel untuk pengguna
void BukuManager::tampilkanDataBukuUser(QTableWidget* tableWidget)
{
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    Buku* current = head;
    int row = 0;
    while (current) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(current->judul));
        tableWidget->setItem(row, 1, new QTableWidgetItem(current->harga));
        current = current->next;
        ++row;
    }
}

// Metode untuk melakukan pencarian buku berdasarkan kata kunci untuk pengguna
void BukuManager::pencarianBukuUser(const QString& kataKunci, QTableWidget* tableWidget)
{
    // Iterasi melalui semua baris dan kolom dalam tabel
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            // Mendapatkan item di setiap sel
            QTableWidgetItem* item = tableWidget->item(row, col);
            // Memeriksa apakah item mengandung kata kunci (tidak case sensitive)
            if (item && item->text().contains(kataKunci, Qt::CaseInsensitive)) {
                tableWidget->setRowHidden(row, false);
                break;
            } else {
                tableWidget->setRowHidden(row, true);
            }
        }
    }
}
