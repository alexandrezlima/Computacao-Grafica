#version 400

in vec3 fN;
in vec3 fE;
in vec3 fL;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform float cutoff;

out vec4 outfragcolor;


vec4 Phong(vec3 n)
{
    vec3 N = normalize(n);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    float NdotL = dot(N, L);
    vec3 R = normalize(2.0 * NdotL * N - L);
    float Kd = max(NdotL, 0.0);
    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, E), 0.0), shininess);
    vec4 diffuse = Kd * diffuseProduct;
    vec4 specular = Ks * specularProduct;
    vec4 ambient = ambientProduct;


    float spotlightAngle = dot(L, E);

    if (spotlightAngle > cos(radians(cutoff)))
    {
        return ambient + diffuse + specular;
    }
    else
    {
        return vec4(ambient + diffuse* 0.5f);
    }
}

void main()
{
    outfragcolor = Phong(fN);
    outfragcolor.a = 1.0;
}
