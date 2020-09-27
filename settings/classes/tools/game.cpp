#include "game.h"

Game::Game()
{
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
    plain = new Plain();
    background = new Background(plain);
    ground = new Ground(plain);

    plainMap = new PlainMap();
    player = new Player(plainMap);
}

void Game::ProcessInput(GLFWwindow *window) {
    player->rig->ProcessInput(window);
}

void Game::Draw() {
    background->Draw();
    ground->Draw();
    player->Draw();
}
