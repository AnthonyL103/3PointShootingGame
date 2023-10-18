#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/******************************************************
** Program: 3PointShootingGame.cpp
** Author: Anthony Li
** Date: 10/14/2023
** Description: Summary of how code works, uses player class to represent every single player. For every player an array of characters is created 
with their choice of Money ball rack position. Then we iterate through that array per player and modify it based on if they made the
shot or not. We also calculate the score per rack, print it, and print out their final score at the end. I chose this way to approach
this problem because classes make initiating multiple players extremely easy, storing their data, and accessing it in the end. 
All I had to do was take in my inputs, create an array of garbage pointers for the amount of players there are, then populate them, and
after I don't need to use them anymore (after the final results are printed) I delete them to avoid a memory leak. I also originally 
made this as a game you can actually play by pressing y to shoot, that is why a lot of code is commented out so just ignore that.
******************************************************/


//initialize player class and pass in starting index of chosen Money Ball rack
class Player {
public:
    //initialize ShotRes array and set characters to their corresponding indexes (Starry, Moneyballrack, etc.)
    Player(int Mballrack) {
        int i;
        for (i = 0; i < 27; i++) {
            if (i == 16 || i == 10) {
                ShotRes[i] = 'S';
            }
            else if (i >= Mballrack && i <= (Mballrack+4)) {
                ShotRes[i] = 'M';
            }
            else {
                ShotRes[i] = 'O';
            }
        }
        
    }
    //Make shots function that modifies ShotRes array based on if they made the shot or not
    void makeshots (int CurrRack) {
        //if the index is 10 or 16 we set val to X based on the result of shot()
        if (CurrRack == 10 || CurrRack == 16) {
            if (shot() == false) {
                ShotRes[CurrRack] = 'X';
            }
        }
        else {
            //otherwise we set the val to X based on the result for shot() for the entire current rack
            for (int i = CurrRack; i < CurrRack + 5; i++) {
                if (shot() == false) {
                    ShotRes[i] = 'X';
                }
                //make sure that the last ball of the rack is always a money ball
                else {
                    if (i == CurrRack+4) {
                        ShotRes[i] = 'M';
                    }
                }
            }
        }
    }
    //print shot results of the current rack
    void printshotres (int CurrRack) {
        //uses hashmap to convert starting indexes of racks to their actual numbers
        unordered_map<int, string> CorrRack;
        CorrRack[0] = "1";
        CorrRack[5] = "2";
        CorrRack[11] = "3";
        CorrRack[17] = "4";
        CorrRack[22] = "5";
        //if it is index 10 or 16 then we treat that as a rack of its own and print it as such 
        if (CurrRack == 10 || CurrRack == 16 ) {
            cout << "Starry Ball result: " << ShotRes[CurrRack];
            //print the score for the starry ball 
            cout << " | " << scorecalc(CurrRack) << " pts" << endl;
        }
        //otherwise we print out the entire rack results (it's already modified by makeshots at this point)
        else {
            cout << "Rack " << CorrRack[CurrRack] << " results: ";
            for (int i = CurrRack; i < CurrRack + 5; i++) {
                cout << ShotRes[i] << " ";
            }
            //print out the score for the rack
            cout << " | " << scorecalc(CurrRack) << " pts" << endl;
        }
    }
    //calculates the score of the current rack
    int scorecalc(int CurrRack) {
        //hashmap to convert ball characters to numbers
        unordered_map<char, int> Chtopoints;
        Chtopoints['O'] = 1;
        Chtopoints['M'] = 2;
        Chtopoints['S'] = 3;
        Chtopoints['X'] = 0;
        //declare score value
        int score = 0;
        //if index is 10 or 16 we know its a starry ball and to treat it as its own rack
        if (CurrRack == 10 || CurrRack == 16) {
                score += Chtopoints[ShotRes[CurrRack]];
        }
        //otherwise iterate through the entire current rack and add the values that their keys represent in the hashmap to score.
        else {
            for (int i = CurrRack; i < CurrRack + 5; i++) {
                score += Chtopoints[ShotRes[i]];
            }
        }
        //return score 
        return score;
    }

    //print all final results by using rackpos array (array of all rack's starting positions)
    void printfinalres(int rackpos[]) {
        //establishes a final score value 
        int finalscore = 0;
        //for every values in rackpos we call printshotres and scorecalc which will print the results for every rack
        for (int i = 0; i < 7; i++) {
            printshotres(rackpos[i]);
            //adds total score of every rack to final score
            finalscore += scorecalc(rackpos[i]);
        }
        //print out final score 
        cout << "Final score: " << finalscore << endl;
    }

//Only Player class methods can manipulate/interact
private:
    //establishes ShotRes array with length 27
    char ShotRes[27];
    //generates random number and if it is even then we return true otherwise we return false, creating a 50% chance
    bool shot() {
        return rand() % 2 == 0;
    }
};
//Play again function 
static bool playAgain() {
    //declares choice character
    char choice;
    //prompts user to input their choice on playing again or not
    cout << "Thanks for playing!! Enter y to play again or n to quit.";
    //takes in choice 
    cin >> choice;
    //if the choice is y we return true 
    if (choice == 'y') {
        return true;
    }
    //if choice is n we return false 
    else if (choice == 'n') {
        cout << "Thanks for playing the 3 point shooting game...quitting program" << endl;
        return false;
    }
    //otherwise for invalid inputs we prompt user to input again and recursively call playAgain until the correct input is made
    else {
        cout << "Invalid input please try again" << endl;
        return playAgain();
    }
}

