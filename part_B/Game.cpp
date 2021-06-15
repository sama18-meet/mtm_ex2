#include "Game.h"
#include <memory>
#include <cstddef>

using namespace mtm;


Game::Game(int height, int width) : height(height), width(width) {
    if (heigth <=0 || width <=0){
        throw IllegalArgument(); 
    }
    grid = new char[height*width]; 
    memset(grid, ' ', height*width);
}

Game::~Game() {
    delete[] grid;
}

bool Game::isOver(Team* winningTeam=nullptr) const{
    if(characters.size()==0){
        return false;
    }
    std::vector<Character>::iterator i = characters.begin();     
    Team first_character_team = i.getTeam;
    for ( ; i != characters.end(); ++i)
    {
        if(i->.getTeam != first_character_team){
            return false;
        }
    } 
    if(winningTeam!=nullptr){
    winningTeam=first_character_team;
    }
    return true;
}

