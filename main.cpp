#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Player.h"

void fillLegend(std::unordered_map<std::string, std::string>&);
void printPlayers(std::map<std::string, Player>&);

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

    cout << legend["F8"] << endl;
    cout << legend["1-3"] << endl;



    while(getline(file,line))
    {
        //create a player object
        Player player;

        char c;
        stringstream(line) >> c;
        line.erase(0,2);

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
        stringstream(line) >> name;
        player.setName(name);
        line.erase(0, name.length() + 1);

        //get the player's stats
        string code;
        stringstream(line) >> code;
        line.erase(0, code.length() + 1);
    
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
                atbat = false;
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
            //if the player is already in the map, update their stats
            if(homePlayers.find(name) != homePlayers.end())
            {
                homePlayers[name].setHits(homePlayers[name].getHits() + player.getHits());
                homePlayers[name].setWalks(homePlayers[name].getWalks() + player.getWalks());
                homePlayers[name].setStrikeouts(homePlayers[name].getStrikeouts() + player.getStrikeouts());
                homePlayers[name].setHits_By_Pitch(homePlayers[name].getHits_By_Pitch() + player.getHits_By_Pitch());
                homePlayers[name].setSacrifices(homePlayers[name].getSacrifices() + player.getSacrifices());
                homePlayers[name].setAt_Bats(homePlayers[name].getAt_Bats() + player.getAt_Bats());
                homePlayers[name].setPlate_Appearances(homePlayers[name].getPlate_Appearances() + player.getPlate_Appearances());
            }
            else
            {
                homePlayers.insert(pair<string, Player>(name, player));
            }
        }
        //if the player is an away player, add the name and the player object to the awayPlayers map
        else
        {
            //if the player is already in the map, update their stats
            if(awayPlayers.find(name) != awayPlayers.end())
            {
                awayPlayers[name].setHits(awayPlayers[name].getHits() + player.getHits());
                awayPlayers[name].setWalks(awayPlayers[name].getWalks() + player.getWalks());
                awayPlayers[name].setStrikeouts(awayPlayers[name].getStrikeouts() + player.getStrikeouts());
                awayPlayers[name].setHits_By_Pitch(awayPlayers[name].getHits_By_Pitch() + player.getHits_By_Pitch());
                awayPlayers[name].setSacrifices(awayPlayers[name].getSacrifices() + player.getSacrifices());
                awayPlayers[name].setAt_Bats(awayPlayers[name].getAt_Bats() + player.getAt_Bats());
                awayPlayers[name].setPlate_Appearances(awayPlayers[name].getPlate_Appearances() + player.getPlate_Appearances());
            }
            else
            {
                awayPlayers.insert(pair<string, Player>(name, player));
            }
        }
    }

    //call a function that prints the away players
    printPlayers(awayPlayers);
    printPlayers(homePlayers);



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
        cout << "HOME" << endl;
    }
    else
    {
        cout << "AWAY" << endl;
    }

    for(map<string, Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        cout << it->first << "\t";
        cout << it->second.getAt_Bats() << "\t";
        cout << it->second.getHits() << "\t";
        cout << it->second.getWalks() << "\t";
        cout << it->second.getStrikeouts() << "\t";
        cout << it->second.getHits_By_Pitch() << "\t";
        cout << it->second.getSacrifices() << "\t";
        cout << fixed << setprecision(3) << it->second.getBatting_Average() << "\t";
        cout << it->second.getOn_Base_Percentage();
        cout << endl;
    }
    cout << endl;
}

//create a function that is responsible for printing the leaders in each category

