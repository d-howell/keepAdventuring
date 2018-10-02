//Dalton Howell
//IN200: Intro to C++
//Keep Adventuring?

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

bool debug; //global bool for debug mode
int health = 30, totalTreasure = 0; //start with 30 health, and 0 treasure

//this_thread::sleep_for(chrono::milliseconds(1500));

bool AskYesNo(string question) { //returns true or false
    char input; //char for input  
    while(true){
        cout << question << endl; //output the question
        cout << "(Y/N) >> "; //prompt to enter y for yes or n for no
        cin >> input;
        input = toupper(input); //make the input uppercase
        switch (input){
            case 'Y': //if input is Y, return true
                return true; 
                break;
            case 'N': //if input is N, return false
                return false;
                break;
            default: //if input is anything else, say invalid and send back to beginning of loop
                cout << "\nInvalid input!\n";
                break; //using 'break;' to leave switch, rather than 'continue;' to send to top of loop, both work the same
        }
    }   
}

int rollDie(int sides = 6) { //sides defaults to 6 for a standard die, returns int as dice cant be float/double    
    return (rand() % sides + 1); //return a random number between 1 and the amount of sides
}

void Story() { //just the story before it starts
    cout << "*You wake up to a loud knocking on your door.*\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Friar Tuck: Sir Robin! It seems King Richard has gone off to fight in the Crusades!\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "You: Admirable. And what of it?\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Tuck: Now his brother, Prince John has taken over!\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Tuck: The man is fueled by greed. He has raised taxes for the third time this month!\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "You: Well, I must do something about this.\n";
    this_thread::sleep_for(chrono::milliseconds(1500)); 
    cout << "*You arm yourself with Bow and Sword*\n";
    this_thread::sleep_for(chrono::milliseconds(1500));  
}

void Ending() {

    if(health <= 0){ //If ending because health is 0
        cout << "You died an honorable death, helping others.\n";
        this_thread::sleep_for(chrono::milliseconds(1500)); 
        cout << "You were able to gather " << totalTreasure << " Gold before your death, and it is distributed throughout your town.\n";

    } else { //if ending because player decided to stop
        cout << "You made it out alive.\n";
        this_thread::sleep_for(chrono::milliseconds(1500)); 
        if(health < 5){
            cout << "But just barely.\n";
            this_thread::sleep_for(chrono::milliseconds(1500)); 
        }

        cout << "You were able to gather " << totalTreasure << " Gold before you retire.\n";
        this_thread::sleep_for(chrono::milliseconds(1500)); 

        if(totalTreasure <= 0 ){
            cout << "That is nothing, the people of your town will starve.\n";
        } else if(totalTreasure < 60){
            cout << "It's not much, but every bit counts.\n";
        } else {
            cout << "You have saved your town.\n";
        }

    }

    this_thread::sleep_for(chrono::milliseconds(1500)); 
    cout << "Thank you for playing!";
}

void Adventure() {
    int myBlock, enemyAttack, addTreasure = rollDie(20), addHealth;

    myBlock = rollDie();
    this_thread::sleep_for(chrono::milliseconds(200));
    enemyAttack = rollDie();

    if(health < 10) { //if health is low
        cout << "Robin! You are far too injured to continue!\n";
        this_thread::sleep_for(chrono::milliseconds(1500));
        if(AskYesNo("Would you like me to heal you for 5 Gold?")) {
            addHealth = rollDie();//Add random amount of health between 1 and 6
            health += addHealth;
            totalTreasure -= 5;
            if(debug){ cout << "Healed for " << addHealth << " health.\n";}
            return; //if player chose to heal, end this turn of adventuring
        } else {
            cout << "Okay, it's your funeral!\n";
        }
    }
    
    if(debug){ cout << "Attack = " << enemyAttack << ". Block = " << myBlock << ".\n" ;  }

    if(enemyAttack > myBlock) { //if attack higher than block
        cout << "You've been hit!\n";
        health -= enemyAttack;
        this_thread::sleep_for(chrono::milliseconds(1500));
        if(debug){ cout << "Health Lost: " << enemyAttack << ".\n"; }
    } else {
        cout << "Successful block! \nNow a counterattack!\n";
        this_thread::sleep_for(chrono::milliseconds(1500));
        if(debug){ cout << "Treasure Gained: " << addTreasure << ".\n"; }
        totalTreasure += addTreasure;
    }

    
}

int main() {
    cout << "Before we begin...\n";
    debug = AskYesNo("Would you like to enable debug mode?");
    this_thread::sleep_for(chrono::milliseconds(1500));

    srand(time(0)); //seed rng

    if(!debug){ Story(); } //if debug is on, skip the story to speed up debugging

    while(AskYesNo("Would you like to go Adventuring?")){
        Adventure();
        cout << "Current Health: " << health << ". Current Gold: " << totalTreasure << ".\n"; //moved this out of Adventure() so it shows up when healing as well
        this_thread::sleep_for(chrono::milliseconds(1500));
        if(health <= 0)
        {
            break;
        }
    }

    Ending();

}