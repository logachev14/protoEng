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
            data = m_rawData;
            *len = m_dataLen;
        }

        void fromPacket(IPacket & packet)
        {
            uint8_t * headerPtr;
            uint32_t * headerLen;
            uint8_t * dataPtr;
            uint32_t * dataLen;
            packet.getHeader(headerPtr, headerLen);
            parseHeader(headerPtr, *headerLen);
            packet.getData(dataPtr, dataLen);
            memcpy(m_rawData, dataPtr, *dataLen);

        }

    private:
        SlAcknowledge m_currAck;
        SlMessageType m_currMessType;
        uint16_t m_currAddr;
        uint8_t m_rawData[SL_MAX_DATA_LEN];
        uint32_t m_dataLen;

        void parseHeader(uint8_t * header, uint32_t len)
        {
            if(len < SL_HEADER_LEN)
            {
                ENG_ASSERT();
            }
            uint8_t ack = *(header + SL_ACK_POS);
            uint8_t mType = *(header + SL_MTYPE_POS);
            uint16_t addr = 0;
            addr |= *(header + SL_ADDR_POS)  << 0;
            addr |= *(header + SL_ADDR_POS + 1) << 8;

            switch(ack)
            {
                case SL_ACK_REQUEST:
                {
                    m_currAck = SlAcknowledge::SL_REQUEST;
                    break;
                }
                case SL_ACK_RESPONSE:
                {
                    m_currAck = SlAcknowledge::SL_RESPONSE;
                    break;
                }
                default:
                {
                    ENG_ASSERT();
                }
            }


            switch(mType)
            {
                case SL_MESS_BROADCAST:
                {
                    m_currMessType = SlMessageType::SL_BROADCAST;
                    break;
                }
                case SL_MESS_WRITE:
                {
                    m_currAck = SlMessageType::SL_WRITE;
                    break;
                }
                case SL_MESS_READ:
                {
                    m_currAck = SlMessageType::SL_READ;
                    break;
                }
                default:
                {
                    ENG_ASSERT();
                }
            }
            m_currAddr = addr;
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
