#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <memory>
#include <vector>
#include "Auxiliaries.h"

#define EMPTY_CELL -1

/** Type for defining the cell content */
typedef int cell_content_t;


/**
* Abstract class Character. 
* All characters types share the same fileds, that's why they're declared in this struct.
* There are 3 character types : Medic, Soldire, Sniper. Each type has his own class and override functions. 
* 
* The following functions are available: 
* 
*    roundUpDivision    -Returns a rounded up result of numerator devided by denominator.
* 
*    Character          -Construct a new Character object.
* 
*    ~Character         -Destroy the Character object.
* 
*    Character          -Copy construct - copies character object.
* 
*    operator=          -character 2= character1 : puts character 1 in character 2.  
* 
*    getTeam            -Returns character's team. 
* 
*    getHealth          -Returns character's health. 
* 
*    getAmmo            -Returns character's ammo. 
*  
*    getRange           -Returns character's range. 
* 
*    getPower           -Returns character's power.
* 
*    getCoordinates     -Returns character's coordinates.
* 
*    updateCoordinates  -Updates character's coordinates when the character moves to a destination grid point.
* 
*    increaseHealth     -Calculate and update character's health if attack occurs, according to characters typrs.
* 
*    moveInRange        -Checks if the destination grid point is included in the character's range
                          that he can move in.

*    reload             -Adds load additions to ammo and updates it. 
*
*    attackInRange      -Checks if the destination grid point is included in the character's range that he can attack in.
*                         Const grid point to insure we don't change it.
*
*    enoughAmmo          -Checks if current character has enough ammo in order to attack, because every attack costs ammo.
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
    /**
    * roundUpDivision: Returns a rounded up result of numerator devided by denominator.
    *
    * @param numerator - The number we want to divide - numerator. 
    * @param denominator - The number we want to divide with - denominator.
    * @return
    *   rounded up division result. 
    */
    int static roundUpDivision(int numerator, int denominator);

public:
    /**
    * Character : Construct a new Character object.
    * 
    * @param team -
    *   Character's team.
    * @param health -
    *   Character's health.
    * @param ammo =
    *   Character's ammo.     
    * @param range -
    *   Character's range.
    * @param power -
    *   Character's power.
    */
    Character(mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

    /**
     * ~Character : Destroy the Character object.
     * 
     */
    ~Character() = default;

    /**
     * Character : Copy construct - copies character object.
     * 
     */
    Character(const Character&) = default;


    /**
     * operator= :  character 2= character1 : puts character 1 in character 2.  
     * 
     * @return Character2 
     */
    Character& operator=(const Character&) = default;

    /**
    * getTeam: Returns character's team. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's team. 
    */
    mtm::Team getTeam() const;


    /**
    * getHealth: Returns character's health. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's health. 
    */
    mtm::units_t getHealth() const;


    /**
    * getAmmo: Returns character's ammo. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's ammo. 
    */
    mtm::units_t getAmmo() const;


    /**
    * getRange: Returns character's range. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's range. 
    */
    mtm::units_t getRange() const;


    /**
    * getPower: Returns character's power. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's power. 
    */
    mtm::units_t getPower() const;
    
    
    /**
    * getCoordinates: Returns character's coordinates. Const since wo don't want any changes in character.
    *
    * @return
    *   Character's coordinates. 
    */
    const mtm::GridPoint& getCoordinates() const;

    /**
    * updateCoordinates: Updates character's coordinates when the character moves to a destination grid point.
    *                    Const grid point to insure we don't change it.
    *
    * @param GridPoint& -
    *   The destination grid point that the character want's to move to.
    */    
    void updateCoordinates(const mtm::GridPoint&);

    /**
    * increaseHealth: Calculate and update character's health if attack occurs, according to characters typrs.
    *                    Const grid point to insure we don't change it.
    *
    * @param amount -
    *   The amount we want to add to current health.
    */ 
    void increaseHealth(mtm::units_t amount);

    /**
    * moveInRange: Checks if the destination grid point is included in the character's range that he can move in.
    *                    Const grid point to insure we don't change it.
    *
    * @param dst -
    *   The destination grid point wa want to check.
    * @return
    *   True if the grid point is in range, false otherwise.
    */ 
    bool moveInRange(const mtm::GridPoint& dst) const;

    /**
    * reload: Adds load additions to ammo and updates it. 
    *
    */ 
    void reload();

    /**
    * attackInRange: Checks if the destination grid point is included in the character's range that he can attack in.
    *                    Const grid point to insure we don't change it.
    *                    virtual function because every character type has her own range and conditions.    
    *
    * @param dst_grid_point -
    *   The destination grid point we want to check.
    * @return
    *   True if the grid point is in range, false otherwise.
    */ 
    virtual bool attackInRange(const mtm::GridPoint& dst_grid_point) const = 0;


    /**
    * enoughAmmo: Checks if current character has enough ammo in order to attack, because every attack costs ammo.
    *
    * @param dst_grid_team -
    *   The opponent team we want to attack.
    * @return
    *   True if the character has enough ammo to attack, false otherwise.
    */ 
    virtual bool enoughAmmo(cell_content_t dst_character_team) const = 0;


    /**
    * legalTarget: Checks if current character can attack this target according to character's requirments.
    *
    * @param GridPoint -
    *   The opponent grid point we want to attack.
    * @param dst_character_team -
    *   The opponent team we want to attack.
    * @return
    *   True if the character can attack this target, false otherwise.
    */ 
    virtual bool legalTarget(const mtm::GridPoint&, cell_content_t dst_character_team) const = 0;


    /**
    * updateAmmo: Subtract character's attack cost from ammo and updates it. 
    *
    * @param dst_character_team -
    *   The opponent team we attacked.
    */ 
    virtual void updateAmmo(cell_content_t dst_character_team) = 0;


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
    virtual void updateTargetsHealth(const mtm::GridPoint& dst, std::vector<std::shared_ptr<Character>>&) = 0;
    
    
     /**
    * getTypeChar: Returns the character's team and type : "character's team"_"character's type".
    *
    * @return
    *   Character's team and type. 
    */ 
    virtual char getTypeChar() const = 0;
    
    /**
     * clone : clone function. 
     * 
     * @return Character* 
     */
    virtual Character* clone() const = 0;
};
#endif
