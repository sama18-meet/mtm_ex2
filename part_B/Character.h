#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <memory>
#include <vector>
#include "Auxiliaries.h"

#define EMPTY_CELL -1

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

public:
    virtual bool attackInRange(const mtm::GridPoint& dst_grid_point) const = 0;
    virtual bool enoughAmmo(cell_content_t dst_character_team) const = 0;
    virtual bool legalTarget(cell_content_t dst_character_team) const = 0;
    virtual void updateAmmo(std::shared_ptr<Character> target) = 0;
    virtual void updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>> characters) = 0;
    Character(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
    ~Character() = default;
    Character(const Character&) = default;
    Character& operator=(const Character&) = default;
    mtm::Team getTeam() const;
    mtm::units_t getHealth() const;
    mtm::units_t getAmmo() const;
    mtm::units_t getRange() const;
    mtm::units_t getPower() const;
    const mtm::GridPoint& getCoordinates() const;
    void updateCoordinates(const mtm::GridPoint&);
    void increaseHealth(mtm::units_t amount);
    bool moveInRange(const mtm::GridPoint& dst) const;
    virtual Character* clone() const = 0;
    void reload();
};
#endif
