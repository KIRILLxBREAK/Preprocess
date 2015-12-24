// <10

#ifndef FILE
#define FILE

#include <iostream>

#define Q 340

using namespace std;

double func(double n)
{
    return (2*n-1)*(2*n-1)/n;
}

int main(int argc, char *argv[])
{
    int k, m, count;
    count  = 0;

    cout << "Please enter an real value: " << endl;
    cin >> k >> m; //read k and m

    for(int i = 1; func(i) <= m;i++)
    {
        if(func(i) >= k)
        {
            count++;
        }
    }

    cout << "Count: " << count << endl; // print out the count of numbers which satisfying

    return 0;
}

#endif



