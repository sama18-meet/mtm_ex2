#include "Sniper.h"

using namespace mtm;


Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates) :
                    Character(team, health, ammo, range, power, coordinates) {
    motion_range = SNIPER_MOTION_RANGE;
    load_addition = SNIPER_LOAD_ADDITION;
}


bool Sniper::attackInRange(GridPoint dst_grid_point) {
    int distance = GridPoint::distance(coordinates, dst_grid_point);
    if (distance > range || distance < (range/2 + 1)) {
        return false;
    }
    return true;
}


bool Sniper::enoughAmmo(cell_content_t dst_team) {
    return ammo >= 1;
}


bool Sniper::legalTarget(cell_content_t dst_team) {
    if (dst_team == this->team) {
        return false;
    }
    return true;
}
