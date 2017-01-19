"#version 330 core\n"
"\n"
"layout (location = 0) in vec2 position;\n"
"\n"
"uniform mat4 mvp;\n"
"\n"
"void main()\n"
"{\n"
"	gl_Position.xy = position;\n"
"	gl_Position.zw = vec2(0.f, 1.f);\n"
"	gl_Position = mvp * gl_Position;\n"
"}\n"
