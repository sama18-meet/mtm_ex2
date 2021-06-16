#include <memory>
#include <cstddef>
#include <string.h>
#include "Game.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

using namespace mtm;
using std::shared_ptr;


Game::Game(int height, int width) {
    if (height <=0 || width <=0){
        throw IllegalArgument(); 
    }
    height = height;
    width = width;
    grid = new char[height*width]; 
    memset(grid, ' ', height*width);
}

Game::~Game() {
    delete[] grid;
}

Game::Game(const Game& other) : height(other.height), width(other.width) {
    characters_vec = other.characters_vec;  
    strncpy(grid, other.grid, height*width);
}

Game& Game::operator=(const Game& other) {
    height = other.height;
    width = other.width;
    characters_vec = other.characters_vec;  
    strncpy(grid, other.grid, height*width);
    return *this;
}


char getCharacterTypeChar(Character* character) {
    if (dynamic_cast<Soldier*>(character) != nullptr) {
        return character->getTeam() == CROSSFITTERS ? 's' : 'S';    
    }
    if (dynamic_cast<Medic*>(character) != nullptr) {
        return character->getTeam() == CROSSFITTERS ? 'm' : 'M';    
    }
    if (dynamic_cast<Sniper*>(character) != nullptr) {
        return character->getTeam() == CROSSFITTERS ? 'n' : 'N';    
    }
    return '?';
}


void Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character) {
    if (!legalCell(coordinates)) {
        throw IllegalCell();
    }
    if (cellOccupied(coordinates)) {
        throw CellOccupied();
    }
    characters_vec.push_back(character);
    int index_in_char_arr = coordinates.row*coordinates.col+coordinates.row;
    char character_type = getCharacterTypeChar(character.get());
    grid[index_in_char_arr] = character_type;
}


shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
    if (health <= 0 || ammo < 0 || power < 0 || range < 0) {
        throw IllegalArgument();
    }
    //shared_ptr<Character> new_character_ptr;
    //if (type == SOLDIER) {
        Soldier new_soldier = Soldier(team, health, ammo, range, power);
        Character* new_character_ptr = &new_soldier;
        shared_ptr<Character>new_character_shared_ptr(new_character_ptr);
    //}
/*    else if (type == MEDIC) {
        new_character = Medic(team, health, ammo, range, power);
    }
    else if (type == SNIPER) {
        new_character = Sniper(team, health, ammo, range, power);
    }
*/
    return new_character_shared_ptr;
}


bool Game::isOver(Team* winningTeam) const {
    if (characters_vec.size()==0) {
        return false;
    }
    Team first_character_team = (*(characters_vec.begin()))->getTeam();
    for (shared_ptr<Character> curr_character : characters_vec) {
        if(curr_character->getTeam() != first_character_team) {
            return false;
        }
    } 
    if (winningTeam != nullptr) {
        *winningTeam = first_character_team;
    }
    return true;
}

