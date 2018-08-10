#pragma once
#include "eng_settings.h"
#include "i_packet.h"

class ISegment
{
    public :
        virtual void getData(uint8_t * data, uint32_t * len) = 0;
        virtual void getRaw(uint8_t * data, uint32_t * dataLen, uint8_t * header, uint8_t * headerLen) = 0;
        virtual void fromPacket(IPacket & packet) = 0;
        virtual ~ISegment(){};
};


template<class AckType, class MessageType, class DeviceAddrType>
class SegmentBase : public ISegment
{
    public:
        virtual AckType & getAck() = 0;
        virtual MessageType & getMessageType() = 0;
        virtual DeviceAddrType & getDevAddr() = 0;
        virtual ~SegmentBase(){};
};




