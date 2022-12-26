//POP 2021-01-22 projekt 2 Poćwiardowski Jakub AIR 3 184827
//Microsoft Visual Studio Community 2019 16.7.6, MSVC 2019

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define ALF_SIZE 128
#define ZNAK_PL 9

void naMorse(string nazwa, string nazwa2) {
    string morse[ALF_SIZE] = { " / ", "-.-.--", ".-..-.", "#", "...-..-", "#", ".-...", ".----.", "-.--.", "-.--.-", "#", ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
                            // spacja      !         "      #       $       %      &        '         (         )      *      +         ,         -        .         /
"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
//  0         1       2        3        4        5        6        7        8        9 
"---...", "-.-.-.", "-.--.", "-...-", "-.--.-", "..--..", ".--.-.",
//   :         ;          <      =         >         ?         @
 ".-", "-...", "-.-.", "-..",".", "..-.", "--.", "....", "..", ".---",
"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",  // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
"..-", "...-", ".--", "-..-", "-.--", "--..",
 "-.--.", "-..-.", "-.--.-", "#", "..--.-" };
    //  [        \        ]       ^       _
    string latinPL = "ąęćłóśńźżĄĘĆŁÓŚŃŹŻ";
    string morsePL[ZNAK_PL] = { ".-.-", "..-..", "-.-..", ".-..-", "---.", "...-...", "--.--", "--..-","--..-." };
    ifstream plik;
    ofstream zapis;
    char znak;
    string linia;
    plik.open(nazwa);
    zapis.open(nazwa2);
    if (plik.good()) {
        while (getline(plik, linia)) {
            for (int i = 0; i < linia.length(); i++) {
                if (linia[i] >= ' ' && linia[i] <= '}') {
                    if (linia[i] >= 'a' && linia[i] <= 'z') {
                        linia[i] -= 'a' - 'A';
                    }
                    else if (linia[i] >= '{' && linia[i] <= '}') {
                        linia[i] -= '{' - '[';
                    }
                    int litera = linia[i] - ' ';
                    zapis << morse[litera]<<" ";
                }
                else {
                    int pol = int(linia[i]) + int(linia[++i]);
                    cout << pol << endl;
                    if (pol == -246) zapis << morsePL[0] << " ";
                    else if (pol == -206) zapis << morsePL[1]<<" ";
                    else if (pol == -242) zapis << morsePL[2] << " ";
                    else if (pol == -252) zapis << morsePL[3] << " ";
                    else if (pol == -154) zapis << morsePL[4] << " ";
                    else if (pol == -202) zapis << morsePL[5] << " ";
                    else if (pol == -248) zapis << morsePL[6] << " ";
                    else if (pol == -140) zapis << morsePL[7] << " ";
                    else if (pol == -136) zapis << morsePL[8] << " ";
                }
                
            }
            zapis << endl;
        }
    }
    else cout << "Nie udalo sie otworzyc pliku" << endl;

    plik.close();
    zapis.close();
    return;
}

void naLatin(string nazwa, string nazwa2) {
    char znaki[ALF_SIZE] = { 'e', 't',
                             'i','a','n','m',
                            's','u','r','w','d','k','g','o',
                        'h','v','f','#','l','ą','p','j','b','x','c','y','z','q','ó','ch',
                    '5','4','ś','3','ę','#','#','2','#','ł','+','#','#','#','#','1','6','=','/','#','ć','#','(','#','7','ź','#','ń','8','#','9','0',
        '#','#','#','#','#','#','#','#','#','#','#','#','?','_','#','#','#','#','"','#','#','.','#','#','#','#','@','#','#','#','\'','#','#',' - ','#','#','#','#','#','#','#','#','; ','!','#',')','#','#','#','#','ż',',','#','#','#','#',':','#','#','#','#','#','#','#' };
    ifstream plik;
    ofstream zapis;
    char znak;
    bool czykropka=1;
    plik.open(nazwa);
    zapis.open(nazwa2);
    if (plik.good()) {
        while (!plik.eof()) {
            string slowo;
            plik >> slowo;
            if (slowo == "/") zapis << " ";
            else {
                int i = 0;
                int index = 1;
                while (slowo[i] == '.' || slowo[i] == '-' || slowo[i] == '_') {
                    if (slowo[i] == '.') index *= 2;
                    else if (slowo[i] == '-' || slowo[i] == '_') index = index * 2 + 1; //System zamieniający na alfabet Morse'a działa na zasadzie tworzenia liczby binarnej, w której . oznacza 0, a - 1. 
                    i++;
                }
                index -= 2;
                if (index >= 0 && index <= 128) {
                    if (czykropka && isalpha(znaki[index])) {
                        zapis << char(toupper(znaki[index]));
                        czykropka = 0;
                    }
                    else zapis << znaki[index];
                }
                else if (index == 134) zapis << "ś";
                if (znaki[index] == '.') czykropka = 1;

            }
        }
    
    }
    else cout << "Nie udalo sie otworzyc pliku";

    plik.close();
    zapis.close();
}

int main()
{
    setlocale(LC_CTYPE, "Polish");
    int wybor = 0;
    while (wybor != 3) {
        cout << "Podaj czy chcesz przetłumaczyć plik na alfabet Morse'a, czy tez zdekodować plik zapisany tym alfabetem: " << endl;
        cout << "1. Zamiana na alfabet Morse'a" << endl;
        cout << "2. Zdekodowanie alfabetu Morse'a na alfabet łacinski" << endl;
        cout << "3. Zakończenie działania programu" << endl;
        cin >> wybor;
        while (!(wybor == 1 || wybor == 2 || wybor == 3)||isalpha(wybor)) {
            cout << "Nieprawidlowy wybor, sprobuj ponownie" << endl;
            cin >> wybor;
        }
        if (wybor == 3) break;
        cout << endl;
        cout << "Podaj nazwę pliku lub ścieżki do pliku który ma zostać przetworzony: " << endl;
        string nazwa, nazwa2;
        cin >> nazwa;
        cout << "Podaj nazwę pliku lub ścieżki do pliku w którym ma zostać zapisany tekst: " << endl;
        cin >> nazwa2;
        if (wybor == 1) naMorse(nazwa, nazwa2);
        else if (wybor == 2) naLatin(nazwa, nazwa2);
        cout << endl;
    }
    return 0;
}