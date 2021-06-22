#include "Soldier.h"

#define POWERLIFTER_SOLDIER 'S'
#define CROSSFITTER_SOLDIER 's'
#define SOLDIER_ATTACK_COST 1
#define THREE 3
#define TWO 2


using namespace mtm;
using std::shared_ptr;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
                    Character(team, health, ammo, range, power) {
    motion_range = SOLDIER_MOTION_RANGE;
    load_addition = SOLDIER_LOAD_ADDITION;
}

bool Soldier::enoughAmmo(cell_content_t dst_team) const {
    return ammo >= SOLDIER_ATTACK_COST;
}

bool Soldier::attackInRange(const GridPoint& dst_grid_point) const {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    return true;
}


bool Soldier::legalTarget(const GridPoint& dst_grid_point, cell_content_t dst_team) const {
    if (coordinates.row != dst_grid_point.row && coordinates.col != dst_grid_point.col) {
        return false;
    }
    return true;
}


void Soldier::updateAmmo(cell_content_t dst_character_team) {
    ammo -= SOLDIER_ATTACK_COST;
}


void Soldier::updateTargetsHealth(const GridPoint& dst,
                                  std::vector<shared_ptr<Character>>& characters) {
    for (shared_ptr<Character> curr_character : characters) {
        if (curr_character->getTeam() == team) {
            continue;
        }
        int distance = GridPoint::distance(curr_character->getCoordinates(), dst);
        if (distance == 0) {
            curr_character->increaseHealth(-power);
            continue;
        }
        if (distance <= roundUpDivision(range,THREE)) {
            curr_character->increaseHealth(-roundUpDivision(power,TWO));
        }
    }
}

 
char Soldier::getTypeChar() const {
    return team==POWERLIFTERS ? POWERLIFTER_SOLDIER : CROSSFITTER_SOLDIER;
}

Character* Soldier::clone() const {
    return new Soldier(*this);
}
