#version 400

in vec4 v2fcolor;   //Vector de entrada do fragment shader. Recebido da saída do vertex shader.

out vec4 outfragcolor;  //Vector de saída do fragment shader.


void main ()
{
    outfragcolor = v2fcolor;    //Cor de saída é a mesma fornecida pelo vertex shader, sem modificações.
}


/*

Anotações do livro interativo do professor Harlan:

Cada fragmento é descrito por dados como:
    @ posição (x, y, z) em coordenadas da janela, sendo z a profundidade.
    @ atributos interpolados a p0artir dos vértices da primitiva, o que inclui todos os atributos definidos na saída do vertex shader.
        @ assim, se a saída do vertex shader devolve um atributo de cor RGB para cada vértice, então cada fragmento também terá uma cor RGB com valores
          obtidos por meio da interpolação dos atributos definidos nos vértices.

A entrada do fragment shader é o mesmo conjunto de atributos definidos pelo usuário na saída do vertex shader.
A saída do fragment shader geralmente é uma cor em formato RGBA. Também é possível produzir mais de uma cor caso o pipeline tenha sido configurado para
renderizar simultaneamente vários buffers de cor.
*/

