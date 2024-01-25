#include "coins.hpp"

#include <iostream>

using namespace std;

Coins::Coins(int q, int d, int n, int p){
	quarters = q;
	dimes = d;
	nickels = n;
	pennies = p;
}

void Coins::deposit_coins(Coins& coins){
	quarters += coins.quarters;
	dimes += coins.dimes;
	nickels += coins.nickels;
	pennies += coins.pennies;

	coins.quarters = 0;
	coins.dimes = 0;
	coins.nickels = 0;
	coins.pennies = 0;
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const{
	if(quarters >= coins.quarters && dimes >= coins.dimes && nickels >= coins.nickels && pennies >= coins.pennies){
		return true;
	}
	else{
		return false;
	}
}

Coins Coins::extract_exact_change(const Coins& coins){
	if(!has_exact_change_for_coins(coins)){
		return Coins(0, 0, 0, 0);
	}

	else{
		quarters -= coins.quarters;
		dimes -= coins.dimes;
		nickels -= coins.nickels;
		pennies -= coins.pennies;
		return coins;
	}
}

int Coins::total_value_in_cents()const{
	return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + nickels * CENTS_PER_NICKEL + pennies;
}

void Coins::print(std::ostream& out) const{
	out << quarters << " quarters, "
        << dimes << " dimes, "
        << nickels << " nickels, "
        << pennies << " pennies";
}
	
std::ostream& operator<<(std::ostream& out, const Coins& coins) {
	coins.print(out);
	return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
    int quarters = amount_in_cents / 25;
    amount_in_cents %= 25;

    int dimes = amount_in_cents / 10;
    amount_in_cents %= 10;

    int nickels = amount_in_cents / 5;
    amount_in_cents %= 5;

    int pennies = amount_in_cents;

    return Coins(quarters, dimes, nickels, pennies);
}

void print_cents(int cents, std::ostream& out) {
    int dollars = cents / 100;
    cents %= 100;  
	out << "$" << dollars << ".";
    if (cents < 10) {
        out << '0';  
    }
    out << cents;
}

Coins ask_for_coins(std::istream& in, std::ostream& out) {
    int quarters, dimes, nickels, pennies;
    
    out << "Quarters? ";
    in >> quarters;
    
    out << "Dimes? ";
    in >> dimes;
    
    out << "Nickels? ";
    in >> nickels;
    
    out << "Pennies? ";
    in >> pennies;
    
    return Coins(quarters, dimes, nickels, pennies);
}

void coins_menu(std::istream& in, std::ostream& out){
	Coins myCoins(0,0,0,0); 
	int choice;
	cout << "Coins Menu\n";

    do {
        out << "\n1. Deposit Change\n"
            << "2. Extract Change\n"
            << "3. Print Balance\n"
            << "4. Exit\n"
            << "\nUser Input: ";
        in >> choice;

        switch (choice) {
            case 1:{
                int q, d, n, p;
                cout << "\nQuarters? ";
                cin >> q;
                cout << "Dimes? ";
                cin >> d;
                cout << "Nickels? ";
                cin >> n;
                cout << "Pennies? ";
                cin >> p;
                
                Coins deposit(q, d, n, p);
                myCoins.deposit_coins(deposit);
                cout << "\nThank you!\n";
                break;
			}
            case 2:{
                int q, d, n, p;
                cout << "\nQuarters? ";
                cin >> q;
                cout << "Dimes? ";
                cin >> d;
                cout << "Nickels? ";
                cin >> n;
                cout << "Pennies? ";
                cin >> p;
                
                Coins extract(q, d, n, p);
                if (myCoins.has_exact_change_for_coins(extract)) {
                    myCoins.extract_exact_change(extract);
                    cout << "\nThank you!\n";
                } else {
                    cout << "\nERROR: Insufficient Funds\n";
                }
                break;
			}
			case 3:{
                cout << "\n";
			    print_cents(myCoins.total_value_in_cents(), cout);
     			cout << "\n\nThank you!\n";               
				break;
			}

            case 4:
				cout << "\n";
                break;
            default:
                out << "\nERROR: Invalid Command\n";
                break;
        }

    } while (choice != 4);
}




