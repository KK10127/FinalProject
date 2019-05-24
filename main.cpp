/*
 * FINAL PROJECT
 * CS 151
 * Tu 5:30-9:20 with Porto
 * Programmer: Jay Montoya
 *
 * Final Project Specifications
 *
 *  My final project is a restaurant inventory manager. In particular, a counts program. Each night at my restaurant,
 *  one of the employees is responsible for counting and reporting the amount of stock we have of each ingredient. At
 *  most corporate restaurants, the number of food items delievered can go well into the 100's, including produce,
 *  meats, seafood, frozen foods, fried foods, poultry, etc.
 *
 *  When the count's sheet is turned into management, it is automatically compared to a "levels" sheet which contains
 *  every item and what the inventory level SHOULD be at. A report is then generated and sent to the corporate office,
 *  which coordinates with delivery men and shipments.
 *
 *  TERMINOLOGY:
 *      - One unit is one bag.
 *      EX: 6 Units of fries is 6 bags of fries
 *      - One BOX contains 5 units upon delivery
 *      - One CASE contains 10 units (or 2 boxes) upon delivery
 *
 *  ALGORITHM FOR MAIN:
 *      1. Declare three arrays, one for the item names, their needed stock levels,
 *          and the units they come shipped in.
 *      2. Open the output file stream 'counts.dat' in binary, read, and write mode.
 *      3. For each spot in the arrays of inventory items.
 *          4. Ask the user for the units in house for the item.
 *          5. Create an Inventory item (depending on if its boxed or cased)
 *              - use the 'units' array to determine which object to create.
 *          6. IF the item comes boxed
 *              - Create the boxed inventory item.
 *              - Call 'calculateShippingUnitsNeeded()'
 *              - write the object to the filestream
 *          7. ELSE IF the item comes CASED
 *              - Create the cased inventory item
 *              - Call 'CalculateShippingUnitsNeeded'
 *              - write the object to the filestream
 *          8. Flush the stream
 *
 *     NOW READ THE COUNTS BACK TO THE USER
 *     9. Seek to the beginninng of the file.
 *     10. For each record in the file.
 *          11. Read the record into the record object.
 *          12. Use the record's accessor methods to display the records contents.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

// using the standard namespace
using namespace std;

/*
 * InventoryItem class is an abstract class because it contains the pure virtual function:
 *      virtual int calculateShippingUnitsNeeded() = 0;
 *
 * PRIVATE MEMBERS:
 *      name : string - the name of the inventory item
 *      levelValue : int - the number units needed to maintain operation
 *      inHouse : int - the number of units in house when the counts are performed
 *      shippingUnitsNeeded : int - the number of shipping units (boxes/cases) needed
 *      shippingUnitName : string - the unit name "BX" or "CASE"
 *
 * PUBLIC MEMBERS:
 *      InventoryItem(string x, int y, int z)
 *          - Full constructor for the name, levelValue, and inHouse
 *      string getName()
 *          - accessor method for the name
 *      int getLevelValue()
 *          - accessor method for the level value
 *        int getUnitsInHouse()
 *           - accessor method for the units in house value
 *      void setName(string x)
 *           - mutator method to set the name of the object
 *      void setShippingUnitName(string x)
 *           - mutator method for the shipping unit name
 *      string getShippingUnitName()
 *           - accessor method for the shipping unit name
 *      int setShippingUnitsNeeded(int x)
 *           - mutator method for the needed shipping units
 *      int getShippingUnitsNeeded()
 *           - accessor method for the shipping units needed
 *
 *       virtual int calculateShippingUnitsNeeded() = 0;
 *           - virtual function needs to be implemented in any derived classes!
 *
 */
class InventoryItem {

    // private members
    private:
        string name;
        int levelValue;
        int inHouse;
        int shippingUnitsNeeded;
        string shippingUnitName;

    // public functions
    public:
        // constructor sets the name and level value
        InventoryItem(string x, int y, int z) {
            this->name = x;
            this->levelValue = y;
            this->inHouse = z;
        }

        string getName() {
            return name;
        }

        int getLevelValue() {
            return levelValue;
        }

        int getUnitsInHouse() {
            return inHouse;
        }

        void setName(string x) {
            name = x;
        }

        void setShippingUnitName(string x) {
            shippingUnitName = x;
        }

        string getShippingUnitName() {
            return shippingUnitName;
        }

        int setShippingUnitsNeeded(int x) {
            shippingUnitsNeeded = x; return x;
        }

        int getShippingUnitsNeeded() {
            return shippingUnitsNeeded;
        }

        virtual int calculateShippingUnitsNeeded() = 0;
};

/*
 * BoxedInventoryItem class inherits all members and functions
 * from InventoryItem class, but implements virtual function:
 *      calculateShippingUnitsNeeded()
 *
 * Calculates the number of BOXES needed to be ordered by the supplier
 * given the rule that 5 units fit into a box.
 *
 */
class BoxedInventoryItem : public InventoryItem {

    // private members (no additional)
    private:

    // public members (constructor + virtual function implementation)
    public:

        // consturctor
        BoxedInventoryItem(string x, int y, int z) : InventoryItem(x,y,z) {
            setShippingUnitName("BX");
        }

