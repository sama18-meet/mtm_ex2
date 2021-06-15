#include "Character.h"

#define SNIPER_MOTION_RANGE 4
#define SNIPER_LOAD_ADDITION 2


class Sniper : public Character {
private:
    bool enoughAmmo(cell_content_t dst_team) override;
    bool attackInRange(mtm::GridPoint dst_grid_point) override;
    bool legalTarget(cell_content_t dst_team);
public:
    Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::GridPoint coordinates);
};
