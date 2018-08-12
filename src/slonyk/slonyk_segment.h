#pragma once
#include "eng_settings.h"
#include "i_segment.h"
#include "slonyk_settings.h"
#include "i_packet.h"

class SlSegment : public SegmentBase<SlAcknowledge, SlMessageType, uint16_t>
{
    public:
        SlSegment() : m_currAck(SlAcknowledge::SL_REQUEST),
					  m_currMessType(SlMessageType::SL_BROADCAST),
					  m_currAddr(0),
					  m_dataLen(0)
        {

        }
        SlAcknowledge & getAck()
        {
            return m_currAck;
        }
        void setAck(SlAcknowledge & ack)
        {
        	m_currAck = ack;
        }
        SlMessageType & getMessageType()
        {
            return m_currMessType;
        }
        void setMessageType(SlMessageType & messType)
        {
        	m_currMessType = messType;
        }
        uint16_t & getDevAddr()
        {
            return m_currAddr;
        }
        void setAddr(uint16_t addr)
        {
        	m_currAddr = addr;
        }

        void getData(uint8_t * data, uint32_t * len)
        {
            data = m_rawData;
            *len = m_dataLen;
        }
        void setData(uint8_t * newData, uint32_t len)
        {
        	if(len > SL_MAX_DATA_LEN)
        	{
        		ENG_ASSERT();
        	}
        	memcpy(m_rawData, newData, len);
        	m_dataLen = len;
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
                	m_currMessType = SlMessageType::SL_WRITE;
                    break;
                }
                case SL_MESS_READ:
                {
                	m_currMessType = SlMessageType::SL_READ;
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
