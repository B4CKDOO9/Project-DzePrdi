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
#include <cstring>

#if defined(_WIN32)
#define CLEAR system("cls");
#elif defined(__linux__)
#define CLEAR system("clear");
#endif

using namespace std;

fstream teme_za_igru;

void rtrim(string &s) // credit: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
{
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

vector<int> shuffle_numbers() // credit: Copilot
{
    vector<int> numbers;
    for (int i = 0; i < 7; i++)
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
    index = (index + 1) % 7;
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

    string *teme_za_iguru_ran_polje = new string[7];
    for (int i = 0; i < 7; i++) // upisivanje podataka iz ploce u polje sa kojem mozemo generirati random teme, treba osposobiti generator
    {
        getline(teme_za_igru, teme_za_iguru_ran_polje[i]);
    }
    for (int i = 0; i < 7; i++) //trimaje polja
    {
        rtrim(teme_za_iguru_ran_polje[i]);
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
    cout << endl;

    int const izbor_retka = 5;
    int const izbor_stupaca = 6;
    int izbor_polja[izbor_retka][izbor_stupaca];
    string izbor_teme[1]; // velicina polja na 1 jer ce uvijek biti zapisan samo jedan podatak

    cout << "Enter the topic you want: " << endl;
    cin.ignore();
    getline(cin, izbor_teme[0]);

    bool izbor_teme_auth = false;
    for (int i = 0; i < 7; i++)
    {
        if (izbor_teme[0] == teme_za_iguru_ran_polje[i]) 
        {
            izbor_teme_auth = true;
            break;
        }
    }
    if (!izbor_teme_auth)
    {
        cout << "Please try again!" << endl;
        //dodati goto statment
    }

}
struct {
    string ekipa;

} login;
struct Rezultat{
    char Timovi[50];
    float Rez;
};
int main()
{
    srand(time(NULL));
    // credit: https://www.asciiart.eu/text-to-ascii-art
    cout << "██████╗ ███████╗███████╗██████╗ ██████╗ ██████╗ ██╗██╗" << endl;
    cout << "██╔══██╗╚══███╔╝██╔════╝██╔══██╗██╔══██╗██╔══██╗██║██║" << endl;
    cout << "██║  ██║  ███╔╝ █████╗  ██████╔╝██████╔╝██║  ██║██║██║" << endl;
    cout << "██║  ██║ ███╔╝  ██╔══╝  ██╔═══╝ ██╔══██╗██║  ██║██║╚═╝" << endl;
    cout << "██████╔╝███████╗███████╗██║     ██║  ██║██████╔╝██║██╗" << endl;
    cout << "╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝" << endl;

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
        cout << "Enter selection 1. - 5. " << endl;
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
            cout << "Prijasnji timovi: " << endl;
            while (getline(datotekaTimovi, ispis))
                cout << ispis << endl;
            datotekaTimovi.close();
            cout << endl << "Unesite naziv tima: " << endl;
            getline(cin, unos);
            cout << endl;
            datotekaTimovi.open("Scores&Teams/Teams.txt", ios::out | ios::app);
            datotekaTimovi <<endl<< unos << endl;
            datotekaTimovi.close();
        }
        if (izbor == 3)
        {
            /*cout << "izbor 3" << endl;
            // binarna datoteka
            struct Rezultat tim[100];
            int brTimova = 0;
            fstream datoteka("Score.bin", ios::binary | ios::in);
            while(datoteka.read((char*)&tim[brTimova],sizeof(Rezultat)))
            {
                cout << tim[brTimova].Timovi << " " << tim[brTimova].Rez << endl;
                brTimova++;
            }
            datoteka.close();
            int n;
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n;i++){
                cin.getline(tim[brTimova + i].Timovi, 50);
                cin >> tim[brTimova + i].Rez;
            }
            sort(tim, tim + brTimova + n, cmp());
            datoteka.open("Score.bin", ios::binary | ios::out | ios::trunc);
            datoteka.write((char *)tim, sizeof(Rezultat) * (brTimova + n));
            datoteka.close();*/
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
