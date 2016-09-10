#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include <click/packet.hh>
#include "rtr.hh" 

CLICK_DECLS

rtr::rtr() : _timerUPD(this), _timerHello(this){
	_seq = 0;
	_period = 5;
	_periodHello = 5;
	_delay = 0;
	_time_out = 1;
	_my_address = 0;
	_other_address = 0;
	transmissions = 0;
}

rtr::~rtr() {

}

int rtr::initialize(ErrorHandler *errh) {
	_timerUPD.initialize(this);
	_timerHello.initialize(this);
    	_timerUPD.schedule_after_sec(_period);
	_timerHello.schedule_after_sec(_periodHello);
    return 0;
}

int rtr::configure(Vector<String> &conf, ErrorHandler *errh) {
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


void rtr::run_timer(Timer *timer) {
if(timer == &_timerHello){
	click_chatter("Transmitting hello packet %u for %d time", _seq, transmissions);
	WritablePacket *packet = Packet::make(0, 0, sizeof(struct DataPacket) + 5, 0);
	memset(packet->data(), 0, packet->length());
	struct DataPacket *format1 = (struct DataPacket*) packet->data();
	format1->type = 1;
	format1->seqno = _seq;
	format1->sourceaddress = _my_address;
	format1->k = 1;
	format1->destinationaddress1 = _other_address;
	format1->destinationaddress2 = 0;
	format1->destinationaddress3 = 0;
format1->pay="HELLO";
	format1->length = sizeof(struct DataPacket) + 5;
	char *data1 = (char*)(packet->data() + sizeof(struct DataPacket));
	memcpy(data1, "HELLO", 5);
	output(0).push(packet);	

click_chatter("Transmitting update packet %u for %d time", _seq, transmissions);
	WritablePacket *pack = Packet::make(0, 0, sizeof(struct DataPacket) + 5, 0);
	memset(pack->data(), 0, pack->length());
	struct DataPacket *format2 = (struct DataPacket*) pack->data();
	format2->type = 2;
	format2->seqno = _seq;
	format2->sourceaddress = _my_address;
	format2->k = 1;
	format2->destinationaddress1 = _other_address;
	format2->destinationaddress2 = 0;
	format2->destinationaddress3 = 0;
format2->pay="UPDATE";
	format2->length = sizeof(struct DataPacket) + 5;

format2->tab=getRT();

	char *data2 = (char*)(pack->data() + sizeof(struct DataPacket));
	memcpy(data2, "HELLO", 5);
	output(0).push(pack);
_seq++;
transmissions++;
_timerHello.schedule_after_sec(_periodHello);

}

}

void rtr::push(int port, Packet *packet) 
{
	assert(packet);
struct DataPacket *header = (struct DataPacket *)packet->data();
if (header->type == 1)
{
	click_chatter("Hello packet received from %u",header->destinationaddress1);
packet->set_anno_u8(0, port);
	output(1).push(packet);
}
else if (header->type == 2)
{ 	click_chatter("Received Update Packet from %u",header->destinationaddress1);
	output(1).push(packet);
}
else if (header->type == 3 || header->type == 4)
{
	if (header->type == 3)
	{
click_chatter("Received Acknowledgement Packet from %u",header->destinationaddress1);

		if (header->destinationaddress1 == _my_address)
			packet->kill();
	}
	else {
		click_chatter("Received Data Packet from %u,Sending Acknowledgement",header->destinationaddress1);

if (!packet->anno_u8(8))
{
			output(1).push(packet);



}
		else {
			int outport = packet->anno_u8(8);
			output(outport).push(packet);
		}

	}
}
else {
	click_chatter("Received WrongPacket killing it");
	packet->kill();
}
}

CLICK_ENDDECLS
EXPORT_ELEMENT(rtr)
