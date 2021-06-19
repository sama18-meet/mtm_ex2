#include "Sniper.h"

using namespace mtm;
using std::shared_ptr;


Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) :
                    Character(team, health, ammo, range, power), attack_counter(0) {
    motion_range = SNIPER_MOTION_RANGE;
    load_addition = SNIPER_LOAD_ADDITION;
}


bool Sniper::attackInRange(const GridPoint& dst_grid_point) const {
    int distance = GridPoint::distance(coordinates, dst_grid_point);
    int min_dist = (range%2 == 0) ? range/2 : range/2 + 1;
    if (distance > range || distance < min_dist) {
        return false;
    }
    return true;
}


bool Sniper::enoughAmmo(cell_content_t dst_team) const {
    return ammo >= 1;
}


bool Sniper::legalTarget(const GridPoint& dst_grid_point, cell_content_t dst_team) const {
    if (dst_team == this->team) {
        return false;
    }
    return true;
}

void Sniper::updateAmmo(cell_content_t dst_character_team) {
    ammo -= 1;
}
void Sniper::updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>> characters) {
    for (shared_ptr<Character> curr_character : characters) {
        if (!(curr_character->getCoordinates() == dst)) {
            continue; 
        }
        if (attack_counter%3 == 2) {
            curr_character->increaseHealth(-power*2);
        }
        else {
            curr_character->increaseHealth(-power);
        }
        break;
    }
    attack_counter++;
}

char Sniper::getTypeChar() const {
    return team==POWERLIFTERS ? 'N' : 'n';
}


Character* Sniper::clone() const {
    return new Sniper(*this);
}
