#include <iostream>
#include <cstring>

using namespace std;
enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem() {
        ime = nullptr;
        verzija = 0;
        tip = LINUX;
        golemina = 0;
    }

    OperativenSistem(char *ime, float verzija, Tip tip, float golemina) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->tip = tip;
        this->golemina = golemina;
    }

    OperativenSistem(const OperativenSistem &op) {
        this->ime = new char[strlen(op.ime) + 1];
        strcpy(this->ime, op.ime);
        this->verzija = op.verzija;
        this->tip = op.tip;
        this->golemina = op.golemina;
    }

    OperativenSistem &operator=(const OperativenSistem &op) {
        if (this != &op) {
            delete[]ime;
            this->ime = new char[strlen(op.ime) + 1];
            strcpy(this->ime, op.ime);
            this->verzija = op.verzija;
            this->tip = op.tip;
            this->golemina = op.golemina;
        }
        return *this;
    }

    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tip << " Golemina:" << golemina <<"GB"<< endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        if (!strcmp(ime, os.ime) && verzija == os.verzija && tip == os.tip && golemina == os.golemina) {
            return true;
        }
        return false;
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (verzija == os.verzija)
            return 0;
        else if (verzija > os.verzija)
            return 1;
        else
            return -1;
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        if (tip == sporedba.tip && !strcmp(ime, sporedba.ime)) {
            return 1;
        }
        return 0;
    }
};

class Repozitorium {
    char ime[20];
    OperativenSistem *sistemi;
    int brSistemi;
public:
    Repozitorium(const char *ime) {
        strcpy(this->ime, ime);
        sistemi = nullptr;
        brSistemi = 0;
    }

    ~Repozitorium() { delete[]sistemi; }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << endl;
        for (int i = 0; i < brSistemi; i++) {
            sistemi[i].pecati();
        }
    }

    void dodadi(const OperativenSistem &nov) {
        bool t = true;
        for (int i = 0; i < brSistemi; i++) {
            if (sistemi[i].istaFamilija(nov) && sistemi[i].sporediVerzija(nov) == -1) {
                sistemi[i] = nov;
                if (t)
                    t = false;
            }
        }
        if (t) {
            OperativenSistem *temp = new OperativenSistem[brSistemi + 1];
            for (int i = 0; i < brSistemi; i++) {
                temp[i] = sistemi[i];
            }
            temp[brSistemi] = nov;
            brSistemi++;
            delete[]sistemi;
            sistemi = temp;
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int counter = 0;
        for (int i = 0; i < brSistemi; i++) {
            if (sistemi[i].ednakviSe(operativenSistem)) {
                
                counter++;
                for (int j = i; j < brSistemi - 1; j++) {
                    OperativenSistem temp = sistemi[j];
                    sistemi[j] = sistemi[j + 1];
                    sistemi[j + 1] = temp;
                }
            }
        }
        OperativenSistem *temp = new OperativenSistem[brSistemi - counter];
        for (int i = 0; i < brSistemi - counter; i++) {
            temp[i] = sistemi[i];
        }
        brSistemi = brSistemi - counter;
        delete[]sistemi;
        sistemi = temp;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
