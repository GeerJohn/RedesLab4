#ifndef NET
#define NET

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>
#include <iostream>
#include <cstdlib>

using namespace omnetpp;

class Net: public cSimpleModule {
private:
    cOutVector hopsCount;
public:
    Net();
    virtual ~Net();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Net);

#endif /* NET */

Net::Net() {
}

Net::~Net() {
}

void Net::initialize() {
    hopsCount.setName("Hops Count");
}

void Net::finish() {
}

void Net::handleMessage(cMessage *msg) {
    //genero dos numeros random entre los numeros 0 y 1
    int random = rand() % 2;
    // All msg (events) on net are packets
    Packet *pkt = (Packet *) msg;
    // If this node is the final destination, send to App
    if (pkt->getDestination() == this->getParentModule()->getIndex()) {
        send(msg, "toApp$o");
        hopsCount.record(pkt->getHopCount());
    }
    // If not, forward the packet to some else... to who?
    else {
        // Si el numero random es 1 => envio a lnk 1
        if (random == 1) {
            send(msg, "toLnk$o", 1);
            pkt->setHopCount(pkt->getHopCount() + 1);
        }
        // Si no es 1, envio por lnk 0
        else {
            send(msg, "toLnk$o", 0);
            pkt->setHopCount(pkt->getHopCount() + 1);
        }
    }
}
