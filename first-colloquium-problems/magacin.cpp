#include <iostream>
#include <cstring>

using namespace std;

class Gitara {
    char seriskiBroj[25];
    double nabavnaCena;
    int godinaNaProizvodstvo;
    char tip[20];
    friend class Magacin;

public:
    Gitara() {}

    Gitara(char *tip, char *seriski, int godina, double cena) {
        strcpy(this->tip, tip);
        strcpy(seriskiBroj, seriski);
        godinaNaProizvodstvo = godina;
        nabavnaCena = cena;
    }

    bool daliIsti(Gitara g) {
        if (!strcmp(seriskiBroj, g.seriskiBroj))
            return true;
        return false;
    }

    void pecati() {
        cout << seriskiBroj << " " << tip << " " << nabavnaCena << endl;
    }

    const char *getSeriski() const {
        return seriskiBroj;
    }

    double getNabavna() const {
        return nabavnaCena;
    }

    int getGodina() const {
        return godinaNaProizvodstvo;
    }

    const char *getTip() const {
        return tip;
    }
};

class Magacin {
    char ime[30];
    char lokacija[60];
    static int brojNaGitari;
    Gitara *gitari = new Gitara[30];
    int godinaNaOtvaranje;
public:
    Magacin() {}

    Magacin(const char ime[], const char lokacija[]) {
        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);
    }

    Magacin(const char *ime, const char *lokacija, int godina) {
        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);
        godinaNaOtvaranje = godina;
    }

    Magacin(const Magacin &m) {
        strcpy(this->ime, m.ime);
        strcpy(this->lokacija, m.lokacija);
        godinaNaOtvaranje = m.godinaNaOtvaranje;
    }

    double vrednost() {
        double zbir = 0;
        for (int i = 0; i < brojNaGitari; i++) {
            zbir += gitari[i].nabavnaCena;
        }
        return zbir;
    }

    void dodadi(Gitara d) {
        gitari[brojNaGitari] = d;
        brojNaGitari++;
    }

    void prodadi(Gitara p) {
        for (int i = 0; i < brojNaGitari; i++) {
            if (!strcmp(p.seriskiBroj, gitari[i].seriskiBroj)) {
                for (int j = i; j < brojNaGitari - 1; ++j) {
                    Gitara temp = gitari[j + 1];
                    gitari[j + 1] = gitari[j];
                    gitari[j] = temp;
                }
                brojNaGitari--;
                i--;
            }
        }
    }

    void pecati(bool daliNovi) {
        if (!daliNovi) {
            cout << ime << " " << lokacija << endl;
            for (int i = 0; i < brojNaGitari; i++) {
                gitari[i].pecati();
            }
        } else {
            cout << ime << " " << lokacija << endl;
            for (int i = 0; i < brojNaGitari; i++) {
                if (gitari[i].godinaNaProizvodstvo > godinaNaOtvaranje)
                    gitari[i].pecati();
            }
        }
    }
};

int Magacin::brojNaGitari = 0;

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
