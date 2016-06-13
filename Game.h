#ifndef GAME_H
#define GAME_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Global.h"
#include "Utility/Clock.h"
#include "Graphics/Configurator.h"
#include "Utility/ResMgr.h"
#include "Hero.h"
#include "Sphere.h"
#include "Island.h"
#include "ScreenRenderer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/ColoredRect.h"
#include "Graphics/Model.h"

class Game
{
private:
   Game();

public:
   static Game& get();
   void run();
   static void initSystems();

private:
   void mainLoop();
   void handleEvents();
   void update();
   void draw();

   int isHeroOnIsland(); /* If hero collides an island - returns its number in container, otherwise returns -1 */
   glm::vec2 countThrowDir();

private:
   static SDL_Window* m_window;
   static SDL_GLContext m_context;
   ScreenRenderer m_renderer;

   Hero m_hero;
   Sphere m_sphere;
   std::vector<Island> m_vecIslands;
   gr::Model m_model;

   ut::Clock m_timer;
   float dt;

   bool m_running;

public:
   constexpr static GLuint WIN_X = 800, WIN_Y = 600;
};

#endif
