#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "Player.h"

using namespace std;

void fillLegend(std::unordered_map<std::string, std::string>&);
void printPlayers(std::map<std::string, Player>&);
void printLeaders(std::vector<Player> &);

bool compareBattingAverage(Player &player1, Player &player2);
bool compareOnBasePercentage(Player &player1, Player &player2);
bool compareName(Player &player1, Player &player2);
bool compareInput(Player &player1, Player &player2);
bool compareHits(Player &player1, Player &player2);
bool compareWalks(Player &player1, Player &player2);
bool compareStrikeouts(Player &player1, Player &player2);
bool compareHitsByPitch(Player &player1, Player &player2);

void printBA(vector<Player> &leaders);
void printOBP(vector<Player> &leaders);
void printHits(vector<Player> &leaders);
void printWalks(vector<Player> &leaders);
void printStrikeouts(vector<Player> &leaders);
void printHits_By_Pitch(vector<Player> &leaders);

void printTies(vector<Player> &temp);

int main()
{
    // Parse sample file
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;

    map<string, Player> awayPlayers; //ordered hashmap for away players
    map<string, Player> homePlayers; //ordered hashmap for home players

    unordered_map<string, string> legend; //legend to convert from code to play
    fillLegend(legend); //fills the legend from the legend file (keyfile)

    vector<Player> leaders;

    ifstream file(fileName);
    string line;


    while(getline(file,line)) //for each line in the sample file
    {
        Player player; //create a player object
        
        char c;
        stringstream(line) >> c;
        line.erase(0,2);

        switch(c) //if the player is away or home, set corresponding bool
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
        line.erase(0, name.length() + 1); //remove from line

        //get the play code
        string code;
        stringstream(line) >> code;
        line.erase(0, code.length() + 1); //remove from line
    
        string description = legend[code]; //get the description of the play
        bool atbat = false;
        /**
         * @brief Depending on the play, update corresponding player stat
         * 
         */
        if((int)description.size() != 0)
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

            if(atbat) //if it's an at bat, update player at bats
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
        
        bool found = false;
        /**
         * @brief If the player is already in the leader vector, update their stats. Else add them to the vector
         * 
         */
        for(int i = 0; i < (int)leaders.size(); i++)
        {
            if(leaders[i].getName() == player.getName())
            {
                found = true;
                leaders[i].setHits(leaders[i].getHits() + player.getHits());
                    leaders[i].setWalks(leaders[i].getWalks() + player.getWalks());
                    leaders[i].setStrikeouts(leaders[i].getStrikeouts() + player.getStrikeouts());
                    leaders[i].setHits_By_Pitch(leaders[i].getHits_By_Pitch() + player.getHits_By_Pitch());
                    leaders[i].setSacrifices(leaders[i].getSacrifices() + player.getSacrifices());
                    leaders[i].setAt_Bats(leaders[i].getAt_Bats() + player.getAt_Bats());
                    leaders[i].setPlate_Appearances(leaders[i].getPlate_Appearances() + player.getPlate_Appearances());
                break;
            }
        }
        if(!found)
        {
            leaders.push_back(player);
        }

        if(player.isHome()) //if the player is already in the home map, update their stats. Else insert
        {
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
        else //if the player is already in the away map, update their stats. Else insert
        {
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

    printPlayers(awayPlayers);
    printPlayers(homePlayers);

    printLeaders(leaders);
}

void fillLegend(unordered_map<string, string> &legend)
{
    ifstream file("keyfile.txt");
    string line;

    int count = 0;
    string description = "";
    while(getline(file,line)) //parse input from the legend file.
    {
        if(line[0] == '#') //checks if the line is a header
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
        else if ((int)line.size() == 0)
        {
            continue;
        }
        else //it's a code
        {
            legend.insert(pair<string, string>(line, description));
        }
    }
}


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

    for(map<string, Player>::iterator it = players.begin(); it != players.end(); it++) //for each player in the map, print out the stats in proper formatting
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

void printLeaders(vector<Player> &leaders)
{
    cout << "LEAGUE LEADERS" << endl;
    printBA(leaders);
    printOBP(leaders);
    printHits(leaders);
    printWalks(leaders);
    printStrikeouts(leaders);
    printHits_By_Pitch(leaders);
}

//---------PRINTING LEADERS-----------//

//-----------BATTING AVERAGE------------//
void printBA(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareBattingAverage); //sort the players by batting average to have access to leaders
    
    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "BATTING AVERAGE" << endl;
    cout << fixed << setprecision(3) << leaders[0].getBatting_Average() << "\t"; //print the first leader's batting average
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getBatting_Average() == leaders[0].getBatting_Average())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        if(leaderCount >= (int)leaders.size()) cout << "OUT OF BOUNDS" << endl;
        cout << fixed << setprecision(3) << leaders[leaderCount].getBatting_Average() << "\t"; //print the 2nd place leader's batting average
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getBatting_Average() == leaders[initialLeaderCount].getBatting_Average())
            {
                temp.push_back(leaders[i]); //add the player to the temp vector
                leaderCount++;
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            if(leaderCount >= (int)leaders.size()) cout << "OUT OF BOUNDS" << endl;
            cout << fixed << setprecision(3) << leaders[leaderCount].getBatting_Average() << "\t"; //print the 3rd place leader's batting average
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getBatting_Average() == leaders[initialLeaderCount].getBatting_Average())
                {
                    temp.push_back(leaders[i]); //add the player to the temp vector
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}



//-----------ON BASE PERCENTAGE------------//

void printOBP(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareOnBasePercentage); //sort the players by on base percentage to have access to leaders

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "ON-BASE PERCENTAGE" << endl;
    cout << fixed << setprecision(3) << leaders[0].getOn_Base_Percentage() << "\t"; //print the first leader's on base percentage
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getOn_Base_Percentage() == leaders[0].getOn_Base_Percentage())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getOn_Base_Percentage() << "\t"; //print the 2nd place leader's on base percentage
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getOn_Base_Percentage() == leaders[initialLeaderCount].getOn_Base_Percentage())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getOn_Base_Percentage() << "\t"; //print the 3rd place leader's on base percentage
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getOn_Base_Percentage() == leaders[initialLeaderCount].getOn_Base_Percentage()) 
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}




