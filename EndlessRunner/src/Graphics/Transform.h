#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Configurator.h"

namespace fhl
{

struct Transform
{
   Transform& rotate(float _angle, glm::vec3 _axis = {0, 0, 1})
   {
      rotation = glm::translate(rotation, glm::vec3(origin, 0));
      rotation = glm::rotate(rotation, glm::radians(_angle), _axis);
      rotation = glm::translate(rotation, glm::vec3(-origin, 0));
      return *this;
   }

   Transform& setRotation(float _angle, glm::vec3 _axis = {0, 0, 1})
   {
      glm::mat4 newRotation;
      newRotation = glm::translate(glm::mat4(), glm::vec3(origin, 0));
      rotation = glm::rotate(newRotation, glm::radians(_angle), _axis);
      rotation = glm::translate(rotation, glm::vec3(-origin, 0));
      return *this;
   }

   Transform& move(glm::vec2 _offset)
   {
      translation = glm::translate(translation, glm::vec3(_offset, 0));
      return *this;
   }

   Transform& move(glm::vec3 _offset)
   {
      translation = glm::translate(translation, _offset);
      return *this;
   }

   Transform& setPosition(glm::vec2 _pos)
   {
      translation = glm::translate(glm::mat4(), glm::vec3(_pos - origin, 0));
      return *this;
   }

   Transform& setPosition(glm::vec3 _pos)
   {
      translation = glm::translate(glm::mat4(), _pos - glm::vec3(origin, 0));
      return *this;
   }

   Transform& setScale(glm::vec2 _scale)
   {
      scale = glm::scale(glm::mat4(), glm::vec3(_scale, 1));
      return *this;
   }

   Transform& setScale(glm::vec3 _scale)
   {
      scale = glm::scale(glm::mat4(), _scale);
      return *this;
   }

   glm::mat4 translation, rotation, scale;
   glm::vec2 origin;
};

} // ns

#endif // TRANSFORM_H
