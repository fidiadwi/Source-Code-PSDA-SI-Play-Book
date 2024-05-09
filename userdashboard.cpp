#include "userdashboard.h"
#include "bukumanager.h"
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "mainwindow.h"

// Konstruktor untuk kelas UserDashboard
UserDashboard::UserDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userdashboard),
    bukuManager(new BukuManager())
{
    // Menginisialisasi UI
    ui->setupUi(this);

    // Memperbarui data buku yang ditampilkan dalam tabel
    refreshTableWidget();

    // Menghubungkan event klik tombol cari ke slot yang sesuai
    connect(ui->btn_cari, &QPushButton::clicked, this, &UserDashboard::on_btn_cari_clicked);
}

// Destruktor untuk kelas UserDashboard
UserDashboard::~UserDashboard()
{
    delete ui;
    delete bukuManager;
}

// Metode untuk memperbarui data buku yang ditampilkan dalam tabel
void UserDashboard::refreshTableWidget()
{
    bukuManager->tampilkanDataBukuUser(ui->tableWidget);
}

// Slot untuk menangani event klik tombol cari
void UserDashboard::on_btn_cari_clicked()
{
    // Mengambil kata kunci pencarian dari input pengguna
    QString kataKunci = ui->tf_cari->text();

    // Melakukan pencarian buku berdasarkan kata kunci dan menampilkan hasilnya dalam tabel
    bukuManager->pencarianBukuUser(kataKunci, ui->tableWidget);
}

// Slot untuk menangani event klik tombol logout
void UserDashboard::on_btn_logout_clicked()
{
    // Menutup jendela dashboard pengguna
    this->close();

    // Membuat dan menampilkan jendela utama untuk login
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void UserDashboard::on_btn_beli_clicked()
{
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();
    if(selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Peringatan", "Harap pilih data terlebih dahulu.");
        return;
    }

    int choice = QMessageBox::question(this, "Konfirmasi Pembelian", "Apakah anda yakin ingin membeli buku ini?", QMessageBox::Yes | QMessageBox::No);
    if(choice == QMessageBox::No)
        return;

    int selectedRow = selectedIndexes.at(0).row();
    QTableWidgetItem* judulItem = ui->tableWidget->item(selectedRow, 0);
    QString judul = judulItem->text();
    bukuManager->hapusBuku(judul);

    ui->tableWidget->removeRow(selectedRow);

    QMessageBox::information(this, "Buku Terbeli", "Buku berhasil dibeli!");

    qDebug() << "Isi linked list setelah pembelian:";
    bukuManager->tampilkanDataBuku();
}

