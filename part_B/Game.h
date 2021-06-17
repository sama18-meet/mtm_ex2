#include <memory>
#include <vector>
#include "Auxiliaries.h"
#include "Character.h"

class Game {
private:
    int height;
    int width;
    char* grid;
    std::vector<std::shared_ptr<Character>> characters_vec;


private:
    bool legalCell(const mtm::GridPoint& grid_point);
    bool cellOccupied(const mtm::GridPoint& grid_point);
    char getCharacterTypeChar(Character*);
    std::shared_ptr<Character> getCharacterByCoordinates(const mtm::GridPoint&);

public: // ?
    Game(int height, int width);
    ~Game();
    Game(const Game& other);
    Game& operator=(const Game& other);
    void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);
    static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
    void move(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);
    void attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);
    void reload(const mtm::GridPoint & coordinates);
    bool isOver(mtm::Team* winningTeam=NULL) const;
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
