#include<iostream>
#include<cstring>

using namespace std;
enum Extension {
    pdf, txt, exe
};

class File {
    char *imeDatoteka, *imeSopstvenik;
    Extension ekstenzija;
    int golemina;

    friend class Folder;

public:
    File() {
        imeDatoteka = nullptr;
        imeSopstvenik = nullptr;
        ekstenzija = txt;
        golemina = 0;
    }

    File(char *imeDatoteka, char *imeSopstvenik, int golemina, Extension ekstenzija) {
        this->imeDatoteka = new char[strlen(imeDatoteka) + 1];
        this->imeSopstvenik = new char[strlen(imeSopstvenik) + 1];
        strcpy(this->imeDatoteka, imeDatoteka);
        strcpy(this->imeSopstvenik, imeSopstvenik);
        this->golemina = golemina;
        this->ekstenzija = ekstenzija;
    }

    File(const File &f) {
        this->imeDatoteka = new char[strlen(f.imeDatoteka) + 1];
        this->imeSopstvenik = new char[strlen(f.imeSopstvenik) + 1];
        strcpy(this->imeDatoteka, f.imeDatoteka);
        strcpy(this->imeSopstvenik, f.imeSopstvenik);
        this->golemina = f.golemina;
        this->ekstenzija = f.ekstenzija;
    }

    File &operator=(const File &f) {
        if (this != &f) {
            delete[]imeDatoteka;
            delete[]imeSopstvenik;
            this->imeDatoteka = new char[strlen(f.imeDatoteka) + 1];
            this->imeSopstvenik = new char[strlen(f.imeSopstvenik) + 1];
            strcpy(this->imeDatoteka, f.imeDatoteka);
            strcpy(this->imeSopstvenik, f.imeSopstvenik);
            this->golemina = f.golemina;
            this->ekstenzija = f.ekstenzija;
        }
        return *this;
    }

    ~File() {
        delete[]imeDatoteka;
        delete[]imeSopstvenik;
    }

    void print() {
        cout << "File name: " << imeDatoteka << ".";
        switch (ekstenzija) {
            case 1:
                cout << "txt" << endl;
                break;
            case 0:
                cout << "pdf" << endl;
                break;
            case 2:
                cout << "exe" << endl;
                break;
        }
        cout << "File owner: " << imeSopstvenik << endl;
        cout << "File size: " << golemina << endl;
    }

    bool equals(const File &that) {
        if (!strcmp(imeDatoteka, that.imeDatoteka) && !strcmp(imeSopstvenik, that.imeSopstvenik) &&
            ekstenzija == that.ekstenzija) {
            return true;
        }
        return false;
    }

    bool equalsType(const File &that) {
        if (!strcmp(imeDatoteka, that.imeDatoteka) && ekstenzija == that.ekstenzija)
            return true;
        return false;
    }
};

class Folder {
    char *ime;
    int brDatoteki;
    File *datoteki;
public:
    Folder(const char *name) {
        ime = new char[strlen(name) + 1];
        strcpy(ime, name);
        brDatoteki = 0;
        datoteki = nullptr;
    }

    ~Folder() { delete[]datoteki; }

    void print() {
        cout << "Folder name: " << ime << endl;
        for (int i = 0; i < brDatoteki; i++) {
            datoteki[i].print();
        }
    }

    void remove(const File &file) {
        for (int i = 0; i < brDatoteki; i++) {
            if (datoteki[i].equals(file)) {
                for (int j = i; j < brDatoteki - 1; j++) {
                    File temp1 = datoteki[j];
                    datoteki[j] = datoteki[j + 1];
                    datoteki[j + 1] = temp1;
                }
                File *temp = new File[brDatoteki - 1];
                for (int j = 0; j < brDatoteki - 1; j++) {
                    temp[j] = datoteki[j];
                }
                delete[]datoteki;
                brDatoteki--;
                datoteki = temp;
                break;
            }
        }
    }

    void add(const File &file) {
        File *temp = new File[brDatoteki + 1];
        for (int i = 0; i < brDatoteki; i++) {
            temp[i] = datoteki[i];
        }
        temp[brDatoteki] = file;
        delete[]datoteki;
        brDatoteki++;
        datoteki = temp;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
