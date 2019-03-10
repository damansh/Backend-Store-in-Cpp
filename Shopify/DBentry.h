#ifndef _DBENTRY_H
#define _DBENTRY_H

#include <string>
using namespace std;

class DBentry {
private:
	string title;
    float price;
    int inventoryCount;

public:
	DBentry();
    DBentry(string _title, float _price, int _inventoryCount);

 	~DBentry();

	void setTitle(string _title);

	void setPrice(float _price);
    
    void setInventory (int _inventoryCount);

	string getTitle() const;

    float getPrice() const;

    int getInventory () const;
    
    void purchaseUnits(string title, int units);

    friend ostream& operator<< (ostream& out, const DBentry& rhs);
};

#endif 

