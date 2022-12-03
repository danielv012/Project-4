#ifndef PLAYER_H
#define PLAYER_H

#include <string>

//q: how do I correctly format a highlighted block of text by lines in vscode?
//a: use the "editor.action.smartSelect.grow" command (ctrl+shift+right arrow)
//   to select the lines you want to format, then use the "editor.action.formatSelection" command (ctrl+k, ctrl+f)
//   to format the selected lines





class Player
{
public:
    Player();
    Player(const Player &player);
    ~Player();

    //getters
    std::string getName() const { return name; }
    bool isHome() const { return home; }
    int getAt_Bats() const { return at_bats; }
    int getHits() const { return hits; }
    int getWalks() const { return walks; }
    int getStrikeouts() const { return strikeouts; }
    int getHits_By_Pitch() const { return hits_by_pitch; }
    int getSacrifices() const { return sacrifices; }
    int getPlate_Appearances() const { return plate_appearances; }

    //setters
    void setName(std::string name) { this->name = name; }
    void setHome(bool home) { this->home = home; }
    void setAt_Bats(int at_bats) { this->at_bats = at_bats; }
    void setHits(int hits) { this->hits = hits; }
    void setWalks(int walks) { this->walks = walks; }
    void setStrikeouts(int strikeouts) { this->strikeouts = strikeouts; }
    void setHits_By_Pitch(int hits_by_pitch) { this->hits_by_pitch = hits_by_pitch; }
    void setSacrifices(int sacrifices) { this->sacrifices = sacrifices; }
    void setPlate_Appearances(int plate_appearances) { this->plate_appearances = plate_appearances; }

    //calculators
    double getBatting_Average() const { return (double)hits / at_bats; }
    double getOn_Base_Percentage() const { return (double)(hits + walks + hits_by_pitch) / plate_appearances; }

    //overloaded operators
    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    bool operator<(const Player &player) const;
    bool operator>(const Player &player) const;
    bool operator==(const Player &player) const;
    
private:
    std::string name;
    bool home; //is the player on the home team? (true) or the away team? (false)
    int at_bats, hits, walks, strikeouts, hits_by_pitch, sacrifices, plate_appearances;
};


#endif //PLAYER_H