#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

class Book {
protected:
    char isbn[20];
    char naslov[50];
    char avtor[30];
    float cena;
public:
    virtual float bookPrice() = 0;

    bool operator>(const Book &rhs) const {
        if (cena > rhs.cena)
            return true;
        return false;
    }

    friend ostream &operator<<(ostream &os, Book &book) {
        os << book.isbn << ": " << book.naslov << ", " << book.avtor << " " << book.bookPrice() << endl;
        return os;
    }

    void setISBN(char isbn[20]) {
        strcpy(this->isbn, isbn);
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int golemina;
public:
    OnlineBook(char isbn[20], char naslov[50], char avtor[30], float cena, char *url, int golemina) {
        strcpy(this->isbn, isbn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena = cena;
        this->golemina = golemina;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    float bookPrice() {
        if (golemina > 20)
            return cena * 1.20f;
        return cena;
    }
};

class PrintBook : public Book {
private:
    float masa;
    bool zaliha;
public:
    PrintBook(char isbn[20], char naslov[50], char avtor[30], float cena, float masa, bool zaliha) {
        strcpy(this->isbn, isbn);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena = cena;
        this->masa = masa;
        this->zaliha = zaliha;
    }

    float bookPrice() {
        if (masa > 0.7)
            return cena * 1.15f;
        return cena;
    }
};

void mostExpensiveBook(Book **books, int n) {
    cout << "FINKI-Education" << endl;
    int c1 = 0, c2 = 0, indeks;
    float max = INT_MIN;
    for (int i = 0; i < n; i++) {
        Book *temp = dynamic_cast<OnlineBook *>(books[i]);
        if (!temp) {
            c1++;
        } else
            c2++;
        if (max < books[i]->bookPrice()) {
            indeks = i;
            max = books[i]->bookPrice();
        }
    }
    cout << "Total number of online books: " << c2 << endl;
    cout << "Total number of print books: " << c1 << endl;
    cout << "The most expensive book is: " << endl << *books[indeks];
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
