#pragma once
#include "slonyk_settings.h"
#include "i_network_provider.h"
#include "slonyk_packet.h"




//class SlSlaveNetworkProvider : public INetworkProvider
//{
//    public:
//        SlSlaveNetworkProvider(uint16_t addr) : m_addr(addr)
//        {
//
//        }
//        void send(ISegment & segment)
//        {
//
//        }
//        void dataReceived(uint8_t * data, uint32_t len)
//        {
//            uint16_t recAddr;
//            memcpy(&recAddr, data + SL_ADDRESS_START_POS, sizeof(recAddr));
//
//            if(m_addr == recAddr || recAddr == SL_BROADCAST_ADDRESS)
//            {
//                m_slutPacket.setHeader(data, SL_HEADER_LEN);
//                m_slutPacket.setData(data + SL_DATA_START_POS, len - SL_HEADER_LEN);
//                onPacketReceived(m_slutPacket);
//            }
//        }
//    private:
//        SlPacket m_slutPacket;
//        uint16_t m_addr;
//};
//
//template<uint16_t... slaves>
//class SlMasterNetworkProvider : public INetworkProvider
//{
//    public:
//        SlMasterNetworkProvider()
//        {
//
//        }
//        void send(ISegment & segment)
//        {
//
//        }
//        void dataReceived(uint8_t * data, uint32_t len)
//        {
//            uint16_t recAddr;
//            memcpy(&recAddr, data + SL_ADDRESS_START_POS, sizeof(recAddr));
//
//            if(isAddrInRange(recAddr) || recAddr == SL_BROADCAST_ADDRESS)
//            {
//                m_slutPacket.setHeader(data, SL_HEADER_LEN);
//                m_slutPacket.setData(data + SL_DATA_START_POS, len - SL_HEADER_LEN);
//                onPacketReceived(m_slutPacket);
//            }
//        }
//    private:
//        SlPacket m_slutPacket;
//        uint32_t m_nums = sizeof...(slaves);
//        uint16_t m_slavesAddr[sizeof...(slaves)] = {slaves ...};
//        bool isAddrInRange(uint16_t addr)
//        {
//            bool result = false;
//            for(uint32_t i = 0; i < m_nums; i++ )
//            {
//                if(m_slavesAddr[i] == addr)
//                {
//                    result = true;
//                    break;
//                }
//            }
//            return result;
//        }
//};
