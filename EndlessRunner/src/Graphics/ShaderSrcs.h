#ifndef FHL_SHADERSRCS_H
#define FHL_SHADERSRCS_H

namespace fhl {	namespace shaderSrcs {

	 constexpr const char * vertexArray_Vertex =
	 #include "Shaders/array_vs.glsl"
	 ;
	 constexpr const char * vertexArray_Fragment =
	 #include "Shaders/array_fs.glsl"
	 ;
	 constexpr const char * model_Vertex =
	 #include "Shaders/model_vs.glsl"
	 ;
	 constexpr const char * model_Fragment =
	 #include "Shaders/model_fs.glsl"
	 ;
	 constexpr const char * model_LightVertex =
	 #include "Shaders/modelLight_vs.glsl"
	 ;
	 constexpr const char * model_LightFragment =
	 #include "Shaders/modelLight_fs.glsl"
	 ;
	 constexpr const char * coloredRect_Vertex =
	 #include "Shaders/rect_vs.glsl"
	 ;
	 constexpr const char * coloredRect_Fragment =
	 #include "Shaders/rect_fs.glsl"
	 ;
	 constexpr const char * coloredRect_LightVertex =
	 #include "Shaders/rectLight_vs.glsl"
	 ;
	 constexpr const char * coloredRect_LightFragment =
	 #include "Shaders/rectLight_fs.glsl"
	 ;
	 constexpr const char * sprite_Vertex =
	 #include "Shaders/sprite_vs.glsl"
	 ;
	 constexpr const char * sprite_Fragment =
	 #include "Shaders/sprite_fs.glsl"
	 ;
	 constexpr const char * sprite_LightVertex =
	 #include "Shaders/spriteLight_vs.glsl"
	 ;
	 constexpr const char * sprite_LightFragment =
	 #include "Shaders/spriteLight_fs.glsl"
	 ;

}}

#endif // FHL_SHADERSRCS_H
