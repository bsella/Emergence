#include "lib/LogicGate.h"

data_t ORGate::eval()const{
    return iGates[0]->eval() || iGates[1]->eval();
}

data_t ANDGate::eval()const{
    return iGates[0]->eval() && iGates[1]->eval();
}

data_t XORGate::eval()const{
    return iGates[0]->eval() ^ iGates[1]->eval();
}

data_t NORGate::eval()const{
    return !(iGates[0]->eval() || iGates[1]->eval());
}

data_t NANDGate::eval()const{
    return !(iGates[0]->eval() && iGates[1]->eval());
}

data_t XNORGate::eval()const{
    return !(iGates[0]->eval() ^ iGates[1]->eval());
}
