#ifndef CHECK_TWO_LINE
#define CHECK_TWO_LINE

#include <iostream>
#include <string>
#include <sstream>

#include "func.cpp"

using namespace std;

bool ifDefIndent = false; //включен, если до этого уже просканили хотя бы один отступ
int ind = 0; //количество пробелов в отступе

void checkIndent(string strline, string prevline, int line);
void checkTwoLine(string strline, string prevline, int line)
{
    checkIndent(strline, prevline, line);
}

int indent(string line)
{
    int i = 0;
    while (line[i] == ' ')
    {
        i++;
    }

    return i;
}

void checkIndent(string strline, string prevline, int line)
{
    //std::cout << "EEEEEEEEEEEE: " << strline << " " << ifDefIndent << " " << ind << std::endl;
    if(ifDefIndent)
    {
        string pvln = prevline;
        int fpv = pvln.size() -1;
        int fst = strline.size() - 1;
        if(pvln[fpv] == '{')
        {
            if (indent(strline) != (indent(pvln)+ind))
            {
                std::stringstream ss("");
                ss << "Неровное количество отступов в { строке " << line;
                cout << ss.str() << endl;
                printError(ss.str());
            }
        }
        else if(strline[fst] == '}')
        {
            std::cout << "prevline: " << prevline << " " << indent(prevline) << std::endl;
            std::cout << "strline: " << strline << " " << indent(strline) << std::endl << std::endl;
            if (indent(strline) != (indent(pvln)-ind))
            {
                std::stringstream ss("");
                ss << "Неровное количество отступов в } строке " << line;
                cout << ss.str() << endl;
                printError(ss.str());
            }
        }
        else
        {
            if (indent(strline) != indent(pvln))
            {
                std::stringstream ss("");
                ss << "Неровное количество отступов в строке " << line;
                cout << ss.str() << endl;
                printError(ss.str());
            }
        }
    }
}

#endif
