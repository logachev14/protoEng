#pragma once
#include "eng_settings.h"
#include "i_slave.h"

#include "slonyk_table.h"

template <class TableType>
class SlSlave : public ISlave
{
    public:
        SlSlave(uint32_t addr, TableType & table): m_addr(addr), m_table(table)
        {

        }
        virtual uint32_t getSlaveAddr()
        {
            return m_addr;
        }
        virtual ITable & getSlaveTable()
        {
            return m_table;
        }
        TableType & getTable()
        {
            return m_table;
        }
    private:
    uint32_t m_addr;
    TableType & m_table;

};
