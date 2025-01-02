//
//  main.cpp
//  ASS_4
//
//  Created by Rashil Shibakoti on 2/25/24.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int SIZE = 50;
const int COLS = 50;

// Function prototypes
int readData(string nameArray[], int intArray[], int count);
int welcome(string nameArray[], int intArray[], int count);
void sortArray(string nameArray[], int intArray[], int count);
void PrintTotalSeeds(string nameArray[], int intArray[], int count);
void SearchArray(string nameArray[], int intArray[], int count);

int main() {
    char choice;
    
    do {
        int intArray[SIZE];
        string nameArray[SIZE];
        int num = 0;
        int count = 0;
        int option = 0;
        num = 0;

        count = readData(nameArray, intArray, num);
        option = welcome(nameArray, intArray, count);

        switch(option){
            case 1:
                SearchArray(nameArray, intArray, count);
                break;
                
            case 2:
                sortArray(nameArray, intArray, count);
                
                cout << "Here are the plant details in alphabetical order... " << endl << endl << endl;
                
                cout << setw(20) << left  << "PLANT NAME";
                
                cout << setw(20) << right <<  "SEEDS PLANTED" << endl << endl;
                
                for(int x = 0; x < count; x++){
                    
                    cout << setw(20) << left  << nameArray[x];
                    cout << setw(20) << right <<  intArray[x] << endl;
                    
                }
                break;
                
            case 3:
                PrintTotalSeeds(nameArray, intArray, count);
                break;
                
            case 4:
                exit(102);
        }
        
        cout << endl << endl << endl;
        cout << "Do you want to use this program again? (Y | N): ";
        cin >> choice;
        cin.ignore();

    } while(choice == 'Y' || choice == 'y');
    
    cout << endl << endl;

    return 0;
}

int readData(string nameArray[], int intArray[], int num) {
    ifstream inFile;
    inFile.open ("/Users/rashilci132a/Desktop/CSC250/CS250_ASS/ASS_4/seeds_planted.txt");
    if(!inFile){
        cout << "Error connecting to file";
        exit(102);
    }
    
    while (num < SIZE && inFile >> intArray[num]) {
        inFile.ignore();
        getline(inFile, nameArray[num]);
        if(inFile.eof()) {
          break;
        }
        num++;
    }
    
    inFile.close();
    return num;
}

int welcome(string nameArray[], int intArray[], int count) {
    int option;
    string banner;
    for(int x = 0; x < count; x++){
        banner += nameArray[x];
        if (x < count - 1){
            banner += " ~ ";
        }
    }
    cout << endl;
    cout << banner;

    cout << endl << endl;
    cout << "_____________________________________" << endl;
    cout << "|                                   |" << endl;
    cout << "|             M E N U               |" << endl;
    cout << "|                                   |" << endl;
    cout << "|          1. Search                |" << endl;
    cout << "|          2. Print Sorted List     |" << endl;
    cout << "|          3. Print Total Plants    |" << endl;
    cout << "|          4. Exit                  |" << endl;
    cout << "|                                   |" << endl;
    cout << "|    ENTER OPTION 1, 2, 3 OR 4.     |" << endl;
    cout << "|                                   |" << endl;
    cout << "|___________________________________|" << endl;
    cout << "                            option>> ";
    
    cin >> option;
    cin.ignore();
    cout << endl << endl;
    return option;
}



void SearchArray(string nameArray[], int intArray[], int count) {
    string search;
    cout << "Enter a plant name to search: ";
    getline(cin, search);

    bool found = false;
    cout << endl;
    
    cout << setw(20) << left  << "PLANT NAME";
    cout << setw(20) << right << "SEEDS PLANTED" << endl;
    
    for (int i = 0; i < count; ++i) {
        if (nameArray[i].find(search) != string::npos) {
            cout << endl;
            cout << setw(20) << left  << nameArray[i];
            cout << setw(20) << right <<  intArray[i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << setw(20) << left  << " - NO MATCHES FOUND - ";
        cout << setw(20) << right << "- - -" << endl;
    }
    
    cout << endl;
}




void sortArray(string nameArray[], int intArray[], int count) {
    for(int x = 0; x < count - 1; x++){
        for(int y = 0; y < count - 1 - x ; y++){
            if (nameArray[y] > nameArray[y + 1]){
                swap(nameArray[y], nameArray[y + 1]);
                swap(intArray[y], intArray[y + 1]);
            }
        }
    }
}



void PrintTotalSeeds(string nameArray[], int intArray[], int count){
    int total = 0;
    
    for(int x = 0; x < count ; x++){
        cout << nameArray[x] << " has " << intArray[x] << " seeds planted. " << endl;
        total += intArray[x];
    }
    
    cout << endl;
    cout << "There are " << total << " seeds planted in total." << endl << endl;
}