//Get Player count function 
string getplayercount () {
    //declares playercount as string 
    string playercount;
    //prompts user input and takes it in
    cout << "How many players will be playing today?" << endl;
    cin >> playercount;
    while (true) {
        //uses try and except to catch non valid type inputs (I used stackoverflow for this)
        try {
            //sets count to integer conversion of playercount 
            int count = stoi(playercount);
            //if count valid (1-10) return playercount
            if (count >= 1 && count <= 10) {
                return playercount;
            } else {
                //otherwise we know that the number is not in this range 
                cout << "Invalid input. Please enter a number between 1-10." << endl;
            }
        //catches invalid type arguement
        } catch (const invalid_argument& e) {
            //we know the error is an invalid type so we display that it was an invalid input
            cout << "Invalid input. Please enter a valid integer." << endl;
        }
        //clears error state 
        cin.clear();
        //discards remaining characters in input stream 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //reads in playercount again
        cin >> playercount;
    }
}
//gets money ball rack position, very similiar to getting the playercount so I'm going to specify a little less
string getMBrack (int currplayermb) {
        string Mballrack;
        cout << "Player " << currplayermb + 1 << " enter your Money Ball rack position (1-5)." << endl;
        cin >> Mballrack;
        while (true) {
            try {
                int rack  = stoi(Mballrack);
                //only difference, we are checking if the input is within (1-5) rather than (1-10)
                if (rack >= 1 && rack <= 5) {
                   return Mballrack;
                }
                else {
                    cout << "Invalid input. Please enter a number between 1-5." << endl;
                }
            } catch (const invalid_argument& e) {
                cout << "Invalid input. Please enter a valid integer." << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> Mballrack;
        }
}
//playgame function 
void playGame(Player* player, int rackpos[], int rack) {
    char choice;
    do {
        cout << "Enter y to shoot" << endl;
        cin >> choice;
        if (choice != 'y' || cin.fail()) {
            cout << "Invalid input please try again, enter y to shoot" << endl;
        } else {
            player->makeshots(rackpos[rack - 1]);
            player->printshotres(rackpos[rack - 1]);
        }
    } while (choice != 'y' || cin.fail());
}
//prints all final results for every player
void printallfinalres (Player* players[], int playercount, int rackpos[]) {
    //iterates through all players 
    for (int currplayer = 0; currplayer < playercount; currplayer++) {
        //prints out the current player so we know who's results it is
        cout << "Player " << currplayer+1 << " here are your final results" << endl;
        //calls that players printfinalres function and passes in the rackpos array
        players[currplayer] -> printfinalres(rackpos);
        //deletes the player object so we don't have memory leaks
        delete players[currplayer];
    }
}
//main function 
int main () {
    //seeds random number generator 
    srand(time(0));
    do {
        cout << "Welcome to the 3 point shooting contest" << endl;
        //sets playercount integer to int conversion of getplayercount function output
        int playercount = stoi(getplayercount());
        //initialises Money ball rack positions array and sets size to the amount of players
        int MBrackpos [playercount];
        //for every player we call getMBrack and store it in our MBrackpos array so we know what everyone wants as their money ball rack
        for (int currplayermb = 0; currplayermb < playercount; currplayermb++) {
            MBrackpos[currplayermb] = stoi(getMBrack(currplayermb));
        }
        //creates rackpos array which is the starting indexes of all racks
        int rackpos[] = {0, 5, 10, 11, 16, 17, 22};
        //creates rackpos array without starry ball indexes 
        int rackposnostarry[] = {0, 5, 11, 17, 22};
        //creates an array of garbage pointers for the amount for players that will point to all the player objects we create, 
        Player* players[playercount];
        //for every rack we go through every player 
        for (int rack = 1; rack <= 7; rack++) {
            for (int currplayer = 0; currplayer < playercount; currplayer++) {
                cout << "Current Player: " << currplayer + 1 << endl;
                //sets CurrMBrack to the chosen Money ball rack of the current player 
                int CurrMBrack = MBrackpos[currplayer];
                //creates a Player object for that player and we pass in starting index of moneyball rack so we can initialize the ShotRes array correctly 
                players[currplayer] = new Player(rackposnostarry[CurrMBrack-1]);
                //calls play game function to execute all the functions in the player class to calculate scores and print them accordingly
                playGame(players[currplayer], rackpos, rack);
            }
        }
        //after the game is finished we call printallfinalres to print the final results for every player
        printallfinalres(players, playercount, rackpos);
    //Calls playAgain function and if it returns true we run the program again starting a new game
    } while (playAgain() == true);
    return 0;
}

