#pragma once
#include "eng_settings.h"
#include "i_packet.h"
#include "i_segment.h"
#include "i_network_provider.h"
#include "i_slave.h"

class ITransportProvider
{
    public:
        // для того, что стоит выше
        virtual void send(ISegment & segment) = 0;

        // для Network provider'a
        virtual void packetReceived(IPacket & packet) = 0;
        callback::Callback<void (IPacket & packet)> sendPacket;
        virtual ~ITransportProvider(){};
};
