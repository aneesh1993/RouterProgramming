
#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <click/packet.hh>
#include <click/vector.hh>
#include "topology.hh"

CLICK_DECLS

topology::topology()
{

}

topology::~topology()
{

}


int topology::initialize(ErrorHandler *errh)
{
	return 0;
}


void topology::updateFT(uint8_t p,int src)
{
Vector<ForwardingTable>::iterator i;
	int flg = 0;
	for (i = forwardingtable.begin();i != forwardingtable.end();i++)
	{
		if (i->destination == src)
		{
			flg = 1;
			break;
		}
	}
	if (flg == 0)
	{
ForwardingTable ft;
		ft.destination = src;
		ft.port = p;
		forwardingtable.push_back(ft);
	}
}

void topology::updateRT(int sourceaddress, int destinationaddress, int c)
{
Vector<RoutingTable>::iterator i;

	RoutingTable rt;
	int flag = 0;
	for (i = routingtable.begin();i != routingtable.end();i++)
	{
		if (rt.destination == destinationaddress)
		{
			flag = 1;

			if (sourceaddress == destinationaddress)
			{
				break;
			}

			else if (sourceaddress != destinationaddress)
			{
				int a = c + 1;

				if ((rt.cost) > a)
				{
					rt.cost = a;
					rt.nexthop[0] = sourceaddress;
				}
else if(rt.cost==a)
{
for(int i=0;i<3;i++)
{
if(rt.nexthop[i]!=0)
{
rt.nexthop[i]=a;
break;
}
}
}
else break;
			}
		}
	}
		
	if (flag == 0)
	{
		if (sourceaddress == destinationaddress)
		{
			rt.destination=rt.nexthop[0]=sourceaddress;
			rt.cost = 1;
			routingtable.push_back(rt);
		}
		else {
			rt.destination = destinationaddress;
			rt.nexthop[0] = sourceaddress;
			rt.cost = c + 1;
routingtable.push_back(rt);
		}
	}

}


uint8_t topology:: getFT(int destinationaddress)
{
Vector<ForwardingTable>::iterator i;
for (i = forwardingtable.begin();i != forwardingtable.end();i++)
	{
if(i->destination==destinationaddress)
return i->port;
}
return -1;
}

Vector<RoutingTable> topology::getRT()
{
return routingtable;
}

void topology::push(int port, Packet *p)
{

	assert(p);
	struct DataPacket *header = (struct DataPacket *)p->data();
click_chatter("Hello Packet received in topology block, updating forwarding table and routing table");

	uint8_t prt = p->anno_u8(0);
	int src = header->sourceaddress;
	updateFT(prt, src);
	updateRT(src, src, 1);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(topology)

