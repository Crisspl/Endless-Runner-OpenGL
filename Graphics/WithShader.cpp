#include "WithShader.h"

namespace gr
{

WithShader::WithShader(Shader& _shader)
   : m_shader(&_shader)
{
}

const Shader& WithShader::getShader() const
{
   return *m_shader;
}

void WithShader::setShader(Shader& _shader)
{
   m_shader = &_shader;
}

} // gr
