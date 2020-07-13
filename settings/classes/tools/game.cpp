#include "game.h"

Game::Game()
{
    plain = new Plain();
    background = new Background(plain);
    ground = new Ground(plain);

    plainMap = new PlainMap();
    player = new Player(plainMap);

    Init();
}
Game::~Game() {
    delete plain;
    delete background;
    delete ground;
    delete plainMap;
    delete player;
}
void Game::Init() {

}

void Game::Draw() {
    background->Draw();
    ground->Draw();
    player->Draw();
}
