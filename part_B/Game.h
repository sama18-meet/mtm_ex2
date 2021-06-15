#include "Auxiliaries.h"
#include <memory>



class Game {
private:
    struct CharacterCoordinates_t {
        std::shared_ptr<GridPoint> grid_point;
        std::shared_ptr<Character> character;
    } std::shared_ptr<CharacterCoordinates>;

    int height;
    int width;
    char* grid;
    vector<shared_ptr<Character>> grid_state;


private:
    bool legalCell(const GridPoint&, grid_point);
    bool cellOccupied(const GridPoint& grid_point);

public: // ?
    Game(int height, int width);
    ~Game();
    Game(const Game& other);
    Game& operator=(const Game& other);
    void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
    static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health,
    void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void reload(const GridPoint & coordinates);
    std::ostream& operator<<(std::ostream& os, const char* grid);
    bool isOver(Team* winningTeam=NULL) const;

}
