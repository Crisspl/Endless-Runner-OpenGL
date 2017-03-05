#ifndef FHL_VERTEX_H
#define FHL_VERTEX_H

#include "Color.h"

namespace fhl
{

	 struct Vertex
	 {
		  Vertex(Vec2f _pos, Color _col = Color::Transparent) :
				position(_pos),
				color(_col)
		  {}

		  Vec2f position;
		  Color color;
	 };

} // ns

#endif // FHL_VERTEX_H
