#pragma once
#include "i_table.h"

class IDescriptor
{
    public:
        virtual ITable & getTable() = 0;
        virtual ~IDescriptor(){};
};
