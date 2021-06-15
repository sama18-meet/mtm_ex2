#include "Soldier.h"

using namespace mtm;

bool Soldier::attackInRange(GridPoint dst_grid_point) override {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    if (src_grid_point.x != dst_grid_point.x && src_grid_point.y != dst_grid_point.y) {
        return false
    }
    return true;
}

bool Soldier::enoughAmmo(Team dst_team) override {
    return ammo >= 1;
}

bool legalTarget(Team dst_team) override {
    return true;
}
