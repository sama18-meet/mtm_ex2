#include "Medic.h"

using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates) :
                    Character(team, health, ammo, range, power, coordinates) {
    motion_range = MEDIC_MOTION_RANGE;
    load_addition = MEDIC_LOAD_ADDITION;
}

bool Medic::attackInRange(GridPoint dst_grid_point) {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    return true;
}


bool Medic::enoughAmmo(cell_content_t dst_team) {
    if (dst_team == static_cast<cell_content_t>(this->getTeam())) {
        return true;
    }
    return ammo >= 1;
}


bool Medic::legalTarget(cell_content_t dst_team) {
    if (dst_team == EMPTY_CELL) {
        return false;
    }
    return true;
}

