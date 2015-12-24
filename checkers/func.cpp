#ifndef UNCOMENT
#define UNCOMENT

#include <iostream>
#include <string>

#include <QFileInfo>
#include <QString>
#include <QTextStream>

using namespace std;

string uncoment(string line)
{
    size_t pos = 0;
    string unLine = "";
    if ((pos = line.find("//")) != string::npos)
    {
        unLine = line.erase(pos);
        return unLine;
    }
    else
    {
        return line;
    }
}

string unspaceForward(string line)
{
    int i = 0;
    while (line[i] == ' ')
    {
        line.erase(i);
        i++;
    }
}

string unspaceBackward(string line)
{
    int i = line.size() - 1;
    while (line[i] == ' ')
    {
        line.erase(i);
        i--;
    }
    return line;
    return line;
}

void printError(string error)
{
    QFile file("log.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << QString::fromStdString(error) << endl;
        file.close();
    }
    else
    {
        std::cout << "can't open log.txt to log" << std::endl;
    }
}

#endif

