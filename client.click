require(library /home/comnetsii/elements/routerport.click);

rp :: RouterPort(DEV veth1, IN_MAC f2:fd:13:ff:d3:8a , OUT_MAC  be:da:bf:73:ff:0d );

client::BasicClient(MY_ADDRESS 1, OTHER_ADDRESS 4);

client->rp;
rp->client;


