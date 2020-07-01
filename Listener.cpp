#include "Listener.h"

Listener::Listener(){
    
}

Listener::~Listener(){
    
}

void Listener::debugReturn(int debugLevel, const JString& string){
    s3d::Print << U"debugReturn";// << endl;
}

void Listener::connectionErrorReturn(int errorCode){
    s3d::Print << U"connectionErrorReturn";// << endl;
}

void Listener::clientErrorReturn(int errorCode){
    s3d::Print << U"clientErrorReturn";// << endl;
}

void Listener::warningReturn(int warningCode){
    s3d::Print << U"warningReturn";// << endl;
}

void Listener::serverErrorReturn(int errorCode){
    s3d::Print << U"serverErrorReturn";// << endl;
}


//誰か入った時
void Listener::joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player){
    s3d::Print << U"joinRoomEventAction";// << endl;
}

//誰か出た時
void Listener::leaveRoomEventAction(int playerNr, bool isInactive){
    s3d::Print << U"leaveRoomEventAction";// << endl;
}

void Listener::customEventAction(int playerNr, nByte eventCode, const Object& eventContent){
    receiveData.push_back(eventContent);
}

void Listener::connectReturn(int errorCode,
                             const JString& errorString,
                             const JString& region,
                             const JString& cluster){
    
    s3d::Print << U"connectReturn";// << endl;
    if(errorCode == 0)
        serverConnected = true;
}

void Listener::disconnectReturn(){
    s3d::Print << U"disconnectReturn";// << endl;
}

void Listener::createRoomReturn(int localPlayerNr,
                                const Hashtable& roomProperties,
                                const Hashtable& playerProperties,
                                int errorCode,
                                const JString& errorString){
    s3d::Print << U"createRoomReturn";// << endl;
}

void Listener::joinOrCreateRoomReturn(int localPlayerNr,
                                      const Hashtable& roomProperties,
                                      const Hashtable& playerProperties,
                                      int errorCode,
                                      const JString& errorString){
    s3d::Print << U"joinOrCreateRoomReturn " << localPlayerNr;// << endl;
    if(errorCode == 0){
        joinRoom = true;
        playerID = localPlayerNr;
    }
}

void Listener::joinRandomOrCreateRoomReturn(int localPlayerNr,
                                            const Hashtable& roomProperties,
                                            const Hashtable& playerProperties,
                                            int errorCode,
                                            const JString& errorString){
    s3d::Print << U"joinRandomOrCreateRoomReturn";// << endl;
}

void Listener::joinRoomReturn(int localPlayerNr,
                              const Hashtable& roomProperties,
                              const Hashtable& playerProperties,
                              int errorCode,
                              const JString& errorString){
    s3d::Print << U"joinRoomReturn";// << endl;
}

void Listener::joinRandomRoomReturn(int localPlayerNr,
                          const Hashtable& roomProperties,
                          const Hashtable& playerProperties,
                          int errorCode,
                          const JString& errorString){
    s3d::Print << U"joinRandomRoomReturn";// << endl;
}

void Listener::leaveRoomReturn(int errorCode, const JString& errorString){
    s3d::Print << U"leaveRoomReturn";// << endl;
}

void Listener::joinLobbyReturn(){
    s3d::Print << U"joinLobbyReturn";// << endl;
}

void Listener::leaveLobbyReturn(){
    s3d::Print << U"leaveLobbyReturn";// << endl;
}

void Listener::onFindFriendsResponse(){
    s3d::Print << U"onFindFriendsResponse";// << endl;
}

void Listener::onLobbyStatsResponse(const JVector<LobbyStatsResponse>& lobbyStats){
    s3d::Print << U"onLobbyStatsResponse";// << endl;
}

void Listener::webRpcReturn(int errorCode,
                            const JString& errorString,
                            const JString& uriPath,
                            int resultCode,
                            const Dictionary<Object, Object>& returnData){
    s3d::Print << U"webRpcReturn";// << endl;
}

void Listener::onRoomListUpdate(){
    s3d::Print << U"onRoomListUpdate";// << endl;
}

void Listener::onRoomPropertiesChange(const Hashtable& changes){
    s3d::Print << U"onRoomPropertiesChange";// << endl;
}

void Listener::onPlayerPropertiesChange(int playerNr, const Hashtable& changes){
    s3d::Print << U"onPlayerPropertiesChange";// << endl;
}

void Listener::onAppStatsUpdate(){
    s3d::Print << U"onAppStatsUpdate";// << endl;
}

void Listener::onLobbyStatsUpdate(const JVector<LobbyStatsResponse>& lobbyStats){
    s3d::Print << U"onLobbyStatsUpdate";// << endl;
}

void Listener::onCacheSliceChanged(int cacheSliceIndex){
    s3d::Print << U"onCacheSliceChanged";// << endl;
}

void Listener::onMasterClientChanged(int id, int oldID){
    s3d::Print << U"onMasterClientChanged";// << endl;
}

// custom authentication
void Listener::onCustomAuthenticationIntermediateStep(const Dictionary<JString, Object>& customResponseData){
    s3d::Print << U"onCustomAuthenticationIntermediateStep";// << endl;
}

// receive the available server regions during the connect workflow (if you have specified in the constructor, that you want to select a region)
void Listener::onAvailableRegions(const JVector<JString>& availableRegions,
                                  const JVector<JString>& availableRegionServers){
    s3d::Print << U"onAvailableRegions";// << endl;
}

void Listener::onSecretReceival(const JString& secret){
    s3d::Print << U"onSecretReceival";// << endl;
}

void Listener::onDirectConnectionEstablished(int remoteID){
    s3d::Print << U"onDirectConnectionEstablished";// << endl;
}

void Listener::onDirectMessage(const Object& msg, int remoteID, bool relay){
    s3d::Print << U"onDirectMessage";// << endl;
}

void Listener::onCustomOperationResponse(const ExitGames::Photon::OperationResponse& operationResponse){
    s3d::Print << U"onCustomOperationResponse";// << endl;
}

void Listener::onGetRoomListResponse(const JVector<ExitGames::Common::Helpers::SharedPointer<Room> >& roomList,
                                     const JVector<JString>& roomNameList){
    s3d::Print << U"onGetRoomListResponse";// << endl;
}

list<Object>& Listener::getReceiveData(){
    return receiveData;
}

void Listener::ClearReceiveData(){
    receiveData.clear();
}

int Listener::getPlayerID(){
    return playerID;
}
