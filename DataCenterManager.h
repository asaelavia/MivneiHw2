//
// Created by Avia on 28/11/2019.
//

#ifndef HW2_DATACENTERMANAGER_H
#define HW2_DATACENTERMANAGER_H

#include "AVLTree.h"
#include "DataCenter.h"

class DataCenterManager {
    AVLTree<DataCenter> farms;
    AVLTree<int> farmsLin;
    AVLTree<int> farmsWin;
    int farmsCount;

public:
    DataCenterManager() = default;
    ~DataCenterManager() = default;
    StatusType AddDataCenter(int dataCenterID, int numOfServers);
    StatusType RemoveDataCenter(int dataCenterID);
    StatusType RequestServer(int dataCenterID, int serverID, int os, int* assignedID);
    StatusType FreeServer(int dataCenterID, int serverID);
    StatusType GetDataCentersByOS(int os, int **dataCenters, int* numOfDataCenters);
    void Quit();
};


StatusType DataCenterManager::AddDataCenter(int dataCenterID, int numOfServers) {
    try{
        DataCenter* dc = new DataCenter(dataCenterID, numOfServers);
        AVLNode<DataCenter>* node = farms.find(farms.getRoot(), dataCenterID);
        if(node != nullptr){
            return FAILURE;
        }
        farms.insertNode(dataCenterID, *dc);
        farmsLin.insertNode((numOfServers + (1.0 / dataCenterID)), dataCenterID);
        farmsWin.insertNode((0 + (1.0 / dataCenterID)), dataCenterID);
        farmsCount++;
        return SUCCESS;
    }
    catch(std::bad_alloc e){
        e.what();
        return ALLOCATION_ERROR;
    }
}

StatusType DataCenterManager::RemoveDataCenter(int dataCenterID) {
    AVLNode<DataCenter>* node = farms.find(farms.getRoot(), dataCenterID);

    if(node == nullptr){
        return FAILURE;
    }
    int linServers = node->data.getLinsInDb();
    int winServers = node->data.getWinsInDb();

    farms.deleteNode(dataCenterID);
    farmsLin.deleteNode(linServers + 1.0 / dataCenterID);
    farmsWin.deleteNode(winServers + 1.0 / dataCenterID);
    farmsCount--;

    return SUCCESS;
}

StatusType DataCenterManager::RequestServer(int dataCenterID, int serverID, int os, int *assignedID) {
    AVLNode<DataCenter>* node = farms.find(farms.getRoot(), dataCenterID);

    if(node == nullptr){
        return FAILURE;
    }

    int linServers = node->data.getLinsInDb();
    int winServers = node->data.getWinsInDb();

    farmsLin.deleteNode(linServers + (1.0 / dataCenterID));
    farmsWin.deleteNode(winServers + (1.0 / dataCenterID));

    StatusType st = node->data.requestServerFromDb(serverID,os,assignedID);

    linServers = node->data.getLinsInDb();
    winServers = node->data.getWinsInDb();

    farmsLin.insertNode((linServers + (1.0 / dataCenterID)), dataCenterID);
    farmsWin.insertNode((winServers + (1.0 / dataCenterID)), dataCenterID);

    return st;

}

StatusType DataCenterManager::FreeServer(int dataCenterID, int serverID) {
    AVLNode<DataCenter>* node = farms.find(farms.getRoot(), dataCenterID);

    if(node == nullptr){
        return FAILURE;
    }

    return node->data.freeServerFromDb(serverID);
}

void inOrderInsertList(AVLNode<int>* ptr, LinkedList<int>* inOrderList){
    if(ptr == nullptr) return;
    if(ptr->left){
        inOrderInsertList(ptr->left,inOrderList);
    }
    inOrderList->add(ptr->data);
    if(ptr->right){
        inOrderInsertList(ptr->right,inOrderList);
    }

}

StatusType DataCenterManager::GetDataCentersByOS(int os, int **dataCenters, int *numOfDataCenters) {
    if(farms.getRoot() == nullptr || farmsCount <= 0){
        return FAILURE;
    }

    *numOfDataCenters = farmsCount;

    AVLNode<int>* ptr;

    if(os == 1){
        ptr = farmsWin.getRoot();
    }
    else{
        ptr = farmsLin.getRoot();
    }

    try{
        *dataCenters = (int*)malloc(farmsCount* sizeof(int));
        if (*dataCenters == nullptr){
            return ALLOCATION_ERROR;
        }
    }
    catch(std::bad_alloc e){
        e.what();
        return ALLOCATION_ERROR;
    }

    LinkedList<int> inOrderList;
    inOrderInsertList(ptr, &inOrderList);
    Node<int>* ptr2 = inOrderList.head;
    for(int i = inOrderList.getListSize() - 1; i >= 0; i--){
        (*dataCenters)[i] = ptr2->data;
        ptr2 = ptr2->next;
    }
    return SUCCESS;

}

void DataCenterManager::Quit() {

    /**
    int* dataCenters0;
    int* dataCenters1;
    int numOfDataCenters0;
    int numOfDataCenters1;

    StatusType res0 = GetDataCentersByOS(0, &dataCenters0, &numOfDataCenters0);
    StatusType res1 = GetDataCentersByOS(1, &dataCenters1, &numOfDataCenters1);

    if(res0 == SUCCESS){
        for(int i=0; i < numOfDataCenters0; i++){
            RemoveDataCenter(dataCenters0[i]);
        }
    }

    if(res1 == SUCCESS){
        for(int i=0; i < numOfDataCenters1; i++){
            RemoveDataCenter(dataCenters1[i]);
        }
    }
    **/
}

#endif //HW2_DATACENTERMANAGER_H
