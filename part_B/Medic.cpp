#include "Medic.h"

#define POWERLIFTER_MEDIC 'M'
#define CROSSFITTER_MEDIC 'm'
#define MEDIC_ATTACK_COST 1


using namespace mtm;
using std::shared_ptr;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) :
                    Character(team, health, ammo, range, power) {
    motion_range = MEDIC_MOTION_RANGE;
    load_addition = MEDIC_LOAD_ADDITION;
}

bool Medic::attackInRange(const GridPoint& dst_grid_point) const {
    if (GridPoint::distance(coordinates, dst_grid_point) > range) {
        return false;
    }
    return true;
}


bool Medic::enoughAmmo(cell_content_t dst_team) const {
    if (dst_team == static_cast<cell_content_t>(this->getTeam())) {
        return true;
    }
    return ammo >= MEDIC_ATTACK_COST;
}


bool Medic::legalTarget(const GridPoint& dst_grid_point, cell_content_t dst_team) const {
    if (dst_team == EMPTY_CELL) {
        return false;
    }
    if (GridPoint::distance(coordinates, dst_grid_point) == 0) {
        return false;
    }
    return true;
}

void Medic::updateAmmo(cell_content_t dst_character_team) {
    if (dst_character_team != team) {
        ammo -= MEDIC_ATTACK_COST;
    }
}

void Medic::updateTargetsHealth(const mtm::GridPoint& dst, std::vector<shared_ptr<Character>> characters) {
    for (shared_ptr<Character> curr_character : characters) {
        if (curr_character->getCoordinates() == dst) {
            if (curr_character->getTeam() == team) {
                curr_character->increaseHealth(power);
            }
            else {
                curr_character->increaseHealth(-power);
            }
        break;
        }
    }
}

char Medic::getTypeChar() const {
    return team==POWERLIFTERS ? POWERLIFTER_MEDIC : CROSSFITTER_MEDIC;
}

Character* Medic::clone() const {
    return new Medic(*this);
}
