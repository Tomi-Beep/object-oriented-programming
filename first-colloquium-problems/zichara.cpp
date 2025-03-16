#include<iostream>
#include<cstring>

using namespace std;

class Zichara {
    char *mesto;
    int cena;
public:
    Zichara(const char *mesto = "", int cena = 0) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->cena = cena;
    }

    Zichara(const Zichara &z) {
        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);
        this->cena = z.cena;
    }

    Zichara &operator=(Zichara &z) {
        if (this != &z) {
            delete[]mesto;
            this->mesto = new char[strlen(z.mesto) + 1];
            strcpy(this->mesto, z.mesto);
            this->cena = z.cena;
        }
        return *this;
    }

    ~Zichara() { delete[]mesto; }

    int getCena() const {
        return cena;
    }

};

class PlaninarskiDom {
    char ime[15];
    int ceni[2];
    char klasa;
    bool imaZichara;
    Zichara *zhichara;
public:
    PlaninarskiDom() {
        strcpy(ime, "");
        ceni[0] = 0;
        ceni[1] = 0;
        klasa = 'A';
        imaZichara = false;
        zhichara = nullptr;
    }

    PlaninarskiDom(const char *ime, int ceni[2], char klasa) {
        strcpy(this->ime, ime);
        this->ceni[0] = ceni[0];
        this->ceni[1] = ceni[1];
        this->klasa = klasa;
        imaZichara = false;
        zhichara = nullptr;
    }

    PlaninarskiDom(const PlaninarskiDom &p) {
        strcpy(this->ime, p.ime);
        this->ceni[0] = p.ceni[0];
        this->ceni[1] = p.ceni[1];
        this->klasa = p.klasa;
        this->imaZichara = p.imaZichara;
        if (imaZichara) {
            this->zhichara = new Zichara(*p.zhichara);
        } else {
            zhichara = nullptr;
        }
    }

    PlaninarskiDom &operator=(PlaninarskiDom &p) {
        if (this != &p) {
            delete zhichara;
            strcpy(this->ime, p.ime);
            this->ceni[0] = p.ceni[0];
            this->ceni[1] = p.ceni[1];
            this->klasa = p.klasa;
            this->imaZichara = p.imaZichara;
            if (imaZichara) {
                this->zhichara = new Zichara(*p.zhichara);
            } else {
                zhichara = nullptr;
            }
        }
        return *this;
    }

    ~PlaninarskiDom() {
        delete zhichara;
    }

    void setZichara(Zichara zhichara) {
        imaZichara = true;
        this->zhichara = new Zichara(zhichara);
    }

    PlaninarskiDom operator--() {
        switch (klasa) {
            case 'A':
                klasa = 'B';
                break;
            case 'B':
                klasa = 'C';
                break;
            case 'C':
                klasa = 'D';
                break;
            case 'D':
                klasa = 'E';
                break;
            case 'E':
                klasa = 'F';
                break;
            case 'F':
                klasa = 'F';
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const PlaninarskiDom &dom) {
        cout << dom.ime << " klasa:" << dom.klasa;
        if (dom.imaZichara) { cout << " so Zichara" << endl; }
        else { cout << endl; }
        return os;
    }

    bool operator<=(char k) {
        if (klasa >= k)
            return 1;
        return 0;
    }

    void presmetajDnevenPrestoj(int den, int mesec, int &cena) {
        if (mesec > 12 || mesec < 1 || den < 1 || den > 31)
            throw 1;
        if (mesec >= 4 && mesec < 9) {
            cena = ceni[0];
        } else if ((mesec >= 1 && mesec < 4) || (mesec >= 9 && mesec <= 12)) {
            cena = ceni[1];
        }
        if (imaZichara) {
            cena += zhichara->getCena();
        }
    }

};

int main() {

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[2];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den, mesec;
    cin >> den >> mesec;
    try {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    }
    catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
}
