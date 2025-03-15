#include <cstring>
#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool veteran;
public:
    Vozac(const char ime[100], int vozrast, int brTrki, bool veteran) {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->brTrki = brTrki;
        this->veteran = veteran;
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {
        os << vozac.ime << endl << vozac.vozrast << endl << vozac.brTrki << endl;
        if (vozac.veteran) {
            cout << "VETERAN" << endl;
        }
        return os;
    }

    virtual float zarabotuvachka() = 0;

    virtual bool operator==(Vozac &rhs) {
        if (zarabotuvachka() == rhs.zarabotuvachka())
            return true;
        return false;
    }

    virtual float danok() = 0;
};

class Avtomobilist : public Vozac {
private:
    float cena;
public:
    Avtomobilist(const char ime[100], int vozrast, int brTrki, bool veteran, float cena) : Vozac(ime, vozrast, brTrki,
                                                                                                 veteran) {
        this->cena = cena;
    }

    float zarabotuvachka() {
        return cena / 5;
    }

    float danok() {
        if (brTrki > 10) {
            return 0.15f * zarabotuvachka();
        } else
            return 0.1f * zarabotuvachka();
    }
};

class Motociklist : public Vozac {
private:
    int mokjnost;
public:
    Motociklist(const char ime[100], int vozrast, int brTrki, bool veteran, int mokjnost) : Vozac(ime, vozrast, brTrki,
                                                                                                  veteran) {
        this->mokjnost = mokjnost;
    }

    float zarabotuvachka() {
        return (float)mokjnost * 20;
    }

    float danok() {
        if (veteran) {
            return 0.25f * zarabotuvachka();
        } else
            return 0.2f * zarabotuvachka();
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int brVozaci, Vozac *vozac) {
    int counter = 0;
    for (int i = 0; i < brVozaci; i++) {
        if (*vozaci[i] == *vozac) {
            counter++;
        }
    }
    return counter;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}


