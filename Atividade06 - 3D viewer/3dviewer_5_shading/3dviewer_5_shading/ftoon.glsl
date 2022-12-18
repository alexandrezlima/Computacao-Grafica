#version 400

in vec3 fN;
in vec3 fE;
in vec3 fL;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform vec4 toonColor;
uniform float toonLevel;

uniform float cutoff;

//Toon shading (ideia base: https://github.com/daw42/glslcookbook/blob/master/chapter03/shader/toon.fs)

out vec4 outfragcolor;

vec3 toonShading()
{
    vec3 N = normalize(fN);
    vec3 L = normalize(fL);
    vec3 E = normalize(fE);

    float scaleFactor = 1.0f/toonLevel;

    float NdotL = dot(N, L);

    vec3 R = normalize(2.0 * NdotL * N - L);


    vec3 ambient = vec3(ambientProduct);

    vec3 Kd = vec3(toonColor);

    vec3 ka = vec3(Kd.x * 1.0f, Kd.y * 1.0f, 1.0f);

    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, E), 0.0), shininess);

    vec3 diffuse = Kd * floor(NdotL * toonLevel) * scaleFactor;

    vec3 specular = Ks * vec3(specularProduct) * 1.5;


    float spotlightAngle = dot(L, E);

    if (spotlightAngle > cos(radians(cutoff)))
    {
        return specular + diffuse;
    }
    else
    {
        return vec3(specular + diffuse* 0.5f);
    }
}

void main()
{
    outfragcolor = vec4(toonShading(), 1.0);
}
