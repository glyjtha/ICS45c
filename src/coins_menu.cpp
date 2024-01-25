#include "coins.hpp"
#include <iostream>
using namespace std;

void print_menu() {
    cout << "\n1. Deposit Change\n";
    cout << "2. Extract Change\n";
    cout << "3. Print Balance\n";
    cout << "4. Exit\n\n";
    cout << "User Input: ";
}

int main(){
	Coins myCoins(0, 0, 0, 0);
	int choice;
	cout << "Coins Menu";

	do{
		print_menu();
        cin >> choice;
	
		switch(choice){
			case 1: {
				int a, b, c, d;
                cout << "\nQuarters? ";
                cin >> a;
                cout << "Dimes? ";
                cin >> b;
                cout << "Nickels? ";
                cin >> c;
                cout << "Pennies? ";
                cin >> d;
                
                Coins deposit(a, b, c, d);
                myCoins.deposit_coins(deposit);
                cout << "\nThank you!\n";
                break;
			}

			case 2: {
				int a, b, c, d;
                cout << "\nQuarters? ";
                cin >> a;
                cout << "Dimes? ";
                cin >> b;
                cout << "Nickels? ";
                cin >> c;
                cout << "Pennies? ";
                cin >> d;
                
                Coins extract(a, b, c, d);
                if (myCoins.has_exact_change_for_coins(extract)) {
                    myCoins.extract_exact_change(extract);
                    cout << "\nThank you!\n";
                } else {
                    cout << "\nERROR: Insufficient Funds\n";
                }
                break;
			}

			case 3: {
				cout << "\n";
    			print_cents(myCoins.total_value_in_cents(), cout);
   				cout << "\n\nThank you!\n";
				break;
			}

			case 4: 
				cout << "\n";
                break;
			
			default:
                cout << "\nERROR: Invalid Command\n";
                break;

		}
	
	}while(choice!=4);

	return 0;

}


