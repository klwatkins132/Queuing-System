# Queuing-System

A C++ Queuing System that can be used in a variety of applications. This system consists of a list of servers and a waiting queue holding the customers to be served. The customer at the front of the queue waits for the next available server. When a server becomes free, the customer at the front of the queue moves to the free server to be served.

When the first customer arrives, all servers are free and the customer moves to the first server. When the next customer arrives, if a server is available, the customer immediately moves to the available server; otherwise, the customer waits in the queue.

When a customer arrives, he or she goes to the end of the queue and the customer’s waiting time begins. If the queue is empty and a server is free, the customer is served immediately, so this customer’s waiting time is zero. On the other hand, if a customer arrives and either the queue is nonempty or all of the servers are busy, the customer must wait for the next available server and, therefore, this customer’s waiting time begins.

When a server becomes free and the waiting customer’s queue is nonempty, the customer at the front of the queue proceeds to begin the transaction. When the customer arrives at a server, the transaction time is set to five and is decremented after each time unit. When the transaction time becomes zero, the server is marked free.
