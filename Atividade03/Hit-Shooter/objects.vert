
#version 400

layout ( location = 0) in vec4 inPosition;   //Vector de entrada para posições. Vamos utilizar um vec2 para passar apenas as coordenadas x e y.
layout ( location = 1) in vec4 inColors;    //Vector de entrada para cores.

uniform float rotation;
uniform float scale;
uniform vec4 translation;

out vec4 fragColor;  //Vector de saída para cores. Será utilizado na entrada do fragment shader.


void main ()
{
    //A rotação não será necessariamente utilizada por todos os objects. Powerups e balas, por exemplo, utilizarão rotação.
    float sinAngle = sin(rotation);
    float cosAngle = cos(rotation);

    vec2 rotated = vec2(inPosition.x * cosAngle - inPosition.y * sinAngle,
                        inPosition.x * sinAngle + inPosition.y * cosAngle);

    //gl_Position = rotated * scale + translation; //gl_position -- variavel built-in
    gl_Position = inPosition * vec4(scale, scale, scale, scale) + translation; //gl_position -- variavel built-in

    //Usam-se as cores passadas sem modificações.
    fragColor = inColors;
    //Note que é um vec4, r,g,b,a.
}

/*
#version 400

layout ( location = 0) in vec4 vPosition;   //Vector de entrada para posições.
layout ( location = 1) in vec4 vColors;     //Vector de entrada para cores.

out vec4 v2fcolor;  //Vector de saída para cores. Será utilizado na entrada do fragment shader.


void main ()
{
    //Aplicação simples. Usam-se as posições passadas sem distorções.
    gl_Position = vPosition ; //gl_position -- variavel built-in

    //Usam-se as cores passadas sem modificações.
    v2fcolor = vColors ;
}
*/


