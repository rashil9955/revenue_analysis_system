//
//  main.cpp
//  assign_5
//
//  Created by Rashil Shibakoti on 3/18/24.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;


//defining enumerated type
enum kind {
    FLOWER,
    VEGETABLE,
    GRASS,
    SHRUB,
};

// Array of strings corresponding to each enum value
const string plantTypes[] = {
    "FLOWER",
    "VEGETABLE",
    "GRASS",
    "SHRUB"
};

//create a structure data set
struct info{
    string name;
    kind type;
    float cost;
    int qty_avail;
    int qty_ordered;
};


// Function prototype
void processOption(info plant[], int option, int &type, float total[], int &item_num, int &item_quant, float &tax);
void printTableHeader();
void displayTable(info plant[], int &option, int &type, float total[]);
void FilterTable(info plant[], int &option, int &type);
void PurchaseItems(info plant[], int &option, int &item_num, int &item_quant, float &tax, float total[]);
void Checkout(info plant[], int &option, int &item_num, int &item_quant, int &type, float &tax, float total[]);


//constant declerations
const int SIZE = 10;
const int ARRAY_SIZE = SIZE + 1;
const float TAX_PERCENT = 0.07;












int main() {
    
    
    //declaring variables used throughout the program
    int option;
    int item_num = 0;
    int item_quant = 0;
    int type = 5;
    float tax = 0.0;
    
    //initialize the array
    float total[ARRAY_SIZE] = {0};
    
    

    
    
    // store the data into the structure array
    info plant[SIZE] = {
        {"Purple Iris", FLOWER, 10.50, 25, 0},
        {"Fuschia Peony", FLOWER, 24.99,  15, 0},
        {"Orange Day Lily", FLOWER, 14.50, 25, 0},
        {"Beefsteak Tomato", VEGETABLE, 4.50, 40, 0},
        {"Butternut Squash", VEGETABLE, 3.50, 25, 0},
        {"Jalapeno Pepper", VEGETABLE, 2.99, 30, 0},
        {"Striped Lemon Grass", GRASS, 10.50, 15, 0},
        {"Blue Spike", GRASS, 8.50, 40, 0},
        {"Everbearing Raspberry", SHRUB, 7.50, 25, 0},
        {"Hardy Blueberry", SHRUB, 25.99, 15, 0}
    };
    
    
    
    
    do {
        
        //display the table with all plants
        displayTable(plant, option, type, total);

        //display the menu
        cout << " _______________________" << endl << endl;
        cout << "  1. Filter the table. " << endl;
        cout << "  2. Purchase Items " << endl;
        cout << "  3. Checkout " << endl;
        cout << "  4. Exit " << endl;
        cout << endl;
        cout << "select an option >> ";
        cin >> option;
        cout << endl << endl;
        
        //a function to process the option
        processOption(plant, option, type, total, item_num, item_quant, tax);
        
        //error handling
        //when the user chooses the fourth option, exit the loop
        //which will complete the program, and end the program
        } while (option != 4 );
    
return 0;
    
}








void processOption(info plant[], int option, int &type, float total[], int &item_num, int &item_quant, float&tax) {
    
    //call the functions as per the choice of the user
    
    
    switch (option) {
        case 1:
            FilterTable(plant, option, type);
            break;
        case 2:
            PurchaseItems(plant, option, item_num, item_quant, tax, total);
            break;
        case 3:
            Checkout(plant, option, item_num, item_quant, type, tax, total);
            
            cout << "Press Enter to continue...";
            
            
                while (cin.get() != '\n') {
                    
                }
                cin.get();
            
            
            
            cout << endl << endl << endl;
            
            
            break;
        case 4:
            exit(0);
            break;
            
        default:
            //clear the input buffer
            cin.clear();
            //ignore upto 100 new line character until a new line is encountered
            cin.ignore(100, '\n');
            cout << "Enter a valid option! (1 - 4)" << endl;
            
    }
}



void printTableHeader() {
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    
    //display the header to print the data table.
    cout << setw(5) << left << "S.N." ;
    cout << setw(25) << left << "Plant Name" ;
    cout << setw(15) << left<< "Type" ;
    cout << setw(10) << right<< "Cost" ;
    cout << setw(15) << right<< "Qty Avail" ;
    cout << setw(15) << right<<"Qty Ordered" ;
    cout << setw(15) << right<< "Total" ;
    cout << endl;
  
    
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << endl;
    
}









