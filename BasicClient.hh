#ifndef CLICK_BASICCLIENT_HH 
#define CLICK_BASICCLIENT_HH 
#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class BasicClient : public Element {
    public:
        BasicClient();
        ~BasicClient();
        const char *class_name() const { return "BasicClient";}
        const char *port_count() const { return "1/1";}
        const char *processing() const { return PUSH; }
		int configure(Vector<String> &conf, ErrorHandler *errh);
		
        void run_timer(Timer*);
		void push(int port, Packet *packet);
        int initialize(ErrorHandler*);
		
    private: 
        Timer _timerHello;
        Timer _timerTO;
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
