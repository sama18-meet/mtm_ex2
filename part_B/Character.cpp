#include "Character.h"

#define EMPTY_CELL -1
#define UNDEFINED -1

using std::shared_ptr;
using namespace mtm;

Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates) : 
                    team(team), health(health), ammo(ammo), range(range), power(power), coordinates(coordinates) {}


Team Character::getTeam() {
    return this->team;
}
units_t Character::getHealth() {
    return this->health;
}
units_t Character::getAmmo() {
    return this->ammo;
}
units_t Character::getRange() {
    return this->range;
}
units_t Character::getPower() {
    return this->power;
}

GridPoint Character::getCoordinates() {
    return this->coordinates;
}
bool Character::canMove(const GridPoint& src, const GridPoint& dst){
    if (GridPoint::distance(src, dst) <= motion_range) {
        return true;
    }
    return false;
}

void Character::reload(){
    ammo += this->load_addition;
}

bool Character::canAttack(shared_ptr<Character> dst_character, GridPoint dst_coordinates) {
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
