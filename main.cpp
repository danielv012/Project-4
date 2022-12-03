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
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;

    map<string, Player> awayPlayers;
    map<string, Player> homePlayers;

    unordered_map<string, string> legend;
    fillLegend(legend);

    vector<Player> leaders;

    ifstream file(fileName);
    string line;

    int count = 0;

    while(getline(file,line))
    {
        Player player;
        
        player.setInput(count);

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

        //get the play code
        string code;
        stringstream(line) >> code;
        line.erase(0, code.length() + 1);
    
        string description = legend[code];
        bool atbat = false;
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
        
        bool found = false;
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

        if(player.isHome())
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
        else
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
        else if ((int)line.size() == 0)
        {
            continue;
        }
        else
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
    std::sort(leaders.begin(), leaders.end(), compareBattingAverage);
    
    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "BATTING AVERAGE" << endl;
    cout << fixed << setprecision(3) << leaders[0].getBatting_Average() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getBatting_Average() == leaders[0].getBatting_Average())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        if(leaderCount >= (int)leaders.size()) cout << "OUT OF BOUNDS" << endl;
        cout << fixed << setprecision(3) << leaders[leaderCount].getBatting_Average() << "\t";
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getBatting_Average() == leaders[initialLeaderCount].getBatting_Average())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            if(leaderCount >= (int)leaders.size()) cout << "OUT OF BOUNDS" << endl;
            cout << fixed << setprecision(3) << leaders[leaderCount].getBatting_Average() << "\t";
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getBatting_Average() == leaders[initialLeaderCount].getBatting_Average())
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp);
        }

    }
    cout << endl;
}



//-----------ON BASE PERCENTAGE------------//

void printOBP(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareOnBasePercentage);

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "ON-BASE PERCENTAGE" << endl;
    cout << fixed << setprecision(3) << leaders[0].getOn_Base_Percentage() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getOn_Base_Percentage() == leaders[0].getOn_Base_Percentage())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getOn_Base_Percentage() << "\t";
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
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getOn_Base_Percentage() << "\t";
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
            printTies(temp);
        }

    }
    cout << endl;
}




//-----------HITS------------//

void printHits(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareHits);

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "HITS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getHits() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getHits() == leaders[0].getHits())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getHits() << "\t";
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getHits() == leaders[initialLeaderCount].getHits())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getHits() << "\t";
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getHits() == leaders[initialLeaderCount].getHits())
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp);
        }

    }
    cout << endl;
}





//----------WALKS-----------//

void printWalks(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareWalks);

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "WALKS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getWalks() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getWalks() == leaders[0].getWalks())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getWalks() << "\t";
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getWalks() == leaders[initialLeaderCount].getWalks())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getWalks() << "\t";
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getWalks() == leaders[initialLeaderCount].getWalks())
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp);
        }

    }
    cout << endl;
}





//----------STRIKEOUTS-----------//

void printStrikeouts(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareStrikeouts);

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "STRIKEOUTS" << endl;
    cout << fixed << setprecision(3) << leaders[0].getStrikeouts() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getStrikeouts() == leaders[0].getStrikeouts())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getStrikeouts() << "\t";
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getStrikeouts() == leaders[initialLeaderCount].getStrikeouts())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getStrikeouts() << "\t";
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getStrikeouts() == leaders[initialLeaderCount].getStrikeouts())
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp);
        }

    }
    cout << endl;
}

//----------HITS BY PITCh-----------//

void printHits_By_Pitch(vector<Player> &leaders)
{
    std::sort(leaders.begin(), leaders.end(), compareHitsByPitch);

    vector<Player> temp;

    int leaderCount = 0, i = 0;
    cout << "HIT BY PITCH" << endl;
    cout << fixed << setprecision(3) << leaders[0].getHits_By_Pitch() << "\t";
    for(i = 0; i < (int)leaders.size(); i++) // 1st PLACE TIES /////////////
    {
        if(leaders[i].getHits_By_Pitch() == leaders[0].getHits_By_Pitch())
        {
            temp.push_back(leaders[i]);
            leaderCount++;
        }
        else break;
    }
    printTies(temp);

    if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
    else
    {
        cout << fixed << setprecision(3) << leaders[leaderCount].getHits_By_Pitch() << "\t";
        int initialLeaderCount = leaderCount;
        for(i = leaderCount; i < (int)leaders.size(); i++) // 2nd PLACE TIES ///////////
        {
            if(leaders[i].getHits_By_Pitch() == leaders[initialLeaderCount].getHits_By_Pitch())
            {
                temp.push_back(leaders[i]);
                leaderCount++;
            }
            else break;
        }
        printTies(temp);

        if(leaderCount >= 3 || i >= (int)leaders.size()) {/*continue*/}
        else
        {
            cout << fixed << setprecision(3) << leaders[leaderCount].getHits_By_Pitch() << "\t";
            int initialLeaderCount = leaderCount;
            for(i = leaderCount; i < (int)leaders.size(); i++) // 3rd PLACE TIES ////////
            {
                if(leaders[i].getHits_By_Pitch() == leaders[initialLeaderCount].getHits_By_Pitch())
                {
                    temp.push_back(leaders[i]);
                    leaderCount++;
                }
                else break;
            }
            printTies(temp);
        }

    }
    cout << endl;
}



//----------Print Ties Helper-----------//

void printTies(vector<Player> &temp)
{
    std::sort(temp.begin(), temp.end(), compareName);
    int printedCount = 0;
    for (int j = 0; j < (int)temp.size(); j++) // AWAY /////////////
    {
        if (temp[j].isHome())
        {
            continue;
        }
        else
        {
            if (printedCount != 0)
            {
                cout << ", ";
            }

            cout << temp[j].getName();
            printedCount++;
        }
    }
    for (int j = 0; j < (int)temp.size(); j++) // HOME /////////////
    {
        if (temp[j].isHome())
        {
            if (printedCount != 0)
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

bool compareInput(Player &player1, Player &player2)
{
    return player1.getInput() < player2.getInput();
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