#ifndef CLICK_TOPOLOGY_HH
#define CLICK_TOPOLOGY_HH
#include <click/element.hh>
#include <click/vector.hh>
#include <click/timer.hh>
#include "packet.hh"

CLICK_DECLS

class topology : public Element {
public:

	topology();
	~topology();

	const char *class_name() const { return "topology"; }
	const char *port_count() const { return "1/0"; }
	const char *processing() const { return PUSH; }

	void push(int port, Packet *packet);
	int initialize(ErrorHandler *);


Vector<ForwardingTable> forwardingtable;
Vector<RoutingTable> routingtable;

	void updateFT(uint8_t,int);
	uint8_t getFT(int);
	void updateRT(int,int,int);
	Vector<RoutingTable> getRT();
};

CLICK_ENDDECLS
#endif
