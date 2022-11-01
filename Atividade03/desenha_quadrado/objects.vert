#version 400

layout ( location = 0) in vec2 inPosition;   //Vector de entrada para posições. Vamos utilizar um vec2 para passar apenas as coordenadas x e y.
layout ( location = 1) in vec4 inColors;    //Vector de entrada para cores.

uniform float rotation;
uniform float scale;
uniform vec2 translation;

out vec4 fragColor;  //Vector de saída para cores. Será utilizado na entrada do fragment shader.


void main ()
{
    //A rotação não será necessariamente utilizada por todos os objects. Powerups e balas, por exemplo, utilizarão rotação.
    float sinAngle = sin(rotation);
    float cosAngle = cos(rotation);

    vec2 rotated = vec2(inPosition.x * cosAngle - inPosition.y * sinAngle,
                        inPosition.x * sinAngle + inPosition.y * cosAngle);

    vec2 newPosition = rotated * scale + translation;

    //Usa as posição passada sem distorções.
    gl_Position = vec4(newPosition, 0, 1); //gl_position -- variavel built-in
    //Note que "forçamos" um vec4 a partir de um vec2 (que contém x,y), inserindo z e w para ter x,y,z,w.

    //Usam-se as cores passadas sem modificações.
    fragColor = inColors;
    //Note que é um vec4, r,g,b,a.
}
