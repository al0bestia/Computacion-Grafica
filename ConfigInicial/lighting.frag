#version 330 core

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

// Dos luces con parámetros distintos
uniform Light light1;
uniform Light light2;


uniform sampler2D texture_diffuse1;

vec3 applyLight(Light L, vec3 norm, vec3 viewDir, vec3 baseDiffuse, vec3 baseSpecular)
{
    vec3 lightDir   = normalize(L.position - FragPos);
    float diff      = max(dot(norm, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specPow   = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = L.ambient  * baseDiffuse;
    vec3 diffuse  = L.diffuse  * diff * baseDiffuse;
    vec3 specular = L.specular * specPow * baseSpecular;
    return ambient + diffuse + specular;
}

void main()
{
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 texCol = texture(texture_diffuse1, TexCoords).rgb;

    vec3 baseDiffuse  = material.diffuse * texCol;
    vec3 baseSpecular = material.specular;

    vec3 result = vec3(0.0);
    result += applyLight(light1, norm, viewDir, baseDiffuse, baseSpecular);
    result += applyLight(light2, norm, viewDir, baseDiffuse, baseSpecular);

    color = vec4(result, 1.0);
}
