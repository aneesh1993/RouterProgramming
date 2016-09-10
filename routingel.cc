#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <click/vector.cc>
 #include "routingel.hh"

CLICK_DECLS

routingel::routingel()
{

}

routingel::~routingel()
{

}

int routingel::configure(ErrorHandler *errh)
{
	return 0;
}

void routingel::push(int port, Packet *p)
{
	assert(p);
	struct DataPacket *header = (struct DataPacket *)p->data();

click_chatter("Update Packet received in topology block, updating routing table");

Vector<RoutingTable> routingtable=header->tab;

	for (Vector<RoutingTable>::const_iterator i = routingtable.begin();i != routingtable.end();i++)
	{
int src=header->sourceaddress;
int dest=i->destination;
int c=i->cost;
         updateRT(src,dest,c);
	}
                   
}

CLICK_ENDDECLS
EXPORT_ELEMENT(routingel)
ELEMENT_MT_SAFE(routingel)