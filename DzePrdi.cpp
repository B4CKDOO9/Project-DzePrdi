#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <time.h>
#include <windows.h>
#include <iomanip>

#if defined(_WIN32)
#define CLEAR system("cls");
#elif defined(__linux__)
#define CLEAR system("clear");
#endif

using namespace std;

bool izbor_bool(int &izbor)
{
    if(izbor < 1 || izbor > 5)
        return true;
    return false;
}

void ispisivanje_ploce()
{
    int const br_Retka = 5;
    int const  br_Stupaca = 6;
    int const br_Tema = 6;
    int polje_money[br_Retka][br_Stupaca] = {{200, 200, 200, 200, 200, 200},
                                             {400, 400, 400, 400, 400, 400},
                                             {600, 600, 600, 600, 600, 600},
                                             {800, 800, 800, 800, 800, 800},
                                             {1000, 1000, 1000, 1000, 1000, 1000}};
    for (int i = 0; i < br_Tema; i++)
    {
        cout << setw(12) << "Tema ";
    }

    for (int i = 0; i < br_Retka; i++)
    {
        cout << endl;
        for (int j = 0; j < br_Stupaca; j++)
        {
            cout << setw(10) << polje_money[i][j] << "$ ";
        }
    }                           
}

    int
    main()
    {
        cout << " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " << endl;
        cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "| |  ________    | || |   ________   | || |  _________   | || |   ______     | || |  _______     | || |  ________    | || |     _____    | |" << endl;
        cout << "| | |_   ___ `.  | || |  |  __   _|  | || | |_   ___  |  | || |  |_   __ \\   | || | |_   __ \\    | || | |_   ___ `.  | || |    |_   _|   | |" << endl;
        cout << "| |   | |   `. \\ | || |  |_/  / /    | || |   | |_  \\_|  | || |    | |__) |  | || |   | |__) |   | || |   | |   `. \\ | || |      | |     | |" << endl;
        cout << "| |   | |    | | | || |     .'.' _   | || |   |  _|  _   | || |    |  ___/   | || |   |  __ /    | || |   | |    | | | || |      | |     | |" << endl;
        cout << "| |  _| |___.' / | || |   _/ /__/ |  | || |  _| |___/ |  | || |   _| |_      | || |  _| |  \\ \\_  | || |  _| |___.' / | || |     _| |_    | |" << endl;
        cout << "| | |________.'  | || |  |________|  | || | |_________|  | || |  |_____|     | || | |____| |___| | || | |________.'  | || |    |_____|   | |" << endl;
        cout << "| |              | || |              | || |              | || |              | || |              | || |              | || |              | |" << endl;
        cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
        cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
        while (1)
        {
            int izbor;
            cout << "Menu" << endl;
            cout << "1. Start game!" << endl;
            cout << "2. Teams" << endl;
            cout << "3. Scores" << endl;
            cout << "4. Rules!" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter selection 1. - 5.: " << endl;
            cin >> izbor;
            if (izbor_bool(izbor))
            {
                CLEAR;
                cout << "Wrong selection please try again!" << endl;
                Sleep(3000);
                CLEAR;
                continue;
            }
            if (izbor == 1)
            {
                ispisivanje_ploce();
            }
            if (izbor == 2)
            {
                cout << "izbor 2" << endl;
            }
            if (izbor == 3)
            {
                cout << "izbor 3" << endl;
            }
            if (izbor == 4)
            {
                cout << "izbor 4" << endl;
            }
            if (izbor == 5)
            {
                cout << "izbor 5" << endl;
                break;
            }
        }
}
