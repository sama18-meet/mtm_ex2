#include "Sniper.h"

using namespace mtm;

bool Sniper::attackInRange(GridPoint dst_grid_point) override {
    int distance = GridPoint::distance(coordinates, dst_grid_point);
    if (distance > range || distance < (range/2 + 1)) {
        return false;
    }
    return true;
}


bool Sniper::enoughAmmo(Team dst_team) override {
    return ammo >= 1;
}


bool Sniper::legalTarget(Team dst_team) override {
    if (dst_team == this->team) {
        return false;
    }
    return true;
}
