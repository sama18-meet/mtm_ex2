#include <memory>
#include <string.h>
#include "Game.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Exceptions.h"

using namespace mtm;
using std::shared_ptr;


Game::Game(int height, int width) :
        height(height), width(width), grid(height*width, ' '), characters_vec() {
    if (height <=0 || width <=0){
        throw IllegalArgument(); 
    }
}


shared_ptr<Character> Game::getCharacterByCoordinates(const GridPoint& grid_point) {
    for (shared_ptr<Character> curr_character : characters_vec) {
        if (curr_character->getCoordinates() == grid_point) {
            return curr_character; 
        }
    }
    return nullptr;
}

void Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character) {
    if (!legalCell(coordinates)) {
        throw IllegalCell();
    }
    if (cellOccupied(coordinates)) {
        throw CellOccupied();
    }
    character->updateCoordinates(coordinates);
    characters_vec.push_back(character);
    int index_in_char_arr = get1DIndexByCoordinates(coordinates);
    grid[index_in_char_arr] = character->getTypeChar();
}

int Game::get1DIndexByCoordinates(const GridPoint& coordinates) {
    return coordinates.row*width+coordinates.col;
}


shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
    if (health <= 0 || ammo < 0 || power < 0 || range < 0) {
        throw IllegalArgument();
    }
    if (type == SOLDIER) {
        shared_ptr<Character> new_character_shared_ptr(new Soldier(team, health, ammo, range, power));
        return new_character_shared_ptr;
    }
    else if (type == MEDIC) {
        shared_ptr<Character> new_character_shared_ptr(new Medic(team, health, ammo, range, power));
        return new_character_shared_ptr;
    }
    else if (type == SNIPER) {
        shared_ptr<Character> new_character_shared_ptr(new Sniper(team, health, ammo, range, power));
        return new_character_shared_ptr;
    }
    return nullptr;
}


void Game::move(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates) {
    if (!legalCell(dst_coordinates)) {
        throw IllegalCell();
    }
    if (!cellOccupied(src_coordinates)) {
        throw CellEmpty();
    }
    shared_ptr<Character> src_character = getCharacterByCoordinates(src_coordinates);
    if (!src_character->moveInRange(dst_coordinates)) {
        throw MoveTooFar();
    }
    if (cellOccupied(dst_coordinates)) {
        throw CellOccupied();
    }
    src_character->updateCoordinates(dst_coordinates);
}

bool Game::legalCell(const mtm::GridPoint& grid_point){
    if (grid_point.row>=0 && grid_point.row<width && grid_point.col>=0 && grid_point.col<height) {
        return true;
    }
    return false; 
}

bool Game::cellOccupied(const mtm::GridPoint& grid_point){
    return getCharacterByCoordinates(grid_point)!=nullptr;
}

void Game::reload(const mtm::GridPoint & coordinates){
    if(!legalCell(coordinates)){
        throw IllegalCell();
    }
    if(!cellOccupied(coordinates)){
        throw CellEmpty();
    }
    getCharacterByCoordinates(coordinates)->reload();
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

std::ostream& operator<<(std::ostream& os, const Game& game){
    printGameBoard(os, game.grid.c_str(), game.grid.c_str()+game.width*game.height, game.width);
    return os;
}

void Game::attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates){
    if(!legalCell(src_coordinates) || !legalCell(dst_coordinates)) {
        throw IllegalCell();
    }
    if(!cellOccupied(src_coordinates)) {
        throw CellEmpty();
    }
    shared_ptr<Character> src_character = getCharacterByCoordinates(src_coordinates);
    if(!src_character->attackInRange(dst_coordinates)) {
        throw OutOfRange();
    }
    cell_content_t dst_cell_content;
    shared_ptr<Character> dst_character = getCharacterByCoordinates(dst_coordinates);
    if (dst_character==nullptr){
        dst_cell_content=EMPTY_CELL;
    }
    else {
        dst_cell_content=dst_character->getTeam();
    }
    if (!src_character->enoughAmmo(dst_cell_content)) {
        throw OutOfAmmo();
    }
    if (!src_character->legalTarget(dst_cell_content)) {
        throw IllegalTarget();
    }
    src_character->updateAmmo(dst_cell_content);
    src_character->updateTargetsHealth(dst_coordinates, characters_vec);
    for (std::vector<shared_ptr<Character>>::iterator it = characters_vec.begin(); it!=characters_vec.end(); ) {
        if ((*it)->getHealth() <= 0) {
            grid[get1DIndexByCoordinates((*it)->getCoordinates())] = ' ';
            it = characters_vec.erase(it);
        }
        else { 
            it++;
        }
    }
}


