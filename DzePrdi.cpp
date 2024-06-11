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
#include <limits>

using namespace std;

fstream teme_za_igru;
fstream datotekaTimovi;
ofstream datotekaRezultat;
fstream datoteka_pitanja_trazilica;
fstream datoteka_odgovori_trazilica;
fstream odabrana_tema_pitanja_stream;
fstream odabrana_tema_odgovori_stream;

int money;
bool game_finished = false;

void clear_screen() // https://stackoverflow.com/questions/1348563/clearing-output-of-a-terminal-program-linux-c-c
{
    printf("\033[2J\033[1;1H");
}

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

bool izbor_cifre_bool(int &izbor)
{
    if (izbor < 0 || izbor > 4)
        return true;
    return false;
}

/*struct Team
{
    string tim;
    int money;
};*/
// struct Team timek;

void ispisivanje_logika_ploce()
{
    clear_screen();
    // otvaranje tema za igru

    teme_za_igru.open("Q&A/Teme.txt", ios::in);
    string *teme_za_iguru_ran_polje = new string[7];
    for (int i = 0; i < 7; i++) // upisivanje podataka iz ploce u polje sa kojem mozemo generirati random teme, treba osposobiti generator
    {
        getline(teme_za_igru, teme_za_iguru_ran_polje[i]);
    }
    for (int i = 0; i < 7; i++) // trimaje polja
    {
        rtrim(teme_za_iguru_ran_polje[i]);
    }
    teme_za_igru.close();

    // otvaranje datoteke sa pathovima za pitanja

    datoteka_pitanja_trazilica.open("Q&A/PitanjaTrazilica.txt", ios::in);
    string *pitanja_otvaranje_dat = new string[7];

    for (int i = 0; i < 7; i++)
    {
        datoteka_pitanja_trazilica >> pitanja_otvaranje_dat[i];
    }
    datoteka_pitanja_trazilica.close();

    // otvaranje datoteke sa paathovima za odgovore

    datoteka_odgovori_trazilica.open("Q&A/OdgovoriTrazilica.txt", ios::in);
    string *odgovori_otvaranje_dat = new string[7];

    for (int i = 0; i < 7; i++)
    {
        datoteka_odgovori_trazilica >> odgovori_otvaranje_dat[i];
    }
    datoteka_odgovori_trazilica.close();

    int index = 0;
    int const br_Retka = 5;
    int const br_Stupaca = 6;
    int const br_Tema = 6;
    vector<int> index_tema(7);
    vector<int> numeros = shuffle_numbers();
    int index_tema_int[7];
    int brojac_odigranih_polja = 0;
    int odgovor_da_ne = 1;

    for (int i = 0; i < 7; i++)
    {
        index_tema[i] = generator(numeros, index); // pamcenje generiranih brojeva
    }

    for (int i = 0; i < 7; i++)
    {
        index_tema_int[i] = index_tema[i];
    }

    int polje_money[br_Retka][br_Stupaca] = {{200, 200, 200, 200, 200, 200},
                                             {400, 400, 400, 400, 400, 400},
                                             {600, 600, 600, 600, 600, 600},
                                             {800, 800, 800, 800, 800, 800},
                                             {1000, 1000, 1000, 1000, 1000, 1000}}; // logika ce nesto sitno ici ako je ovo broj stupca j isti kao i odabrana tema i tada mozemo napravit provjeru da izvucemo pitanje za pravu temu
    while (1)
    {

        if (brojac_odigranih_polja == 30)
        {
            break;
        }

        if (odgovor_da_ne != 1)
        {
            break;
        }

        for (int i = 0; i < br_Tema; i++)
        {
            cout << setw(22) << teme_za_iguru_ran_polje[index_tema[i]]; // resolve genrator printa samo jedno onak polje jebati breg mater
        }

        for (int i = 0; i < br_Retka; i++)
        {
            cout << endl;
            for (int j = 0; j < br_Stupaca; j++)
            {
                cout << setw(20) << polje_money[i][j] << "$ ";
            }
        }

        cout << endl
             << endl;
        cout << setw(30) << "200$ = 0" << setw(22) << "400$ = 1" << setw(22) << "600$ = 2" << setw(22) << "800$ = 3" << setw(22) << "1000$ = 4" << endl;

        string izbor_teme[1]; // velicina polja na 1 jer ce uvijek biti zapisan samo jedan podatak
        int index_odabrane_teme;

        while (1)
        {
            cout << "Enter the topic you want: " << endl;
            getline(cin, izbor_teme[0]);

            bool izbor_teme_auth = false;
            for (int i = 0; i < 7; i++)
            {
                if (izbor_teme[0] == teme_za_iguru_ran_polje[i])
                {
                    index_odabrane_teme = i;
                    izbor_teme_auth = true;
                    break;
                }
            }
            if (!izbor_teme_auth)
            {
                clear_screen();
                cout << "Wrong selection please try again!" << endl;
                izbor_teme[0].erase();
                Sleep(2000);
                clear_screen();
                break;
            }
            else // ostatak igre
            {
                int index_odabrana_cifra;
                string odgovor[1];
                string odgovor_tolower[1];

                // UCITAVANJE PITANJA

                odabrana_tema_pitanja_stream.open(pitanja_otvaranje_dat[index_odabrane_teme], ios::in);
                string *odabrana_tema_pitanja = new string[5];
                for (int i = 0; i < 5; i++)
                {
                    getline(odabrana_tema_pitanja_stream, odabrana_tema_pitanja[i]);
                }
                odabrana_tema_pitanja_stream.close();

                // UCITAVANJE ODGOVORA
                odabrana_tema_odgovori_stream.open(odgovori_otvaranje_dat[index_odabrane_teme], ios::in);
                string *odabrana_tema_odgovori = new string[5];
                for (int i = 0; i < 5; i++)
                {
                    getline(odabrana_tema_odgovori_stream, odabrana_tema_odgovori[i]);
                }
                odabrana_tema_odgovori_stream.close();

                while (1)
                {
                    cout << "Enter the value for which you want to play from 0 - 4" << endl; // polje[index_odabrana_cifra][index_odabrane_teme]
                    cin >> index_odabrana_cifra;

                    if (izbor_cifre_bool(index_odabrana_cifra))
                    {
                        clear_screen();
                        cout << "Wrong selection please try again!" << endl;
                        cin.ignore();
                        Sleep(2000);
                        clear_screen();
                        break;
                    }

                    int *begin_teme = begin(index_tema_int);
                    int *end_teme = end(index_tema_int);
                    int *trazen_index_adresa = find(begin_teme, end_teme, index_odabrane_teme);
                    int trazeni_index = distance(begin_teme, trazen_index_adresa);

                    if (polje_money[index_odabrana_cifra][trazeni_index] == 0)
                    {
                        cout << "Wrong selection please try again!" << endl;
                        brojac_odigranih_polja++;
                        break;
                    }

                    clear_screen();
                    cout << "You have chosen topic: " << teme_za_iguru_ran_polje[index_odabrane_teme] << " for " << polje_money[index_odabrana_cifra][index_odabrane_teme] << "$" << endl;
                    cout << "The question is: " << odabrana_tema_pitanja[index_odabrana_cifra] << endl;
                    cout << "Your answer: ";
                    cin.ignore();
                    getline(cin, odgovor[0]);

                    // provjera da li je odgovor vec bio odigran

                    // pretvaranje u lowercase

                    for (int i = 0; i < odgovor[0].length(); i++)
                    {
                        odgovor_tolower[0] += tolower(odgovor[0][i]);
                    }

                    // usporedba odgovora

                    if (odgovor_tolower[0] == odabrana_tema_odgovori[index_odabrana_cifra])
                    {
                        clear_screen();
                        cout << "Congrats! You have won: " << polje_money[index_odabrana_cifra][index_odabrane_teme] << "$" << endl;
                        money += polje_money[index_odabrana_cifra][index_odabrane_teme];
                        polje_money[index_odabrana_cifra][trazeni_index] = 0;
                        Sleep(3000);
                        clear_screen();
                        cout << "Do you wish to contonue with the game? 1/0" << endl;
                        cin >> odgovor_da_ne;
                        cin.ignore();
                        break;
                    }
                    else
                    {
                        clear_screen();
                        cout << "Unfortunately, your answer was wrong!" << endl;
                        polje_money[index_odabrana_cifra][trazeni_index] = 0;
                        Sleep(3000);
                        clear_screen();
                        cout << "Do you wish to contonue with the game? 1/0" << endl;
                        cin >> odgovor_da_ne;
                        cin.ignore();
                        break;
                    }
                }
                // brisanje stringova zbog overwrita
                for (int i = 0; i < 5; i++)
                {
                    odabrana_tema_pitanja[i].erase();
                    odabrana_tema_odgovori[i].erase();
                }
                clear_screen();
                break;
            }
        }
    }
}

