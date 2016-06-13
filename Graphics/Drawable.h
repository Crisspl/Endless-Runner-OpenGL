#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace gr
{

class Drawable
{
public:
   virtual ~Drawable() { }
   virtual void draw() const = 0;
};

} // ns

#endif // DRAWABLE_H
