#include "Character.h"

#define MEDIC_MOTION_RANGE 5
#define MEDIC_LOAD_ADDITION 5


class Medic: public Character {
private:
    bool enoughAmmo(cell_content_t dst_team) override;
    bool attackInRange(mtm::GridPoint dst_grid_point) override;
    bool legalTarget(cell_content_t dst_team);
public:
    Medic(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::GridPoint coordinates);
};
