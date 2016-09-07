#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "DrawConf.h"

namespace fhl
{

class Drawable
{
   friend void draw(const Drawable &, const DrawConf &);

public:
   virtual ~Drawable() { }

protected:
   virtual void draw(const DrawConf &) const = 0;
};

} // ns

#endif // DRAWABLE_H