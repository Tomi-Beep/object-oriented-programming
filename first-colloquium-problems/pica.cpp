#include <iostream>
#include <cstring>

using namespace std;

class Pica {
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;

    friend class Picerija;

public:
    Pica(char *ime = "", int cena = 0, char *sostojki = "", int namaluvanje = 0) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
        this->namaluvanje = namaluvanje;
    }

    Pica(const Pica &p) {
        strcpy(ime, p.ime);
        cena = p.cena;
        sostojki = new char[strlen(p.sostojki) + 1];
        strcpy(sostojki, p.sostojki);
        namaluvanje = p.namaluvanje;
    }

    ~Pica() { }

    void pecati() {
        cout << ime << " - " << sostojki << ", " << cena << endl;
    }

    bool istiSe(Pica p) {
        if (!strcmp(sostojki, p.sostojki))
            return 1;
        return 0;
    }
};

class Picerija {
    char ime[15];
    Pica *pici;
    int brojNaPici;
public:
    Picerija(char ime[], Pica *pici, int brojNaPici) {
        strcpy(this->ime, ime);
        this->brojNaPici = brojNaPici;
        *pici = new char[brojNaPici];
        for (int i = 0; i < brojNaPici; i++) {
            this->pici[i] = pici[i];
        }
    }

    Picerija(const char *ime = "") {
        strcpy(this->ime, ime);
        this->ime[14] = 0;
        pici = NULL;
        brojNaPici = 0;
    }

    ~Picerija() {
        
    }

    const char *getIme() const {
        return ime;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    void dodadi(Pica p) {
        if (brojNaPici == 0) {
            pici[0] = p;
            brojNaPici++;
        } else {
            bool t = true;
            for (int i = 0; i < brojNaPici; i++) {
                if (!strcmp(pici[i].sostojki, p.sostojki)) {
                    t = false;
                }
            }
            if (t) {
                pici[brojNaPici] = p;
                brojNaPici++;
            }
        }
    }

    Picerija &operator+=(Pica &p) {
        bool imaIsta = false;
        for (int i = 0; i < brojNaPici; i++)
            if (pici[i].istiSe(p))
                imaIsta = true;
        if (!imaIsta) {
            Pica *tmp = new Pica[brojNaPici + 1];
            for (int i = 0; i < brojNaPici; i++)
                tmp[i] = pici[i];
            tmp[brojNaPici++] = p;
            delete[] pici;
            pici = tmp;
        }
        return *this;
    }

    void piciNaPromocija() {
        for (int i = 0; i < brojNaPici; i++) {
            if (pici[i].namaluvanje > 0) {
                cout << pici[i].ime << " - " << pici[i].sostojki << ", "
                     << pici[i].cena << " " << (float)pici[i].cena * (float) (1 - (float)pici[i].namaluvanje / 100)<<endl;
            }
        }
    }
};


int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1 += p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2 += p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