        // implemented virtual function
        int calculateShippingUnitsNeeded() {

            if ( getUnitsInHouse() >= getLevelValue()) {
                return setShippingUnitsNeeded(0);
            } else {
                cout << "\t\t\t\t(" << getLevelValue() << " - " << getUnitsInHouse() << ") / 5 ="
                     << (getLevelValue() - getUnitsInHouse()) / 5 << endl;
                return setShippingUnitsNeeded((getLevelValue() - getUnitsInHouse()) / 5);
            }
        }
};


/*
 * CasedInventoryItem class inherits all members and functions
 * from InventoryItem class, but implements virtual function:
 *      calculateShippingUnitsNeeded()
 *
 * Calculates the number of CASES needed to be ordered by the supplier
 * given the rule that 10 units fit into a CASE.
 *
 */
class CasedInventoryItem : public InventoryItem {

// private members (no additional!)
private:

// public members (constructor + virtual function implementation)
public:

    // constructor
    CasedInventoryItem(string x, int y, int z) : InventoryItem(x,y,z) {
        setShippingUnitName("CASE");
    }

    // implemented virtual function
    int calculateShippingUnitsNeeded() {
        if ( getUnitsInHouse() >= getLevelValue()) {
            return setShippingUnitsNeeded(0);
        } else {
            cout << "\t\t\t\t(" << getLevelValue() << " - " << getUnitsInHouse() << ") / 10 ="
            << (getLevelValue() - getUnitsInHouse()) / 10 << endl;
            return setShippingUnitsNeeded((getLevelValue() - getUnitsInHouse()) / 10);
        }
    }
};


/*
 * Main function is the driver of the program!
 *
 * Main method loads up food items and their stock levels and
 * asks the employee to perform the counts for the night.
 *
 * The item counts are then processed by the three classes above, and written to a binary
 * file 'counts.dat' which is ready to send to corporate.
 */
int main() {

    // greeting
    cout << "Welcome to the demo of my final project!" << endl;
    cout << "This project is a Restaurant Inventory Counter" << endl;

    // declare items
    cout << "\nLoading contents..." << endl;

    // names of our food items
    string items[] = {"Fries",
                      "Fries-SWT",
                      "PotStickers",
                      "EggWhite",
                      "EggWhole",
                      "Mayonnaise",
                      "HeavyCream",
                      "Bread-PKRHS",
                      "Bread-SRDGH",
                      "Bread-WHEAT",
                      "Dough-SM",
                      "Dough-M",
                      "Dough-L"};

    // quanity needed
    int levelValue[] = {64, // Fries
                      16,
                      10,
                      24,
                      24,
                      8,
                      8,
                      36, //Bread-PKRHS
                      30,
                      12, // Bread-WHEAT
                      48,
                      56,
                      64}; // Dough-L

    // shipment units (e.g. FRIES: 10 BX, Bread-WHEAT: 3 CASE)
    string units[] = {"BX",
                      "BX",
                      "BX",
                      "BX",
                      "BX",
                      "CASE",
                      "CASE",
                      "CASE",
                      "CASE",
                      "CASE",
                      "BX",
                      "BX",
                      "BX"};

    // time to do the counts
    cout << "Time to do the nightly counts!\n" << endl;

    int unitsInHouse;
    fstream file;

    // opening the output file stream
    file.open("counts.dat", ios::out | ios::in | ios::binary);



    // for each spot in the arrays of inventory items
    for (int i = 0; i < (sizeof(items) / sizeof(items[0])); i++) {

        // ask the user for the units in house for each item
        cout << "ITEM #" << i << "[ " << items[i] << " ]" << endl;
        cout << "\tUnits in-house: ";
        cin >> unitsInHouse;

        // create an inventoryItem (depending on whether it's boxed or cased)
        string shippingUnit = units[i];
        string BOX = "BX";
        string CASE = "CASE";

        // check if the item comes BOXED
        if (strcmp(shippingUnit.c_str(), BOX.c_str()) == 0) {

            // create the boxed inventory item
            BoxedInventoryItem boxedInventoryItem(items[i], levelValue[i], unitsInHouse);
            boxedInventoryItem.calculateShippingUnitsNeeded();

            // write the object to the file
            file.write(reinterpret_cast<char *>(&boxedInventoryItem), sizeof(boxedInventoryItem));

        // check if the item comes CASED
        } else if (strcmp(shippingUnit.c_str(), CASE.c_str()) == 0) {

            // create the cased inventory item
            CasedInventoryItem casedInventoryItem(items[i], levelValue[i], unitsInHouse);
            casedInventoryItem.calculateShippingUnitsNeeded();

            // write the object to the file
            file.write(reinterpret_cast<char *>(&casedInventoryItem), sizeof(casedInventoryItem));
        }
        // flush the stream
        file.flush();

    }

    // inform the user of report generation
    cout << "\nCounts finished! Generating report: " << endl;

    // seek to the beginning of the file
    file.seekg(0, ios::beg);

    while (!file.eof()) {
        // read the record
        BoxedInventoryItem record("dummy_data", 0, 0);

        file.read(reinterpret_cast<char *>(&record), sizeof(record));

        if (file.eof()) {
            break;
        }

        // display the record contents
        cout << "\n\t\tITEM: " << record.getName() << endl;
        cout << "\t\tQUANITY NEEDED: " << record.getLevelValue() << endl;
        cout << "\t\tQUANTITY IN HOUSE: " << record.getUnitsInHouse() << endl;
        cout << "\t\tNEED: " << record.getShippingUnitsNeeded() << " " << record.getShippingUnitName();
        cout << "\n";
    }

    cout << "This concludes the demo of the program..." << endl;

    // close
    file.close();
    return 0;
}