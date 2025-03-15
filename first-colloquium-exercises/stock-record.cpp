#include<iostream>
#include<cstring>

using namespace std;

using namespace std;

class StockRecord {
    char ID[12];
    char imeNaKompanija[50];
    double kupenaCena;
    double momentalnaCena;
    int brojAkcii;
public:

    StockRecord(const char *id = "", const char *ime = "", double kupena = 0, int broj = 0, double moment = 0) {
        strcpy(ID, id);
        strcpy(imeNaKompanija, ime);
        kupenaCena = kupena;
        momentalnaCena = moment;
        brojAkcii = broj;
    }

    void setNewPrice(double c) {
        momentalnaCena = c;
    }

    double value() {
        return (float) brojAkcii * momentalnaCena;
    }

    double profit() {
        return (float) brojAkcii * (momentalnaCena - kupenaCena);
    }

    friend ostream &operator<<(ostream &os, StockRecord &record) {
        os << record.imeNaKompanija << " " << record.brojAkcii << " " <<
           record.kupenaCena << " " << record.momentalnaCena << " " << record.profit() << endl;
        return os;
    }

};

class Client {
    char imePrezime[60];
    int ID;
    int brKompanii;
    StockRecord *kompanii;
public:
    Client(const char *ime = "", int id = 0, int broj = 0, StockRecord *kompanii = nullptr) {
        strcpy(imePrezime, ime);
        ID = id;
        brKompanii = broj;
        this->kompanii = new StockRecord[brKompanii];
        for (int i = 0; i < brKompanii; i++) {
            this->kompanii[i] = kompanii[i];
        }
    }

    Client(Client &c) {
        strcpy(imePrezime, c.imePrezime);
        ID = c.ID;
        brKompanii = c.brKompanii;
        this->kompanii = new StockRecord[brKompanii];
        for (int i = 0; i < brKompanii; i++) {
            this->kompanii[i] = c.kompanii[i];
        }
    }

    Client &operator=(Client &c) {
        if (this != &c) {
            strcpy(imePrezime, c.imePrezime);
            ID = c.ID;
            brKompanii = c.brKompanii;
            delete[]kompanii;
            kompanii = new StockRecord[brKompanii];
            for (int i = 0; i < brKompanii; i++) {
                this->kompanii[i] = c.kompanii[i];
            }
        }
        return *this;
    }

    ~Client() {
        delete[]kompanii;
    }

    Client &operator+=(StockRecord &c) {
        StockRecord *temp = new StockRecord[brKompanii + 1];;
        for (int i = 0; i < brKompanii; i++) {
            temp[i] = kompanii[i];
        }
        temp[brKompanii] = c;
        delete[]kompanii;
        brKompanii++;
        kompanii = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, Client &client) {
        os << client.ID << " " << client.totalValue() << endl;
        for (int i = 0; i < client.brKompanii; i++) {
            cout << client.kompanii[i];
        }
        return os;
    }

    double totalValue() {
        double zbir = 0;
        for (int i = 0; i < brKompanii; i++) {
            zbir += kompanii[i].value();
        }
        return zbir;
    }
};

// ne menuvaj vo main-ot

int main() {

    int test;
    cin >> test;

    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
