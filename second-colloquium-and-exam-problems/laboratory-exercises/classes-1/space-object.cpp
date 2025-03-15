#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

class SpaceObject {
    char name[100], type[100];
    int distanceFromEarth;
public:
    SpaceObject() {}

    SpaceObject(char *n, char *t, int d) {
        strcpy(name, n);
        strcpy(type, t);
        distanceFromEarth = d;
    }

    ~SpaceObject(){};

    const char *getName() const {
        return name;
    }

    const char *getType() const {
        return type;
    }

    int getDistanceFromEarth() const {
        return distanceFromEarth;
    }

    void setDistanceFromEarth(int distanceFromEarth) {
        SpaceObject::distanceFromEarth = distanceFromEarth;
    }

    void setName(char *n) {
        strcpy(name, n);
    }

    void setType(char *t) {
        strcpy(type, t);
    }

    void print() {
        cout << name << " (" << type << ") - distance: " << distanceFromEarth << " light years away from Earth" << endl;
    }
};

class Alien {
    char name[100], homePlanet[100];
    int age, numObj;
    SpaceObject spaceObjects[10];
public:
    SpaceObject getObjectClosestToEarth() {
        int min = INT_MAX;
        SpaceObject r;
        for (int i = 0; i < numObj; ++i) {
            if (min > spaceObjects[i].getDistanceFromEarth()) {
                min = spaceObjects[i].getDistanceFromEarth();
                r = spaceObjects[i];
            }
        }
        return r;
    }

    void print() {
        cout << "Alien name: " << name << endl << "Alien age: " << age << endl
             << "Alien home planet: " << homePlanet << endl << "Favourite space object closest to earth: ";
        getObjectClosestToEarth().print();
    }

    Alien() {};

    Alien(char *n, int a, char *h, int num, SpaceObject *s) {
        strcpy(name, n);
        strcpy(homePlanet, h);
        age = a;
        numObj = num;
        for (int i = 0; i < numObj; ++i) {
            spaceObjects[i] = s[i];
        }
    }

    ~Alien(){};

    const char *getName() const {
        return name;
    }

    const char *getHomePlanet() const {
        return homePlanet;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        Alien::age = age;
    }

    int getNumObj() const {
        return numObj;
    }

    void setNumObj(int numObj) {
        Alien::numObj = numObj;
    }

    const SpaceObject *getSpaceObjects() const {
        return spaceObjects;
    }

    void setName(char *n) {
        strcpy(name, n);
    }

    void setHomePlanet(char *n) {
        strcpy(homePlanet, n);
    }

    void setSpaceObjects(SpaceObject *s) {
        for (int i = 0; i < numObj; ++i) {
            spaceObjects[i] = s[i];
        }
    }
};

int main() {
    char name[100], homePlanet[100];
    int age, numObj;
    cin >> name >> age >> homePlanet >> numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for (int i = 0; i < numObj; i++) {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin >> spaceObjectName >> spaceObjectType >> distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i] = SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien = Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}
