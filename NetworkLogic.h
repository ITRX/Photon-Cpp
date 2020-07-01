#ifndef _NETWORK_LOGIC_H_
#define _NETWORK_LOGIC_H_

#include "Main.h"
#include "Listener.h"

using ExitGames::Common::JString;

class NetworkLogic {
private:
    ExitGames::LoadBalancing::Client *mLoadBalancingClient;
    Listener mListener; // your implementation of the ExitGames::LoadBalancing::Listener interface
    ExitGames::Common::Logger mLogger; // accessed by EGLOG()
    
    bool received;
    
public:
    NetworkLogic(const JString& appID, const JString& appVersion);
    ~NetworkLogic();
    
    void connect();
    void disconnect();
    void run();
    void JoinOrCreateRoom(const JString& roomName, nByte maxPlayers);
    
    bool isReceive();
    
    template<class T>
    void SendData(const T &data){
        static bool first = true;
        if(first){
            first = false;
            s3d::Print << s3d::Time::GetSecSinceEpoch();
        }
        
        mLoadBalancingClient->opRaiseEvent(false, data, 1);
    }
    
    template<class T>
    void ReceiveData(T &data){
        list<Object> &receiveData = mListener.getReceiveData();
        static bool first = true;
        
        if(!receiveData.empty()){
            if(first){
                first = false;
                s3d::ClearPrint();
                s3d::Print << s3d::Time::GetMillisecSinceEpoch();
            }
            
            received = true;
            data = ExitGames::Common::ValueObject<T>(receiveData.front()).getDataCopy();
            receiveData.pop_front();
        }
    }
};

#endif
