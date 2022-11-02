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
