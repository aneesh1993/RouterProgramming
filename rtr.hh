#ifndef CLICK_RTR_HH 
#define CLICK_RTR_HH 
#include <click/timer.hh>
#include <click/element.hh>
#include "topology.hh"
CLICK_DECLS

class rtr: public topology {
public:
	rtr();
	~rtr();
	const char *class_name() const { return "rtr"; }
	const char *port_count() const { return "3/3"; }
	const char *processing() const { return PUSH; }
int configure(Vector<String> &conf, ErrorHandler *errh);

	void run_timer(Timer*);
	void push(int port, Packet *packet);
	int initialize(ErrorHandler*);

private:
	Timer _timerHello;
        Timer _timerUPD;
        uint32_t _seq;
		uint32_t _delay;
		uint32_t _period;
		uint32_t _periodHello;
		uint32_t _time_out;
		uint32_t _my_address;
		uint32_t _other_address;
		int transmissions;
};

CLICK_ENDDECLS
#endif 
