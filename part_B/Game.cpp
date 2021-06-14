



Game::Game(int height, int width) height(height), width(width) {
    grid = new char[height*width]; 
    memset(grid, ' ', height*width);
}


Game::~Game() {
    delete[] grid;
}



void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates) {
    
}
