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
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	float cutoff;
	float outercutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 fragpos;
in vec3 Normal;
in vec2 texcroods;

out vec4 fragcolor;

uniform Light light;
uniform Material material;

void main()
{
	//color
	vec3 lightdir = normalize(light.position - fragpos);
	float theta = dot(lightdir, normalize(-light.direction));
	float epsilon = light.cutoff - light.outercutoff;
	float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0f, 1.0f);
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texcroods));

	//diffuse
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texcroods));

	//specular
	vec3 viewdir = normalize(light.position - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texcroods));

	//lightIntensity
	float distance = length(light.position - fragpos);
	float lightIntensity = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
		
	vec3 result = ambient + diffuse * intensity + specular * intensity;
	fragcolor = vec4(result * lightIntensity, 1.0);
};
