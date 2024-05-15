#include <fstream>
#include <iostream>
#include <String>

using namespace std;

int main()
{
    fstream kaj("test.txt");
    string ispispod;
    while(getline(kaj,ispispod))
    {
        cout << ispispod << endl;
    }
    
}