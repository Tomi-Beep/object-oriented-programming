#include <iostream>
#include <cstring>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class BasketballPlayer {
private:
    char name[20];
    char last[20];
    int number;
    int points_1, points_2, points_3;
public:
    BasketballPlayer() {
    }

    BasketballPlayer(char n[], char l[], int num, int p1, int p2, int p3) {
        strcpy(name, n);
        strcpy(last, l);
        number = num;
        points_1 = p1;
        points_2 = p2;
        points_3 = p3;
    }

    ~BasketballPlayer(){};

    const char *getName() const {
        return name;
    }

    const char *getLast() const {
        return last;
    }

    int getNumber() const {
        return number;
    }

    int getPoints1() const {
        return points_1;
    }

    int getPoints2() const {
        return points_2;
    }

    int getPoints3() const {
        return points_3;
    }

    void setNumber(int number) {
        BasketballPlayer::number = number;
    }

    void setPoints1(int points1) {
        points_1 = points1;
    }

    void setPoints2(int points2) {
        points_2 = points2;
    }

    void setPoints3(int points3) {
        points_3 = points3;
    }

    void setName(char n[]) {
        strcpy(name, n);
    }

    void setLast(char l[]) {
        strcpy(last, l);
    }

    void print() {
        cout << "Player: " << name << " " << last << " with number: " << number << " has "
             << ((float) points_1 + (float) points_2 + (float) points_3) / 3<<" points on average";
    }
};


int main() {
    char name[20], last[20];
    int number, p1, p2, p3;
    cin >> name >> last >> number >> p1 >> p2 >> p3;
    BasketballPlayer player(name, last, number, p1, p2, p3);
    player.print();
    return 0;
}
