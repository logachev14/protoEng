#pragma once
#include "eng_settings.h"
#include "i_descriptor.h"

#include "i_slave.h"


template<uint32_t slavesNum>
class SlMaster
{
    public:
        template <class... SlavesArg>
        SlMaster(SlavesArg*... slavesArg)
        {
            addSlave(slavesArg...);
        }
        void updateRoRegs()
        {

        }
    private:
        template <class... AddArg>
        void addSlave(ISlave * slave, AddArg*... slavesArg)
        {
            m_slaves[m_slavesItr] = slave;
            m_slavesItr++;
            addSlave(slavesArg...);
        }
        void addSlave(){};
        uint32_t m_slavesItr = 0;
        ISlave * m_slaves[slavesNum];
};
