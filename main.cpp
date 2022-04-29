#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

#include "simulation.h"
#include "queueAsArray.h"

using namespace std;

void setSimulation(int &simulationTime, int &numOfServers, int &transactionTime, int &timeBetweenCustArrival);

bool isCustomerArrived(double arrivedTimeDiff);

void generateStatistics(serverListType &serverList, waitingCustomerQueueType &CQueue, int numOfCustArrived, int waitTimeServedCustomers);

void runSimulation();

int main()
{
    runSimulation();

    return 0;
}

void setSimulation(int &simulationTime, int &numOfServers, int &transactionTime, int &timeBetweenCustArrival)
{
    cout << "Enter the simulation time: ";
    cin >> simulationTime;
    cout << endl;

    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << endl;

    cout << "Enter the transaction time: ";
    cin >> transactionTime;
    cout << endl;

    cout << "Enter the time between customer arrivals: ";
    cin >> timeBetweenCustArrival;
    cout << endl;
}

bool isCustomerArrived(double arrivedTimeDiff)
{
    double value;

    value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

    return (value > exp(-1.0 / arrivedTimeDiff));
}

void runSimulation()
{
    waitingCustomerQueueType customerQueue;
    customerType customer;

    int simulationTime;
    int numOfServers;
    int transactionTime;
    int timeBetweenCustArrival;
    int numOfCustArrived = 0;
    int waitTimeServedCustomers = 0;
    int totalWaitTime = 0;
    int numberOfCustomersServed = 0;
    int customersLeftInServers = 0;
    int clock = 0;
    int serverID;

    setSimulation(simulationTime, numOfServers, transactionTime, timeBetweenCustArrival);

    serverListType serverList(numOfServers);

    for (clock = 1; clock <= simulationTime; clock++)
    {
        serverList.updateServers(cout);

        if (!customerQueue.isEmptyQueue())
            customerQueue.updateWaitingQueue();

        if (isCustomerArrived(timeBetweenCustArrival))
        {
            numOfCustArrived++;
            customer.setCustomerInfo(numOfCustArrived, clock, 0, transactionTime);
            customerQueue.addQueue(customer);
            cout << "Customer number " << numOfCustArrived << " arrived at time unit " << clock << endl;
        }
        serverID = serverList.getFreeServerID();
        if (serverID != -1 && !customerQueue.isEmptyQueue())
        {
            customer = customerQueue.front();
            customerQueue.deleteQueue();
            waitTimeServedCustomers = waitTimeServedCustomers + customer.getWaitingTime();
            serverList.setServerBusy(serverID, customer);
        }
    }
    cout << endl;

    cout << "The simulation ran for " << simulationTime << " time units" << endl;
    cout << "Number of servers: " << numOfServers << endl;
    cout << "Average transaction time: " << transactionTime << endl;
    cout << "Average arrival time difference between customers: " << timeBetweenCustArrival << endl;

    generateStatistics(serverList, customerQueue, numOfCustArrived, waitTimeServedCustomers);
}
void generateStatistics(serverListType &serverList, waitingCustomerQueueType &CQueue, int numOfCustArrived, int waitTimeServedCustomers)
{
    customerType customer;

    int customersLeftInQueue = 0;

    int totalWaitTime = waitTimeServedCustomers;

    while (!CQueue.isEmptyQueue())
    {
        customer = CQueue.front();
        CQueue.deleteQueue();
        totalWaitTime = totalWaitTime + customer.getWaitingTime();
        customersLeftInQueue++;
    }

    int customersLeftInServers = serverList.getNumberOfBusyServers();

    int numberOfCustomersServed = numOfCustArrived - customersLeftInServers - customersLeftInQueue;

    double averageWaitTime = 0;

    cout << "Total waiting time: " << totalWaitTime << endl;
    cout << "Number of customers that completed a transaction: " << numberOfCustomersServed << endl;
    cout << "Number of customers left in the servers: " << customersLeftInServers << endl;
    cout << "The number of customers left in queue: " << customersLeftInQueue << endl;

    if (numOfCustArrived > 0)
        averageWaitTime = (static_cast<double>(totalWaitTime)) / numOfCustArrived;

    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "Average waiting time: " << averageWaitTime << endl;
    cout << "************** END SIMULATION *************" << endl;
}