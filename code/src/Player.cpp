#include "Player.h"

#include "GoldPiecesObject.h"
#include "Random.h"

#include "GameObjectFactory.h"

Player::Player() : name(""), health(20), hitChancePercent(40), equippedWeapon(nullptr), equippedArmor(nullptr) {}

String Player::getName() const { return name; }

void Player::setName(String name) { this->name = name; }

int Player::getHealth() const { return health; }

void Player::setHealth(int health) { this->health = health; }

int Player::getHitChancePercent() const { return hitChancePercent; }

void Player::setHitChancePercent(int hitChancePercent) { this->hitChancePercent = hitChancePercent; }

int Player::getGold() const { return gold; }

void Player::setGold(int gold) { this->gold = gold; }

std::vector<std::unique_ptr<GameObject>>& Player::getInventory() { return inventory; }

void Player::addObject(std::unique_ptr<GameObject> gameObject) {
    if (dynamic_cast<GoldPiecesObject*>(gameObject.get())) {
        std::cout << "Added Gold " << gameObject->getName() << " to inventory." << std::endl;
        gold += Random::getInstance().generateIntInRange(gameObject->getMin(), gameObject->getMax());
        return;
    }

    std::cout << "Adding " << gameObject->getName() << " to inventory." << std::endl;

    inventory.push_back(std::move(gameObject));
}

void Player::removeObject(std::unique_ptr<GameObject>& gameObject) {
    for (std::size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == gameObject) {
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}

std::unique_ptr<GameObject>& Player::getEquippedWeapon() { return equippedWeapon; }

void Player::setEquippedWeapon(String weaponName) {
    for (std::size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->getName() == weaponName) {
            // move current weapon to inventory
            if (equippedWeapon != nullptr) {
                inventory.push_back(std::move(equippedWeapon));
                equippedWeapon = nullptr;
            }

            equippedWeapon = std::move(inventory[i]);
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}

std::unique_ptr<GameObject>& Player::getEquippedArmor() { return equippedArmor; }

void Player::setEquippedArmor(String armorName) {
    for (std::size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->getName() == armorName) {
            // move current armor to inventory
            if (equippedArmor != nullptr) {
                inventory.push_back(std::move(equippedArmor));
                equippedArmor = nullptr;
            }

            equippedArmor = std::move(inventory[i]);
            inventory.erase(inventory.begin() + i);
            return;
        }
    }
}

bool Player::isAlive() const { return health > 0; }
