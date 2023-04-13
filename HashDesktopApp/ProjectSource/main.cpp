#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCryptographicHash>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    //ana penceremiz
    QWidget window;

    // background için palet objesi oluşturduk
    QPalette pal = window.palette();
    pal.setBrush(QPalette::Window , QBrush(QImage("4.png")));
    window.setPalette(pal);
    window.setFixedSize(800, 550);

    // Çerçeve oluşturduk
    QFrame *frame = new QFrame(&window);
    frame->setStyleSheet("background-color: transparent; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255,111,0,0.75), stop:0.42 rgba(205,152,26,0.45), stop:1 rgba(0,164,255,0.1)); border-radius: 18px;");

    frame->setFixedSize(350, 250);
    frame->move((window.width() - frame->width()) / 2, (window.height() - frame->height()) / 2); // merkezlemek için konumunu ayarlayın
    //PRU uygulama yazımız
    QLabel *titleLabel = new QLabel("Piri Reis Üniversitesi", &window);
    titleLabel->setAlignment(Qt::AlignHCenter);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 18pt; background-color: rgba(200, 141, 71,1); border-radius: 12px;");
    titleLabel->setGeometry((window.width() - frame->width()) / 2, 75, frame->width(), 30);


    // Yerleşim düzeni oluşturduk
    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);

    QLabel userLabel("Kullanıcı Adı", frame);
    userLabel.setStyleSheet("QLabel { background-color : rgba(200, 141, 71,0); }");
    layout->addWidget(&userLabel);

    QLineEdit userInput(frame);
    userInput.setFixedWidth(175);
    userInput.setStyleSheet("QLineEdit {background-color: rgb(148, 117, 77); border-width: 2px; border-style: solid; border-radius: 10px; }");
    layout->addWidget(&userInput);

    QLabel passwordLabel("Şifre", frame);
    passwordLabel.setStyleSheet("QLabel { background-color : rgba(0, 0, 0 ,0); }");
    layout->addWidget(&passwordLabel);

    QLineEdit passwordInput(frame);
    passwordInput.setEchoMode(QLineEdit::Password);
    passwordInput.setFixedWidth(175);
    passwordInput.setStyleSheet("QLineEdit { background-color: rgb(148, 117, 77); border-width: 2px; border-style: solid; border-radius: 10px; }");
    layout->addWidget(&passwordInput);

    QPushButton loginButton("Giriş", frame);
    loginButton.setFixedSize(80, 30);
    loginButton.setStyleSheet("QPushButton { background-color: rgb(148, 117, 77); color: black;border-width: 2px; border-style: solid; border-radius: 11px; }");
    layout->addWidget(&loginButton);

    QPushButton registerButton("Kayıt Ol", frame);
    registerButton.setFixedSize(80, 30);
    registerButton.setStyleSheet("QPushButton { background-color: rgb(148, 117, 77); color: black;border-width: 2px; border-style: solid; border-radius: 11px; }");
    layout->addWidget(&registerButton);

    QObject::connect(&registerButton, &QPushButton::clicked, [&](){
        QString username = userInput.text();
        QString password = passwordInput.text();

        if(username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(&window, "Hata", "Kullanıcı adı ve şifre boş bırakılamaz!");
            return;
        }

        QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5);
        QString hashedPassword(hash.toHex());

        QFile file("kullanicilar.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << username << "," << hashedPassword << "\n";
            file.close();
        }

        QMessageBox::information(&window, "Başarılı", "Kayıt Başarılı");
    });

    QObject::connect(&loginButton, &QPushButton::clicked, [&](){
        QString username = userInput.text();
        QString password = passwordInput.text();

        if(username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(&window, "Hata", "Kullanıcı adı ve şifre boş bırakılamaz!");
            return;
        }

        QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5);
        QString hashedPassword(hash.toHex());

        QFile file("kullanicilar.txt");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString line;
            bool found = false;
            while(!stream.atEnd()) {
                line = stream.readLine();
                QStringList fields = line.split(",");
                if(fields.size() == 2 && fields[0] == username && fields[1] == hashedPassword) {
                    found = true;
                    break;
                }
            }
            file.close();
            if(found) {
                QMessageBox::information(&window, "Başarılı", "Giriş Başarılı");
            }
            else {
                QMessageBox::warning(&window, "Hata", "Kullanıcı adı veya şifre yanlış ");
            }
        }
    });

    window.show();
    return app.exec();
}
