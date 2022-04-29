#include <iostream>
#include <string>
#include <cstdlib>

#include "simulation.h"
#include "queueAsArray.h"

using namespace std;

//*************** customerType ************
void customerType::setCustomerInfo(int customerN, int arrvTime, int wTime, int tTime)
{
    customerNumber = customerN;
    arrivalTime = arrvTime;
    waitingTime = wTime;
    transactionTime = tTime;
}

customerType::customerType(int customerN, int arrvTime, int wTime, int tTime)
{
    setCustomerInfo(customerN, arrvTime, wTime, tTime);
}

int customerType::getWaitingTime() const
{
    return waitingTime;
}

void customerType::incrementWaitingTime()
{
    waitingTime++;
}

void customerType::setWaitingTime(int time)
// Function to set the waiting time of a customer.
// Postcondition: waitingTime = time;
{
    waitingTime = time;
}
int customerType::getArrivalTime() const
// Function to return the arrival time of a customer.
// Postcondition: The value of arrivalTime is returned.
{
    return arrivalTime;
}
int customerType::getTransactionTime() const
// Function to return the transaction time of a customer.
// Postcondition: The value of transactionTime is returned.
{
    return transactionTime;
}
int customerType::getCustomerNumber() const
// Function to return the customer number.
// Postcondition: The value of customerNumber is returned.
{
    return customerNumber;
}

//**************** serverType **********
serverType::serverType()
{
    status = "free";
    transactionTime = 0;
}

bool serverType::isFree() const
{
    return (status == "free");
}

void serverType::setBusy()
{
    status = "busy";
}

void serverType::setFree()
{
    status = "free";
}

void serverType::setTransactionTime(int t)
{
    transactionTime = t;
}

void serverType::setTransactionTime()
{
    int time;

    time = currentCustomer.getTransactionTime();

    transactionTime = time;
}

void serverType::decreaseTransactionTime()
{
    transactionTime--;
}

int serverType::getRemainingTransactionTime() const
// Function to return the remaining transaction time.
// Postcondition: The value of transactionTime is returned.
{
    return transactionTime;
}
void serverType::setCurrentCustomer(customerType cCustomer)
// Function to set the info of the current customer
// according to the parameter cCustomer.
// Postcondition: currentCustomer = cCustomer;
{
    currentCustomer = cCustomer;
}
int serverType::getCurrentCustomerNumber() const
// Function to return the customer number of the current
// customer.
// Postcondition: The value of customerNumber of the
//                current customer is returned.
{
    return currentCustomer.getCustomerNumber();
}
int serverType::getCurrentCustomerArrivalTime() const
// Function to return the arrival time of the current
// customer.
// Postcondition: The value of arrivalTime of the current
//                customer is returned.
{
    return currentCustomer.getArrivalTime();
}
int serverType::getCurrentCustomerWaitingTime() const
// Function to return the current waiting time of the
// current customer.
// Postcondition: The value of transactionTime is
//                returned.
{
    return currentCustomer.getWaitingTime();
}
int serverType::getCurrentCustomerTransactionTime() const
// Function to return the transaction time of the
// current customer.
// Postcondition: The value of transactionTime of the
//                current customer is returned.
{
    return currentCustomer.getTransactionTime();
}

//************** serverListType ***********
serverListType::serverListType(int num)
{
    numOfServers = num;
    servers = new serverType[num];
}

serverListType::~serverListType()
{
    delete[] servers;
}

int serverListType::getFreeServerID() const
{
    int serverID = -1;

    int i;

    for (i = 0; i < numOfServers; i++)
        if (servers[i].isFree())
        {
            serverID = i;
            break;
        }

    return serverID;
}

int serverListType::getNumberOfBusyServers() const
{
    int busyServers = 0;

    int i;

    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
            busyServers++;

    return busyServers;
}

void serverListType::setServerBusy(int serverID, customerType cCustomer, int tTime)
{
    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(tTime);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void serverListType::setServerBusy(int serverID, customerType cCustomer)
{
    int time;

    time = cCustomer.getTransactionTime();

    servers[serverID].setBusy();
    servers[serverID].setTransactionTime(time);
    servers[serverID].setCurrentCustomer(cCustomer);
}

void serverListType::updateServers(ostream &outFile)
{
    int i;

    for (i = 0; i < numOfServers; i++)
        if (!servers[i].isFree())
        {
            servers[i].decreaseTransactionTime();

            if (servers[i].getRemainingTransactionTime() == 0)
            {
                outFile << "From server number " << (i + 1)
                        << " customer number "
                        << servers[i].getCurrentCustomerNumber()
                        << "\n     departed at time unit "
                        << servers[i].getCurrentCustomerArrivalTime() + servers[i].getCurrentCustomerWaitingTime() + servers[i].getCurrentCustomerTransactionTime()
                        << endl;
                servers[i].setFree();
            }
        }
}

//*************** waitQueue ************
waitingCustomerQueueType::waitingCustomerQueueType(int size) : queueType<customerType>(size)
{
}

void waitingCustomerQueueType::updateWaitingQueue()
{
    customerType cust;

    cust.setWaitingTime(-1);
    int wTime = 0;

    addQueue(cust);

    while (wTime != -1)
    {
        cust = front();
        deleteQueue();

        wTime = cust.getWaitingTime();
        if (wTime == -1)
            break;
        cust.incrementWaitingTime();
        addQueue(cust);
    }
}