
bool Medic::attackInRange(GridPoint src_grid_point, GridPoint dst_grid_point) override {
    if (GridPoint::distance(src_grid_point, dst_grid_point) > range) {
        return false;
    }
    return true;
}


bool Medic::isOutOfAmmo(CharacterCoordinates dst_character_coordinates) override {
    if (dst_character_coordinates->character->team != this->team) {
        return ammo < 1;
    }
    return false;
}


bool Medic::legalTarget(CharacterCoordinates dst_character_coordinates) override {
    if (dst_character_coordinates->character == NULL) {
        return false;
    }
    return true;
}
