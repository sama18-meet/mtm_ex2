

// abstract class

class Character:
protected:
    Team team;
    units_t health;
    units_t ammo;
    units_t range;
    units_t power;

protected:
    bool canMove(const GridPoint& src, const GridPoint& dst); // raghad
    bool canAttack(CharacterCoordinates src_character_coordinates, CharacterCoordinates dst_character_coordinates);
    virtual bool attackInRange(CharacterCoordinates src_character_coordinates, CharacterCoordinates dst_character_coordinates) = 0;
    virtual bool isOutOfAmmo(CharacterCoordinates src_character_coordinates, CharacterCoordinates dst_character_coordinates) = 0;
    virtual bool legalTarget(CharacterCoordinates src_character_coordinates, CharacterCoordinates dst_character_coordinates) = 0;
    virtual void updateAmmo(std::shared_ptr<Character> target) = 0;
    virtual void updateTargetsHealth(CharacterCoordinates src_character_coordinates, vector<CharacterCoordinates> grid_state) = 0;
    void reload(); // raghad

public:
    Character(Team team, units_t health, units_t ammo, units_t range, units_t power);
    ~Character() = default;
    Character(const Character&) = default;
    Character& operator=(const Character&) = default;
    clone();
