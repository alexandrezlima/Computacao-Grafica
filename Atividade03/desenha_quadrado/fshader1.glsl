#version 400

in vec4 v2fcolor;   //Vector de entrada do fragment shader. Recebido da saída do vertex shader.

out vec4 outfragcolor;  //Vector de saída do fragment shader.


void main ()
{
    outfragcolor = v2fcolor;    //Cor de saída é a mesma fornecida pelo vertex shader, sem modificações.
}

