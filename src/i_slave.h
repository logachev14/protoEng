#pragma once
#include "eng_settings.h"
#include "i_table.h"

class ISlave
{
    public:
        virtual uint32_t getSlaveAddr() = 0;
        virtual ITable & getSlaveTable() = 0;
        virtual ~ISlave(){};
};
