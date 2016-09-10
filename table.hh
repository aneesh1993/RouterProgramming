struct ForwardingTable
{
	uint8_t destination=0;
	uint8_t port=0;
};

struct RoutingTable
{
	int destination=0;
	int cost=0;
	uint8_t nexthop[3]={0};
};