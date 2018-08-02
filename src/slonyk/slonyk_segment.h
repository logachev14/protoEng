#pragma once
#include "eng_settings.h"
#include "i_segment.h"
#include "slonyk_settings.h"
#include "i_packet.h"

enum class SlMessageType
{
        SL_BROADCAST = 0,
        SL_WRITE = 1,
        SL_READ = 2
};

enum class SlAcknowledge
{
        SL_REQUEST = 0,
        SL_RESPONSE = 1
};

class SlSegment : public SegmentBase<SlAcknowledge, SlMessageType, uint16_t>
{
    public:
        SlSegment() : m_currAck(SlAcknowledge::SL_REQUEST), m_currMessType(SlMessageType::SL_BROADCAST), m_currAddr(0), m_dataLen(0)
        {

        }
        SlAcknowledge & getAck()
        {
            return m_currAck;
        }
        SlMessageType & getMessageType()
        {
            return m_currMessType;
        }
        uint16_t & getDevAddr()
        {
            return m_currAddr;
        }
        void getData(uint8_t * data, uint32_t * len)
        {
            data = rawData;
            *len = m_dataLen;
        }

        void fromPacket(IPacket & packet)
        {
            uint8_t * headerPtr;
            uint32_t * headerLen;
            packet.getHeader(headerPtr, headerLen);


            packet.getData()
        }

    private:
        SlAcknowledge m_currAck;
        SlMessageType m_currMessType;
        uint16_t m_currAddr;
        uint8_t rawData[SL_MAX_DATA_LEN];
        uint32_t m_dataLen;
        void parseHeader(uint8_t * header, uint32_t len)
        {
            if(len < SL_HEADER_LEN)
            {
                ENG_ASSERT();
            }
            uint8_t ack = *(header + SL_ACK_POS);
            uint8_t mType = *(header + SL_MTYPE_POS);

        }
};




//template<class AckType, class MessageType, class DeviceAddrType>
//class SegmentBase
//{
//    public:
//        virtual AckType & getAck() = 0;
//        virtual MessageType & getMessageType() = 0;
//        virtual DeviceAddrType & getDevAddr() = 0;
//        virtual void getData(uint8_t * data, uint32_t len);
//        virtual ~SegmentBase(){};
//};
