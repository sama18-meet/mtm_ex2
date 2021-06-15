
bool Sniper::attackInRange(GridPoint src_grid_point, GridPoint dst_grid_point) override {
    int distance = GridPoint::distance(src_grid_point, dst_grid_point);
    if (distance > range || distance < (range/2 + 1)) {
        return false;
    }
}


bool Sniper::isOutOfAmmo(CharacterCoordinates dst_character_coordinates) override {
    return ammo < 1;
}


bool Sniper::legalTarget(CharacterCoordinates dst_character_coordinates) override {
    if (dst_character_coordinates->character->team == this->team) {
        return false;
    }
    return true;
}
