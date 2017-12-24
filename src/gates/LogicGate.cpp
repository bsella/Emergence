#include "lib/LogicGate.h"

data_t ORGate::eval()const{
    return input[0]->eval() || input[1]->eval();
}

data_t ANDGate::eval()const{
    return input[0]->eval() && input[1]->eval();
}

data_t XORGate::eval()const{
    return input[0]->eval() ^ input[1]->eval();
}

data_t NORGate::eval()const{
    return !(input[0]->eval() || input[1]->eval());
}

data_t NANDGate::eval()const{
    return !(input[0]->eval() && input[1]->eval());
}

data_t XNORGate::eval()const{
    return !(input[0]->eval() ^ input[1]->eval());
}