void displayTable(info plant[], int &option, int &type, float total[]){
    
    
        //calls the function to print the table header
        printTableHeader();
    
        //displays the type of the plant the user wants
            //if not, prints ALL plants as the default value for type is given
    
        switch(type){
            case 1:
                
                for(int x = 0; x < SIZE; x++){
                    if(plant[x].type == FLOWER){
                        cout << setw(5) << left << x+1;
                        cout << setw(25) << left << plant[x].name;
                        cout << setw(15) << left << plantTypes[plant[x].type];
                        cout << setw(10) << fixed << setprecision(2) << right << plant[x].cost;
                        cout << setw(15) << right << plant[x].qty_avail;
                        cout << setw(15) << right << plant[x].qty_ordered;
                        cout << setw(15) << right << total[x];
                        
                        cout << endl;
                        
                    }
                    
                }
                
                //displays the grand total just below the total column
                cout << setw(95)<<"Grand Total: ";
                cout << setw(5) << fixed << right << setprecision(2) << total[ARRAY_SIZE-1] << endl;
                cout << setw(100)<<"------------------";
                break;
                
                
            case 2:
                for(int x = 0; x < SIZE; x++){
                    if(plant[x].type == VEGETABLE){
                        cout << setw(5) << left << x+1;
                        cout << setw(25) << left << plant[x].name;
                        cout << setw(15) << left << plantTypes[plant[x].type];
                        cout << setw(10) << fixed << setprecision(2) << right << plant[x].cost;
                        cout << setw(15) << right << plant[x].qty_avail;
                        cout << setw(15) << right << plant[x].qty_ordered;
                        cout << setw(15) << right << total[x];
                        
                        cout << endl;
                        
                    }
                    
                }
                cout << setw(95)<<"Grand Total: ";
                cout << setw(5) << fixed << right << setprecision(2) << total[ARRAY_SIZE-1] << endl;
                cout << setw(100)<<"------------------";
                break;
                
                
            case 3:
                for(int x = 0; x < SIZE; x++){
                    if(plant[x].type == GRASS){
                        cout << setw(5) << left << x+1;
                        cout << setw(25) << left << plant[x].name;
                        cout << setw(15) << left << plantTypes[plant[x].type];
                        cout << setw(10) << fixed << setprecision(2) << right << plant[x].cost;
                        cout << setw(15) << right << plant[x].qty_avail;
                        cout << setw(15) << right << plant[x].qty_ordered;
                        cout << setw(15) << right << total[x];
                        
                        cout << endl;
                        
                    }
                    
                    
                }
                cout << setw(95)<<"Grand Total: ";
                cout << setw(5) << fixed << right << setprecision(2) << total[ARRAY_SIZE-1] << endl;
                cout << setw(100)<<"------------------";
                break;
                
                
            case 4:
                for(int x = 0; x < SIZE; x++){
                    if(plant[x].type == SHRUB){
                        cout << setw(5) << left << x+1;
                        cout << setw(25) << left << plant[x].name;
                        cout << setw(15) << left << plantTypes[plant[x].type];
                        cout << setw(10) << fixed << setprecision(2) << right << plant[x].cost;
                        cout << setw(15) << right << plant[x].qty_avail;
                        cout << setw(15) << right << plant[x].qty_ordered;
                        cout << setw(15) << right << total[x];
                        
                        cout << endl;
                        
                    }
                    
                    
                }
                cout << setw(95)<<"Grand Total: ";
                cout << setw(5) << fixed << right << setprecision(2) << total[ARRAY_SIZE-1] << endl;
                cout << setw(100)<<"------------------";
                break;
                
                
            case 5:
                for(int x = 0; x < SIZE; x++){
                    cout << setw(5) << left << x+1;
                    cout << setw(25) << left << plant[x].name;
                    cout << setw(15) << left << plantTypes[plant[x].type];
                    cout << setw(10) << fixed << setprecision(2) << right << plant[x].cost;
                    cout << setw(15) << right << plant[x].qty_avail;
                    cout << setw(15) << right << plant[x].qty_ordered;
                    cout << setw(15) << right << total[x];
                    
                    cout << endl;
                    
                }
                cout << setw(95)<<"Grand Total: ";
                cout << setw(5) << fixed << right << setprecision(2) << total[ARRAY_SIZE-1] << endl;
                cout << setw(100)<<"------------------";
                
                break;
                
                
            default:
                //if the input is invalid, clear the input buffer and display an error message
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid Input!";
                cout << endl;
                cout << endl;
    }
    
    cout << endl;
    cout << endl;
    
}














