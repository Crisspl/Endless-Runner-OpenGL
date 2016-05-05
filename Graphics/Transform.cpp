#include "Transform.h"

glm::mat4 Transform::view = glm::lookAt(glm::vec3(0.664f, 0.5f, 1.2f), glm::vec3(0.664f, 0.5f, -1), glm::vec3(0, 1,0 ));
glm::mat4 Transform::projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
