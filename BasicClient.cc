#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <click/packet.hh>
#include "BasicClient.hh" 
#include "packet.hh"

CLICK_DECLS 

BasicClient::BasicClient() : _timerTO(this), _timerHello(this) {
	_seq = 0;
	_period = 5;
	_periodHello = 5;
	_delay = 0;
	_time_out = 1;
	_my_address = 0;
	_other_address = 0;
	transmissions = 0;
}

BasicClient::~BasicClient(){
	
}

int BasicClient::initialize(ErrorHandler *errh){
    _timerTO.initialize(this);
	_timerHello.initialize(this);
	if(_delay>0){
    	_timerTO.schedule_after_sec(_delay);
	}
	_timerHello.schedule_after_sec(_periodHello);
    return 0;
}

int BasicClient::configure(Vector<String> &conf, ErrorHandler *errh) {
  if (cp_va_kparse(conf, this, errh,
                  "MY_ADDRESS", cpkP+cpkM, cpUnsigned, &_my_address,
                  "OTHER_ADDRESS", cpkP+cpkM, cpUnsigned, &_other_address,
                  "DELAY", cpkP, cpUnsigned, &_delay,
                  "PERIOD", cpkP, cpUnsigned, &_period,
                   "PERIOD_HELLO", cpkP, cpUnsigned, &_periodHello,
                  "TIME_OUT", cpkP, cpUnsigned, &_time_out,
                  cpEnd) < 0) {
    return -1;
  }
  return 0;
}

void BasicClient::run_timer(Timer *timer) {
if(timer == &_timerHello){
		click_chatter("Transmitting hello packet %u for %d time", _seq, transmissions);
    WritablePacket *packet = Packet::make(0,0,sizeof(struct DataPacket)+5, 0);
    memset(packet->data(),0,packet->length());
    struct DataPacket *format = (struct DataPacket*) packet->data();
    format->type =1;
	format->seqno = _seq;
	format->sourceaddress = _my_address;
	format->destinationaddress1 = _other_address;
        format->length = sizeof(struct DataPacket)+5;
format->pay="HELLO";
	char *data = (char*)(packet->data()+sizeof(struct DataPacket));
	memcpy(data, "hello", 5);
    output(0).push(packet);
	transmissions++;
_seq++;	
	    _timerHello.schedule_after_sec(_periodHello);
    
	} else if(timer == &_timerTO){
		click_chatter("Transmitting data packet %u for %d time", _seq, transmissions);
    WritablePacket *packet = Packet::make(0,0,sizeof(struct DataPacket)+5, 0);
    memset(packet->data(),0,packet->length());
    struct DataPacket *format = (struct DataPacket*) packet->data();
    format->type =4;
	format->seqno = _seq;
	format->sourceaddress = _my_address;
	format->k=3;
	format->destinationaddress1 = _other_address;
	format->destinationaddress2 = 500;
	format->destinationaddress3 = 600;
format->pay="DATAPACKET";
    format->length = sizeof(struct DataPacket)+5;
	char *data = (char*)(packet->data()+sizeof(struct DataPacket));
	memcpy(data, "hello", 5);
    output(0).push(packet);
	transmissions++;
_seq++;	
    _timerTO.schedule_after_sec(_time_out);
	} else {
    	assert(false);
	}
}

void BasicClient::push(int port, Packet *packet) {
	assert(packet);
			struct DataPacket *header = (struct DataPacket *)packet->data();
if(header->type==4)
{
		click_chatter("Received packet %u from %u", header->seqno, header->sourceaddress);
		click_chatter("Details of the packet are k= %u,length= %u", header->k, header->length);
	    WritablePacket *Packet = Packet::make(0,0,sizeof(struct DataPacket), 0);
	    memset(Packet->data(),0,Packet->length());
		struct DataPacket *format = (struct DataPacket*) Packet->data();
	    format->type = 3;
		format->seqno = header->seqno;
		format->sourceaddress = _my_address;
		format->destinationaddress1 = header->sourceaddress;
		format->k= 1;
format->pay="DATA_ACK";
		click_chatter("Sending Ack");
		char *data = (char*)(packet->data()+sizeof(struct DataPacket));
	memcpy(data, "hello", 5);
packet->kill();
		output(0).push(Packet);
_timerTO.schedule_after_sec(_period);
	} else if (header->type==3) { 
		struct DataPacket *header = (struct DataPacket *)packet->data();
		click_chatter("Received AckPacket %u from %u", header->seqno, header->sourceaddress);
		if(header->seqno == _seq) {
			_timerTO.unschedule();
			_seq++;
			transmissions=0;
			_timerTO.schedule_after_sec(_period);
		} 

else if(header->type==1)
{
click_chatter("Received HelloPacket %u from %u", header->seqno, header->sourceaddress);
}

else { //received wrong seqno number
click_chatter("Received WrongPacket killing it");

			packet->kill();
		}
	} else {
		packet->kill();
	}
}

CLICK_ENDDECLS 
EXPORT_ELEMENT(BasicClient)
