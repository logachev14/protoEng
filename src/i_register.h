#pragma once
#include "eng_settings.h"


enum class RegAccessType
{
        RO = 0,
        WO = 1
};

struct IRegister
{
    public:
        virtual void getBytes(uint8_t * buf, uint32_t * len) = 0;
        virtual void setBytes(uint8_t * buf, uint32_t len) = 0;
        virtual uint32_t getLen() = 0;
        virtual uint32_t getRegAddr() = 0;
        virtual RegAccessType getAccessType() = 0;
        virtual ~IRegister(){};
};

template<class T>
class Register : public IRegister
{
public:
    Register(uint32_t addr, RegAccessType accType): m_size(sizeof(T)),
                                                    m_accType(accType),
                                                    m_addr(addr)
    {

    }
    T getRegVal()
    {
        return m_value;
    }

    virtual void getBytes(uint8_t * buf, uint32_t * len) = 0;
    virtual void setBytes(uint8_t * buf, uint32_t len) = 0;
    virtual uint32_t getLen() = 0;
    virtual uint32_t getRegAddr()
    {
            return m_addr;
    }
    RegAccessType getAccessType()
    {
        return m_accType;
    }
protected:
    T m_value;
    size_t m_size;
private:
    RegAccessType m_accType;
    uint32_t m_addr;
};



class Uint32Reg : public Register<uint32_t>
{
    public:
        Uint32Reg(uint32_t addr, RegAccessType accType) : Register<uint32_t>(addr, accType)
        {

        }
        virtual void getBytes(uint8_t * buf, uint32_t * len)
        {
            *buf = 0;
            *(buf + 1) = 1;
            *(buf + 2) = 2;
            *(buf + 3) = 3;
            *len = 4;
        }
        virtual void setBytes(uint8_t * buf, uint32_t len)
        {

        }
        virtual uint32_t getLen()
        {
            return m_size;
        }
};

class Uint8Reg : public Register<uint8_t>
{
    public:
        Uint8Reg(uint32_t addr, RegAccessType accType) : Register<uint8_t>(addr, accType)
        {

        }
        virtual void getBytes(uint8_t * buf, uint32_t * len)
        {
            *buf = 0;
            *(buf + 1) = 1;
            *(buf + 2) = 2;
            *(buf + 3) = 3;
            *len = 4;
        }
        virtual void setBytes(uint8_t * buf, uint32_t len)
        {

        }
        virtual uint32_t getLen()
        {
            return m_size;
        }
};





enum class RoUint32RegNames
{
    x = 0,
    y = 1,
    z = 2,
    FUCK = 3,
};

enum class RoInt8RegNames
{
    tmp1 = 4,
    tmp2 = 5,
};

enum class WoUint32RegNames
{
    x = 6,
    y = 7,
    z = 8,
};

enum class WoInt8RegNames
{
    tmp1 = 9,
    tmp2 = 10,
};


class SimpleTable
{
    public:
        Uint32Reg & getReg(RoUint32RegNames addr)
        {
            return m_rouint32regnames_gen[static_cast<uint32_t>(addr) - 0];
        }
        Uint8Reg & getReg(RoInt8RegNames addr)
        {
            return m_roint8regnames_gen[static_cast<uint32_t>(addr) - 4];
        }
        Uint32Reg & getReg(WoUint32RegNames addr)
        {
            return m_wouint32regnames_gen[static_cast<uint32_t>(addr) - 6];
        }
        Uint8Reg & getReg(WoInt8RegNames addr)
        {
            return m_woint8regnames_gen[static_cast<uint32_t>(addr) - 9];
        }

    private:
        Uint32Reg m_rouint32regnames_gen[4] = { Uint32Reg(0, RegAccessType::RO),
                                                Uint32Reg(1, RegAccessType::RO),
                                                Uint32Reg(2, RegAccessType::RO),
                                                Uint32Reg(3, RegAccessType::RO) };

        Uint8Reg m_roint8regnames_gen[2] = { Uint8Reg(4, RegAccessType::RO),
                                             Uint8Reg(5, RegAccessType::RO) };

        Uint32Reg m_wouint32regnames_gen[3] = { Uint32Reg(6, RegAccessType::WO),
                                                Uint32Reg(7, RegAccessType::WO),
                                                Uint32Reg(8, RegAccessType::WO) };

        Uint8Reg m_woint8regnames_gen[2] = { Uint8Reg(9, RegAccessType::WO),
                                             Uint8Reg(10, RegAccessType::WO) };

};







