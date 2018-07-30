#include "standart_registers.h"
#include <iostream>
#include "slonyk_network_provider.h"
#include "i_transport_provider.h"
#include "slonyk_master.h"
#include "slonyk_slave.h"
#include "slonyk_table.h"
using namespace std;

int main()
{
    SlTable myTable;
    SimpleTable smTable;
    smTable.writeReg(WoUint32RegNames::x, 100);
    SlSlave<SimpleTable> slave1(10, smTable);
    SlSlave<SimpleTable> slave2(20, smTable);
    SlSlave<SlTable> slave3(30, myTable);
    SlMaster<3> master(&slave1, &slave2, &slave3);



	cout << "Pain" << endl; // prints Pain
	return 0;
}