void FilterTable(info plant[], int &option, int &type){
    
    //asks the user for options to filter the menu
    
    cout << endl;
    cout << endl;
    cout << "    | Choose any one type of plants. " << endl;
    cout << "    | 1. Flower" << endl;
    cout << "    | 2. Vegetable" << endl;
    cout << "    | 3. Grass" << endl;
    cout << "    | 4. Shrub" << endl;
    cout << "    | 5. All" << endl;
    cout << endl << endl;
    
    do {
        cout << "Select a plant type (1 - 5): ";
        cin >> type;
        cin.clear();
        cin.ignore(1000, '\n');
        
        //error handling
        if (type < 1 || type > 5) {

            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
        }
    } while (type < 1 || type > 5);
    
    cout << endl;
    
    
}






void PurchaseItems(info plant[], int &option, int &item_num, int &item_quant, float &tax, float total[]){
    
    
    //ask user to select item number and amount of that item number to purchase
    do {
        cout << "Select an Item Number: ";
        cin >> item_num;
        cin.clear();
        cin.ignore(100, '\n');
        
        //validate the number user input is in between the range we have
        if (item_num < 1 || item_num > 10) {
            cout << endl;
            cout << "Invalid input. Please enter a number between 1 and " << SIZE << "." << endl;
            
        }
        
        //run the loop until the user inputs a valid number
    } while (item_num < 1 || item_num > 10);
    item_num = item_num - 1;
    
    
    
    
    
    
    cout << "Enter the quantity: ";
    cin >> item_quant;
    
    
    
    //if the amount user entered is available, update the table
    if (item_quant < plant[item_num].qty_avail+1 && plant[item_num].qty_avail > plant[item_num].qty_ordered){
            
        plant[item_num].qty_ordered = plant[item_num].qty_ordered + item_quant;
        
        cout << "  -------------  ITEM ADDED  -------------  " << endl << endl;
        cout << "Press Enter to continue...";
        
        
            while (cin.get() != '\n') {
                
            }
            cin.get();
        cout << endl << endl;
    }
    
    else{

        //if it is not available, display an error message
        cout << "-------------------------------------------------------" << endl;
        
        
        

        
        cout << endl << endl;
        cout << item_quant <<  " amount of " << plant[item_num].name  << " not available.";
        cout << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "Press Enter to continue...";
        
        
            while (cin.get() != '\n') {
                
            }
            cin.get();
        cout << endl << endl;
        
        //exit the further processing if the quantity is not available
        return;
    }
    
     //update the total array
            //multiply the unit cost with the amount ordered and pass the value to the total array
                //multiply with item quantity does not overlap the cost again
    total[item_num] = total[item_num] + (plant[item_num].cost * item_quant);
    

    
    //add the total cost to the last element of the array
        //which represents the grand total cost.
    total[ARRAY_SIZE-1] = total[ARRAY_SIZE-1] + (plant[item_num].cost * item_quant);


    
    //update the value for tax each time the user adds another plant
    tax = tax + (TAX_PERCENT * plant[item_num].cost);
    

        //it would print (0.07) even though the user did not buy anything.
            //so, if the number of items user bought is zero, the tax is set to zero
    if (total[ARRAY_SIZE - 1] == 0){
        tax = 0;
    }
    

    
    cout << endl << endl;
    
}





void Checkout(info plant[], int &option, int &item_num, int &item_quant, int &type, float &tax, float total[]){
    
    
    
    
    
    
    
    //displays output message
    
    
    cout << "  -------------  CHECKOUT  -------------  " << endl << endl;
    
    
    cout << "Purchased Items: " << endl << endl;
    
    for(int x = 0; x < SIZE; x++){
        
        if (plant[x].qty_ordered > 0) {
            
            cout <<  "   | ";
            
            cout << plant[x].name << endl << endl;
            
        }
    }
        
        
        cout << "      Subtotal :       " << total[ARRAY_SIZE-1]<< endl;
        
        cout << "      Tax(7.0%) :      " << tax << endl;
        
        //after the subtotal and the tax amount is displayed
        //the last element of the array is refreshed again adding together
        //the tax amount and the total cost
        
        total[ARRAY_SIZE-1] = total[ARRAY_SIZE-1] + tax;
        
        cout << "      Total :          " << total[ARRAY_SIZE-1] << endl << endl;
        
        cout << " ---------------------------------------- " << endl << endl << endl;
        
        
        
        //reduce the number of quantity available by the number of quantity the user ordered
        //set the quantity ordered to zero
        //set the "total" array to zero
        for(int x = 0; x < SIZE; x++){
            plant[x].qty_avail = plant[x].qty_avail - plant[x].qty_ordered;
            plant[x].qty_ordered = 0;
            total[x] = 0;
        }
        
        
        //set the last element of the array
        //which represents the grand total, to zero
        total[ARRAY_SIZE-1] = 0;
        
        
        //set type to 5
        //so that, the table is not filtered
        //and the table shows the value for all the elements.
        type = 5;
        
        cout << endl << endl << endl;
        
        
    }
    
 
