#include "Character.h"

#define SNIPER_MOTION_RANGE 4
#define SNIPER_LOAD_ADDITION 2


class Sniper : public Character {
private:
    int attack_counter;
private:
    bool enoughAmmo(cell_content_t dst_team) const override;
    bool attackInRange(const mtm::GridPoint& dst_grid_point) const override;
    bool legalTarget(cell_content_t dst_team) const override;
    void updateAmmo(std::shared_ptr<Character> target);
    void updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>> characters);
    Character* clone() const;

public:
    Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
};
