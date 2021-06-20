#ifndef _MEDIC_H
#define _MEDIC_H

#include "Character.h"

#define MEDIC_MOTION_RANGE 5
#define MEDIC_LOAD_ADDITION 5


class Medic: public Character {
private:
    bool enoughAmmo(cell_content_t dst_team) const override;
    bool attackInRange(const mtm::GridPoint& dst_grid_point) const override;
    bool legalTarget(const mtm::GridPoint&, cell_content_t dst_team) const override;
    void updateAmmo(cell_content_t dst_character_team);
    void updateTargetsHealth(const mtm::GridPoint& dst,
                            std::vector<std::shared_ptr<Character>>& characters);
    char getTypeChar() const override;
    Character* clone() const override;
public:
    Medic(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
};
#endif // _MEDIC_H
