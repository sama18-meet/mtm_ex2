

class Soldier: public Character {
    int motion_range = 3;
    Soldier(int range, );
    load() { ammo += 3}
    attack() { ammo-=1 }

}
