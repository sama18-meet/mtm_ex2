#include <memory>
#include <cstddef>
#include <string.h>
#include "Game.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include "Exceptions.h"

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
    characters_vec = std::vector<shared_ptr<Character>>();
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


char Game::getCharacterTypeChar(Character* character) {
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
    characters_vec.push_back(character);
    int index_in_char_arr = get1DIndexByCoordinates(coordinates);
    char character_type = getCharacterTypeChar(character.get());
    grid[index_in_char_arr] = character_type;
}

int Game::get1DIndexByCoordinates(const GridPoint& coordinates) {
    return coordinates.row*width+coordinates.col;
}


shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
    if (health <= 0 || ammo < 0 || power < 0 || range < 0) {
        throw IllegalArgument();
    }
    shared_ptr<Character> new_character_shared_ptr;
    if (type == SOLDIER) {
        Soldier new_soldier = Soldier(team, health, ammo, range, power);
        shared_ptr<Character>new_character_shared_ptr(&new_soldier);
    }
    else if (type == MEDIC) {
        Medic new_medic = Medic(team, health, ammo, range, power);
        shared_ptr<Character>new_character_shared_ptr(&new_medic);
    }
    else if (type == SNIPER) {
        Sniper new_sniper = Sniper(team, health, ammo, range, power);
        shared_ptr<Character>new_character_shared_ptr(&new_sniper);
    }
    return new_character_shared_ptr;
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
    if(grid_point.row>=0 && grid_point.row<width && grid_point.col>=0 && grid_point.col<height) {
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
    printGameBoard(os, game.grid, game.grid+game.width*game.height, game.width);
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


