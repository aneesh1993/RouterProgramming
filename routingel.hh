#ifndef CLICK_ROUTINGEL_HH
#define CLICK_ROUTINGEL_HH
#include <click/element.hh>
#include "topology.hh"
CLICK_DECLS

class routingel :public topology {
public:

	routingel();
	~routingel();

	const char *class_name() const { return "routingel"; }
	const char *port_count() const { return "1/0"; }
	const char *processing() const { return PUSH; }

	void push(int port, Packet *packet);
	int configure(ErrorHandler *errh);
       
        
};
CLICK_ENDDECLS
#endif

