require(library /home/comnetsii/elements/routerport.click);

rp1 :: RouterPort(DEV veth4, IN_MAC  fa:98:ad:2d:44:26 , OUT_MAC 82:e2:ef:55:33:8f );
rp2 :: RouterPort(DEV veth5, IN_MAC  5a:18:ed:09:03:0e , OUT_MAC 1a:32:4b:30:2a:df );

router1::rtr(MY_ADDRESS 3, OTHER_ADDRESS 2);
bc::BasicClassifier;
t::topology;
r::routingel;
f::fwd;

rp1->[0]router1[0]->rp1;
router1[1]->bc;
bc[0]->t;
bc[1]->r;
bc[2]->f;
f->[1]router1;
rp2->[2]router1[2]->rp2;