//-----------HITS------------//

void printHits(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareHits); //sort the players by hits to have access to leaders

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "HITS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getHits() << "\t";  //print the first leader's hits
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getHits() == leaders[0].getHits())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getHits() << "\t"; //print the 2nd place leader's hits
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getHits() == leaders[initialLeaderCount].getHits())
            {
                temp.push_back(leaders[i]); //add the player to the temp vector
                leaderCount++;
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getHits() << "\t"; //print the 3rd place leader's hits
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getHits() == leaders[initialLeaderCount].getHits())
                {
                    temp.push_back(leaders[i]); //add the player to the temp vector
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}





//----------WALKS-----------//

void printWalks(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareWalks); //sort the players by walks to have access to leaders

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "WALKS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getWalks() << "\t"; //print the first leader's walks
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getWalks() == leaders[0].getWalks())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getWalks() << "\t"; //print the 2nd place leader's walks
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getWalks() == leaders[initialLeaderCount].getWalks())
            {
                temp.push_back(leaders[i]); //add the player to the temp vector
                leaderCount++;
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getWalks() << "\t"; //print the 3rd place leader's walks
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getWalks() == leaders[initialLeaderCount].getWalks())
                {
                    temp.push_back(leaders[i]); //add the player to the temp vector
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}





//----------STRIKEOUTS-----------//

