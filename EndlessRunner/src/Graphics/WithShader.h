#ifndef WITHSHADER_H
#define WITHSHADER_H

#include "Shader.h"

namespace fhl
{

class WithShader
{
public:
   WithShader(Shader& _shader);
   virtual ~WithShader() { }

   virtual const Shader& getShader() const;
   virtual void setShader(Shader& _shader);

protected:
   Shader* m_shader;
};

} // ns

#endif // WITHSHADER_H
