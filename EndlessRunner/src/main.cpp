#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

#include "Game.h"

int main(int argc, char *argv[])
{
   Game::initSystems();

   Game::get().run();

   ut::ResMgr::clear();

   return 0;
}
