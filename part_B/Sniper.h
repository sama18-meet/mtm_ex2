

class Medic : public Character {
    int motion_range = 4;
    int successful attacks = 0;
    load() { ammo += 2 };
    attach() { ammo -= 1 };
}
