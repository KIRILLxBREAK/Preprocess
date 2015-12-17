#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>

#include <mainwindow.h>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();
    window ->resize(376, 301);
    window->show();
    /*QWidget *widget = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *but = new QPushButton("Open");
    layout->addWidget(but);

    widget->setLayout(layout);
    widget->resize(700, 700);
    widget->show();*/

    return app.exec();
}


