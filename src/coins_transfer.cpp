#include "coins.hpp"
#include <iostream>
using namespace std;

int main(){
	Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);

	cout << "Initial piggy Bank: ";
	piggyBank.print(std::cout);
	cout << endl;

	cout << "Initial pocket: ";
	pocket.print(cout);
	cout << endl;

	Coins chips_cost = coins_required_for_cents(149);
    pocket.extract_exact_change(chips_cost);
	cout << "\nBought chips using pocket" << endl;
	cout << "Chips required the coins: "<< chips_cost << endl;
	cout << "Pocket after paying for chips: ";
	pocket.print(cout);
	cout << endl;

	cout << "\nTransferring money to pocket" << endl;
	Coins transfer_cost = coins_required_for_cents(405);
	Coins transferred = piggyBank.extract_exact_change(transfer_cost);
	pocket.deposit_coins(transferred);
	cout << "Coins for transfer: " << transferred << endl;
	cout << "Pocket: " << pocket << endl;
	cout << "Piggy bank: ";
	piggyBank.print(cout);
	cout << endl;

	Coins sofa(10, 10, 10, 10);
	piggyBank.deposit_coins(sofa);
	cout << "\nTransferring sofa change to piggy bank" << endl;
    cout << "Sofa: " << sofa << endl;
    cout << "Piggy bank: ";
	piggyBank.print(cout);
	cout << endl;

	cout <<"\nPiggy bank total: ";
	print_cents(piggyBank.total_value_in_cents(), cout);
	cout << endl;

	return 0;
}


	
