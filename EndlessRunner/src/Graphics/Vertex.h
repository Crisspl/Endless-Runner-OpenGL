#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

#include "Color.h"

namespace fhl
{

struct Vertex
{
   Vertex(Vec2f _pos, Color _col = Color(0, 0, 0, 0));

   Vec2f position;
   Color color;
};

} // ns

#endif
