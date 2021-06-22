#ifndef _SNIPER_H
#define _SNIPER_H

#include "Character.h"

#define SNIPER_MOTION_RANGE 4
#define SNIPER_LOAD_ADDITION 2

/**
* Sniper class - one of the three character types.  
* The following functions are available : 
*    enoughAmmo          -Checks if current character has enough ammo in order to attack, because every attack costs ammo.
*
*   attackInRange      -Checks if the destination grid point is included in the character's range that he can attack in.
*                         Const grid point to insure we don't change it.
*
*    legalTarget         -Checks if current character can attack this target according to character's requirments.
*
*    updateAmmo          -Subtract character's attack cost from ammo and updates it. 
*
*    updateTargetsHealth  -Updates the opponent health that the character attacked
*                         according to character's requirments.

*   getTypeChar           -Returns the character's team and type : "character's team"_"character's type".
*
*   clone                 -clone function. 
*
*/
class Sniper : public Character {
private:
    int attack_counter;
private:

    /**
    * enoughAmmo: Checks if current character has enough ammo in order to attack, because every attack costs ammo.
    *
    * @param dst_team -
    *   The opponent team we want to attack.
    * @return
    *   True if the character has enough ammo to attack, false otherwise.
    */ 
    bool enoughAmmo(cell_content_t dst_team) const override;


    /**
    * attackInRange: Checks if the destination grid point is included in the Sniper's range that he can attack in.
    *                    Const grid point to insure we don't change it.
    *                    virtual function because every character type has her own range and conditions.    
    *
    * @param dst_grid_point -
    *   The destination grid point we want to check.
    * @return
    *   True if the grid point is in range, false otherwise.
    */ 
    bool attackInRange(const mtm::GridPoint& dst_grid_point) const override;


    /**
    * legalTarget: Checks if current character can attack this target according to Sniper's requirments.
    *
    * @param GridPoint -
    *   The opponent grid point we want to attack.
    * @param dst_character_team -
    *   The opponent team we want to attack.
    * @return
    *   True if the character can attack this target, false otherwise.
    */
    bool legalTarget(const mtm::GridPoint&, cell_content_t dst_team) const override;


    /**
    * updateAmmo: Subtract character's attack cost from ammo and updates it. 
    *
    * @param dst_character_team -
    *   The opponent team we attacked.
    */ 
    void updateAmmo(cell_content_t dst_character_team);


    /**
    * updateTargetsHealth: Updates the opponent health that the character attacked
    *                      according to character's requirments.
    *
    * @param dst -
    *   The opponent grid point the character attacked.
    * @param std::vector<std::shared_ptr<Character>> -
    *   Every index in this array points to a character who's in the grid..
    * 
    */
    void updateTargetsHealth(const mtm::GridPoint& dst,
                                std::vector<std::shared_ptr<Character>>& characters);


    /**
    * getTypeChar: Returns the character's team and type : "character's team"_"character's type".
    *
    * @return
    *   Character's team and type. 
    */
    char getTypeChar() const override;


    /**
    * clone : clone function. 
    * 
    * @return Character* 
    */
    Character* clone() const override;

public:
    /**
    * @brief Construct a new Sniper object
    * 
    * @param team -
    *  Sniper's team.
    * @param health -
    *   Sniper's health.
    * @param ammo -
    *   Sniper's ammo.
    * @param range -
    *   Sniper's range.
    * @param power -
    *   Sniper's power. 
    */
    Sniper(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
};
#endif // _SNIPER_H
