#define MEDIC_MOTION_RANGE 5

class Medic : public Character {
    const int motion_range;
    load() { ammo += 5 };
public:
    Medic(...) ... motion_range(MEDIC_MOTION_RANGE) {
   
    }
}