struct Rezultat
{
    char Timovi[50];
    int  money;
};

int main()
{
    srand(time(NULL));
    string upis_timova;
    int broj_timova = 0;
    bool unos_player = false;
    bool scores_player = false;

    while (1)
    {
        clear_screen();
        // credit: https://www.asciiart.eu/text-to-ascii-art
        cout << "██████╗ ███████╗███████╗██████╗ ██████╗ ██████╗ ██╗██╗" << endl;
        cout << "██╔══██╗╚══███╔╝██╔════╝██╔══██╗██╔══██╗██╔══██╗██║██║" << endl;
        cout << "██║  ██║  ███╔╝ █████╗  ██████╔╝██████╔╝██║  ██║██║██║" << endl;
        cout << "██║  ██║ ███╔╝  ██╔══╝  ██╔═══╝ ██╔══██╗██║  ██║██║╚═╝" << endl;
        cout << "██████╔╝███████╗███████╗██║     ██║  ██║██████╔╝██║██╗" << endl;
        cout << "╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝" << endl;

        int izbor;

        cout << endl;
        cout << "Menu" << endl;
        cout << "1. Start game!" << endl;
        cout << "2. Players" << endl;
        cout << "3. Scores" << endl;
        cout << "4. Rules!" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter selection 1. - 5. " << endl;
        cin >> izbor;
        if (izbor_bool(izbor))
        {
            clear_screen();
            cout << "Wrong selection please try again!" << endl;
            Sleep(3000);
            clear_screen();
            continue;
        }
        if (izbor == 1)
        {
            if (unos_player && !game_finished)
            {
                cin.ignore();
                ispisivanje_logika_ploce();
                scores_player = true;
                game_finished = true;
            }
            else
            {
                clear_screen();
                cout << "You have finished the game or you havent entered the player name!" << endl;
                Sleep(3000);
            }
        }
        if (izbor == 2)
        {
            if(!unos_player)
            {
                clear_screen();
                cin.ignore();
                string ispis_timova;
                datotekaTimovi.open("Scores&Teams/Teams.txt", ios::in);
                cout << "Names of past players" << endl;
                while(getline(datotekaTimovi,ispis_timova))
                {
                    cout << ispis_timova << endl;
                }
                datotekaTimovi.close();
                cout << endl;
                datotekaTimovi.open("Scores&Teams/Teams.txt",ios::app | ios::out);
                cout << "Enter the name of the player:" << endl;
                getline(cin, upis_timova);
                broj_timova++;
                datotekaTimovi << upis_timova << endl;
                datotekaTimovi.close();
                unos_player = true;
                }
                else
                {
                        clear_screen();
                        cout << "You have already entered your player name!" << endl;
                        Sleep(3000);
                }
        }
        if (izbor == 3)
        {
            //if (scores_player)
            //{
            datotekaRezultat.open("Scores&Teams/Score.bin", std::ios::binary | std::ios::out | std::ios::app);
            size_t size = upis_timova.size();
            datotekaRezultat.write(reinterpret_cast<char *>(&size), sizeof(size));
            datotekaRezultat.write(upis_timova.c_str(), size);
            datotekaRezultat.write(reinterpret_cast<char *>(&money), sizeof(money));
            datotekaRezultat.close();

            std::ifstream datotekaUlaz;
            datotekaUlaz.open("Scores&Teams/Score.bin", std::ios::binary | std::ios::in);
            std::string ispis_timova_bin;
            int ispis_money_bin;
            while (datotekaUlaz.read(reinterpret_cast<char *>(&size), sizeof(size)))
            {
                ispis_timova_bin.resize(size);
                datotekaUlaz.read(&ispis_timova_bin[0], size);
                datotekaUlaz.read(reinterpret_cast<char *>(&ispis_money_bin), sizeof(ispis_money_bin));
                for (int i = 0; i < broj_timova; i++)
                {
                    std::cout << ispis_timova_bin << " " << ispis_money_bin << std::endl;
                }
            }
            datotekaUlaz.close();

            Sleep(10000);
            //}
            /*else
            {
                clear_screen();
                cout << "Please, finish the game!" << endl;
                Sleep(3000);
            }*/
        }

        if (izbor == 4)
        {
            clear_screen();
            cout << "The Player chooses the category and amount of money for which he wants to play." << endl
                 << "If the player answers corectly he gets the money and the right to choose another question." << endl
                 << "When the player answers the question, that question can't be answered again." << endl
                 << "The player can play until all the questions aren't answered or he can stop the game after every answer." << endl
                 << "HAVE FUN!" << endl;
            cout << "Press Enter to continue. . . ";
            cin.ignore();
            getchar();

        }
        if (izbor == 5)
        {
            break;
        }
    }
}