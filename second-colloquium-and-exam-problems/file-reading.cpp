#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void writeToFile() {
    ofstream outFile("text.txt");
    char c;
    while((c = cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    ifstream inFile("text.txt");
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int lowercaseCount = 0;
    int uppercaseCount = 0;
    int totalCount = 0;
    char c;

    while (inFile.get(c)) {
        if (isalpha(c)) {
            totalCount++;
            if (islower(c)) {
                lowercaseCount++;
            } else if (isupper(c)) {
                uppercaseCount++;
            }
        }
    }

    inFile.close();

    if (totalCount > 0) {
        double lowerFrequency = static_cast<double>(lowercaseCount) / totalCount;
        double upperFrequency = static_cast<double>(uppercaseCount) / totalCount;

        // Print frequencies with four decimal places
        cout << fixed;
        cout.precision(4);
        cout << upperFrequency << endl;
        cout << lowerFrequency << endl;
    } else {
        cout << "0.0000" << endl;
        cout << "0.0000" << endl;
    }

    return 0;
}
