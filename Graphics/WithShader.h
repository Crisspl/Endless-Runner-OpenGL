#pragma once

#include "Shader.h"

namespace gr
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
