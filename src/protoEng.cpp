#include "standart_registers.h"
#include <iostream>
#include "slonyk_network_provider.h"
#include "i_transport_provider.h"
#include "slonyk_master.h"
#include "slonyk_slave.h"
#include "slonyk_table.h"
#include "slonyk_data_link_provider.h"
#include "i_provider.h"
#include "slonyk_transport_provider.h"
using namespace std;




class SomeSlLinkProvider : public SlDataLinkProvider<1>
{
    public:
        void sendData(uint8_t * data, uint32_t len)
        {
            printf("dataTryToSend. len = %d \n", len);
            printf("data :\n");

            for(uint8_t i = 0; i < len; i++)
            {
                printf("%0x", *(data + i));
            }
            printf("\n");
        }
        void dataReceiveCallback(uint8_t * data, uint32_t len)
        {
            for(uint8_t i = 0; i < m_totalProviders; i++)
            {
                m_providers[i]->dataReceived(data, len);
            }
        }
};

class SlRawData
{
public:
	SlRawData(): data(0), len(0)
	{

	}
	SlRawData& operator= (uint8_t * right)
	{
		data = right;
		return *this;
	}
	SlRawData& operator= (uint32_t right)
	{
		len = right;
		return *this;
	}
	uint8_t * data;
	uint32_t len;

};

int main()
{
    SomeSlLinkProvider dtlProvider;
    SlTransportProvider trProvider;
    SimpleTable smTable;
    SlSlave<SimpleTable> slave(10, smTable, trProvider);
    SimpleSlave smSlave;
    SlMaster<1> master(&smSlave);
    SlSegment seg;
    smSlave.segmentReceivedCallback(seg);
    //SlNetworkProvider<1> networkProvider(dtlProvider);
//    SlTable myTable;
//    SimpleTable smTable;
//    smTable.writeReg(WoUint32RegNames::x, 100);
//    SlSlave<SimpleTable> slave1(10, smTable);
//    SlSlave<SimpleTable> slave2(20, smTable);
//    SlSlave<SlTable> slave3(30, myTable);
//    SlMaster<3> master(&slave1, &slave2, &slave3);



	cout << "Pain" << endl; // prints Pain
	return 0;
}
