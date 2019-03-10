#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <list>

using namespace std;

#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

int main(int argc, const char * argv[]) {
    string line, command, title, status;
    float price;
    int inventoryCount, units;
    TreeDB* mainList = NULL;
    
    cout << "> ";
    getline(cin, line);
    
    // Checks the input from the user and runs the appropriate command
    while (!cin.eof()) {
        stringstream lineStream (line);
        lineStream >> command;
        
        if(command == "add") {
            
            if(mainList == NULL) {
                mainList = new TreeDB;
            }
            lineStream >> title;
            lineStream.ignore(256,'$');
            lineStream >> price;
            lineStream >> inventoryCount;

            DBentry* newNode = new DBentry(title, price, inventoryCount);
            
            if(!mainList -> insert(newNode)) {
                cout << "Error: product already exists" << endl;
                delete newNode;
            } else {
                cout << "Success" << endl;
            }
            
        } else if(command == "find") {
            
            lineStream >> title;
            if(mainList == NULL || mainList -> find(title) == NULL) {
                cout << "Error: product does not exist" << endl;
            } else {
                cout << *mainList -> find(title);
            }
            
        } else if(command == "remove") {
            
            lineStream >> title;
            if(mainList == NULL || !mainList -> remove(title)) {
                cout << "Error: product does not exist" << endl;
            } else {
                cout << "Success" << endl;
            }
            
        } else if(command == "allproducts") {
            
            if(mainList != NULL) {
                cout << *mainList;
            } else {
                cout << endl;
            }
            
        } else if(command == "removeall") {
            
            delete mainList;
            mainList = NULL;
            cout << "Success" << endl;
            
        } else if(command == "countinventory") {
            
            if(mainList != NULL) {
                mainList -> countInventory();
            }
            
        } else if(command == "addinventory") {
            lineStream >> title;
            lineStream >> inventoryCount;

            if(mainList == NULL || mainList -> find(title) == NULL) {
                cout << "Error: product does not exist" << endl;
            } else {
                mainList -> find(title) -> setInventory(inventoryCount);
                cout << "Success" << endl;
            }
            
        } else if(command == "purchase") {
            lineStream >> title;
            lineStream >> units;
            
            if(mainList == NULL || mainList -> find(title) == NULL) {
                cout << "Error: product does not exist" << endl;
            } else {
                mainList -> find(title) -> purchaseUnits(title, units);
                if(mainList -> find(title) -> getInventory() == 0) {
                    mainList -> remove(title);
                }
                
            }
        } else if(command == "cart") {
            cout << "Type the name of the product then the quantity (e.g. iPad 50)" << endl;
            cout << "Type in 'done' to proceed." << endl;
            
            cout << "> ";
            getline(cin, line);
            
            list<string> cartItems;
            list<int> cartItemsUnits;
            float totalCost = 0;
            
            while(line != "done") {
                stringstream lineStream (line);
                lineStream >> title;
                lineStream >> units;
                
                
                if(mainList == NULL || mainList -> find(title) == NULL) {
                    cout << "Error: product does not exist" << endl;
                } else if(mainList -> find(title) -> getInventory() < units) {
                    cout << "Error: number of units entered exceeds units in the inventory. Try again." << endl;
                } else {
                    totalCost = totalCost + (mainList -> find(title) -> getPrice())*units;
                    cartItems.push_back(title);
                    cartItemsUnits.push_back(units);
                }
                
                cout << "> ";
                getline(cin, line);
            }
            list<string>::iterator i = cartItems.begin();
            list<int>::iterator k = cartItemsUnits.begin();
            
            for(; i != cartItems.end() && k != cartItemsUnits.end(); i++, k++) {
                cout << "Product: " << *i << " Units: " << *k << endl;
            }
            cout << "Total Cost: $" << totalCost << endl;
            cout << "Proceed? Enter 'y' to continue or 'n' to close the cart" << endl;
            
            cout << "> ";
            getline(cin, line);
            stringstream lineStream (line);
            lineStream >> command;
            
            if(command == "y") {
                
                list<string>::iterator i = cartItems.begin();
                list<int>::iterator k = cartItemsUnits.begin();
                
                for(; i != cartItems.end() && k != cartItemsUnits.end(); i++, k++) {
                    mainList -> find(*i) -> purchaseUnits(*i, *k);
                    if(mainList -> find(*i) -> getInventory() == 0) {
                        mainList -> remove(*i);
                    }
                }
            }
            
            cout << "Successfuly purchased!" << endl;
            
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
        cout << "> ";
        getline(cin, line);
    }
    delete mainList;
    mainList = NULL;
    return 0;
}
