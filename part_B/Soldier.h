#include "Character.h"

#define SOLDIER_MOTION_RANGE 3
#define SOLDIER_LOAD_ADDITION 3
#define SOLDIER_ATTACK_COST 1


class Soldier: public Character {
private:
    bool enoughAmmo(cell_content_t dst_team) const override;
    bool attackInRange(const mtm::GridPoint& dst_grid_point) const override;
    bool legalTarget(const mtm::GridPoint&, cell_content_t dst_team) const override;
    void updateAmmo(cell_content_t dst_character_team);
    void updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>>);
    char getTypeChar() const override;
    Character* clone() const;
public:
    Soldier(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
};
