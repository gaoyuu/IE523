//
//  main.cpp
//  cardgame
//
//  Created by Yu Gao on 9/17/17.
//  Copyright © 2017 Yu Gao. All rights reserved.
//

#include <iostream>
#include "card_game.h"

using namespace std;

int main (int argc, char * const argv[])
{
    int total_number_of_cards;
    
    sscanf (argv[1], "%d", &total_number_of_cards);
    
    cout << "Total Number of Cards = " << total_number_of_cards << endl;
    
    cout << "Value of the game = " << value(total_number_of_cards/2,total_number_of_cards/2) << endl;
    
    return 0;
}

