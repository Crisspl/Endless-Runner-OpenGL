#ifndef COLOREDRECT_H
#define COLOREDRECT_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>

#include "Drawable.h"
#include "Vao.h"
#include "Transformable.h"
#include "Sizeable.h"
#include "Shader.h"
#include "Vertex.h"
#include "../Utility/ResMgr.h"
#include "Litable.h"

namespace fhl
{

class ColoredRect
   : public Transformable,
     public Sizeable,
     public Drawable,
     public Litable
{
public:
   explicit ColoredRect(glm::vec2 _size);

   Color getColor() const { return m_color; }

   Transformable& setColor(Color _color) { m_color = _color;
                                           return *this; }
   void setShader(Shader& _shader = fhl::ResMgr::getShader(SHADER_NAME)) override;
   void setLight(const Light& _light) override;

   void draw() const override;

private:
   void setUp();

private:
   Color m_color;

   bool m_usingOriginalShader;

   static bool LIGHT_SHADER_LOADED;

   constexpr static const char* SHADER_NAME = "rectShader";
   constexpr static const char* VSHADER_PATH = "Graphics/Shaders/rect_vs.glsl";
   constexpr static const char* FSHADER_PATH = "Graphics/Shaders/rect_fs.glsl";

   constexpr static const char* LIGHT_SHADER_NAME = "rectLightShader";
   constexpr static const char* LIGHT_VSHADER_PATH = "Graphics/Shaders/rectLight_vs.glsl";
   constexpr static const char* LIGHT_FSHADER_PATH = "Graphics/Shaders/rectLight_fs.glsl";
};

}

#endif // COLOREDRECT_H
