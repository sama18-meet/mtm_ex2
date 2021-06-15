#include "Medic.h"

using namespace mtm;

bool Medic::attackInRange(GridPoint dst_grid_point) override {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    return true;
}


bool Medic::enoughAmmo(Team dst_team) override {
    if (dst_team == this->team()) {
        return true;
    }
    return ammo >= 1;
}


bool Medic::legalTarget(Team dst_team) override {
    if (dst_team == EMPTY_CELL) {
        return false;
    }
    return true;
}
