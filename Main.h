#define NO_S3D_USING
#include <Siv3D.hpp>

#include <Common-cpp/inc/Common.h>
#include <Photon-cpp/inc/PhotonPeer.h>
#include <LoadBalancing-cpp/inc/Client.h>
#include <LoadBalancing-cpp/inc/LobbyStatsResponse.h>
#include <LoadBalancing-cpp/inc/Player.h>
#include <LoadBalancing-cpp/inc/Room.h>

#include <iostream>
#include <list>

#ifndef _MAIN_H_
#define _MAIN_H_

using std::cout;
using std::endl;
using std::cin;
using std::list;

using ExitGames::Common::JString;
using ExitGames::Common::JVector;
using ExitGames::Common::Hashtable;
using ExitGames::Common::Object;
using ExitGames::Common::Dictionary;
using ExitGames::LoadBalancing::Player;
using ExitGames::LoadBalancing::LobbyStatsResponse;
using ExitGames::LoadBalancing::Room;
using ExitGames::LoadBalancing::RoomOptions;

extern bool serverConnected;
extern bool joinRoom;

#endif