void printStrikeouts(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareStrikeouts); //sort the players by strikeouts to have access to leaders

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "STRIKEOUTS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getStrikeouts() << "\t"; //print the first leader's strikeouts
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getStrikeouts() == leaders[0].getStrikeouts())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getStrikeouts() << "\t"; //print the 2nd place leader's strikeouts
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getStrikeouts() == leaders[initialLeaderCount].getStrikeouts())
            {
                temp.push_back(leaders[i]); //add the player to the temp vector
                leaderCount++;
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getStrikeouts() << "\t"; //print the 3rd place leader's strikeouts
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getStrikeouts() == leaders[initialLeaderCount].getStrikeouts())
                {
                    temp.push_back(leaders[i]); //add the player to the temp vector
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}

//----------HITS BY PITCh-----------//

void printHits_By_Pitch(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareHitsByPitch); //sort the players by hits by pitch to have access to leaders

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "HIT BY PITCH" << endl;
    cout << fixed << setprecision(3) << leaders[0].getHits_By_Pitch() << "\t"; //print the first leader's hits by pitch
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getHits_By_Pitch() == leaders[0].getHits_By_Pitch())
        {
            temp.push_back(leaders[i]); //add the player to the temp vector
            leaderCount++;
        }
        else break;
    }
    printTies(temp); //print the ties for 1st place

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getHits_By_Pitch() << "\t"; //print the 2nd place leader's hits by pitch
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getHits_By_Pitch() == leaders[initialLeaderCount].getHits_By_Pitch()) 
            {
                temp.push_back(leaders[i]); //add the player to the temp vector
                leaderCount++; 
            }
            else break;
        }
        printTies(temp); //print the ties for 2nd place

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getHits_By_Pitch() << "\t"; //print the 3rd place leader's hits by pitch
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getHits_By_Pitch() == leaders[initialLeaderCount].getHits_By_Pitch())
                {
                    temp.push_back(leaders[i]); //add the player to the temp vector
                    leaderCount++;
                }
                else break;
            }
            printTies(temp); //print the ties for 3rd place
        }

    }
    cout << endl;
}



//----------Print Ties Helper-----------//

void printTies(vector<Player> &temp)
{
    std::sort(temp.begin(), temp.end(), compareName); //sort the players alphabetically
    int printedCount = 0;
    /**
     * @brief print the away players first
     * 
     */
    for (int j = 0; j < (int)temp.size(); j++) // AWAY /////////////
    {
        if (temp[j].isHome())
        {
            continue;
        }
        else
        {
            if (printedCount != 0) //if it's not the first player, prepend a comma
            {
                cout << ", ";
            }

            cout << temp[j].getName();
            printedCount++;
        }
    }
    /**
     * @brief print the home players second
     * 
     */
    for (int j = 0; j < (int)temp.size(); j++) // HOME /////////////
    {
        if (temp[j].isHome())
        {
            if (printedCount != 0) //if it's not the first player, prepend a comma
            {
                cout << ", ";
            }

            cout << temp[j].getName();
            printedCount++;
        }
        else
        {
            continue;
        }
    }
    cout << endl;
    temp.clear();
}


//------------COMPARISON FUNCTIONS-----------------//

bool compareName(Player &player1, Player &player2)
{
    return player1.getName() < player2.getName();
}

bool compareBattingAverage(Player &player1, Player &player2)
{
    return player1.getBatting_Average() > player2.getBatting_Average();
}

bool compareOnBasePercentage(Player &player1, Player &player2)
{
    return player1.getOn_Base_Percentage() > player2.getOn_Base_Percentage();
}

bool compareHits(Player &player1, Player &player2)
{
    return player1.getHits() > player2.getHits();
}

bool compareWalks(Player &player1, Player &player2)
{
    return player1.getWalks() > player2.getWalks();
}

bool compareStrikeouts(Player &player1, Player &player2)
{
    return player1.getStrikeouts() < player2.getStrikeouts();
}

bool compareHitsByPitch(Player &player1, Player &player2)
{
    return player1.getHits_By_Pitch() > player2.getHits_By_Pitch();
}