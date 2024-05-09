#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "bukumanager.h"
#include "tambahbuku.h"
#include "QMessageBox"
#include "editbuku.h"
#include "mainwindow.h"

admindashboard::admindashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admindashboard),
    bukuManager(new BukuManager)
{
    ui->setupUi(this);
    tampilkanDataBuku();
}

admindashboard::~admindashboard()
{
    delete bukuManager;
    delete ui;
}

void admindashboard::on_btn_tambah_clicked()
{
    tambahbuku *dialog = new tambahbuku(bukuManager, this);
    dialog->exec();
    connect(dialog, &tambahbuku::dialogClosed, this, &admindashboard::refreshTableWidget);
}

void admindashboard::refreshTableWidget()
{
    tampilkanDataBuku();
}

void admindashboard::tampilkanDataBuku()
{
    bukuManager->tampilkanDataBuku(ui->tableWidget);
}

void admindashboard::on_btn_edit_clicked()
{
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();

    if(selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Peringatan", "Harap pilih data terlebih dahulu.");
        return;
    }

    int selectedRow = selectedIndexes.at(0).row();

    QTableWidgetItem* judulItem = ui->tableWidget->item(selectedRow, 0);
    QTableWidgetItem* pengarangItem = ui->tableWidget->item(selectedRow, 1);
    QTableWidgetItem* tahunTerbitItem = ui->tableWidget->item(selectedRow, 2);
    QTableWidgetItem* hargaItem = ui->tableWidget->item(selectedRow, 3);

    QString judul = judulItem->text();
    QString pengarang = pengarangItem->text();
    QString tahunTerbit = tahunTerbitItem->text();
    QString harga = hargaItem->text();

    editbuku *dialog = new editbuku(bukuManager, judul, this);
    dialog->setJudul(judul);
    dialog->setPengarang(pengarang);
    dialog->setTahunTerbit(tahunTerbit);
    dialog->setHarga(harga);
    dialog->exec();
}

void admindashboard::on_btn_hapus_clicked()
{
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();
    if(selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Peringatan", "Harap pilih data terlebih dahulu.");
        return;
    }

    int choice = QMessageBox::question(this, "Konfirmasi Hapus", "Anda yakin ingin menghapus buku?", QMessageBox::Yes | QMessageBox::No);
    if(choice == QMessageBox::No)
        return;

    int selectedRow = selectedIndexes.at(0).row();
    QTableWidgetItem* judulItem = ui->tableWidget->item(selectedRow, 0);
    QString judul = judulItem->text();
    bukuManager->hapusBuku(judul);

    ui->tableWidget->removeRow(selectedRow);

    QMessageBox::information(this, "Hapus Buku", "Buku berhasil dihapus.");

    qDebug() << "Isi linked list setelah penghapusan:";
    bukuManager->tampilkanDataBuku();
}

void admindashboard::on_btn_logout_clicked()
{
    this->close();
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

}






