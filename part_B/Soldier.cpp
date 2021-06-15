#include "Soldier.h"

using namespace mtm;

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
