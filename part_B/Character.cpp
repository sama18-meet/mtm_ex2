#include "Character.h"

#define UNDEFINED -1

using std::shared_ptr;
using namespace mtm;

Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power) : 
                    team(team), health(health), ammo(ammo), range(range), power(power), coordinates(GridPoint(-1,-1)) {}


Team Character::getTeam() const {
    return this->team;
}
units_t Character::getHealth() const {
    return this->health;
}
units_t Character::getAmmo() const {
    return this->ammo;
}
units_t Character::getRange() const {
    return this->range;
}
units_t Character::getPower() const {
    return this->power;
}

void Character::increaseHealth(units_t amount) {
    health += amount; 
}

const GridPoint& Character::getCoordinates() const {
    return this->coordinates;
}

void Character::updateCoordinates(const GridPoint& grid_point) {
    coordinates = grid_point; 
}

bool Character::moveInRange(const GridPoint& dst) const {
    if (GridPoint::distance(coordinates, dst) <= motion_range) {
        return true;
    }
    return false;
}

void Character::reload(){
    ammo += this->load_addition;
}

int Character::roundUpDivision(int numerator, int denominator) {
    return (numerator%denominator == 0) ? numerator/denominator : numerator/denominator + 1;
}
