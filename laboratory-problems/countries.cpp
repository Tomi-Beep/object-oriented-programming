#include <iostream>
#include <cstring>

using namespace std;

class Country {
    char name[100], capital[100];
    float area, population;
public:
    Country() {}

    Country(char *n, char *c, float a, float p) {
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }

    ~Country() {};

    const char *getName() const {
        return name;
    }

    const char *getCapital() const {
        return capital;
    }

    float getArea() const {
        return area;
    }

    float getPopulation() const {
        return population;
    }

    void setArea(float area) {
        Country::area = area;
    }

    void setPopulation(float population) {
        Country::population = population;
    }

    void setName(char *n) {
        strcpy(name, n);
    }

    void setCapital(char *n) {
        strcpy(capital, n);
    }

    void display() {
        cout << "Country: " << name << endl << "Capital: " << capital << endl << "Area: "
             << area << endl << "Population: " << population << endl;
    }
};

void sortCountries(Country *countries, int n) {
    Country c;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i; j < n; ++j) {
            if (countries[i].getArea() > countries[j].getArea()) {
                c = countries[j];
                countries[j] = countries[i];
                countries[i] = c;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        countries[i].display();
    }
}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> capital;
        cin >> area;
        cin>>population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> capital;
    cin >> area;
    cin>>population;
    countries[n-1].setName(name);
    countries[n-1].setCapital(capital);
    countries[n-1].setArea(area);
    countries[n-1].setPopulation(population);

    cout<<"-->Testing set methods and display()"<<endl;
    countries[n-1].display();
    cout<<endl;

    cout<<"-->Testing sortCountries()"<<endl;
    sortCountries(countries,n);
    return 0;
}
