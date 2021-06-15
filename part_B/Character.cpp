#include "Character.h"

using namespace mtm;

Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPint coordinates) : 
                    team(team), health(health), ammo(ammo), range(range), power(power), coordinates(coordinates) {}


Team Character::getTeam(){
    return this->team;
}
units_t Character::getHealth(){
    return this->health;
}
units_t Character::getAmmo(){
    return this->ammo;
}
units_t Character::getRange(){
    return this->range;
}
units_t Character::getPower(){
    return this->power;
}
GridPoint Character::getCoordinates(){
    return this->coordinates;
}
