#include "Main.h"

#ifndef _LISTENER_H_
#define _LISTENER_H_

class Listener : public ExitGames::LoadBalancing::Listener {
private:
    list<Object> receiveData;
    int playerID;
    
public:
    Listener();
    ~Listener();
    
    list<Object>& getReceiveData();
    void ClearReceiveData();
    int getPlayerID();
    
    // receive and print out debug out here
    void debugReturn(int debugLevel, const JString& string);
    
    // implement your error-handling here
    void connectionErrorReturn(int errorCode);
    void clientErrorReturn(int errorCode);
    void warningReturn(int warningCode);
    void serverErrorReturn(int errorCode);
    
    // events, triggered by certain operations of all players in the same room
    void joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player);
    void leaveRoomEventAction(int playerNr, bool isInactive);
    void customEventAction(int playerNr, nByte eventCode, const Object& eventContent);
    
    // callbacks for operations on the server
    void connectReturn(int errorCode, const JString& errorString, const JString& region, const JString& cluster);
    void disconnectReturn();
    void createRoomReturn(int localPlayerNr, const Hashtable& roomProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString);
    void joinOrCreateRoomReturn(int localPlayerNr, const Hashtable& roomProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString);
    void joinRandomOrCreateRoomReturn(int localPlayerNr, const Hashtable& roomProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString);
    void joinRoomReturn(int localPlayerNr, const Hashtable& roomProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString);
    void joinRandomRoomReturn(int localPlayerNr, const Hashtable& roomProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString);
    void leaveRoomReturn(int errorCode, const JString& errorString);
    void joinLobbyReturn();
    void leaveLobbyReturn();
    void onFindFriendsResponse();
    void onLobbyStatsResponse(const JVector<LobbyStatsResponse>& lobbyStats);
    void webRpcReturn(int errorCode, const JString& errorString, const JString& uriPath, int resultCode, const Dictionary<Object, Object>& returnData);
    
    // info, that certain values have been updated
    void onRoomListUpdate();
    void onRoomPropertiesChange(const Hashtable& changes);
    void onPlayerPropertiesChange(int playerNr, const Hashtable& changes);
    void onAppStatsUpdate();
    void onLobbyStatsUpdate(const JVector<LobbyStatsResponse>& lobbyStats);
    void onCacheSliceChanged(int cacheSliceIndex);
    void onMasterClientChanged(int id, int oldID);
    
    // custom authentication
    void onCustomAuthenticationIntermediateStep(const Dictionary<JString, Object>& customResponseData);
    
    // receive the available server regions during the connect workflow (if you have specified in the constructor, that you want to select a region)
    void onAvailableRegions(const JVector<JString>& availableRegions, const JVector<JString>& availableRegionServers);
    void onSecretReceival(const JString& secret);
    void onDirectConnectionEstablished(int remoteID);
    void onDirectMessage(const Object& msg, int remoteID, bool relay);
    void onCustomOperationResponse(const ExitGames::Photon::OperationResponse& operationResponse);
    void onGetRoomListResponse(const JVector<ExitGames::Common::Helpers::SharedPointer<Room>>& roomList, const JVector<JString>& roomNameList);
};

#endif
