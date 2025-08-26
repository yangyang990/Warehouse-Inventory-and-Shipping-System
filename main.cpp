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
#include <cctype>
#include <limits>

using namespace std;

int main()
{
    queue<string> order;     // First in, First Out
    stack<string> inventory; // Last in, First Out

    int choice;
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

        cin.ignore(); // clear newline for getline abo will have error

        switch (choice)
        {
        case 1:
            cout << "Enter item name: ";
            getline(cin, item);
            inventory.push(item);
            cout << item << " added to inventory." << endl;
            cout << endl;
            break;

        case 2:
            // move from stack to queue
            if (!inventory.empty())
            {
                item = inventory.top();
                inventory.pop();  // remove from inventory
                order.push(item); // add to order lsit
                cout << "Processed " << item << " and added to shipping queue." << endl;
                cout << endl;
            }
            else
            {
                cout << "No items in inventory to process!" << endl;
                cout << endl;
            }
            break;

        case 3:
            if (!order.empty())
            {
                cout << "Items in cart: ";
                queue<string> temp = order;
                while (!temp.empty())
                {
                    cout << temp.front();
                    temp.pop();
                    if (!temp.empty())
                    {
                        cout << ", ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else
            {
                cout << "Shipping cart is empty." << endl;
                cout << endl;
            }
            break;

        case 7:
            cout << "Exiting program...\n";
            cout << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
            cout << endl;
        }
    }
    return 0;
}