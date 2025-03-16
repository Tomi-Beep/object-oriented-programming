#include <iostream>
#include <cstring>
using namespace std;

enum tip {
    pop, rap, rok
};

class Pesna {
    int vremetraenje;
    char *ime = new char[50];
    tip pesna;
public:
    Pesna() {}

    Pesna(char *ime,int vremetraenje,  tip pesna) {
        this->vremetraenje = vremetraenje;
        this->pesna = pesna;
        strcpy(this->ime, ime);
    }

    Pesna(const Pesna &p) {
        this->vremetraenje = p.vremetraenje;
        this->pesna = p.pesna;
        strcpy(this->ime, p.ime);
    }

    ~Pesna() {}

    int getVremetraenje() const {
        return vremetraenje;
    }

    char *getIme() const {
        return ime;
    }

    tip getPesna() const {
        return pesna;
    }

    void setVremetraenje(int vremetraenje) {
        Pesna::vremetraenje = vremetraenje;
    }

    void setPesna(tip pesna) {
        Pesna::pesna = pesna;
    }

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    void pecati() {
        cout << '"' << ime << '"' << "-" << vremetraenje << "min" << endl;
    }

};

class CD {
    static int brojNaPesni;
    Pesna pesni[10];
    int maxVremetraenje;
public:
    CD() {}

    CD(int maxVremetraenje) {
        this->maxVremetraenje = maxVremetraenje;
    }

    CD(const CD &p) {
        this->brojNaPesni = p.brojNaPesni;
        this->maxVremetraenje = p.maxVremetraenje;
        for (int i = 0; i < maxVremetraenje; i++) {
            this->pesni[i] = p.pesni[i];
        }
    }

    int getBroj() const {
        return brojNaPesni;
    }

    void setBrojNaPesni(int brojNaPesni) {
        CD::brojNaPesni = brojNaPesni;
    }

    Pesna getPesna(int i) {
        return pesni[i];
    }

    int getMaxVremetraenje() const {
        return maxVremetraenje;
    }

    void setMaxVremetraenje(int maxVremetraenje) {
        CD::maxVremetraenje = maxVremetraenje;
    }

    void setPesni(Pesna *pesni) {
        for (int i = 0; i < maxVremetraenje; i++) {
            this->pesni[i] = pesni[i];
        }
    }

    void dodadiPesna(Pesna p) {
        static int doSega = 0;
        if (doSega + p.getVremetraenje() <= maxVremetraenje && brojNaPesni < 10) {
            pesni[brojNaPesni] = p;
            doSega += p.getVremetraenje();
            brojNaPesni++;
        }
    }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < brojNaPesni; i++) {
            if (pesni[i].getPesna() == t) {
                pesni[i].pecati();
            }
        }
    }
};

int CD::brojNaPesni=0;

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
    }

    return 0;
}
