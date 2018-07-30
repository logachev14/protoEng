#pragma once
#include "eng_settings.h"
#include "i_packet.h"
#include "i_network_provider.h"
#include "i_slave.h"

class ITransportProvider
{
    public:
        // для "личного пользования" тип отправить говна нетворк провайдеру.
        virtual void send(ISegment & segment) = 0;
        // для публичного пользования, тип отправить говна в тарелке для слейва.
        virtual void writeRegAtSlave(ISlave & slave, IRegister & reg) = 0;
        virtual void readRegs(ISlave & slave, IRegister * regs, uint32_t regsNum) = 0;
        virtual void readRegsAsync(ISlave & slave, IRegister * regs, uint32_t regsNum) = 0;
        virtual ~ITransportProvider(){};
};


class SlTransportProvider
{
    public:
        SlTransportProvider()
    private:
        void
};
