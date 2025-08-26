/**********|**********|**********|
Program: main.cpp
Course: OOPDS
Trimester: 2420
Lecture Class:
Tutorial Class:
Trimester: 2430
Member_1: |  |  |
Member_2: 242UC244PP | Nicholas Beh Zhi Yang | NICHOLAS.BEH.ZHI@student.mmu.edu.my | 011-65215166
Member_3: 242UC24551 | LOW ZHENG HAO | LOW.ZHENG.HAO@student.mmu.edu.my | 013-8888444
**********|**********|**********/

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <limits>

using namespace std;

struct Purchase
{
    int quantity;
    string item;
};

int main()
{
    queue<Purchase> order;     // First in, First Out
    stack<Purchase> inventory; // Last in, First Out

    int choice;
    int quantity;
    string item;

    while (true)
    {
        cout << " ***************************************************** " << endl;
        cout << " ----Warehouse Inventory and Shipping System----" << endl;
        cout << " 1. Add incoming item " << endl;
        cout << " 2. Process incoming item " << endl;
        cout << " 3. Display all item in the cart " << endl;
        cout << " 4. Ship item " << endl;
        cout << " 5. View last incoming item " << endl;
        cout << " 6. View next shipment " << endl;
        cout << " 7. Exit " << endl;
        cout << endl;
        cout << " ***************************************************** " << endl;
        cout << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();                                         // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input! Please enter a number.\n";
            cout << endl;
            continue; // back to menu
        }

        cin.ignore(); // removes the leftover newline character abo will have error

        switch (choice)
        {
            // { } separate block scope prevent error
        case 1:
        {
            cout << "Enter item name: ";
            getline(cin, item);

            bool isNumber = true;
            for (char a : item)
            {
                if (!isdigit(a))
                {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber)
            {
                cout << "Item name cannot be only numbers!\n\n";
                break;
            }

            cout << "How many needed: ";
            cin >> quantity;
            if (cin.fail() || quantity <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid quantity!\n\n";
                break;
            }
            cin.ignore();

            inventory.push({quantity, item});
            cout << quantity << "x " << item << " added to inventory.\n\n";
            break;
        }

        case 2:
        {
            // move from stack to queue
            if (!inventory.empty())
            {
                Purchase p = inventory.top();
                inventory.pop();
                order.push(p);
                cout << "Processed \"" << p.item << "\" (x" << p.quantity
                     << ") and added to shipping queue.\n\n";
            }
            else
            {
                cout << "No items in inventory to process!\n\n";
            }
            break;
        }

        case 3:
        {
            if (!order.empty())
            {
                cout << "Items in shipping cart:\n";
                queue<Purchase> temp = order;
                while (!temp.empty())
                {
                    Purchase p = temp.front();
                    temp.pop();
                    cout << "- " << p.item << " (x" << p.quantity << ")\n";
                }
                cout << endl;
            }
            else
            {
                cout << "Shipping cart is empty.\n\n";
            }
            break;
        }

        case 4:
        {
            if (!order.empty())
            {
                Purchase p = order.front();
                order.pop();
                cout << "Shipping item: " << p.item << " (x" << p.quantity << ")\n\n";
            }
            else
            {
                cout << "No items to ship.\n\n";
            }
            break;
        }

        case 5:
        {
            if (!inventory.empty())
            {
                Purchase p = inventory.top();
                cout << "Last incoming item: " << p.item << " (x" << p.quantity << ")\n\n";
            }
            else
            {
                cout << "No incoming items available.\n\n";
            }
            break;
        }

        case 6:
        {
            if (!order.empty())
            {
                Purchase p = order.front();
                cout << "Next item to ship: " << p.item << " (x" << p.quantity << ")\n\n";
            }
            else
            {
                cout << "No shipments pending.\n\n";
            }
            break;
        }

        case 7:
            cout << "Exiting program...\n\n";

            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
            cout << endl;
        }
    }
    return 0;
}