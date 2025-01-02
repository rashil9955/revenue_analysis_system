// Include necessary libraries for input/output, file handling, and string manipulation
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

// Define an enumeration for the different types of plants
enum Kind { FLOWER, VEGETABLE, GRASS, SHRUB };

// Define an enumeration for the different operations that can be performed
enum Operation { ADD, PRINT, EDIT, EDIT_ONE, EXIT };

// Define a structure to represent a plant
struct Plant {
    string name;
    Kind type;
    double cost;
    int qty_avail;
};





// Function prototypes
void displaymenu(int &choiceInt);
void addRecord(fstream& file);
void printAll(fstream& file);
void editQuantities(fstream& file);
void editOneRecord(fstream& file);




int main() {
    
    
    int choiceInt;
    
    
    // Open the file in binary mode for reading and writing
    fstream file("/Users/rashilci132a/Desktop/CSC250/CS250_ASS/Assignment_6/plants.dat", ios::in | ios::out | ios::binary);

    
    
    // If the file doesn't exist, create it
    if (!file) {
        
        file.open("/Users/rashilci132a/Desktop/CSC250/CS250_ASS/Assignment_6/plants.dat", ios::out | ios::binary);
        if (!file) {
            
            
            cout << "Failed to create file." << endl;
            return 1;
        }
        
        
        file.close();
        
        
        
        
        file.open("/Users/rashilci132a/Desktop/CSC250/CS250_ASS/Assignment_6/plants.dat", ios::in | ios::out | ios::binary);
    }
    

    Operation choice;

    // Loop until the user chooses to exit
    do {
        
        
        // Display the menu and get the user's choice
        
        displaymenu(choiceInt);
        
        choice = static_cast<Operation>(choiceInt - 1);

        
        
        // Perform the selected operation
        switch (choice) {
            case ADD:
                addRecord(file);
                break;
                
            case PRINT:
                printAll(file);
                break;
                
                
            case EDIT:
                editQuantities(file);
                break;
                
            case EDIT_ONE:
                editOneRecord(file);
                
                break;
                
            case EXIT:
                cout << "Exiting the program." << endl;
                break;
                
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != EXIT);

    // Close the file before exiting the program
    file.close();

    return 0;
}







// Function to display the menu and get the user's choice
void displaymenu(int &choiceInt) {
    cout << endl;
    cout << "- ------- Menu ------- -" << endl;
    cout << endl;
    cout << "1. Add a Record" << endl;
    cout << "2. Print All Records" << endl;
    cout << "3. Edit All Quantities" << endl;
    cout << "4. Edit One Record" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";

    
    
    if (!(cin >> choiceInt)) {
        
        
        cin.clear();
        cout << endl;
        cout << "Invalid input. Please enter a number." << endl << endl;
        
    }

    if (choiceInt < 1 || choiceInt > 5) {
        cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
    }
}

// Function to add a new plant record to the file
void addRecord(fstream& file) {
    Plant plant;

    // Get the plant name from the user
    cin.ignore();
    cout << "Enter plant name: ";
    getline(cin, plant.name);

    // Check if the plant name is valid
    if (plant.name.size() == 0) {
        cout << "Invalid plant name. Record not added." << endl;
        return;
    }

    // Get the plant type from the user
    cout << "Enter plant type (0: FLOWER, 1: VEGETABLE, 2: GRASS, 3: SHRUB): ";
    int typeChoice;
    cin >> typeChoice;

    // Check if the plant type is valid
    if (typeChoice < FLOWER || typeChoice > SHRUB) {
        cout << "Invalid plant type. Record not added." << endl;
        return;
    }

    // Convert the user's input to the corresponding Kind enumeration value
    plant.type = static_cast<Kind>(typeChoice);

    // Get the plant cost from the user
    cout << "Enter plant cost: ";
    cin >> plant.cost;

    // Check if the plant cost is valid
    if (plant.cost <= 0) {
        cout << "Invalid plant cost. Record not added." << endl;
        return;
    }

    // Get the available quantity from the user
    cout << "Enter available quantity: ";
    cin >> plant.qty_avail;

    // Check if the available quantity is valid
    if (plant.qty_avail < 0) {
        cout << "Invalid available quantity. Record not added." << endl;
        return;
    }

    // Check if the file is in a valid state
    if (!file.good()) {
        cout << "Error: File is not in a valid state. Record not added." << endl;
        return;
    }

    // Move the file pointer to the end of the file
    file.seekp(0, ios::end);

    // Write the plant record to the file
    file.write(reinterpret_cast<char*>(&plant), sizeof(Plant));
    file.flush();

    cout << "Record added successfully." << endl;
}

// Function to print all the plant records in the file
void printAll(fstream& file) {
    // Reset file pointer to the beginning of the file
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    Plant plant;

    // Print the header for the plant records
    cout << left << setw(20) << "Name" << setw(15) << "Type" << setw(10) << "Cost" << setw(10) << "Quantity" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Read and print records from the file
    while (file.read(reinterpret_cast<char*>(&plant), sizeof(Plant))) {
        // Skip records with invalid data
        if (plant.name.size() == 0 || plant.cost <= 0 || plant.qty_avail <= 0) {
            continue;
        }

        // Print the plant name
        cout << left << setw(20) << plant.name;

        // Print the plant type
        switch (plant.type) {
            case FLOWER:
                cout << setw(15) << "FLOWER";
                break;
            case VEGETABLE:
                cout << setw(15) << "VEGETABLE";
                break;
            case GRASS:
                cout << setw(15) << "GRASS";
                break;
            case SHRUB:
                cout << setw(15) << "SHRUB";
                break;
        }

        // Print the plant cost and available quantity
        cout << setw(10) << fixed << setprecision(2) << plant.cost;
        cout << setw(10) << plant.qty_avail << endl;
    }

    // Check for errors while reading
    if (!file.eof() && file.fail()) {
        cout << "Error occurred while reading from file." << endl;
    }
}

// Function to edit the quantities of plant records in the file
void editQuantities(fstream& file) {
    // Reset file pointer to the beginning of the file
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    Plant plant;
    int linenumber = 0; // Initialize line number counter

    // Print the header for the plant records
    cout << left << setw(10) << "S.N" << setw(20) << "Name" << setw(15) << "Type" << setw(10) << "Cost" << setw(10) << "Quantity" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Read and print records from the file
    while (file.read(reinterpret_cast<char*>(&plant), sizeof(Plant))) {
        // Skip records with invalid data
        if (plant.name.empty() || plant.cost <= 0 || plant.qty_avail <= 0) {
            continue;
        }

        linenumber++; // Increment line number for each valid record

        // Print the line number
        cout << setw(10) << linenumber;

        // Print the plant name
        cout << left << setw(20) << plant.name;

        // Print the plant type
        switch (plant.type) {
            case FLOWER:
                cout << setw(15) << "FLOWER";
                break;
            case VEGETABLE:
                cout << setw(15) << "VEGETABLE";
                break;
            case GRASS:
                cout << setw(15) << "GRASS";
                break;
            case SHRUB:
                cout << setw(15) << "SHRUB";
                break;
        }

        // Print the plant cost and available quantity
        cout << setw(10) << fixed << setprecision(2) << plant.cost;
        cout << setw(10) << plant.qty_avail << endl;
    }

    // Reset file pointer to the beginning of the file before editing quantities
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    // Check if no records found
    if (linenumber == 0) {
        cout << "No records found." << endl;
        return;
    }

    // Get the line number of the record to edit from the user
    int lineToEdit;
    cout << endl << "Enter the line number to edit (or 0 to cancel): ";
    cin >> lineToEdit;

    // Check if the line number is valid
    if (lineToEdit < 1 || lineToEdit > linenumber) {
        cout << "Invalid line number. Please enter a valid line number." << endl;
        return;
    }

    // Calculate the position to seek for the record to edit
    int newPos = (lineToEdit - 1) * sizeof(Plant);

    // Move the file pointer to the position of the record to edit
    file.seekp(newPos, ios::beg);

    // Read the plant record at the current position
    file.read(reinterpret_cast<char*>(&plant), sizeof(Plant));

    // Prompt for new quantity and update the record
    cout << "Enter new quantity for " << plant.name << ": ";
    int newQuantity;
    cin >> newQuantity;

    // Check if the new quantity is valid
    if (newQuantity < 0) {
        cout << "Invalid quantity. Quantity not updated." << endl;
        return;
    }

    // Update the quantity of the plant record
    plant.qty_avail = newQuantity;

    // Move the file pointer back to the position of the record to update
    file.seekp(newPos, ios::beg);

    // Write the updated plant record to the file
    file.write(reinterpret_cast<char*>(&plant), sizeof(Plant));
    cout << "Quantity updated successfully." << endl;
}


// Function to edit a single plant record in the file

/*
void editOneRecord(fstream& file) {
    
    // Reset file pointer to the beginning of the file
    file.clear(); // Clear any error flags
    
    file.seekg(0, ios::beg);

    Plant plant;
    int linenumber = 0; // Initialize line number counter

    // Print the header for the plant records
    cout << left << setw(10) << "S.N" << setw(20) << "Name" << setw(15) << "Type" << setw(10) << "Cost" << setw(10) << "Quantity" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Read and print records from the file
    while (file.read(reinterpret_cast<char*>(&plant), sizeof(Plant))) {
        // Skip records with invalid data
        if (plant.name.empty() || plant.cost <= 0 || plant.qty_avail <= 0) {
            continue;
        }

        linenumber++; // Increment line number for each valid record

        // Print the line number
        cout << setw(10) << linenumber;

        // Print the plant name
        cout << left << setw(20) << plant.name;

        // Print the plant type
        switch (plant.type) {
            case FLOWER:
                cout << setw(15) << "FLOWER";
                break;
            case VEGETABLE:
                cout << setw(15) << "VEGETABLE";
                break;
            case GRASS:
                cout << setw(15) << "GRASS";
                break;
            case SHRUB:
                cout << setw(15) << "SHRUB";
                break;
        }

        // Print the plant cost and available quantity
        cout << setw(10) << fixed << setprecision(2) << plant.cost;
        cout << setw(10) << plant.qty_avail << endl;
    }
    

    // Reset file pointer to the beginning of the file before editing the record
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    
    // Check if no records found
    if (linenumber == 0) {
        cout << "No records found." << endl;
        return;
    }

    
    
    // Get the line number of the record to edit from the user
    
    cout << "Menu";
    cout << "1. Edit plant name to edit";
    cout << "2. Edit plant type";
    cout << "3. Edit Plant Cost";
    cout << "4. Edit plant Quantity";
    cout << "5. Exit Edit Mode";
    int opop = 0;
    cin >> opop;
    
    
    switch(opop){
            
        case 0:
            int lineToEdit;
            cout << endl << "Enter the line number to edit (or 0 to cancel): ";
            cin >> lineToEdit;

            // Check if the line number is valid
            if (lineToEdit < 1 || lineToEdit > linenumber) {
                cout << "Invalid line number. Please enter a valid line number." << endl;
                return;
            }

            // Calculate the position to seek for the record to edit
            int newPos = (lineToEdit - 1) * sizeof(Plant);

            // Move the file pointer to the position of the record to edit
            file.seekp(newPos, ios::beg);

            // Read the plant record at the current position
            file.read(reinterpret_cast<char*>(&plant), sizeof(Plant));

            // Edit each field of the plant record
            cout << "Editing record for " << plant.name << endl;

            
        case 1:
            // Edit plant name
            cout << "Current plant name: " << plant.name << endl;
            cout << "Enter new plant name (or press Enter to keep current name): ";
            string newName;
            getline(cin >> ws, newName);
            if (!newName.empty()) {
                plant.name = newName;
            }
            break;
            
        case 2:
            // Edit plant type
            cout << "Current plant type: ";
            switch (plant.type) {
                case FLOWER:
                    cout << "FLOWER" << endl;
                    break;
                case VEGETABLE:
                    cout << "VEGETABLE" << endl;
                    break;
                case GRASS:
                    cout << "GRASS" << endl;
                    break;
                case SHRUB:
                    cout << "SHRUB" << endl;
                    break;
            }
            cout << "Enter new plant type (0: FLOWER, 1: VEGETABLE, 2: GRASS, 3: SHRUB): ";
            int newType;
            cin >> newType;
            if (newType >= FLOWER && newType <= SHRUB) {
                plant.type = static_cast<Kind>(newType);
            }
            break;
            
        case 3:
            // Edit plant cost
            cout << "Current plant cost: " << plant.cost << endl;
            cout << "Enter new plant cost (or -1 to keep current cost): ";
            double newCost;
            cin >> newCost;
            if (newCost > 0) {
                plant.cost = newCost;
            }
            break;
            
        case 4:
            // Edit available quantity
            cout << "Current available quantity: " << plant.qty_avail << endl;
            cout << "Enter new available quantity (or -1 to keep current quantity): ";
            int newQuantity;
            cin >> newQuantity;
            if (newQuantity >= 0) {
                plant.qty_avail = newQuantity;
            }
            break;
            
    }
    
    


    // Move the file pointer back to the position of the record to update
    file.seekp(newPos, ios::beg);

    // Write the updated plant record to the file
    file.write(reinterpret_cast<char*>(&plant), sizeof(Plant));
    cout << "Record updated successfully." << endl;
}
*/


void editOneRecord(fstream& file) {
    // Reset file pointer to the beginning of the file
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    Plant plant;
    int linenumber = 0; // Initialize line number counter

    // Print the header for the plant records
    cout << left << setw(10) << "S.N" << setw(20) << "Name" << setw(15) << "Type" << setw(10) << "Cost" << setw(10) << "Quantity" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Read and print records from the file
    while (file.read(reinterpret_cast<char*>(&plant), sizeof(Plant))) {
        // Skip records with invalid data
        if (plant.name.empty() || plant.cost <= 0 || plant.qty_avail <= 0) {
            continue;
        }

        linenumber++; // Increment line number for each valid record

        // Print the line number
        cout << setw(10) << linenumber;

        // Print the plant name
        cout << left << setw(20) << plant.name;

        // Print the plant type
        switch (plant.type) {
            case FLOWER:
                cout << setw(15) << "FLOWER";
                break;
            case VEGETABLE:
                cout << setw(15) << "VEGETABLE";
                break;
            case GRASS:
                cout << setw(15) << "GRASS";
                break;
            case SHRUB:
                cout << setw(15) << "SHRUB";
                break;
        }

        // Print the plant cost and available quantity
        cout << setw(10) << fixed << setprecision(2) << plant.cost;
        cout << setw(10) << plant.qty_avail << endl;
    }

    // Reset file pointer to the beginning of the file before editing the record
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    // Check if no records found
    if (linenumber == 0) {
        cout << "No records found." << endl;
        return;
    }

    int lineToEdit;
    cout << endl << "Enter the line number to edit (or 0 to cancel): ";
    cin >> lineToEdit;

    // Check if the line number is valid
    if (lineToEdit < 1 || lineToEdit > linenumber) {
        cout << "Invalid line number. Please enter a valid line number." << endl;
        return;
    }

    // Calculate the position to seek for the record to edit
    int newPos = (lineToEdit - 1) * sizeof(Plant);

    // Move the file pointer to the position of the record to edit
    file.seekp(newPos, ios::beg);

    // Read the plant record at the current position
    file.read(reinterpret_cast<char*>(&plant), sizeof(Plant));

    bool editComplete = false;
    while (!editComplete) {
        // Display edit menu options
        cout << endl << "Edit Menu:" << endl;
        cout << "1. Edit plant name" << endl;
        cout << "2. Edit plant type" << endl;
        cout << "3. Edit plant cost" << endl;
        cout << "4. Edit plant quantity" << endl;
        cout << "5. Exit edit mode" << endl;
        cout << "Enter your choice: ";

        int opop = 0;
        cin >> opop;

        switch (opop) {
            case 1:
                // Edit plant name
                cout << "Current plant name: " << plant.name << endl;
                cout << "Enter new plant name (or press Enter to keep current name): ";
                cin.ignore();
                getline(cin, plant.name);
                break;
            case 2:
                // Edit plant type
                cout << "Current plant type: ";
                switch (plant.type) {
                    case FLOWER:
                        cout << "FLOWER" << endl;
                        break;
                    case VEGETABLE:
                        cout << "VEGETABLE" << endl;
                        break;
                    case GRASS:
                        cout << "GRASS" << endl;
                        break;
                    case SHRUB:
                        cout << "SHRUB" << endl;
                        break;
                }
                cout << endl;
                cout << "Enter new plant type (0: FLOWER, 1: VEGETABLE, 2: GRASS, 3: SHRUB): ";
                int newType;
                cin >> newType;
                if (newType >= FLOWER && newType <= SHRUB) {
                    plant.type = static_cast<Kind>(newType);
                }
                break;
            case 3:
                // Edit plant cost
                cout << endl;
                cout << "Current plant cost: " << plant.cost << endl;
                cout << "Enter new plant cost (or -1 to keep current cost): ";
                double newCost;
                cin >> newCost;
                if (newCost > 0) {
                    plant.cost = newCost;
                }
                break;
            case 4:
                // Edit available quantity
                cout << endl;
                cout << endl;
                cout << "Current available quantity: " << plant.qty_avail << endl;
                cout << "Enter new available quantity (or -1 to keep current quantity): ";
                int newQuantity;
                cin >> newQuantity;
                if (newQuantity >= 0) {
                    plant.qty_avail = newQuantity;
                }
                break;
            case 5:
                // Exit edit mode
                editComplete = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        // Move the file pointer back to the position of the record to update
        file.seekp(newPos, ios::beg);

        // Write the updated plant record to the file
        file.write(reinterpret_cast<char*>(&plant), sizeof(Plant));
    }
    cout << endl;
    cout << "Record updated successfully." << endl;
    cout << "--------------------------------------";
    cout << endl;
}
