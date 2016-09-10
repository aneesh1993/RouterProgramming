#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include<click/element.hh>
#include <click/timer.hh>
#include "fwd.hh"


CLICK_DECLS

fwd::fwd()
{

}

fwd::~fwd()
{

}

int fwd::initialize(ErrorHandler *errh)
{
	return 0;
}

void fwd::push(int port, Packet *p)
{
	assert(p);
	struct DataPacket *header = (struct DataPacket *)p->data();

             int dest1 = header->destinationaddress1;
		int prt1 = getFT(dest1);
                p->set_anno_u8(8, prt1);
		output(0).push(p);


}

//CLICK_ENDDECLS
//EXPORT_ELEMENT(fwd)
