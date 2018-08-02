#pragma once
#include "eng_settings.h"

class ISegment
{

};

template<class AckType, class MessageType, class DeviceAddrType>
class SegmentBase
{
    public:
        virtual AckType & getAck() = 0;
        virtual MessageType & getMessageType() = 0;
        virtual DeviceAddrType & getDevAddr() = 0;
        virtual void getData(uint8_t * data, uint32_t * len) = 0;
        virtual ~SegmentBase(){};
};




