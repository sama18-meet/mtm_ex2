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
bool Character::canMove(const GridPoint& src, const GridPoint& dst) const {
    if (GridPoint::distance(src, dst) <= motion_range) {
        return true;
    }
    return false;
}

void Character::reload(){
    ammo += this->load_addition;
}

bool Character::canAttack(shared_ptr<Character> dst_character, const GridPoint& dst_coordinates) const {
    cell_content_t dst_team;
    GridPoint dst_grid_point(UNDEFINED, UNDEFINED);
    if(dst_character == nullptr) {
        dst_team = EMPTY_CELL;
        dst_grid_point = dst_coordinates;
    }
    else {
        dst_team = static_cast<cell_content_t>(dst_character->getTeam());
        dst_grid_point = dst_character->getCoordinates();
    }
    if (!attackInRange(dst_grid_point) || !enoughAmmo(dst_team) || !legalTarget(dst_team))
    {
        return false;
    }
    return true;
}

