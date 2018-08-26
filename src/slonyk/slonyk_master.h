#pragma once
#include "eng_settings.h"
#include "slonyk_slave.h"
#include "i_register.h"
#include "slonyk_segment.h"

enum UpdateState
{
	GET_NEXT_SLAVE = 0,
	READ_SLAVE_REGS = 1,
	COMPOSE_SEGMENT_TO_SEND = 2,
	SEND_SEGMENT = 3,
	SOME_3_STATE = 4,
	SOME_4_STATE = 5,

};

template<uint32_t slavesNum>
class SlMaster : public SlSession
{
    public:
        template <class... SlavesArg>
        SlMaster(SlavesArg*... slavesArg) : m_updateRegsNum(NULL),
											m_slaveToUpdate(NULL),
											m_regsToUpdate(NULL)

        {
            addSlave(slavesArg...);
        }
        void updateRoRegs()
        {
        	switch(m_state)
        	{
				case UpdateState::GET_NEXT_SLAVE:
				{
					// обновление ro регистров каждого слейва начинается отсюда :
					m_slaveToUpdate = m_slaves[m_slavesCounter];
					m_slavesCounter %= slavesNum;
					m_slavesCounter++;
					m_state = UpdateState::READ_SLAVE_REGS;
					break;
				}
				case UpdateState::READ_SLAVE_REGS:
				{
					// спрашиваем регистры для обновления
					m_regsToUpdate = NULL;
					*m_updateRegsNum = 0;
					m_slaveToUpdate->getRegsToUpdate(m_regsToUpdate, m_updateRegsNum);

					// если таких нет, берем следующего слейва
					if(m_regsToUpdate == NULL || *m_updateRegsNum <= 0)
					{
						m_state = UpdateState::GET_NEXT_SLAVE;
					}
					m_segToSend.setAck(SlAcknowledge::SL_REQUEST);
					m_segToSend.setAddr(m_slaveToUpdate->getAddr());
					m_segToSend.setMessageType(SlMessageType::SL_READ);
					m_state = UpdateState::COMPOSE_SEGMENT_TO_SEND;
					break;
				}
				case UpdateState::COMPOSE_SEGMENT_TO_SEND:
				{
					if(*m_updateRegsNum == 0)
					{
						m_state = UpdateState::GET_NEXT_SLAVE;
						break;
					}
					while(m_segToSend.AddReg(m_regsToUpdate->getRegAddr(), m_regsToUpdate->getLen()) ||
					     *m_updateRegsNum > 0 )
					{
						m_regsToUpdate++;
						*m_updateRegsNum--;
					}
					m_state = UpdateState::SEND_SEGMENT;
					break;
				}
				case UpdateState::SEND_SEGMENT:
				{

					break;
				}
        	}
        }
    private:
        void regUpdated(uint32_t slaveAddr, IRegister & reg)
        {

        }

        template <class... AddArg>
        void addSlave(ISlave * slave, AddArg*... slavesArg)
        {
            m_slaves[m_slavesItr] = slave;
            m_slavesItr++;
            addSlave(slavesArg...);
        }
        void addSlave(){};
        uint32_t m_slavesItr = 0;
        ISlave * m_slaves[slavesNum];
        //
        INetworkProvider & m_provider;

        // Все для обновления:
        UpdateState m_state = UpdateState::GET_NEXT_SLAVE;
        uint32_t m_slavesCounter = 0;
        ISlave * m_slaveToUpdate;
        IRegister * m_regsToUpdate;
        uint32_t * m_updateRegsNum;
        uint32_t m_regsCounter = 0;

        SlSegment m_segToSend;
};
