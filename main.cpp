#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

#include "Player.h"

void fillLegend(std::unordered_map<std::string, std::string>&);

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
    vector<Player> leaders;


    ifstream file(fileName);
    string line;

    cout << legend["1-3"] << endl;
    cout << "Expected: Out" << endl;
    cout << legend["3u"] << endl;
    cout << "Expected: Out" << endl;
    cout << legend["K"] << endl;
    cout << "Expected: Strikeout" << endl;
    cout << legend["BB"] << endl;
    cout << "Expected: Walk" << endl;


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
    
        string description = legend[code];
        bool atbat = false;
        if(description.size() != 0)
        {
            if(description == "Hit")
            {
                player.setHits(player.getHits() + 1);
                atbat = true;
            }
            else if(description == "Walk")
            {
                player.setWalks(player.getWalks() + 1);
            }
            else if(description == "Strikeout")
            {
                player.setStrikeouts(player.getStrikeouts() + 1);
                atbat = true;
            }
            else if(description == "Hit By Pitch")
            {
                player.setHits_By_Pitch(player.getHits_By_Pitch() + 1);
            }
            else if(description == "Sacrifice")
            {
                player.setSacrifices(player.getSacrifices() + 1);
            }
            else if(description == "Out")
            {
                atbat = true;
            }
            else if(description == "Error")
            {
                atbat = true;
            }

            if(atbat)
            {
                player.setAt_Bats(player.getAt_Bats() + 1);
            }

            player.setPlate_Appearances(player.getPlate_Appearances() + 1);
        }
        else
        {
            throw invalid_argument("Invalid code");
        }
        
        //add the player to the leader vector if they aren't already there
        bool found = false;
        for(int i = 0; i < leaders.size(); i++)
        {
            if(leaders[i] == player)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            leaders.push_back(player);
        }

        //if the player is a home player, add the name and the player object to the homePlayers map
        if(player.isHome())
        {
            homePlayers.insert(pair<string, Player>(player.getName(), player));
        }
        //if the player is an away player, add the name and the player object to the awayPlayers map
        else
        {
            awayPlayers.insert(pair<string, Player>(player.getName(), player));
        }
    }

    //call a function that prints the away players
    printPlayers(awayPlayers);



}

//create a function that fills the hashmap with the play codes and descriptions
void fillLegend(unordered_map<string, string> &legend)
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
                description = "Hit By Pitch";
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
            legend.insert(pair<string, string>(line, description));
        }
    }
}

//create a function that takes the awayPlayers and homePlayers maps and
//prints the players in the maps
void printPlayers(map<string, Player> &players)
{
    //if the first player in the map is a home player, print "Home Players"
    if(players.begin()->second.isHome())
    {
        cout << "Home Players" << endl;
    }
    else
    {
        cout << "Away Players" << endl;
    }

    for(map<string, Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        cout << it->first << endl;
        cout << "At Bats: " << it->second.getAt_Bats() << endl;
        cout << "Hits: " << it->second.getHits() << endl;
        cout << "Walks: " << it->second.getWalks() << endl;
        cout << "Strikeouts: " << it->second.getStrikeouts() << endl;
        cout << "Hits By Pitch: " << it->second.getHits_By_Pitch() << endl;
        cout << "Sacrifices: " << it->second.getSacrifices() << endl;
        cout << "Plate Appearances: " << it->second.getPlate_Appearances() << endl;
        cout << endl;
    }
}

//create a function that is responsible for printing the leaders in each category

