#pragma once

#include <glm/glm.hpp>

#include "Color.h"

namespace gr
{

struct Vertex
{
   Vertex(glm::vec2 _pos, Color _col = Color(0, 0, 0, 0));

   glm::vec2 position;
   Color color;
};

} // ns
