#include "Main.h"
#include "Listener.h"

#ifndef _NETWORK_LOGIC_H_
#define _NETWORK_LOGIC_H_

using ExitGames::Common::JString;

class NetworkLogic {
private:
    ExitGames::LoadBalancing::Client *mLoadBalancingClient;
    Listener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
    ExitGames::Common::Logger mLogger; // accessed by EGLOG()
    
    int runCount, recieveCount;
    
public:
    NetworkLogic(const JString& appID, const JString& appVersion);
    ~NetworkLogic();
    
    void connect();
    void disconnect();
    void run();
    void JoinOrCreateRoom(const JString& roomName, nByte maxPlayers);
    
    template<class T>
    void SendData(T &data){
        runCount++;
        mLoadBalancingClient->opRaiseEvent(true, data, 1);
    }
    
    template<class T>
    void ReceiveData(T &data){
        list<Object> &receiveData = mListener.getReceiveData();
        
        if(!receiveData.empty()){
            recieveCount++;
            data = ExitGames::Common::ValueObject<T>(receiveData.front()).getDataCopy();
            receiveData.pop_front();
        }
    }
};

#endif
