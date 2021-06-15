#include "Soldier.h"

using std::shared_ptr;
using namespace mtm;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates) :
                    team(team), health(health), ammo(ammo), range(range), power(power), coordinates(coordinates),
                    motion_range(SOLDIER_MOTION_RANGE), load_addition(SOLDIER_LOAD_ADDITION) {}

bool Soldier::attackInRange(shared_ptr<GridPoint> dst_grid_point) {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    if (coordinates.row != dst_grid_point.row && coordinates.col != dst_grid_point.col) {
        return false
    }
    return true;
}

bool Soldier::enoughAmmo(Team dst_team) {
    return ammo >= 1;
}

bool legalTarget(Team dst_team) {
    return true;
}
