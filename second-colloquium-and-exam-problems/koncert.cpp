#include<iostream>
#include<cstring>
using namespace std;

class Koncert {
    char naziv[20];
    char lokacija[20];
    static double popust; // static member for seasonal discount
    double bilet;
public:
    Koncert() : bilet(0) {
        strcpy(naziv, "");
        strcpy(lokacija, "");
    }
    Koncert(char* naziv, char* lokacija, double bilet) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->bilet = bilet;
    }
    virtual ~Koncert() {}
    
    static double getSezonskiPopust() {
        return popust;
    }
    static void setSezonskiPopust(double d) {
        popust = d;
    }
    char* getNaziv() {
        return naziv;
    }
    virtual double cena() {
        return bilet - bilet * popust;
    }
};

double Koncert::popust = 0.2; // initial value for the seasonal discount

class ElektronskiKoncert : public Koncert {
    char* dj;
    double vreme;
    bool tip;
public:
    ElektronskiKoncert() : Koncert() {
        dj = nullptr;
    }
    ElektronskiKoncert(char* naziv, char* lokacija, double bilet, char* dj, double vreme, bool tip)
        : Koncert(naziv, lokacija, bilet) {
        this->dj = new char[strlen(dj) + 1];
        strcpy(this->dj, dj);
        this->vreme = vreme;
        this->tip = tip;
    }
    ~ElektronskiKoncert() {
        delete[] dj;
    }
    double cena() override {
        double nova = Koncert::cena();
        if (vreme > 7) {
            nova += 360;
        } else if (vreme > 5) {
            nova += 150;
        }
        if (tip) {
            nova -= 50;
        } else {
            nova += 100;
        }
        return nova;
    }
};

void najskapKoncert(Koncert** koncerti, int n) {
    Koncert* max = koncerti[0];
    int elektronski = 0;
    for (int i = 0; i < n; i++) {
        if (max->cena() < koncerti[i]->cena()) {
            max = koncerti[i];
        }
        ElektronskiKoncert* e = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if (e != nullptr) {
            elektronski++;
        }
    }
    cout << "Najskap koncert: " << max->getNaziv() << " " << max->cena() << endl;
    cout << "Elektronski koncerti: " << elektronski << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert** koncerti, int n, char* naziv, bool elektronski) {
    bool najden = false;
    for (int i = 0; i < n; i++) {
        if (elektronski) {
            ElektronskiKoncert* e = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if (e != nullptr) {
                if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                    najden = true;
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                }
            }
        } else {
            if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                najden = true;
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
            }
        }
    }
    return najden;
}

int main() {
    int tip;
    cin >> tip;

    if (tip == 1) { // Koncert
        char naziv[100], lokacija[100];
        float cenaBilet;
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) { // cena - Koncert
        char naziv[100], lokacija[100];
        float cenaBilet;
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) { // ElektronskiKoncert
        char naziv[100], lokacija[100], imeDJ[40];
        float cenaBilet, casovi;
        bool dnevna;
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust " << s.getSezonskiPopust() << endl;
    } else if (tip == 4) { // cena - ElektronskiKoncert
        char naziv[100], lokacija[100], imeDJ[40];
        float cenaBilet, casovi;
        bool dnevna;
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) { // najskapKoncert
        // Implement your input here for testing if needed
    } else if (tip == 6) { // prebarajKoncert
        Koncert* koncerti[5];
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) { // prebaraj
        Koncert* koncerti[5];
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else
            cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else
            cout << "Ne e pronajden" << endl;
    } else if (tip == 8) { // smeni cena
        Koncert* koncerti[4];
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        
        Koncert::setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
