#ifndef COMPGATE_H
#define COMPGATE_H

#include "FuncGate.h"

class LogicGate:public FuncGate{};

class ORGate:public LogicGate{
public:
    data_t eval()const;
};

class ANDGate:public LogicGate{
public:
    data_t eval()const;
};

class XORGate:public LogicGate{
public:
    data_t eval()const;
};

class NANDGate:public LogicGate{
public:
    data_t eval()const;
};

class NORGate:public LogicGate{
public:
    data_t eval()const;
};

class XNORGate:public LogicGate{
public:
    data_t eval()const;
};

#endif
