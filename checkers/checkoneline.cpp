#ifndef CHECK_ONE_LINE
#define CHECK_ONE_LINE

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <cstring>
#include <ctype.h>

#include "checktwoline.cpp"
#include "func.cpp"

using namespace std;

void checkLong(string strline, int line);
void checkOneOperator(string strline, int line);
void checkConstantUpRegister(string strline, int line);
void checkInclude(string strline, int line);
void checkFloat(string strline, int line);
void checkSpaceOperator(string strline, int line);
void checkPragmaPack(string strline, int line);
void checkOneLine(string strline, int line)
{
    checkLong(strline, line);
    checkOneOperator(strline, line);
    checkConstantUpRegister(strline, line);
    checkInclude(strline, line);
    checkFloat(strline, line);
    checkSpaceOperator(strline, line);
    checkPragmaPack(strline, line);
}

void checkLong(string strline, int line)
{
    if (strline.size() > 120)
    {
        /*string er = "line: ";
        er += line;
        er += " is more than 120 character";
        cout << er << endl;*/

        std::stringstream ss("");
        ss << "line " << line << " is more than 120 character";
        cout << ss.str() << endl;
        printError(ss.str());
    }
}

void checkOneOperator(string strline, int line)
{
    string str = strline;//uncoment(strline);
    size_t pos = 0;
    if ((pos = str.find(";")) != string::npos)
    {
        str.erase(pos, 1);
    }


    if (str.find("for") == string::npos)
    {
        if (str.find(";") !=  string::npos)
        {
            /*string er = "more then 1 operator in line ";
            er += line;
            cout << er << endl;*/

            std::stringstream ss("");
            ss << "more then 1 operator in line " << line;
            cout << ss.str() << endl;
            printError(ss.str());
        }
    }
    else
    {
        size_t pos1 = 0;
        if ((pos1 = str.find(";")) != string::npos)
        {
            str.erase(pos1, 1);
            size_t pos2 = 0;
            if ((pos2 = str.find(";")) != string::npos)
            {
                str.erase(pos2, 1);
                /*string er = "for in line ";
                er += line;
                cout << er << endl;*/

                std::stringstream ss("");
                ss << "more then 1 operator in line " << line;
                cout << ss.str() << endl;
                printError(ss.str());
            }
        }

    }
}

void checkConstantUpRegister(string strline, int line)
{
    std::vector <char*> vec;
    char *slovo;

    char *writable = new char[strline.size() + 1];
    std::copy(strline.begin(), strline.end(), writable);
    writable[strline.size()] = '\0'; // don't forget the terminating 0

    // разделяем строку на слова
    slovo=strtok(writable," ");
    while(slovo != NULL)
    {
        vec.push_back(slovo);
        slovo=strtok(NULL," ");
    }

    string str(vec[0]);
    if(str == "#define")
    {
        for(unsigned int i =0; i < strlen(vec[1]); i++)
        {
            if( (vec[1][i] != toupper(vec[1][i])) && isalpha(vec[1][i]) )
            {
                std::stringstream ss("");
                ss << "constant must be in upper register " << line << " line";
                cout << ss.str() << endl;
                printError(ss.str());
                break;
            }
        }
    }

    // don't forget to free the string after finished using it
    delete[] writable;
}

void checkInclude(string strline, int line)
{
    std::vector <char*> vec;
    char *slovo;

    char *writable = new char[strline.size() + 1];
    std::copy(strline.begin(), strline.end(), writable);
    writable[strline.size()] = '\0'; // don't forget the terminating 0

    // разделяем строку на слова
    slovo=strtok(writable," ");
    while(slovo != NULL)
    {
        vec.push_back(slovo);
        slovo=strtok(NULL," ");
    }

    string incStr = vec[0];
    if(incStr == "#include")
    {
        string str(vec[1]);
        size_t pos = str.find(".");
        size_t pos1 = str.find(".h");
        size_t pos2 = str.find(".hpp");
        if((pos != string::npos) && pos1 == string::npos && pos2 == string::npos)
        {
            std::stringstream ss("");
            ss << "include only *.h and *.hpp file " << line << " line";
            cout << ss.str() << endl;
            printError(ss.str());

        }
    }

    // don't forget to free the string after finished using it
    delete[] writable;
}

void checkFloat(string strline, int line)
{
    std::vector <char*> vec;
    char *slovo;

    char *writable = new char[strline.size() + 1];
    std::copy(strline.begin(), strline.end(), writable);
    writable[strline.size()] = '\0'; // don't forget the terminating 0

    // разделяем строку на слова
    slovo=strtok(writable," ");
    while(slovo != NULL)
    {
        vec.push_back(slovo);
        slovo=strtok(NULL," ");
    }

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        if (string(vec[i]) == "float")
        {
            /*string er = "You must use double type! ";
            er += line;
            cout << er << endl;*/

            std::stringstream ss("");
            ss << "You must use double type in line " << line;
            cout << ss.str() << endl;
            printError(ss.str());
            break;
        }
    }

    // don't forget to free the string after finished using it
    delete[] writable;
}

void checkSpaceOperator(string strline, int line)
{
    for (unsigned int i = 0; i < strline.size(); i++)
    {
        if(strline[i] == '>')
        {
            if(strline[i+1] == '>')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
        if(strline[i] == '<')
        {
            if(strline[i+1] == '<')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
        if(strline[i] == '&')
        {
            if(strline[i+1] == '&')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
        if(strline[i] == '|')
        {
            if(strline[i+1] == '|')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
        if(strline[i] == '=')
        {
            if(strline[i+1] == '=')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
        if(strline[i] == '!')
        {
            if(strline[i+1] == '=')
            {
                if ( (strline[i-1] != ' ') || (strline[i+2] != ' ') )
                {
                    std::stringstream ss("");
                    ss << "must you space between operator " << line;
                    cout << ss.str() << endl;
                    printError(ss.str());
                }
            }
        }
    }
}

void checkPragmaPack(string strline, int line)
{
    size_t pos = 0;
    if ((pos = strline.find("#pragma pack")) != std::string::npos)
    {
        std::stringstream ss("");
        ss << "You do not need to use pragma pack " << line;
        cout << ss.str() << endl;
        printError(ss.str());
    }
}

#endif
