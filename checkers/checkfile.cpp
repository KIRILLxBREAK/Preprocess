#ifndef CHECK_FILE
#define CHECK_FILE

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <cstring>
#include <ctype.h>

#include <QFileInfo>
#include <QString>
#include <QDebug>

#include "utf8_v2_3_4/source/utf8.h"

#include "func.cpp"

using namespace std;

void checkUtf8File(string file_name);
void checkFileName(string file_name);
void checkComment(string file_name);
void checkMultipleInclude(string file_name);

void checkFile(string file_name)
{
    //checkUtf8File(file_name);
    checkFileName(file_name);
    checkComment(file_name);
    checkMultipleInclude(file_name);
}

void checkUtf8File(string file_name)
{
    ifstream file(file_name.c_str());
    if (!file)
        return; // even better, throw here

    istreambuf_iterator<char> it(file.rdbuf());
    istreambuf_iterator<char> eos;

    if (utf8::is_valid(it, eos))
    {
        std::stringstream ss("");
        ss << "incorrect encoding!";
        cout << ss.str() << endl;
        printError(ss.str());
    }
    file.close();
}

void checkFileName(string file_name)
{
    QFileInfo fi(QString::fromStdString(file_name));
    string basename =  fi.baseName().toStdString();
    std::cout << "path: " << basename << std::endl;
    for(unsigned int i =0; i < basename.size(); i++)
    {
        if (isalpha(basename[i]) && basename[i] == toupper(basename[i]))
        {
            std::stringstream ss("");
            ss << "filename must be in lower register! " << basename[i];
            cout << ss.str() << endl;
            printError(ss.str());

            break;
        }
    }
}

void checkComment(string file_name)
{
    if  (file_name.find(".h") != string::npos || file_name.find(".hpp") != string::npos)
    {
        ifstream file(file_name.c_str());
        string strline;
        if (file.is_open())
        {
            getline(file,strline);
            std::cout << "EEEEEEEE: " << strline << " " << strline.size() << std::endl;

            if (strline.find("/*") == string::npos && strline.find("//") == string::npos)
            {
                std::stringstream ss("");
                ss << "must add comment to introduce  file";
                cout << ss.str() << endl;
                printError(ss.str());
            }
            else if (strline.size() < 10)
            {
                std::stringstream ss("");
                ss << "must add a bigger comment to introduce  file";
                cout << ss.str() << endl;
                printError(ss.str());

            }
            file.close();
        }
    }
}

void checkMultipleInclude(string file_name)
{
    bool isIfndef = false;
    if (file_name.find(".h") != string::npos || file_name.find(".hpp") != string::npos)
    {
        ifstream file(file_name.c_str());
        string strline;
        if (file.is_open())
        {
            getline(file,strline);
            while (getline(file,strline))
            {
                string str = uncoment(strline);
                if (str.find("#ifndef") != string::npos)
                {
                    isIfndef = true;
                }
            }
            file.close();
        }
        if (!isIfndef)
        {
            std::stringstream ss("");
            ss << "must add #ifndef to exclude muiltiple include";
            cout << ss.str() << endl;
            printError(ss.str());
        }
    }
}

#endif
