#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "DrawConf.h"

namespace fhl
{

class Drawable
{
public:
   virtual ~Drawable() { }
   virtual void draw(const DrawConf &) const = 0;
};

} // ns

#endif // DRAWABLE_H
