#version 330 core

in VSOUT
{
	vec3 worldPos;
	vec3 normal;
}fsIn;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fragColor;

float computeDiff(vec3 normal, vec3 lightDir);
float computeSpec(vec3 lightDir, vec3 viewDir);

void main()
{
	float ambientWeight = 0.3;
	float specularWeight = 0.2;
	float diffuseWeight = 0.5;
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	vec3 ambient = ambientWeight * lightColor;

	vec3 lightDir = normalize(lightPos - fsIn.worldPos);
	vec3 viewDir = normalize(viewPos - fsIn.worldPos);

	// diff
	vec3 normal = normalize(fsIn.normal);
	float diff = computeDiff(normal, lightDir);
	vec3 diffuse = diff * diffuseWeight * lightColor;

	// specular  Blinn-Phong
	float spec = computeSpec(lightDir, viewDir);
	vec3 specular = spec * specularWeight * lightColor;

	vec3 total = ambient + diffuse + specular;

	fragColor = vec4(vec3(1.0, 1.0f, 1.0f) * total, 1.0f);
}

float computeDiff(vec3 normal, vec3 lightDir)
{
	return max(dot(lightDir, normal), 0.0f);
}

float computeSpec(vec3 lightDir, vec3 viewDir)
{
	vec3 halfwayDir = normalize(lightDir + viewDir);
	return pow(max(dot(viewDir, halfwayDir), 0.0f), 16.0f);
}
