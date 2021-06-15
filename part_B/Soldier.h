#include "Character.h"

#define SOLDIER_MOTION_RANGE 3
#define SOLDIER_LOAD_ADDITION 3


class Soldier: public Character {
private:
    bool enoughAmmo(mtm::Team dst_team) override;
    bool attackInRange(mtm::GridPoint dst_grid_point);
public:
    Soldier(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::GridPoint coordinates);
};
