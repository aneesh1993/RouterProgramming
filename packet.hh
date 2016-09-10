#include "table.hh"
#include <click/string.hh>
struct DataPacket
{
	uint8_t type=0;
	int sourceaddress=0;
	uint8_t seqno=0;
	uint8_t k=0;
	int destinationaddress1=0;
	int destinationaddress2=0;
	int destinationaddress3=0;
	uint16_t length=0;
	String pay="MESSAGE";
        Vector<RoutingTable> tab; 
};