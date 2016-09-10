require(library /home/comnetsii/elements/routerport.click);

rp :: RouterPort(DEV veth6, IN_MAC 1a:32:4b:30:2a:df , OUT_MAC 5a:18:ed:09:03:0e );
client::BasicClient(MY_ADDRESS 4, OTHER_ADDRESS 1);


client->rp;
rp->client;