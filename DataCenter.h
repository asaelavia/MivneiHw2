//
// Created by Avia on 28/11/2019.
//

#ifndef HW2_DATACENTER_H
#define HW2_DATACENTER_H

#include "Auxiliaries.h"
#include "library1.h"
#include <iostream>

class DataCenter {
    class ServerData {
    private:
        int serverId;
        bool occupied = false;
        int os = 0;
        Node<ServerData *> *listPointer;
    public:

        ServerData(ServerData &) = delete;

        ServerData();

        ~ServerData();

        void setServerId(int serverId);

        int getServerId() const;

        void setListPointer(Node<ServerData *> *listPointer);

        Node<ServerData *> *getListPointer() const;


        bool getOccupied() const;

        void setOccupied(bool occupied);

        int getOs() const;

        void setOs(int os);

    };

private:
    int dataCenterid;
    int numOfServersInDb;
    int linuxCounter;
    int windowsCounter;
    LinkedList<ServerData *> linuxServers;
    LinkedList<ServerData *> windowsServers;
    ServerData *serversArray;
public:
    DataCenter() = default;

    DataCenter(int id, int numOfServers);

    int getLinuxServerCounter();

    int getWindowsServerCounter();

    int getLinsInDb();

    int getWinsInDb();

    StatusType requestServerFromDb(int serverID, int os, int *assignedID);

    StatusType freeServerFromDb(int serverID);

    ~DataCenter();
};

DataCenter::DataCenter(int id, int numOfServers) {
    dataCenterid = id;
    numOfServersInDb = numOfServers;
    linuxCounter = numOfServers;
    windowsCounter = 0;
    serversArray = new ServerData[numOfServers];
    for (int i = 0; i < numOfServers; ++i) {
        serversArray[i].setServerId(i);
        linuxServers.add(&serversArray[i]);
        serversArray[i].setListPointer(linuxServers.tail);
    }
}

int DataCenter::getLinuxServerCounter() {
    return linuxCounter;
}

int DataCenter::getWindowsServerCounter() {
    return windowsCounter;
}

DataCenter::~DataCenter() {
    delete[] (serversArray);
}

StatusType DataCenter::freeServerFromDb(int serverID) {
    if ((serverID < 0) || (serverID >= numOfServersInDb))
        return INVALID_INPUT;
    ServerData *serverData = &serversArray[serverID];
    if (!serverData->getOccupied())
        return FAILURE;
    serverData->setOccupied(false);
    if (serverData->getOs()) {
        windowsServers.add(serverData);
        return SUCCESS;
    }
    linuxServers.add(serverData);
    return SUCCESS;
}

StatusType
DataCenter::requestServerFromDb(int serverId, int os, int *assignedID) {
    if ((serverId >= numOfServersInDb) || (serverId < 0) || (os > 1) ||
        (os < 0) || (assignedID == nullptr))
        return INVALID_INPUT;
    ServerData *serverData = &serversArray[serverId];
    if (serverData->getOccupied()) {
        if (os == 0) {
            if (!linuxServers.isListEmpty()) {
                linuxServers.getFirst()->setOccupied(true);
                *assignedID = linuxServers.getFirst()->getServerId();
                linuxServers.removeFirst();
                return SUCCESS;
            } else {
                if (!windowsServers.isListEmpty()) {
                    windowsServers.getFirst()->setOccupied(true);
                    windowsServers.getFirst()->setOs(0);
                    *assignedID = windowsServers.getFirst()->getServerId();
                    windowsServers.removeFirst();
                    windowsCounter--;
                    linuxCounter++;
                    return SUCCESS;
                } else {
                    return FAILURE;
                }

            }
        } else {
            if (!windowsServers.isListEmpty()) {
                windowsServers.getFirst()->setOccupied(true);
                windowsServers.getFirst()->setOs(os);
                *assignedID = windowsServers.getFirst()->getServerId();
                windowsServers.removeFirst();
                return SUCCESS;
            } else {
                if (!linuxServers.isListEmpty()) {
                    linuxServers.getFirst()->setOccupied(true);
                    linuxServers.getFirst()->setOs(os);
                    *assignedID = linuxServers.getFirst()->getServerId();
                    linuxServers.removeFirst();
                    windowsCounter++;
                    linuxCounter--;
                    return SUCCESS;
                } else {
                    return FAILURE;
                }

            }

        }
    } else {
        serverData->setOccupied(true);
        *assignedID = serverId;
        if (serverData->getOs()) {
            windowsServers.removeNode(serverData->getListPointer());
            serverData->setListPointer(nullptr);
        } else {
            linuxServers.removeNode(serverData->getListPointer());
            serverData->setListPointer(nullptr);
        }
        if (serverData->getOs()) {
            if (os == 0) {
                windowsCounter--;
                linuxCounter++;
            }
        } else {
            if (os == 1) {
                linuxCounter--;
                windowsCounter++;
            }
        }
        serverData->setOs(os);
        return SUCCESS;
    }
}

int DataCenter::getLinsInDb() {
    return linuxCounter;
}

int DataCenter::getWinsInDb() {
    return windowsCounter;
}


void DataCenter::ServerData::setServerId(int serverid) {
    serverId = serverid;
}

void DataCenter::ServerData::setListPointer(
        Node<DataCenter::ServerData *> *listpointer) {
    listPointer = listpointer;
}


bool DataCenter::ServerData::getOccupied() const {
    return occupied;
}

void DataCenter::ServerData::setOccupied(bool occupied) {
    ServerData::occupied = occupied;
}

int DataCenter::ServerData::getOs() const {
    return os;
}

void DataCenter::ServerData::setOs(int os) {
    ServerData::os = os;
}

int DataCenter::ServerData::getServerId() const {
    return serverId;
}

Node<DataCenter::ServerData *> *DataCenter::ServerData::getListPointer() const {
    return listPointer;
}

DataCenter::ServerData::~ServerData() =
default;


DataCenter::ServerData::ServerData() =
default;

#endif //HW2_DATACENTER_H
