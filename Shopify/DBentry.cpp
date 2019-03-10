#include "DBentry.h"
#include <stdio.h>
#include <iostream>

using namespace std;

// Default constructor does not need to initialize any
// variable.
DBentry::DBentry() {
    
}

// This constructor creates an entry based on the three arguments
// provided.
DBentry::DBentry(string _title, float _price, int _inventoryCount) {
    title = _title;
    price = _price;
    inventoryCount = _inventoryCount;
}

// Since there are no variables that are created using the "new"
// operator, it is not necessary to utilize the "delete" operator.
DBentry::~DBentry() {
    
}

// Sets name based on the name passed to the function.
void DBentry::setTitle(string _title) {
    title = _title;
}

// Sets IP Address based on the IP Address passed to the function.
void DBentry::setPrice(float _price) {
    price = _price;
}

// Sets inventory based on the status passed to the function.
void DBentry::setInventory(int _inventoryCount)  {
    inventoryCount += _inventoryCount;
}

// Returns the title that is in the "title" string
string DBentry::getTitle() const {
    return title;
}

// Returns the price that is in the "price" variable.
float DBentry::getPrice() const {
    return price;
}

// Returns the inventory that is in the "inventoryCount" variable.
int DBentry::getInventory() const {
    return inventoryCount;
}

// Overloads the "<<" operator to display the contents of the entry
ostream& operator<< (ostream& out, const DBentry& rhs) {
    out << "Title: " << rhs.title << endl;
    out << "Price: $" << rhs.price << endl;
    out << "Inventory Count: " << rhs.inventoryCount << endl << endl;
    return out;
}

void DBentry::purchaseUnits(string title, int units) {
    if(units > inventoryCount) {
        cout << "Purchased only " << inventoryCount << " units of " << title << endl;
        cout << "Removing " << title << " from inventory" << endl;
        inventoryCount = 0;
    } else if(units == inventoryCount) {
        cout << "Purchased " << units << " units of " << title << endl;
        cout << "Removing " << title << " from inventory" << endl;
        inventoryCount = 0;
    } else {
        cout << "Purchased " << units << " units of " << title << endl;
        inventoryCount -= units;
    }
        
}
