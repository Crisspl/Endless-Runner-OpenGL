set(FHL_GAME_SRCS
	src/AnimationMgr.cpp        
	src/BoxCollider.cpp         
	src/CircleCollider.cpp      
	src/Coin.cpp              
	src/Collideable.cpp
	src/EndlessCliff.cpp
	src/Game.cpp
	src/Global.cpp
	src/Hero.cpp
	src/Island.cpp
	src/main.cpp
	src/ScreenRenderer.cpp
	src/SoundMgr.cpp
	src/Sphere.cpp
)

set(FHL_GAME_HEADERS
	src/AnimationMgr.h          
	src/BoxCollider.h           
	src/CircleCollider.h      
	src/Coin.h                
	src/Collideable.h
	src/Collider.h
	src/EndlessCliff.h
	src/Game.h
	src/Global.h
	src/Hero.h
	src/Input.h
	src/Island.h
	src/ScreenRenderer.h
	src/SoundMgr.h
	src/Sphere.h
)

set(SDL2_ROOT_DIR CACHE PATH "SDL2 root directory")
set(SFML_ROOT CACHE PATH "SFML root directory")

add_executable(EndlessRunner ${FHL_GAME_HEADERS} ${FHL_GAME_SRCS})

source_group("Header Files" FILES ${FHL_GAME_HEADERS})
source_group("Source Files" FILES ${FHL_GAME_SRCS})

add_dependencies(EndlessRunner fhl)

find_package(SFML 2 COMPONENTS system audio REQUIRED)
find_package(SDL2 REQUIRED)

target_include_directories(EndlessRunner PUBLIC ${SDL2_INCLUDE_DIR} ${SFML_INCLUDE_DIR} "../FHL/src")
target_link_libraries(EndlessRunner ${SDL2_LIBRARY} ${SFML_LIBRARIES} fhl)

add_custom_command(
	TARGET EndlessRunner POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/Resources" "$<TARGET_FILE_DIR:EndlessRunner>/Resources"
)
	