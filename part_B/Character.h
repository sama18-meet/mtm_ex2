#include <memory>

#include <Auxiliaries.h>

// abstract class

class Character {
protected:
    mtm::Team team;
    mtm::units_t health;
    mtm::units_t ammo;
    mtm::units_t range;
    mtm::units_t power;
    mtm::GridPoint coordinates;

protected:
    bool canMove(const mtm::GridPoint& src, const mtm::GridPoint& dst);
    bool canAttack(std::shared_ptr<Character> dst_character, std::shared_ptr<mtm::GridPoint> dst_coordinates);
    virtual bool attackInRange(std::shared_ptr<mtm::GridPoint> dst_grid_point) = 0;
    virtual bool enoughAmmo(mtm::Team dst_character_team) = 0;
    virtual bool legalTarget(mtm::Team dst_character_team) = 0;
    virtual void updateAmmo(std::shared_ptr<Character> target) = 0;
    virtual void updateTargetsHealth(std::vector<Character> characters) = 0;
    void reload();

public:
    Character(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
    ~Character() = default;
    Character(const Character&) = default;
    Character& operator=(const Character&) = default;
    clone();
}
