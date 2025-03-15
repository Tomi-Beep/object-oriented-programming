#include <iostream>
#include <cstring>

using namespace std;

class List {
    int *broevi;
    int brojNaBroevi;

    friend class ListContainer;

public:
    List(int *broevi = nullptr, int brojNaBroevi = 0) {
        this->brojNaBroevi = brojNaBroevi;
        this->broevi = new int[brojNaBroevi];
        for (int i = 0; i < brojNaBroevi; i++) {
            this->broevi[i] = broevi[i];
        }
    }

    List(const List &l) {
        this->brojNaBroevi = l.brojNaBroevi;
        this->broevi = new int[brojNaBroevi];
        for (int i = 0; i < brojNaBroevi; i++) {
            this->broevi[i] = l.broevi[i];
        }
    }

    List &operator=(const List &l) {
        if (this != &l) {
            delete[] broevi;
            this->brojNaBroevi = l.brojNaBroevi;
            this->broevi = new int[brojNaBroevi];
            for (int i = 0; i < brojNaBroevi; i++) {
                this->broevi[i] = l.broevi[i];
            }
        }
        return *this;
    }

    ~List() {
        delete[]broevi;
    }

    int sum() {
        int zbir = 0;
        for (int i = 0; i < brojNaBroevi; i++) {
            zbir += broevi[i];
        }
        return zbir;
    };

    double average() {
        double zbir = 0;
        for (int i = 0; i < brojNaBroevi; i++) {
            zbir += (double) broevi[i];
        }
        return zbir / (double) brojNaBroevi;
    };

    void pecati() {
        if (brojNaBroevi != 0)
            cout << brojNaBroevi << ": ";
        for (int i = 0; i < brojNaBroevi; i++) {
            cout << broevi[i] << " ";
        }
        if (brojNaBroevi != 0)
            cout << "sum: " << sum() << " average: " << average() << endl;
    }
};

class ListContainer {
    int brojNaListi, brojNaObidi;
    List *listi;
public:
    ListContainer(int brojNaListi = 0, int brojNaObidi = 0, List *listi = nullptr) {
        this->brojNaListi = brojNaListi;
        this->brojNaObidi = brojNaObidi;
        this->listi = new List[brojNaListi];
        for (int i = 0; i < brojNaListi; i++) {
            this->listi[i] = listi[i];
        }
    }

    ListContainer(const ListContainer &l) {
        this->brojNaListi = l.brojNaListi;
        this->brojNaObidi = l.brojNaObidi;
        this->listi = new List[brojNaListi];
        for (int i = 0; i < brojNaListi; i++) {
            this->listi[i] = l.listi[i];
        }
    }

    ListContainer operator=(const ListContainer &l) {
        if (this != &l) {
            delete[]listi;
            this->brojNaListi = l.brojNaListi;
            this->brojNaObidi = l.brojNaObidi;
            this->listi = new List[l.brojNaListi];
            for (int i = 0; i < brojNaListi; i++) {
                this->listi[i] = l.listi[i];
            }
        }
        return *this;
    }

    ~ListContainer() {
        delete[] listi;
    }

    int sum() {
        int zbir = 0;
        for (int i = 0; i < brojNaListi; i++) {
            zbir += listi[i].sum();
        }
        return zbir;
    }

    double average() {
        double counter = 0;
        for (int i = 0; i < brojNaListi; i++) {
            counter += listi[i].brojNaBroevi;
        }
        return (float) sum() / counter;
    }

    void addNewList(List l) {
        brojNaObidi++;
        bool t = true;
        for (int i = 0; i < brojNaListi; i++) {
            if (l.sum() == listi[i].sum()) {
                t = false;
                break;
            }
        }
        if (t) {
            List *temp = new List[brojNaListi + 1];
            for (int i = 0; i < brojNaListi; i++) {
                temp[i] = listi[i];
            }
            temp[brojNaListi] = l;
            delete[]listi;
            listi = temp;
            brojNaListi++;
        }

    }

    void print() {
        if (brojNaListi == 0) {
            cout << "The list is empty" << endl;
        } else {
            for (int i = 0; i < brojNaListi; i++) {
                cout << "List number: " << i + 1 << " List info: ";
                listi[i].pecati();

            }
            cout << "Sum: " << sum() << " Average: " << average() << endl;
            cout << "Successful attempts: " << brojNaListi << " Failed attempts: " << brojNaObidi - brojNaListi << endl;
        }
    }
};

int main() {

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];

        }

        List l = List(niza, n);
        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    } else {
        lc.print();
    }
    return 0;
}
