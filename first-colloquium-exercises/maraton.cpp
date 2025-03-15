#include<iostream>
#include<cstring>

using namespace std;

class Ucesnik {
    char *ime;
    bool pol;
    int vozrast;

    friend class Maraton;

public:
    Ucesnik(char *ime = "", bool pol = 0, int vozrast = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }

    Ucesnik &operator=(Ucesnik &u) {
        if (this != &u) {
            delete[]ime;
            this->ime = new char[strlen(u.ime) + 1];
            strcpy(this->ime, u.ime);
            this->pol = u.pol;
            this->vozrast = u.vozrast;
        }
        return *this;
    }

    Ucesnik(Ucesnik &u) {
        this->ime = new char[strlen(u.ime) + 1];
        strcpy(this->ime, u.ime);
        this->pol = u.pol;
        this->vozrast = u.vozrast;
    }

    ~Ucesnik() { delete[] ime; }

    bool operator>(Ucesnik &u) {
        if (vozrast >= u.vozrast)
            return 0;
        return 1;
    }

    friend ostream &operator<<(ostream &os, const Ucesnik &ucesnik) {
        os << ucesnik.ime << endl;
        if (!ucesnik.pol) {
            cout << "zhenski" << endl;
        } else
            cout << "mashki" << endl;
        cout << ucesnik.vozrast << endl;
        return os;
    }
};

class Maraton {
    char lokacija[100];
    Ucesnik *uchesnici;
    int brUchesnici;
public:
    Maraton(char *lokacija = "", Ucesnik *uchesnici = nullptr, int brUchesnici = 0) {
        strcpy(this->lokacija, lokacija);
        this->uchesnici = new Ucesnik[brUchesnici];
        this->brUchesnici = brUchesnici;
        for (int i = 0; i < brUchesnici; i++) {
            this->uchesnici[i] = uchesnici[i];
        }
    }

    Maraton(Maraton &m) {
        strcpy(this->lokacija, m.lokacija);
        this->uchesnici = new Ucesnik[m.brUchesnici];
        this->brUchesnici = m.brUchesnici;
        for (int i = 0; i < brUchesnici; i++) {
            this->uchesnici[i] = m.uchesnici[i];
        }
    }

    Maraton &operator=(Maraton &m) {
        if (this != &m) {
            delete[]uchesnici;
            strcpy(this->lokacija, m.lokacija);
            this->uchesnici = new Ucesnik[m.brUchesnici];
            this->brUchesnici = m.brUchesnici;
            for (int i = 0; i < brUchesnici; i++) {
                this->uchesnici[i] = m.uchesnici[i];
            }
        }
        return *this;
    }

    ~Maraton() {
        delete[]uchesnici;
    }

    Maraton &operator+=(Ucesnik &u) {
        Ucesnik *temp = new Ucesnik[brUchesnici + 1];
        for (int i = 0; i < brUchesnici; i++) {
            temp[i] = uchesnici[i];
        }
        temp[brUchesnici] = u;
        brUchesnici++;
        delete[]uchesnici;
        uchesnici = temp;
        return *this;
    }

    double prosecnoVozrast() {
        double zbir = 0;
        for (int i = 0; i < brUchesnici; i++) {
            zbir += (double) uchesnici[i].vozrast;
        }
        return zbir/brUchesnici;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < brUchesnici; i++) {
            if (uchesnici[i] > u)
                cout << uchesnici[i];
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}
