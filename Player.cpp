#include "Player.h"

#include <iostream>
#include <iomanip>

//--------------------Constructors & Destructors--------------------//
Player::Player()
{
    name = "";
    home = true;
    at_bats = 0;
    hits = 0;
    walks = 0;
    strikeouts = 0;
    hits_by_pitch = 0;
    sacrifices = 0;
    plate_appearances = 0;
    input = 0;
}

Player::Player(const Player &player)
{
    name = player.name;
    home = player.home;
    at_bats = player.at_bats;
    hits = player.hits;
    walks = player.walks;
    strikeouts = player.strikeouts;
    hits_by_pitch = player.hits_by_pitch;
    sacrifices = player.sacrifices;
    plate_appearances = player.plate_appearances;
    input = player.input;
}

Player::~Player()
{
    //nothing to do here
}


//--------------------Overloaded Operators--------------------//
std::ostream &operator<<(std::ostream &os, const Player &player)
{
    os << player.name << "\t" 
    << player.name << "\t" 
    << player.at_bats << "\t" 
    << player.hits << "\t" 
    << player.walks << "\t" 
    << player.strikeouts << "\t" 
    << player.hits_by_pitch << "\t" 
    << player.sacrifices << "\t" 
    << std::fixed << std::setprecision(3) 
    << player.getBatting_Average() << "\t" << player.getOn_Base_Percentage() << "\n";
    return os;
}

bool Player::operator==(const Player &player) const
{
    return (name == player.name && 
    home == player.home && 
    at_bats == player.at_bats && 
    hits == player.hits && 
    walks == player.walks && 
    strikeouts == player.strikeouts && 
    hits_by_pitch == player.hits_by_pitch && 
    sacrifices == player.sacrifices && 
    plate_appearances == player.plate_appearances);
}

bool Player::operator<(const Player &player) const
{
    return (name < player.name);
}

bool Player::operator>(const Player &player) const
{
    return (name > player.name);
}