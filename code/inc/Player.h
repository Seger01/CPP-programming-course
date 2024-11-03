#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "GameObject.h"
#include "String.h"
#include "Vector.h"

class Player {
public:
    Player();

    String getName() const;
    void setName(String name);

    int getHealth() const;
    void setHealth(int health);

    int getHitChancePercent() const;
    void setHitChancePercent(int hitChancePercent);

    int getGold() const;
    void setGold(int gold);

    std::vector<std::unique_ptr<GameObject>>& getInventory();
    void addObject(std::unique_ptr<GameObject> gameObject);
    void removeObject(std::unique_ptr<GameObject>& gameObject);

    std::unique_ptr<GameObject>& getEquippedWeapon();
    void setEquippedWeapon(String weaponName);

    std::unique_ptr<GameObject>& getEquippedArmor();
    void setEquippedArmor(String armorName);

    bool isAlive() const;

private:
    String name;
    int health;
    int hitChancePercent;
    int gold;

    std::vector<std::unique_ptr<GameObject>> inventory;
    std::unique_ptr<GameObject> equippedWeapon;
    std::unique_ptr<GameObject> equippedArmor;
};

#endif // PLAYER_H
