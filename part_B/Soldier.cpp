#include "Soldier.h"

using namespace mtm;
using std::shared_ptr;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates) :
                    Character(team, health, ammo, range, power, coordinates) {
    motion_range = SOLDIER_MOTION_RANGE;
    load_addition = SOLDIER_LOAD_ADDITION;
}

bool Soldier::attackInRange(GridPoint dst_grid_point) {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    if (coordinates.row != dst_grid_point.row && coordinates.col != dst_grid_point.col) {
        return false;
    }
    return true;
}

bool Soldier::enoughAmmo(cell_content_t dst_team) {
    return ammo >= 1;
}

bool Soldier::legalTarget(cell_content_t dst_team) {
    return true;
}


void Soldier::updateAmmo(std::shared_ptr<Character> target) {
    ammo -= SOLDIER_ATTACK_COST;
}


void Soldier::updateTargetsHealth(const GridPoint& dst, std::vector<shared_ptr<Character>> characters) {
    for (shared_ptr<Character> curr_character : characters) {
        if (curr_character->getTeam() == team) {
            continue;
        }
        int distance = GridPoint::distance(curr_character->getCoordinates(), coordinates);
        if (distance == 0) {
            curr_character->increaseHealth(-power);
            continue;
        }
        if (distance <= range/3 + 1) {
            curr_character->increaseHealth(-(power/2 + 1));
        }
    }
}
