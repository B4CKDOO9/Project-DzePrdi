#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>

#if defined(_WIN32)
#define CLEAR system("cls");
#elif defined(__linux__)
#define CLEAR system("clear");
#endif

using namespace std;

fstream teme_za_igru;

vector<int> shuffle_numbers() // credit: Copilot
{
    vector<int> numbers;
    for (int i = 1; i < 8; i++)
    {
        numbers.push_back(i);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    return numbers;
}

int generator(vector<int> &numbers, int &index)
{
    int random_broj = numbers[index];
    index = (index + 1) % 8;
    return random_broj;
}

bool izbor_bool(int &izbor)
{
    if (izbor < 1 || izbor > 5)
        return true;
    return false;
}

void ispisivanje_logika_ploce()
{
    fstream teme_za_igru("Q&A/Teme.txt", ios::app | ios::in);

    string *teme_za_iguru_ran_polje = new string[8];
    for (int i = 0; i < 7; i++) // upisivanje podataka iz ploce u polje sa kojem mozemo generirati random teme, treba osposobiti generator
    {
        getline(teme_za_igru, teme_za_iguru_ran_polje[i]);
    }

    teme_za_igru.close();

    int index = 0;
    int const br_Retka = 5;
    int const br_Stupaca = 6;
    int const br_Tema = 6;

    vector<int> numeros = shuffle_numbers();

    int polje_money[br_Retka][br_Stupaca] = {{200, 200, 200, 200, 200, 200},
                                             {400, 400, 400, 400, 400, 400},
                                             {600, 600, 600, 600, 600, 600},
                                             {800, 800, 800, 800, 800, 800},
                                             {1000, 1000, 1000, 1000, 1000, 1000}}; // logika ce nesto sitno ici ako je ovo broj stupca j isti kao i odabrana tema i tada mozemo napravit provjeru da izvucemo pitanje za pravu temu
    for (int i = 0; i < br_Tema; i++)
    {
        cout << setw(22) << teme_za_iguru_ran_polje[generator(numeros, index)]; // resolve genrator printa samo jedno onak polje jebati breg mater
    }

    for (int i = 0; i < br_Retka; i++)
    {
        cout << endl;
        for (int j = 0; j < br_Stupaca; j++)
        {
            cout << setw(20) << polje_money[i][j] << "$ ";
        }
    }

}

int main()
{
    srand(time(NULL));

    // credit: https://www.asciiart.eu/text-to-ascii-art

    cout << "▓█████▄ ▒███████▒▓█████  ██▓███   ██▀███  ▓█████▄  ██▓ ▐██▌" << endl;
    cout << "▒██▀ ██▌▒ ▒ ▒ ▄▀░▓█   ▀ ▓██░  ██▒▓██ ▒ ██▒▒██▀ ██▌▓██▒ ▐██▌" << endl;
    cout << "░██   █▌░ ▒ ▄▀▒░ ▒███   ▓██░ ██▓▒▓██ ░▄█ ▒░██   █▌▒██▒ ▐██▌" << endl;
    cout << "░▓█▄   ▌  ▄▀▒   ░▒▓█  ▄ ▒██▄█▓▒ ▒▒██▀▀█▄  ░▓█▄   ▌░██░ ▓██▒" << endl;
    cout << "░▒████▓ ▒███████▒░▒████▒▒██▒ ░  ░░██▓ ▒██▒░▒████▓ ░██░ ▒▄▄ " << endl;
    cout << " ▒▒▓  ▒ ░▒▒ ▓░▒░▒░░ ▒░ ░▒▓▒░ ░  ░░ ▒▓ ░▒▓░ ▒▒▓  ▒ ░▓   ░▀▀▒" << endl;
    cout << " ░ ▒  ▒ ░░▒ ▒ ░ ▒ ░ ░  ░░▒ ░       ░▒ ░ ▒░ ░ ▒  ▒  ▒ ░ ░  ░" << endl;
    cout << "   ░      ░ ░       ░  ░            ░        ░     ░   ░   " << endl;
    cout << " ░      ░                                  ░               " << endl;
    while (1)
    {
        int izbor;
        cout << endl;
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
            ispisivanje_logika_ploce();
        }
        if (izbor == 2)
        {
            cin.ignore();
            cout << "izbor 2" << endl;
            // tekstualna datoteka 
            fstream datotekaTimovi;
            string ispis, unos;
            datotekaTimovi.open("Scores&Teams/Teams.txt", ios::in);
            while (getline(datotekaTimovi, ispis))
                cout << ispis << endl;
            datotekaTimovi.close();
            getline(cin, unos);
            cout << "PICKEEE" << endl;
            datotekaTimovi.open("Scores&Teams/Teams.txt", ios::out | ios::app);
            datotekaTimovi << unos << endl;
            datotekaTimovi.close();
            
        }
        if (izbor == 3)
        {
            cout << "izbor 3" << endl;
            // binarna datoteka
        }
        if (izbor == 4)
        {
            cout << "izbor 4" << endl;
            cout << "Jedan od natjecatelja bira kategoriju i iznos novaca za to pitanje." << endl
                 << "Nakon postavljenog pitanja imate 15s da prvi stisnete svoju tipku i odaberete je li odgovor a,b ili c." << endl
                 << "Osoba koja točno odgovori dobije iznos novaca i može birati sljedeću kategoriju i pitanje." << endl
                 << "Nakon što odgovorite na neko pitanje to pitanje nestaje i više ga se ne može otvoriti." << endl
                 << "Igra se dok sva pitanja na ploči nisu iskorištena odnosno odgovorena." << endl
                 << "ZABAVITE SE!" << endl;
        }
        if (izbor == 5)
        {
            cout << "izbor 5" << endl;
            break;
        }
    }
}
