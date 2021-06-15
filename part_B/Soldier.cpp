

bool Soldier::attackInRange(GridPoint src_grid_point, GridPoint dst_grid_point) override {
    if (GridPoint::distance(src_grid_point, dst_grid_point) > range) {
        return false;
    }
    if (src_grid_point.x != dst_grid_point.x && src_grid_point.y != dst_grid_point.y) {
        return false
    }
    return true;
}

bool Soldier::isOutOfAmmo(CharacterCoordinates dst_character_coordinates) override {
    return ammo < 1;
}

bool legalTarget(CharacterCoordinates dst_character_coordinates) override {
    return true;
}
