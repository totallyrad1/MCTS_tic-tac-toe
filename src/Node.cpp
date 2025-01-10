#include "../Inc/Node.hpp"

float Node::UCB1(){
    float averageScore = score / (visited * 1.0F);
    float explorationTerm = sqrt(2.0f) * sqrt(log(Parent->visited) / visited);
    if (Parent->state.currentPlayer == 1) {
        return min(averageScore, 1.0F) + explorationTerm;
    } else {
        return max(1.0F - min(averageScore, 1.0F), 0.0F) + explorationTerm;
    }
}