#include <omnetpp.h>

using namespace omnetpp;

class Tic2 : public cSimpleModule
{
private:
    simtime_t timeout;
    cMessage *timeoutEvent = nullptr;

public:
    virtual ~Tic2();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tic2);

Tic2::~Tic2()
{
    cancelAndDelete(timeoutEvent);
}

void Tic2::initialize()
{
    timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");

    EV << "Sending initial message\n";
    cMessage *msg = new cMessage("tictocMsg");
    send(msg, "out");
    scheduleAt(simTime()+timeout, timeoutEvent);
}

void Tic2::handleMessage(cMessage *msg)
{
    if (uniform(0, 1) < 0.25) {  // 90% de probabilidad de pérdida
        EV << "\"Losing\" message, re-sending...\n";
        bubble("message lost");
        send(msg, "out");  // Envía el mensaje original
    }
    else {
        EV << "Sending back same message as acknowledgement.\n";
        send(msg, "out");
    }
}

/////////////////////////////////////////////////

class Toc2 : public cSimpleModule
{
private:
    simtime_t timeout;
    cMessage *timeoutEvent = nullptr;

public:
    virtual ~Toc2();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Toc2);

Toc2::~Toc2()
{
    cancelAndDelete(timeoutEvent);
}


void Toc2::initialize()
{
    timeout = 3.0;
    timeoutEvent = new cMessage("timeoutEvent");
}

void Toc2::handleMessage(cMessage *msg)
{
    if (uniform(0, 1) < 0.5) {  // 90% de probabilidad de pérdida
        EV << "\"Losing\" message, re-sending...\n";
        bubble("message lost");
        send(msg, "out");  // Envía el mensaje original
    }
    else {
        EV << "Sending back same message as acknowledgement.\n";
        send(msg, "out");
    }
}

/////////////////////////////////////////

class Tac2 : public cSimpleModule
{
private:
    simtime_t timeout;
    cMessage *timeoutEvent = nullptr;

public:
    virtual ~Tac2();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Tac2);

Tac2::~Tac2()
{
    cancelAndDelete(timeoutEvent);
}

void Tac2::initialize()
{
    timeout = 1.0;
    timeoutEvent = new cMessage("timeoutEvent");
}

void Tac2::handleMessage(cMessage *msg)
{
    if (uniform(0, 1) < 0.25) {  // 90% de probabilidad de pérdida
        EV << "\"Losing\" message, re-sending...\n";
        bubble("message lost");
        send(msg, "out");  // Envía el mensaje original
    }
    else {
        EV << "Sending back same message as acknowledgement.\n";
        send(msg, "out");
    }
}
