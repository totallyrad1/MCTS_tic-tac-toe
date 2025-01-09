#include "../Inc/Node.hpp"

float Node::UCB1(){
    int value = state.currentPlayer;
    float p1 = (value ? 0 : - 1) + ((((score * 1.0f) / visited) + 1) / 2.0f);
    return p1 + (1.41f * (sqrt(Parent->visited) / (visited * 1.0f)));
}