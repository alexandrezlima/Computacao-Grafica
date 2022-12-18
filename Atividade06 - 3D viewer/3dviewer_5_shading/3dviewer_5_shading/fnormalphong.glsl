#version 400

in vec4 v2fcolor;
in vec3 fN;
in vec3 fE;
in vec3 fL;

uniform vec4 ambientProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform float cutoff;

out vec4 outfragcolor;


vec4 PhongNormal(vec3 n)
{
    vec3 N = normalize(n);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    float NdotL = dot(N, L);
    vec3 R = normalize(2.0 * NdotL * N - L);
    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, E), 0.0), shininess);
    vec4 diffuse = v2fcolor;
    vec4 specular = Ks * specularProduct;
    vec4 ambient = ambientProduct;

    float spotlightAngle = dot(L, E);

    if (spotlightAngle > cos(radians(cutoff)))
    {
        return ambient + specular + diffuse;
    }
    else
    {
        return vec4(ambient + diffuse* 0.5f);
    }

    //Nota: substituímos a difusão pela cor do normal shading. Assim, valores associados a difusão foram removidos.
}

void main()
{
    outfragcolor = PhongNormal(fN);
    outfragcolor.a = 1.0;
}
