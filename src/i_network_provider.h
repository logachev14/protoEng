#pragma once
#include "eng_settings.h"
#include "i_packet.h"
#include "i_segment.h"

// Владеет значнием того, как преобразовать сырую дату в пакет и сегмент в пакет
class INetworkProvider
{
    public:
        virtual void send(ISegment & segment) = 0;
        virtual void dataReceived(uint8_t * data, uint32_t len) = 0;
        callback::Callback<void (IPacket &)> onPacketReceived;
        virtual ~INetworkProvider(){};
    private:
        callback::Callback<void (IPacket &)> send(IPacket & packet);
};
