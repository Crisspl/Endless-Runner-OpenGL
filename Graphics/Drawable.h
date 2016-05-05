#pragma once

namespace gr
{

class Drawable
{
public:
   virtual ~Drawable() { }
   virtual void draw() const = 0;
};

} // ns
