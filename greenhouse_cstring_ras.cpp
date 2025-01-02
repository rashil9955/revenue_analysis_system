//
//  main.cpp
//  ASS_4
//
//  Created by Rashil Shibakoti on 2/25/24.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string.h>
using namespace std;



const int SIZE = 50;
const int COLS = 50;

//functino prototypes
//reads the data from the file and returns the number of data read into the array
int readData(char nameArray[][COLS], int intArray[], int count);

//prints the welcome banner and returns the option user chose
int welcome(char nameArray[][COLS], int intArray[], int count);

//sorts the array in alphabetical order
void sortArray(char nameArray[][COLS], int intArray[], int count);

//prints the informations about the plants and the total number of plants
void PrintTotalSeeds(char nameArray[][COLS], int intArray[], int count);

//compares the userr input and compares it with the array
void SearchArray(char nameArray[][COLS], int intArray[], int count);




int main() {
    
    
    //variable to store user's choice
    char choice;
    
    
    // do while until the user chooses not to use the array
    do {
        int intArray[SIZE];
        char nameArray[SIZE][COLS];
        int num = 0;
        int count = 0;
        int option = 0;
        num = 0;

        
        //read data from the file
        count = readData(nameArray, intArray, num);
        
        //print the welcome banner, and get the option number the user chooses
        option = welcome(nameArray, intArray, count);

        //use switch case to operate the function the user chose
        
        
        switch(option){
            case 1:
                SearchArray(nameArray, intArray, count);
                break;
                
            case 2:
                //sorts the array
                sortArray(nameArray, intArray, count);
                
                
                // prints the sorted array in format
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
        
        //line spacing
        cout << endl << endl << endl;
        
        //prompt to ask to use again??
        cout << "Do you want to use this program again? (Y | N): ";
        cin >> choice;
        cin.ignore();
        //cin.ignore to clear the input buffer, to clear the "enter" from the input buffer


    } while(choice == 'Y' || choice == 'y');
    //repeat if the user chooses Y = for yes
    
    cout << endl << endl;

    
    return 0;

}


//function to read the data from the file.
int readData(char nameArray[][COLS], int intArray[], int num){
    
    ifstream inFile;
    //open the file
    inFile.open ("/Users/rashilci132a/Desktop/CSC250/CS250_ASS/ASS_4/seeds_planted.txt");
    
    //error display ir unable to connect to the file
    if(!inFile){
        cout << "Error connecting to file";
        exit(102);
    }
    
    // copy everything from the file to the array
    //  copy integers to one 1D array and
    //      copy the names, alpbhabets in another 2D array.
    while (num < SIZE && inFile >> intArray[num]) {
        
        
      inFile.ignore();
      inFile.getline(nameArray[num], COLS, '\r');
        
        
        if(inFile.eof()) {
          break;
        }
        

      num++;
    }
    
    //close the file
    inFile.close();
    
    return num;
}





//print the welcome banner
int welcome(char nameArray[][COLS], int intArray[], int count) {

    
    int option;
    //create an array, store contents into the 1D array, and print the array.
    
    //dynamically allocate memory.
    char *banner = new char[SIZE * COLS];
    
    
    
    int index = 0;
    for(int x = 0; x < count; x++){
        for(int y = 0; nameArray[x][y] != '\0' ; y++){
            //copy contents from the 2D array to 1D array
            banner[index++] = nameArray[x][y];
            
        }
        
        
        //print ~ in between each names
        if (x < count - 1){
            banner[index++] = ' ';
            banner[index++] = '~';
            banner[index++] = ' ';
        }
        
        
    }
    
    
    //null terminate the banner string
    banner[index] = '\0';
    cout << endl;
    
    for(int x = 0; x < 900; x++){
            cout  << banner[x];
    }

    //free the memory
    delete[] banner;
    

    
    cout << endl << endl;
    //print the menu
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
    
    
    
    //take input from the user
    cin >> option;
    //clear input buffer
    cin.ignore();
    
    
    cout << endl << endl;
    
    //return the option the user chose
    return option;
    
    
}




//search the array
void SearchArray(char nameArray[][COLS], int intArray[], int count) {
    
    //a temporary array
    char search[COLS];
    
    cout << "Enter a plant name to search: ";
    //store the user input into the temporary array.
    cin.getline(search, COLS);

    //set a variable to false
    bool found = false;
    cout << endl;
    
    //formatting display
    cout << setw(20) << left  << "PLANT NAME";
    cout << setw(20) << right <<  "SEEDS PLANTED" << endl;
    
    for (int i = 0; i < count; ++i) {
        //use strstr function to compare the arrays
        if (strstr(nameArray[i], search) != nullptr) {
            
            //if the arrays compare true, the name and the number is displayed
            cout << endl;
            cout << setw(20) << left  << nameArray[i];
            cout << setw(20) << right <<  intArray[i] << endl;
            
            found = true;
        }
    }

    
    //if not, an error message is displayed
    if (!found) {
        cout << setw(20) << left  << " - NO MATCHES FOUND - ";
        cout << setw(20) << right <<  "- - -" << endl;
    }
    
    
    cout << endl;
}





//function to sort the array
void sortArray(char nameArray[][COLS], int intArray[], int count){
    
    
    for(int x = 0; x < count - 1; x++){
        for(int y = 0; y < count - 1 - x ; y++){
            
            
            //use the string comparison array to compare the arrays
            if (strcmp(nameArray[y], nameArray[y + 1]) > 0){
                
                //f the comparison is true, swap the array.
                char temp[COLS];
                strcpy(temp, nameArray[y]);
                strcpy(nameArray[y], nameArray[y + 1]);
                strcpy(nameArray[y + 1], temp);
                
                
                //also swap the numbers of planted as these are parallel arrays.
                int tempInt = intArray[y];
                intArray[y] = intArray[y + 1];
                intArray[y + 1] = tempInt;
                
            }
        }
    }
    
}

//print the seeds
void PrintTotalSeeds(char nameArray[][COLS], int intArray[], int count){
    int total = 0;
    
    for(int x = 0; x < count ; x++){
        cout << nameArray[x] << " has " << intArray[x] << " seeds planted. " << endl;
        total = total + intArray[x];
    }
    
    cout << endl;
    cout << "There are " << total << " seeds planted in total." << endl << endl;
}


