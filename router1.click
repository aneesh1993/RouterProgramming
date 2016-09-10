require(library /home/comnetsii/elements/routerport.click);

rp1 :: RouterPort(DEV veth2, IN_MAC be:da:bf:73:ff:0d , OUT_MAC f2:fd:13:ff:d3:8a );
rp2 :: RouterPort(DEV veth3, IN_MAC 82:e2:ef:55:33:8f , OUT_MAC fa:98:ad:2d:44:26 );

router1::rtr(MY_ADDRESS 2, OTHER_ADDRESS 3);
bc::BasicClassifier;
t::topology;
r::routingel;
f::fwd;

rp1->[0]router1[0]->rp2;
router1[1]->bc;
bc[0]->t;
bc[1]->r;
bc[2]->f;
f->[1]router1;
rp2->[2]router1[2]->rp1;


