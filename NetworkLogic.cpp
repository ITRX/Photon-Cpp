#include "NetworkLogic.h"

NetworkLogic::NetworkLogic(const JString& appID, const JString& appVersion){
    mLoadBalancingClient = new ExitGames::LoadBalancing::Client(mListener, appID, appVersion, ExitGames::Photon::ConnectionProtocol::TCP);
    
    received = false;
}

NetworkLogic::~NetworkLogic(){ 
    delete mLoadBalancingClient;
}

void NetworkLogic::connect() {
    // connect() is asynchronous - the actual result arrives in the Listener::connectReturn() or the Listener::connectionErrorReturn() callback
    mLoadBalancingClient->connect(ExitGames::LoadBalancing::AuthenticationValues(), "ITRX");
}

void NetworkLogic::run() {
    // needs to be called regularly!
    //mListener.ClearReceiveData();
    mLoadBalancingClient->service();
    
    
    //s3d::ClearPrint();
    //s3d::Print << runCount << U" " << recieveCount;
}

void NetworkLogic::disconnect() {
    // disconnect() is asynchronous - the actual result arrives in the Listener::disconnectReturn() callback
    mLoadBalancingClient->disconnect();
}

void NetworkLogic::JoinOrCreateRoom(const JString& roomName, nByte maxPlayers) {
    //mLoadBalancingClient->opCreateRoom(roomName, RoomOptions().setMaxPlayers(maxPlayers));
    RoomOptions ro;
    ro.setMaxPlayers(maxPlayers);
    ro.setDirectMode(ExitGames::LoadBalancing::DirectMode::ALL_TO_ALL);
    mLoadBalancingClient->opJoinOrCreateRoom(roomName, ro);
}

bool NetworkLogic::isReceive(){
    return received;
}
