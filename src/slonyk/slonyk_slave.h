#pragma once
#include "eng_settings.h"
#include "slonyk_table.h"
#include "sl_session.h"

class SlSlave : public SlSession
{
    public:
        SlSlave(uint32_t addr, ITable & table, ITransportProvider & provider): m_addr(addr), m_table(table), m_provider(provider)
        {

        }
        uint32_t getSlaveAddr()
        {
            return m_addr;
        }
        ITable & getSlaveTable()
        {
            return m_table;
        }
        ITable & getTable()
        {
            return m_table;
        }
        virtual void onSegmentReceived(SlSegment & segment)
        {
        	if(segment.getAck() == SlAcknowledge::SL_REQUEST && segment.getDevAddr() == m_addr)
        	{
        		switch(segment.getMessageType())
        		{
					case SlMessageType::SL_READ :
					{

						break;
					}
					case SlMessageType::SL_WRITE :
					{

						break;
					}
					case SlMessageType::SL_BROADCAST :
					{
						break;
					}

        		}
        	}

        }
        virtual void sync()
        {

        }
    private:
    void composeAnswer(SlSegment & segment)
    {
    	SlAcknowledge ack = SlAcknowledge::SL_RESPONSE;
    	m_responseSegment.setAck(ack);
    	m_responseSegment.setMessageType(segment.getMessageType());
    	m_responseSegment.setAddr(m_addr);

    	uint8_t * responseDataPtr = 0;
    	uint32_t * len;
    	m_responseSegment.getData(responseDataPtr, len);


    	uint8_t * data = 0;
    	uint32_t * len = 0;
    	segment.getData(data, len);
    	if(*len <= 0 )
    	{
    		ENG_ASSERT();
    	}
    	uint8_t numOfRegs = *data;
    	*responseDataPtr = numOfRegs;
    	// проходимс€ по адресам
		uint8_t regDataStartPos = SL_REGS_ADDR_START_POS + (numOfRegs * 2);
		for(uint8_t i = 0; i < numOfRegs; i++)
		{
			// ƒ»чь
			memcpy((responseDataPtr + 1),(data + (SL_REGS_ADDR_START_POS) * (i + 1)), 2 );
			uint16_t addr = 0;
			addr |= *(data + (SL_REGS_ADDR_START_POS) * (i + 1))  << 0;
			addr |= *(data + (SL_REGS_ADDR_START_POS + 1) * (i + 1)) << 8;

			IRegister * reg = m_table.getReg(addr);
			uint8_t regDataLen = reg->getLen();
			if(segment.getMessageType() == SlMessageType::SL_WRITE)
			{
				reg->setBytes((data + regDataStartPos), regDataLen);
			}
			else
			{


			}

			regDataStartPos += regDataLen;
		}
    }
    SlSegment m_responseSegment;
    uint32_t m_addr;
    ITable & m_table;
    ITransportProvider & m_provider;
};
