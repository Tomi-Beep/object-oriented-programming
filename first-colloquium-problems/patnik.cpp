#include<iostream>
#include<cstring>

using namespace std;
enum tip {
    eden = 1, dva
};

class Patnik {
    char ime[100];
    int klasa;
    bool velosiped;

    friend class Voz;

public:
    Patnik(const char *ime = "", int klasa = 1, bool velosiped = false) {
        strcpy(this->ime, ime);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }

    friend ostream &operator<<(ostream &os, Patnik &patnik) {
        os << patnik.ime << endl << patnik.klasa << endl << patnik.velosiped << endl;
    }
};

class Voz {
    char krajnaDestinacija[100];
    Patnik *patnici;
    int brPatnici;
    int brVelosipedi;
public:
    Voz(char *krajnaDestinacija = "", int brVelosipedi = 0, int brPatnici = 0, Patnik *patnici = nullptr) {
        strcpy(this->krajnaDestinacija, krajnaDestinacija);
        this->brVelosipedi = brVelosipedi;
        this->brPatnici = brPatnici;
        this->patnici = new Patnik[brPatnici];
        for (int i = 0; i < brPatnici; i++) {
            this->patnici[i] = patnici[i];
        }
    }

    Voz &operator+=(Patnik &patnik) {
        if (brVelosipedi == 0) {
            if (!patnik.velosiped) {
                Patnik *temp = new Patnik[brPatnici + 1];
                for (int i = 0; i < brPatnici; i++) {
                    temp[i] = patnici[i];
                }
                temp[brPatnici] = patnik;
                delete[]patnici;
                brPatnici++;
                patnici = temp;
            } else
                return *this;
        } else {
            Patnik *temp = new Patnik[brPatnici + 1];
            for (int i = 0; i < brPatnici; i++) {
                temp[i] = patnici[i];
            }
            temp[brPatnici] = patnik;
            delete[]patnici;
            brPatnici++;
            patnici = temp;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Voz &voz) {
        os << voz.krajnaDestinacija << endl;
        for (int i = 0; i < voz.brPatnici; i++) {
            cout << voz.patnici[i] << endl;
        }
        return os;
    }

    void patniciNemaMesto() {
        int prva = 0, vtora = 0;
        for (int i = 0; i < brPatnici; i++) {
            if (patnici[i].klasa == 1 && patnici[i].velosiped)
                prva++;
            if (patnici[i].klasa == 2 && patnici[i].velosiped)
                vtora++;
        }
        if (prva >= brVelosipedi) {
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << prva - brVelosipedi << endl;
            cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << vtora << endl;
        } else if (prva < brVelosipedi) {
            cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << 0 << endl;
            if (vtora >= (brVelosipedi - prva)) {
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << vtora - (brVelosipedi - prva)
                     << endl;
            } else {
                cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << 0 << endl;
            }
        }

    }
};


int main() {
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++) {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
