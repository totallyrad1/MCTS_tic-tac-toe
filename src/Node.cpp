#include "../Inc/Node.hpp"

float Node::UCB1(){
    float averageScore = score / visited;
    float explorationTerm = 1.41f * sqrt(log(Parent->visited) / visited);
    if (Parent->state.currentPlayer == 1) {
        return averageScore + explorationTerm;
    } else {
        return -averageScore + explorationTerm;
    }
}