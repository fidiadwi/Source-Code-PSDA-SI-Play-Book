#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "admindashboard.h"
#include "userdashboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Menginisialisasi komponen UI
    ui->setupUi(this);

    // Menginisialisasi data pengguna dengan username dan password default
    users[0].username = "user";
    users[0].password = "user";

    users[1].username = "user1";
    users[1].password = "user1";

    users[2].username = "user2";
    users[2].password = "user2";

    users[3].username = "admin";
    users[3].password = "admin";

    // Menghubungkan event klik tombol login ke slot yang sesuai
    connect(ui->btn_login, &QPushButton::clicked, this, &MainWindow::on_btn_login_clicked);
}

// Destruktor untuk kelas MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Slot untuk menangani event klik tombol login
void MainWindow::on_btn_login_clicked()
{
    // Mengambil username dan password yang dimasukkan dari field UI
    QString username = ui->tf_username->text();
    QString password = ui->tf_password->text();

    // Menginisialisasi flag keberhasilan login
    bool loginSuccess = false;

    // Iterasi melalui data pengguna untuk mencari username dan password yang cocok
    for (const User &user : users) {
        if (user.username == username && user.password == password) {
            // Memeriksa apakah pengguna yang masuk adalah admin atau pengguna biasa
            if (username == "admin") {
                // Menutup jendela utama dan membuka admin dashboard
                this->close();
                if (!adminDashboard) {
                    adminDashboard = new admindashboard(this);
                }
                adminDashboard->show();
            } else {
                // Menutup jendela utama dan membuka user dashboard
                this->close();
                if (!userDashboard) {
                    userDashboard = new UserDashboard(this);
                }
                userDashboard->show();
            }
            // Mengatur flag keberhasilan login menjadi true dan keluar dari loop
            loginSuccess = true;
            break;
        }
    }

    // Menampilkan pesan error jika login tidak berhasil
    if (!loginSuccess) {
        qDebug() << "Login gagal. Username atau password tidak valid.";
    }
}
