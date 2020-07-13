#include "player.h"

Player::Player(PlainMap *PLAINMAP) : plainMap(PLAINMAP)
{
    Init();
}

Player::~Player() {
    delete rig;
}

void Player::Init() {
    rig = new Rig(plainMap);
}

void Player::Draw() {
    rig->Draw();
}
