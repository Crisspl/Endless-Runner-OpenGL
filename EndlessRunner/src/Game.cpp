#include "Game.h"

#include "Graphics/Configurator.h"

#include "Maths/Vectors.h"

#include "Debug.h"

SDL_Window* Game::m_window;
SDL_GLContext Game::m_context;

Game::Game()
      : m_sphere(&m_hero),
        m_running(true),
        m_model("Resources/cliff/Cliff_new.obj")
{
   ut::ResMgr::loadTexture("Resources/Tex/island1.png", "islandTex");

   m_hero.setPosition({200.f, WIN_Y});

   m_model.setScale(glm::vec3(12.f));
   m_model.setPosition({m_model.getScaledSize().x / 2.f + 200.f, 80.f, 0});
}

Game& Game::get()
{
   static Game singleton;
   return singleton;
}

void Game::run()
{
   mainLoop();
}

void Game::initSystems()
{
   SDL_Init(SDL_INIT_EVERYTHING);

   m_window = SDL_CreateWindow(
                 "EndlessRunner",
                 SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED,
                 WIN_X,
                 WIN_Y,
                 SDL_WINDOW_OPENGL
             );
   m_context = SDL_GL_CreateContext(m_window);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

   SDL_GL_SetSwapInterval(1);

   glewExperimental = GL_TRUE;

   GLenum glewerror = glewInit();
   if(glewerror != GLEW_OK)
   {
      std::cerr << "GLEW init error: " << glewGetErrorString(glewerror) << std::endl;
   }

   glViewport(0, 0, WIN_X, WIN_Y);

   gr::Configurator::init();
}

void Game::mainLoop()
{
   while(m_running)
   {
      dt =  1.f / 60.f;

      handleEvents();
      update();
      draw();
   }
   SDL_Quit();
}

void Game::handleEvents()
{
   SDL_Event event;

   while (SDL_PollEvent(&event)) {
       switch (event.type) {
           case SDL_QUIT:
               m_running = false;
               break;
           case SDL_KEYDOWN:
               if(event.key.keysym.sym == SDLK_SPACE)
                  m_hero.changeState(Hero::State_Jump);
               if(event.key.keysym.sym == SDLK_e)
               {
                  m_vecIslands.emplace_back(glm::vec2(1200, sup::getRand(200, 400)));
               }
               break;
           case SDL_MOUSEBUTTONDOWN:
               if(m_sphere.getState() == Sphere::State_Idle)
               {
                  m_sphere.setDirection(countThrowDir());
                  m_sphere.changeState(Sphere::State_Thrown);
               }
               break;
       }
   }
}

void Game::update()
{
   m_hero.update(dt);
   m_sphere.update(dt);

   if(m_sphere.getState() == Sphere::State_Return &&
      m_hero.isCollision(m_sphere))
   {
      m_sphere.changeState(Sphere::State_Idle);
   }

   for(auto it = m_vecIslands.begin(); it != m_vecIslands.end();)
   {
      it->move(-dt * 600.f);
      if(it->getPosition().x < -200.f)
         m_vecIslands.erase(it);
      else
         it++;
   }

   if(m_hero.getPosition().y > WIN_Y)
   {
      m_hero.setPosY(WIN_Y);
      m_hero.changeState(Hero::State_Move);
   }

   int collidingIslandNum = isHeroOnIsland();
   static auto onIsland = [&]() -> bool { return collidingIslandNum >= 0; };

   if(m_hero.getState() == Hero::State_Move &&
      m_hero.getPosition().y < WIN_Y &&
      !onIsland())
   {
      m_hero.changeState(Hero::State_Fall);
   }

   if(m_hero.getState() == Hero::State_Fall &&
      onIsland() )
   {
      m_hero.setPosY(m_vecIslands[collidingIslandNum].getSurfaceHeight() + 5.f);
      m_hero.changeState(Hero::State_Move);
   }

   m_model.move({-1.f, 0, 0});

   gr::Light light;
   light.position = glm::vec3(m_hero.getPosition(), 300.f);
   light.color = gr::Color(129, 240, 232);
   //light.color = gr::Color(237, 183, 223);
   light.linear = 0.005f;
   light.quadratic = 0.00004f;
   light.cutOffAngle = 15.f;
   light.illuminance = 1.6f;
   light.type = gr::Light::Spot;

   gr::Light light2;
   light2.direction = {-0.4f, 0.5f, -0.1f};
   light2.color = gr::Color::Red;
   light2.type = gr::Light::Directional;

   gr::Light light3;
   light3.color = gr::Color::Blue;
   light3.illuminance = 1.f;
   light3.position = glm::vec3(m_sphere.getPosition(), 300.f);
   light3.cutOffAngle = 15;
   light3.type = gr::Light::Spot;

   mt::Vec4f vec(5);
   vec.p = 4.f;
   DebugLog << vec << '\n';

   m_model.setLights({light, light2, light3});
}

void Game::draw()
{
   glClearColor(0.f, 0.f, 0.f, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   m_renderer.clearColor(glm::vec4(0.f, 0.f, 0.f, 1.f));

   m_renderer.drawToTex(m_model);

   for(Island& isl : m_vecIslands)
      m_renderer.drawToTex(isl);
   m_renderer.drawToTex(m_hero);
   m_renderer.drawToTex(m_sphere);

   m_renderer.drawToScreen();

   SDL_GL_SwapWindow(m_window);
}

int Game::isHeroOnIsland()
{
   int num = 0;
   for(Island& isl : m_vecIslands)
   {
      if(m_hero.isCollision(isl))
         return num;
      num++;
   }
   return -1;
}

glm::vec2 Game::countThrowDir()
{
   glm::vec2 dir = gr::Configurator::getMousePosition() - m_hero.getPosition();
   dir = glm::normalize(dir);

   return dir;
}
