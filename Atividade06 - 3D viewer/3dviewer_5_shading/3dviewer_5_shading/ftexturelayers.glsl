#version 400

in vec3 fN;
in vec3 fV;
in vec3 fL;
in vec2 ftextCoord;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform float angle;


uniform sampler2D layerLower;
uniform sampler2D layerUpper;

out vec4 frag_color;

vec4 Phong(vec3 n)
{
    float cloudspeed = 1.0/25.0;
    float earthspeed = 1.0/100.0;

    vec3 N = normalize(n);
    vec3 V = normalize(fV);
    vec3 L = normalize(fL);
    float NdotL = dot(N,L);
    vec3 R = normalize(2.0 *NdotL * N - L);
    float Kd = max(NdotL, 0.0);
    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, V), 0.0), shininess);
    //ATENCAO!!!: para fazer o exemplo da nuvem, o c?lculo é ligeiramente diferente
    vec4 mixtex = mix(texture(layerLower, vec2(ftextCoord.x + mod(angle, 360)*earthspeed, ftextCoord.y)), texture(layerUpper, vec2(ftextCoord.x + mod(angle, 360)*cloudspeed, ftextCoord.y)), .4);
    vec4 diffuse = Kd * diffuseProduct * mixtex;
    vec4 specular = Ks * specularProduct;
    vec4 ambient = ambientProduct;
    return ambient + diffuse; // + specular;
}

void main()
{
    if (gl_FrontFacing)
    {
        frag_color = vec4(Phong(fN).xyz, 1);
    }
    else
    {
        frag_color = mix(vec4(Phong(-fN).xyz, 1), vec4(0.0, 1.0, 0.0, 1.0), 0.7);
    }
}
