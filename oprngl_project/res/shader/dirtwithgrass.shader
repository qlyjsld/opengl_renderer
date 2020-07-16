#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 atexcrood;

out vec2 texcrood;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	texcrood = atexcrood;
};

#shader fragment
#version 330 core

out vec4 fragcolor;

in vec2 texcrood;

uniform int face;
uniform sampler2D dirtwithgrass;
uniform sampler2D dirt;
uniform sampler2D grass;

void main()
{	
	switch (face) {
	case 1: case 2: case 3: case 4:
		fragcolor = texture(dirtwithgrass, texcrood);
		break;
	case 5:
		fragcolor = texture(dirt, texcrood);
		break;
	case 6:
		fragcolor = texture(grass, texcrood);
		break;
	}
};