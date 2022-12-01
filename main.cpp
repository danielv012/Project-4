#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"

void fillLegend(unordered_map<string, string>);

using namespace std;

int main()
{
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;

    map<string, Player> awayPlayers;
    map<string, Player> homePlayers;

    unordered_map<string, string> legend;
    fillLegend(legend);

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

        //need to do a switch statement that changes the player stat depending on the legend value after indexing a code
    }
}

//create a function that fills the hashmap with the play codes and descriptions
void fillLegend(unordered_map<string, string> legend)
{
    //input from keyfile.txt to fill the hashmap with the play codes and descriptions
    ifstream file("keyfile.txt");
    string line;

    int count = 0;
    string description = "";
    while(getline(file,line))
    {
        if(line[0] == '#')
        {
            count++;

            switch (count)
            {
            case 1:
                description = "Out";
                break;
            case 2:
                description = "Strikeout";
                break;
            case 3:
                description = "Hit";
                break;
            case 4:
                description = "Walk";
                break;
            case 5:
                description = "Sacrifice";
                break;
            case 6:
                description = "Hits By Pitch";
                break;
            case 7:
                description = "Error";
                break;
            default:
                break;
            }
            continue;
        }
        else if (line.size() == 0)
        {
            continue;
        }
        else
        {
            string code;
            file >> code;
            legend.insert(pair<string, string>(code, description));
        }
    }
}

//create a function that takes the awayPlayers and homePlayers maps and

//create a function that is responsible for printing the leaders in each category

