#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <bitset>

/*
Definição dos possíveis inputs in game:
    -Up/Down controlam a nave para cima e para baixo;
    -Fire atira;
    -Shield levanta uma barreira protetora para impedir o dano de projéteis inimigos.
*/
enum class Input {Right, Left, Fire, Shield};
enum class State {Playing, GameOver, Win};


struct GameData
{
    State m_state{State::Playing}; //Responsável por dizer o estado atual do jogo. O jogo inicia no estado "jogando".
    std::bitset<4> m_input; //Define a ação atual da nave. [Up, Down, Fire, Shield] -> [0, 0, 0, 0]
};

#endif // GAMEDATA_H
