#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <memory>
#include <vector>
#include "Auxiliaries.h"

typedef int cell_content_t;
// abstract class

class Character {
protected:
    mtm::Team team;
    mtm::units_t health;
    mtm::units_t ammo;
    mtm::units_t range;
    mtm::units_t power;
    mtm::GridPoint coordinates;
    mtm::units_t motion_range;
    mtm::units_t load_addition;

protected:
    bool canMove(const mtm::GridPoint& src, const mtm::GridPoint& dst);
    bool canAttack(std::shared_ptr<Character> dst_character, mtm::GridPoint dst_coordinates);
    virtual bool attackInRange(mtm::GridPoint dst_grid_point) = 0;
    virtual bool enoughAmmo(cell_content_t dst_character_team) = 0;
    virtual bool legalTarget(cell_content_t dst_character_team) = 0;
    // virtual void updateAmmo(std::shared_ptr<Character> target) = 0;
    // virtual void updateTargetsHealth(std::vector<Character> characters) = 0;
    void reload();

public:
    Character(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::GridPoint coordinates);
    ~Character() = default;
    Character(const Character&) = default;
    Character& operator=(const Character&) = default;
    mtm::Team getTeam();
    mtm::units_t getHealth();
    mtm::units_t getAmmo();
    mtm::units_t getRange();
    mtm::units_t getPower();
    mtm::GridPoint getCoordinates();
    // clone();
};
#endif
