#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"
using namespace std;

void printHelloWorld();

int main()
{
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;

    map<string, Player> awayPlayers;
    map<string, Player> homePlayers;

    unordered_map<string, string> legend;

    //create a vector for leaders in each category and values for each leader
    vector<Player> battingAverageLeaders;
    vector<Player> onBasePercentageLeaders;
    vector<Player> hitsLeaders;
    vector<Player> walksLeaders;
    vector<Player> strikeoutsLeaders;
    vector<Player> hitsByPitchLeaders;


    ifstream file(fileName);
    string line;

    while(getline(file,line))
    {
        //create a player object
        Player player;

        char c;
        file >> c;
        switch(c)
        {
            case 'A':
                player.setHome(false);
                break;
            case 'H':
                player.setHome(true);
                break;
            default:
                throw invalid_argument("Invalid team designation");
                break;
        }

        //get the player's name
        string name;
        file >> name;
        player.setName(name);

        //get the player's stats
        string code;
        file >> code;
        
        

    }
}

//create a function that takes the awayPlayers and homePlayers maps and

//create a function that is responsible for printing the leaders in each category

