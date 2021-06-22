#ifndef _GAME_H
#define _GAME_H

#include <memory>
#include <vector>
#include "Auxiliaries.h"
#include "Character.h"

/**
* The main class.
* 
* The following functions are available: 
* 
*   Game              -Construct a new Game object.
*   ~Game             -Destroy the Game object.
*   Game              -Copy construct a game object.
*   operator=         -game2=game 1 - puts game1 in game2 
*   addCharacter      -Adds a character to the game.  
*   makeCharacter     -makes a character and puts the values in their places.  
*   move              -Moves a character from source coordinates to a distination coordinates,
*                      after checking if this move is legal.
*   attack            -Checks if this attack is legal, then updates everything according to the characters types.
*   reload            -updates ammo of the character according to the attack.
*   isOver            -Checks if there is a winnig team in the grid. 
*   operator<<        -output operator.
*   legalCell         -Check is the grid point is legal - if row and col are included in the grid.  
*   cellOccupied      -Check if there's a character in this grid point. 
*   get1DIndexByCoordinates   -Returns the 1 diminsion index, according to grid pont coordinates. 
*   getCharacterByCoordinates -Get the Character By Coordinates object.
*/

class Game {
private:
    int height;
    int width;
    std::string grid;
    std::vector<std::shared_ptr<Character>> characters_vec;

public: 
    /**
    * Game: Construct a new Game object
    * 
    * @param height - game's height. 
    * @param width - game's width. 
    */
    Game(int height, int width);

    /**
    * ~Game: Destroy the Game object
    * 
    */
    ~Game() = default;

    /**
    * Game: Copy construct a game object
    * 
    * @param other - 
    *  The game we want to copy.
    */
    Game(const Game& other) = default;

    /**
    * operator= : game2=game 1 - puts game1 in game2 
    * 
    * @param other - 
    *  The game we want to put in another one. 
    * @return Game& 
    */
    Game& operator=(const Game& other) = default;

    /**
    * addCharacter : Adds a character to the game.  
    * 
    * @param coordinates -
    *  The coordinated in the game we want to put the character in.
    *  
    * @param character - 
    *  The vector that holds all characters. We want to add an 
    *  index in this vector to point to the new character. 
    */
    void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);

    /**
    * makeCharacter : makes a character and puts the values in their places.  
    * 
    * @param type - character's type. 
    * @param team - character's team. 
    * @param health - character's health. 
    * @param ammo - character's ammo. 
    * @param range - character's range. 
    * @param power - character's power. 
    * @return std::shared_ptr<Character> - a vector with the new character added.
    */
    static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team,
            mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);

    /**
    * move : Moves a character from source coordinates to a distination coordinates,
    *        after checking if this move is legal. 
    * 
    * @param src_coordinates - Current character coordinates, that the character wants to move from.
    * @param dst_coordinates - The destination coordinates that the character wants to move to. 
    */
    void move(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);

    /**
    * attack : Checks if this attack is legal, then updates everything according to the characters types.
    * 
    * @param src_coordinates - Grid point of the character who want's to attack.  
    * @param dst_coordinates - Grid point of the character who's beeing attacked.
    */
    void attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);


    /**
    * reload : updates ammo of the character according to the attack.
    * 
    * @param coordinates - grid point of the character we want to update ammo in. 
    */
    void reload(const mtm::GridPoint & coordinates);

    /**
    * isOver : Checks if there is a winnig team in the grid. 
    * 
    * @param winningTeam 
    * @return true if all character in the grid are in the same team.  
    * @return false if there are characters in both of the teams, or if there aren't characters at all.
    */
    bool isOver(mtm::Team* winningTeam=NULL) const;

    /**
    * operator<< : output operator.
    * 
    * @param os 
    * @param game 
    * @return std::ostream& 
    */
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

private:
    /**
    * legalCell : Check is the grid point is legal - if row and col are included in the grid.  
    * 
    * @param grid_point - 
    *  The grid point we want to check if it's legal. 
    * @return 
    *  True is the cell is legal, false otherwise.
    */
    bool legalCell(const mtm::GridPoint& grid_point) const;

    /**
    * cellOccupied : Check if there's a character in this grid point. 
    * 
    * @param grid_point - 
    *  the grid point we want to check. 
    * @return true if the cell is occuppied by a character, false otherwise.
    */
    bool cellOccupied(const mtm::GridPoint& grid_point) const;

    /**
    * getCharacterByCoordinates : Get the Character By Coordinates object.
    * 
    * @return std::shared_ptr<Character> - returns a shared pointer to the character.
    */
    std::shared_ptr<Character> getCharacterByCoordinates(const mtm::GridPoint&) const;

    /**
    * get1DIndexByCoordinates : Returns the 1 diminsion index, according to grid pont coordinates. 
    * 
    * @return The 1D index.  
    */
    int get1DIndexByCoordinates(const mtm::GridPoint&) const;


};

#endif
