//
// Created by raz_a on 08/12/2019.
//

#include"library1.h"
#include"DataCenterManager.h"

void *Init() {
    DataCenterManager *DS = new DataCenterManager();
    return (void *) DS;
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    if (dataCenterID <= 0 || numOfServers <= 0 || DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((DataCenterManager *) DS)->AddDataCenter(dataCenterID,
                                                     numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    if (DS == nullptr || dataCenterID <= 0) {
        return INVALID_INPUT;
    }

    return ((DataCenterManager *) DS)->RemoveDataCenter(dataCenterID);
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os,
                         int *assignedID) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((DataCenterManager *) DS)->RequestServer(dataCenterID, serverID, os,
                                                     assignedID);
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((DataCenterManager *) DS)->FreeServer(dataCenterID, serverID);
}

StatusType
GetDataCentersByOS(void *DS, int os, int **dataCenters, int *numOfDataCenters) {
    if (DS == nullptr || dataCenters == nullptr ||
        numOfDataCenters == nullptr || os > 1 || os < 0) {
        return INVALID_INPUT;
    }

    return ((DataCenterManager *) DS)->GetDataCentersByOS(os, dataCenters,
                                                          numOfDataCenters);
}

void Quit(void **DS) {
    auto ds = (DataCenterManager *) (*DS);
    delete(ds);
    *DS = nullptr;

}


