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

uniform sampler2D texture_diffuse1;

void main()
{
	fragcolor = texture(texture_diffuse1, texcrood);
};