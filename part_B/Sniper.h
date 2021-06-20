#ifndef _SNIPER_H
#define _SNIPER_H

#include "Character.h"

#define SNIPER_MOTION_RANGE 4
#define SNIPER_LOAD_ADDITION 2


class Sniper : public Character {
private:
    int attack_counter;
private:
    bool enoughAmmo(cell_content_t dst_team) const override;
    bool attackInRange(const mtm::GridPoint& dst_grid_point) const override;
    bool legalTarget(const mtm::GridPoint&, cell_content_t dst_team) const override;
    void updateAmmo(cell_content_t dst_character_team);
    void updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>> characters);
    char getTypeChar() const override;
    Character* clone() const;

public:
    Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
};
#endif // _SNIPER_H
