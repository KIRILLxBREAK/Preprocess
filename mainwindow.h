//#ifndef MAIN_WINDOW_HPP
//#define MAIN_WINDOW_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstring>
#include <ctype.h>

#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() {}// деструктор

    //void check(const char *file_name);

private slots:
    void open();
    void save();
    //void quit();

private:
    QTextEdit *textEdit;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

//#endif
