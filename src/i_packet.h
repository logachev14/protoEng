#pragma once
#include "eng_settings.h"

class IPacket
{
    public:
        virtual void getData(uint8_t * buf, uint32_t * len) = 0;
        virtual void setData(uint8_t * buf, uint32_t len) = 0;

        virtual void getHeader(uint8_t * buf, uint32_t * len) = 0;
        virtual void setHeader(uint8_t * buf, uint32_t len) = 0;
        virtual ~IPacket(){};
};

template<uint32_t MaxHeaderLen, uint32_t MaxDataLen>
class Packet : public IPacket
{
    public:
    void setData(uint8_t * buf, uint32_t len)
    {
        if(len > MaxDataLen)
        {
            ENG_ASSERT();
        }
        memcpy(m_data, buf, len);
        m_dataLen = len;
    }

    void getData(uint8_t * buf, uint32_t * len)
    {
        memcpy(buf, m_data, m_dataLen);
        *len = m_dataLen;
    }

    void setHeader(uint8_t * buf, uint32_t len)
    {
        if(len > MaxHeaderLen)
        {
            ENG_ASSERT();
        }
        memcpy(m_headerData, buf, len);
        m_headerLen = len;
    }

    void getHeader(uint8_t * buf, uint32_t * len)
    {
        memcpy(buf, m_headerData, m_headerLen);
        *len = m_headerLen;
    }

    private:
    uint32_t m_dataLen = 0;
    uint32_t m_headerLen = 0;
    uint8_t m_data[MaxDataLen];
    uint8_t m_headerData[MaxHeaderLen];
};




