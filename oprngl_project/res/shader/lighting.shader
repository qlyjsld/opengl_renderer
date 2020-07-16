#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
};

#shader fragment
#version 330 core

out vec4 fragcolor;

uniform vec3 lightcolor;

void main()
{
	fragcolor = vec4(lightcolor, 1);
};