#include "editbuku.h"
#include "ui_editbuku.h"
#include <QMessageBox>

// Konstruktor untuk kelas editbuku
editbuku::editbuku(BukuManager *bukuManager, const QString &judulLama, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editbuku),
    bukuManager(bukuManager),
    judulLama(judulLama)
{
    // Menginisialisasi UI
    ui->setupUi(this);
    // Menghubungkan event klik tombol edit ke slot yang sesuai
    connect(ui->btn_edit, &QPushButton::clicked, this, &editbuku::editBuku);
}

// Destruktor untuk kelas editbuku
editbuku::~editbuku()
{
    delete ui;
}

// Metode untuk mengatur judul buku pada UI
void editbuku::setJudul(const QString &judul)
{
    ui->tf_judul->setText(judul);
}

// Metode untuk mengatur pengarang buku pada UI
void editbuku::setPengarang(const QString &pengarang)
{
    ui->tf_pengarang->setText(pengarang);
}

// Metode untuk mengatur tahun terbit buku pada UI
void editbuku::setTahunTerbit(const QString &tahunTerbit)
{
    ui->tf_tahun->setText(tahunTerbit);
}

// Metode untuk mengatur harga buku pada UI
void editbuku::setHarga(const QString &harga)
{
    ui->tf_harga->setText(harga);
}

// Metode untuk melakukan pengeditan informasi buku
void editbuku::editBuku()
{
    // Mengambil informasi buku yang baru dari input pengguna
    QString judulBaru = ui->tf_judul->text();
    QString pengarangBaru = ui->tf_pengarang->text();
    QString tahunTerbitBaru = ui->tf_tahun->text();
    QString hargaBaru = ui->tf_harga->text();

    // Memperbarui informasi buku di dalam buku manager
    bukuManager->perbaruiBuku(judulLama, judulBaru, pengarangBaru, tahunTerbitBaru, hargaBaru);

    // Menampilkan pesan informasi bahwa buku berhasil diperbarui
    QMessageBox::information(this, "Edit Buku", "Buku berhasil diperbarui.");

    // Mengirim sinyal bahwa dialog telah ditutup
    emit dialogClosed();
    // Menutup dialog
    this->close();
}
