#ifndef CLICK_FWD_HH
#define CLICK_FWD_HH
#include <click/vector.hh>
#include <click/timer.hh>
#include <click/element.hh>
#include "topology.hh"

CLICK_DECLS

class fwd : public topology {
public:

	fwd();
	~fwd();

	const char *class_name() const { return "fwd"; }
	const char *port_count() const { return "1/1"; }
	const char *processing() const { return PUSH; }
	void push(int port, Packet *packet);
	int initialize(ErrorHandler *errh);

};

CLICK_ENDDECLS
#endif
