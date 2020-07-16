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
	float shininess;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

#define NR_POINT_LIGHTS 4

struct SpotLight {
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

uniform Material material;
uniform PointLight pointlight[NR_POINT_LIGHTS];
uniform DirLight dirlight;
uniform SpotLight spotlight;
uniform vec3 viewpos;
uniform vec3 lightcolor;

in vec3 fragpos;
in vec3 Normal;
in vec2 texcroods;

out vec4 fragcolor;

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewdir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewdir);
vec3 CalcSpotLight(SpotLight light, vec3 norm);

void main()
{
	vec3 viewdir = normalize(viewpos - fragpos);
	vec3 norm = normalize(Normal);
	vec3 result = CalcDirLight(dirlight, norm, viewdir);
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += CalcPointLight(pointlight[i], norm, viewdir);
	}
	result += CalcSpotLight(spotlight, norm);
	fragcolor = vec4(result, 1.0);
};

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewdir) {
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcroods));

	//diffuse
	vec3 lightdir = normalize(-light.direction);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcroods));

	//specular
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texcroods));

	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewdir) {
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcroods));

	//diffuse
	vec3 lightdir = normalize(light.position - fragpos);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcroods));

	//specular
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texcroods));

	//lightIntensity
	float distance = length(light.position - fragpos);
	float lightIntensity = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	vec3 result = (ambient + diffuse + specular) * lightIntensity * lightcolor;
	return result;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm) {

	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcroods));

	//diffuse
	vec3 lightdir = normalize(light.position - fragpos);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcroods));

	//specular
	vec3 viewdir = normalize(light.position - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texcroods));

	//lightIntensity
	float distance = length(light.position - fragpos);
	float lightIntensity = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	//color
	float theta = dot(lightdir, normalize(-light.direction));
	float epsilon = light.cutoff - light.outercutoff;
	float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0f, 1.0f);

	vec3 result = ambient + diffuse * intensity + specular * intensity;
	return result * lightIntensity;
}