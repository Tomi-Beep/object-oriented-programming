#include <iostream>
#include <cstring>

using namespace std;

class IceCream {
    char *ime;
    char sostav[100];
    float cena;
    int popust;
public:
    IceCream(const char *ime = "", const char *sostav = "", float cena = 0, int popust = 0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        strcpy(this->sostav, sostav);
        this->cena = cena;
        this->popust = popust;
    }

    IceCream(IceCream &i) {
        this->ime = new char[strlen(i.ime) + 1];
        strcpy(this->ime, i.ime);
        strcpy(this->sostav, i.sostav);
        this->cena = i.cena;
        this->popust = i.popust;
    }

    IceCream &operator=(IceCream &i) {
        if (this != &i) {
            delete[]ime;
            this->ime = new char[strlen(i.ime) + 1];
            strcpy(this->ime, i.ime);
            strcpy(this->sostav, i.sostav);
            this->cena = i.cena;
            this->popust = i.popust;
        }
        return *this;
    }

    ~IceCream() { delete[]ime; }

    void setName(char *ime) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
    }

    void setDiscount(int popust) {
        this->popust = popust;
    }

    friend ostream &operator<<(ostream &os, const IceCream &cream) {
        os << cream.ime << ": " << cream.sostav << " "
           << cream.cena;
        if (cream.popust > 0) {
            cout << " (" << (1.0 - (float) cream.popust / 100) * cream.cena << ")";
        }
        return os;
    }

    IceCream &operator++() {
        popust = popust + 5;
        return *this;
    }

    IceCream &operator+(const char *niza) {
        char *temp = new char[strlen(ime) + 1 + strlen(niza) + 1 + strlen(" + ") + 1];
        strcpy(temp, ime);
        strcat(temp, " + ");
        strcat(temp, niza);
        delete[]ime;
        ime = new char[strlen(temp) + 1];
        strcpy(ime, temp);
        cena = cena + 10;
        return *this;
    }
};

class IceCreamShop {
    char ime[50];
    IceCream *sladoledi;
    int brSladoledi;
public:
    IceCreamShop(char *ime) {
        strcpy(this->ime, ime);
        sladoledi = nullptr;
        brSladoledi = 0;
    }

    IceCreamShop(IceCreamShop &ic) {
        strcpy(ime, ic.ime);
        brSladoledi = ic.brSladoledi;
        sladoledi = new IceCream[brSladoledi];
        for (int i = 0; i < brSladoledi; i++) {
            sladoledi[i] = ic.sladoledi[i];
        }
    }

    IceCreamShop &operator=(IceCreamShop &ic) {
        if (this != &ic) {
            delete[]sladoledi;
            strcpy(ime, ic.ime);
            brSladoledi = ic.brSladoledi;
            sladoledi = new IceCream[brSladoledi];
            for (int i = 0; i < brSladoledi; i++) {
                sladoledi[i] = ic.sladoledi[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() { delete[]sladoledi; }

    IceCreamShop &operator+=(IceCream &i) {
        IceCream *temp = new IceCream[brSladoledi + 1];
        for (int j = 0; j < brSladoledi; j++) {
            temp[j] = sladoledi[j];
        }
        temp[brSladoledi++] = i;
        delete[]sladoledi;
        sladoledi = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const IceCreamShop &shop) {
        os << shop.ime;
        for (int i = 0; i < shop.brSladoledi; i++) {
            cout << endl;
            cout << shop.sladoledi[i];
        }
        cout << endl;
        return os;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

