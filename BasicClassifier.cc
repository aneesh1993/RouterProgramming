#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <click/packet.hh>
#include "BasicClassifier.hh" 
#include "packet.hh"

CLICK_DECLS 

BasicClassifier::BasicClassifier() {
}

BasicClassifier::~BasicClassifier(){
	
}

int BasicClassifier::initialize(ErrorHandler *errh){
    return 0;
}

void BasicClassifier::push(int port, Packet *packet) {
	assert(packet);
	struct DataPacket *header = (struct DataPacket *)packet->data();
if (header->type==1)
{
click_chatter("Hello packet received, sending through output port 1 of classifier");
		output(0).push(packet);
packet->kill();	
}
else if(header->type==2)
{
click_chatter("Update packet received, sending through output port 2 of classifier");
		output(1).push(packet);
packet->kill();	
}
	else if(header->type == 4) {
	click_chatter("Data packet received, sending through output port 3 of classifier");
		output(2).push(packet);		
	} else if(header->type == 3) {
	click_chatter("Ack packet received, sending througho output port3 of client");
		output(2).push(packet);
	} else {
		click_chatter("Wrong packet type");
		packet->kill();
	}
}

CLICK_ENDDECLS 
EXPORT_ELEMENT(BasicClassifier)
