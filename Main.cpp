#include "Main.h"
#include "NetworkLogic.h"

//using namespace s3d;

bool serverConnected;
bool joinRoom;

enum STATE{
    S_WAIT,
    R_WAIT,
    INROOM,
};

void Main(){
    static const ExitGames::Common::JString appID = L"de748618-35dc-493a-af64-74f5cb60bb30";
    static const ExitGames::Common::JString appVersion = L"1.0";
    
    serverConnected = false;
    joinRoom = false;
    
    s3d::Window::Resize(400, 300);
    
    s3d::Font font(30);
    NetworkLogic networkLogic(appID, appVersion);
    STATE state = S_WAIT;
    int waitTime = 60 * 10;
    s3d::Point myPoint(0, 0), otherPoint(0, 0);
    
    networkLogic.connect();
    
    while(s3d::System::Update()){
        networkLogic.run();
        
        if(s3d::KeyZ.down())
            s3d::ScreenCapture::SaveCurrentFrame();
        if(s3d::KeyX.down())
            s3d::ClearPrint();
        
        
        switch (state) {
            case S_WAIT:
                if(--waitTime < 0){
                    std::cerr << "fail to connect server" << endl;
                    s3d::System::Exit();
                }
                
                if(serverConnected){
                    networkLogic.JoinOrCreateRoom("testRoom", 4);
                    state = R_WAIT;
                    waitTime = 60 * 10;
                }
                break;
                
            case R_WAIT:
                if(--waitTime < 0){
                    s3d::System::Exit();
                    std::cerr << "fail to join room" << endl;
                }
                
                if(joinRoom){
                    state = INROOM;
                    waitTime = 60 * 10;
                }
                
                break;
                
            case INROOM:
                //myPoint = s3d::Cursor::Pos();
                if(s3d::KeyLeft.pressed())
                    myPoint.x -= 8;
                if(s3d::KeyRight.pressed())
                    myPoint.x += 8;
                if(s3d::KeyUp.pressed())
                    myPoint.y -= 8;
                if(s3d::KeyDown.pressed())
                    myPoint.y += 8;
                
                /*int srcX = myPoint.x;
                int srcY = myPoint.y;
                int dstX = otherPoint.x, dstY = otherPoint.y;
                
                networkLogic.SendData(srcX);
                networkLogic.SendData(srcY);
                networkLogic.ReceiveData(dstX);
                networkLogic.ReceiveData(dstY);
                
                otherPoint.x = dstX;
                otherPoint.y = dstY;*/
                
                networkLogic.SendData(myPoint);
                networkLogic.ReceiveData(otherPoint);
                
                s3d::Circle(myPoint, 16).draw(s3d::Palette::Red);
                s3d::Circle(otherPoint, 16).draw(s3d::Palette::Blue);
                break;
        }
        
    }
    
    networkLogic.disconnect();
}

template<> struct ExitGames::Common::Helpers::ConfirmAllowed<s3d::Point> {
    typedef s3d::Point type;
    typedef s3d::Point scalarType;
    static const unsigned int dimensions = 0;
    static const nByte typeName = TypeCode::CUSTOM;
    static const nByte customTypeName = 0;
};
