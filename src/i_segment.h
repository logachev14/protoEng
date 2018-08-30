#pragma once
#include "eng_settings.h"
#include "i_packet.h"
#include "i_register.h"


class ISegment
{
    public :
        //virtual void fromPacket(IPacket & packet) = 0;
		// для формирования сегмента, необходимо указать каким образом будет происходить добавление
		// добавление регистра с данными, или добавление просто адреса ргеистра
		// true - регистр добален в сегмент
		// false - соответственно, добален небыл.
		virtual bool addReg(IRegister & reg) = 0;
		virtual bool addReg(uint32_t regAddr, uint32_t regLen) = 0;
        virtual ~ISegment(){};
};

//каждый segment содержит в себе Ack, MessageType, devAddr и набор полу-сырых байт
template<class AckType, class MessageType, class DeviceAddrType>
class SegmentBase : public ISegment
{
    public:
        virtual AckType & getAck() = 0;
        virtual MessageType & getMessageType() = 0;
        virtual DeviceAddrType & getDevAddr() = 0;
        virtual ~SegmentBase(){};
};




