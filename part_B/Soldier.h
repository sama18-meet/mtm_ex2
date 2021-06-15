#include "Character.h"

#define SOLDIER_MOTION_RANGE 3
#define SOLDIER_LOAD_ADDITION 3


class Soldier: public Character {
private:
    const int motion_range;
    const int load_addition;
public:
    Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power, GridPoint coordinates);
};
