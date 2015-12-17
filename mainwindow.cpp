#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstring>
#include <ctype.h>

#include "checkfile.cpp"
#include "checkoneline.cpp"
#include "checktwoline.cpp"

#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include <mainwindow.h>

MainWindow::MainWindow()
{
    openAction = new QAction("&Open", this);
    saveAction = new QAction("&Save", this);
    exitAction = new QAction("E&xit", this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    setWindowTitle(tr("Preprocess"));
}

void MainWindow::open()
{
    QFile file("log.txt");
    if (file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << QString("start log!") << endl;
        file.close();
    }
    else
    {
        std::cout << "can't open log.txt to start log" << std::endl;
    }


    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("C++ Files (*.cpp *.h);;Text Files (*.txt)"));

    if (fileName != "")
    {
        std::cout << "file_name: " << fileName.toStdString().c_str() << std::endl;
        std::string strline = "", prevline = "", nextline = "";

        std::ifstream file(fileName.toStdString().c_str());
        unsigned int line = 0;

        //checkFile(fileName.toStdString());
        std::cout << "Finish checkFile." << std::endl;

        if (file.is_open())
        {
            while (getline(file,strline))
            {
                line++;
                if (strline != "")
                {
                    if (prevline == "{" && !ifDefIndent)
                    {
                        ind = indent(strline);
                        ifDefIndent = true;
                    }
                    if (strline != "")
                    {
                        checkOneLine(strline, line);
                        checkTwoLine(strline, prevline, line);
                    }
                    prevline = strline;
                }
            }
            file.close();
            std::cout << "Finish check" << std::endl;
        }
        else
        {
            std::cout << "Can't open file. " << std::endl;
        }
    }

    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << QString("\nfinish log!") << endl;
        file.close();
    }
    else
    {
        std::cout << "can't open log.txt to finish log" << std::endl;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString text = textEdit->toPlainText() + line;
            textEdit->setPlainText(text);
        }
        file.close();
    }
    else
    {
        std::cout << "can't open log.txt to show log" << std::endl;
    }
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("C++ Files (*.cpp *.h);;Text Files (*.txt)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

/*void MainWindow::check(const char *file_name)
{
    std::string strline = "", prevline = "", nextline = "";

    std::ifstream file(file_name);
    unsigned int line = 0;

    checkFile(file_name);

    if (file.is_open())
    {
        while (getline(file,strline))
        {
            line++;
            if (prevline == "{" && !ifDefIndent)
            {
                ind = indent(strline);
                ifDefIndent = true;
            }
            checkOneLine(strline, line);
            //checkTwoLine(strline, prevline, line);
            prevline = strline;
        }
        file.close();
    }
}*/

