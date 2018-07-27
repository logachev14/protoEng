#pragma once
#include "i_register.h"

class ITable
{
    public:
        virtual void getRoRegs(IRegister * regs, uint32_t regsNum) = 0;
        virtual ~ITable(){};
};
