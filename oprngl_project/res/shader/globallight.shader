#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcroodss;

out vec3 fragpos;
out vec3 Normal;
out vec2 texcroods;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	Normal = mat3(transpose(inverse(model))) * normal;
	fragpos = vec3(model * vec4(position, 1.0));
	texcroods = texcroodss;
};

#shader fragment
#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragpos;
in vec3 Normal;
in vec2 texcroods;

out vec4 fragcolor;

uniform vec3 viewpos;

uniform Light light;
uniform Material material;
uniform float time;


void main()
{
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcroods));
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightdir = normalize(-light.direction);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcroods));

	//specular
	vec3 viewdir = normalize(viewpos - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texcroods));

	//emission
	/*vec3 emission = vec3(0.0f);
	if (vec3(texture(material.specular, texcroods)) == vec3(0.0)){
		emission = vec3(texture(material.emission, texcroods)) * sin(time);
	}*/
	vec3 result = ambient + diffuse + specular;
	fragcolor = vec4(result, 1.0);
};