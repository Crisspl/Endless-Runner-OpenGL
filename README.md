# FHL (Five Halves Lib)

FHL is going to be an OpenGL graphics library helping to combine 2D and 3D elements.  
The main target is 2.5D (hence the name) games and you shouldn't expect FHL to be a library for 3D apps.
There's no 3D camera control nor depth testing. The last thing rendered is the thing on top.  
  
As for now the lib offers:
* wrapped, into few classes representing 2D or 3D object, OpenGL calls
* easy texture loading using [SOIL](http://lonesock.net/soil.html) (possible change to FreeImage in the future)
* easy model loading using [Assimp](https://github.com/assimp/assimp) (`fhl::Model` class)
* default GLSL shaders and opportunity to write your own and easy
* SFML-inspired interfaces (`fhl::Renderable` and `fhl::Transformable`, `fhl::Transformable3D`)
* lights (but note that there's no "scene", every object is or is not influenced by particular light independently)
* 4x4 matrix and vectors class representation and oprations
* simple collision detection classes (`fhl::Rect` and `fhl::OrientedRect`)
* time measuring using std library (`fhl::Clock`)
* `fhl::ResourceMgr` class enforcing proper resource management (it's the only class allowed to create `fhl::Texture` and `fhl::Shader` objects)
  
In the future there's going to be optional deferred renderer that will be much more efficient in specific situations, but I have to think how to design usage of such.
  
*This repository stores code of FHL along with simple game written using FHL.
Classes which belongs to FHL are inside a `fhl` namespace and their files are located in `Graphics`, `Maths` and `Utility` directories inside `/EndlessRunner/src/` directory.*  
  
It is usable, but there's only VS2015 project file provided. No CMake yet, but it will be as soon as I find time to learn CMake scripts.  
There's still a lot to do and the lib is still rather unefficient.
