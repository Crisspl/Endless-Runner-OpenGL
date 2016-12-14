#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Maths/Vectors.h"
#include "../Maths/Maths_funcs.h"

#include "Configurator.h"

namespace fhl
{

struct Transform
{
   Transform& rotate(float _angle, Vec3f _axis = {0, 0, 1})
   {
      rotation = Mat4::translate(rotation, Vec3f(origin, 0));
      rotation = Mat4::rotate(rotation, _angle, _axis);
      rotation = Mat4::translate(rotation, Vec3f(-origin, 0));
      return *this;
   }

   Transform& setRotation(float _angle, Vec3f _axis = {0, 0, 1})
   {
      Mat4 newRotation;
      newRotation = Mat4::translate(Mat4(), Vec3f(origin, 0));
      rotation = Mat4::rotate(newRotation, _angle, _axis);
      rotation = Mat4::translate(rotation, Vec3f(-origin, 0));
      return *this;
   }

   Transform& move(Vec2f _offset)
   {
      translation = Mat4::translate(translation, Vec3f(_offset, 0));
      return *this;
   }

   Transform& move(Vec3f _offset)
   {
      translation = Mat4::translate(translation, _offset);
      return *this;
   }

   Transform& setPosition(Vec2f _pos)
   {
      translation = Mat4::translate(Mat4(), Vec3f(_pos - origin, 0));
      return *this;
   }

   Transform& setPosition(Vec3f _pos)
   {
      translation = Mat4::translate(Mat4(), _pos - Vec3f(origin, 0));
      return *this;
   }

   Transform& setScale(Vec2f _scale)
   {
      scale = Mat4::scale(Mat4(), Vec3f(_scale, 1));
      return *this;
   }

   Transform& setScale(Vec3f _scale)
   {
      scale = Mat4::scale(Mat4(), _scale);
      return *this;
   }

   bool operator==(const Transform & _other) const
   {
	   return translation == _other.translation &&
		   rotation == _other.rotation &&
		   scale == _other.scale &&
		   origin == _other.origin;
   }

   bool operator!=(const Transform & _other) const
   {
	   return !(*this == _other);
   }

   Mat4 translation, rotation, scale;
   Vec2f origin;
};

} // ns

#endif // TRANSFORM_H
