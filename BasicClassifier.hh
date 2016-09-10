#ifndef CLICK_BASICCLASSIFIER_HH 
#define CLICK_PACKETGENERATOR_HH 
#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class BasicClassifier : public Element {
    public:
        BasicClassifier();
        ~BasicClassifier();
        const char *class_name() const { return "BasicClassifier";}
        const char *port_count() const { return "1/3";}
        const char *processing() const { return PUSH; }
		
		void push(int port, Packet *packet);
        int initialize(ErrorHandler*);
		
}; 

CLICK_ENDDECLS
#endif 
