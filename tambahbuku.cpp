#include "tambahbuku.h"
#include "ui_tambahbuku.h"
#include "QMessageBox"
#include "QDialogButtonBox"

// Konstruktor untuk kelas tambahbuku
tambahbuku::tambahbuku(BukuManager *bukuManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tambahbuku),
    bukuManager(bukuManager)
{
    // Menginisialisasi UI
    ui->setupUi(this);
}

// Destruktor untuk kelas tambahbuku
tambahbuku::~tambahbuku()
{
    delete ui;
    // Mengirim sinyal bahwa dialog telah ditutup
    emit dialogClosed();
}

// Metode untuk menambahkan buku baru
void tambahbuku::tambahBuku() {
    // Memeriksa apakah semua kolom diisi
    if (ui->tf_judul->text().isEmpty() || ui->tf_pengarang->text().isEmpty() || ui->tf_tahun->text().isEmpty() || ui->tf_harga->text().isEmpty()) {
        // Menampilkan pesan peringatan jika ada kolom yang kosong
        QMessageBox::warning(this, "Peringatan", "Mohon lengkapi semua kolom.");
        return;
    }
    // Mengambil informasi buku dari input pengguna
    QString judul = ui->tf_judul->text();
    QString pengarang = ui->tf_pengarang->text();
    QString tahunTerbit = ui->tf_tahun->text();
    QString harga = ui->tf_harga->text();

    // Menambahkan buku baru ke dalam manajer buku
    bukuManager->tambahBuku(judul, pengarang, tahunTerbit, harga);

    // Menampilkan pesan informasi bahwa buku berhasil ditambahkan
    QMessageBox::information(this, "Informasi", "Buku berhasil ditambahkan ke dalam daftar.");

    // Menutup dialog
    this->close();
}
