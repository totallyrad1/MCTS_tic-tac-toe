#include "../Inc/Node.hpp"

float Node::UCB1(){
    float averageScore = score / (visited * 1.0F);
    float explorationTerm = 1.41f * sqrt(log(Parent->visited) / visited);
    if (Parent->state.currentPlayer == 1) {
        return averageScore + explorationTerm;
    } else {
        return (1.0F - averageScore) + explorationTerm;
    }
}