#include "Main.h"
#include "NetworkLogic.h"


bool serverConnected;
bool joinRoom;

enum STATE{
    S_WAIT,
    R_WAIT,
    INROOM,
    GAME
};

void Main(){
    static const ExitGames::Common::JString appID = L"de748618-35dc-493a-af64-74f5cb60bb30";
    static const ExitGames::Common::JString appVersion = L"1.0";
    
    serverConnected = false;
    joinRoom = false;
    
    s3d::Window::Resize(400, 300);
    
    NetworkLogic networkLogic(appID, appVersion);
    STATE state = S_WAIT;
    int waitTime = 60 * 10;
    
    SPoint::constructClass(SPoint());
    SPoint myPoint(0, 0), otherPoint(200, 150);
    
    int signal = 0;
    s3d::Font font(20);
    
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
                if(s3d::SimpleGUI::ButtonAt(U"押すな", s3d::Vec2(200, 150))){
                    signal = 1;
                    s3d::ClearPrint();
                    networkLogic.SendData(signal);
                    state = GAME;
                }
                else{
                    networkLogic.ReceiveData(signal);
                    if(signal == 1){
                        state = GAME;
                    }
                }
                
                break;
                
            case GAME:
                if(s3d::KeyLeft.pressed()){
                    myPoint.x -= 8;
                    networkLogic.SendData(myPoint);
                }
                
                if(s3d::KeyRight.pressed()){
                    myPoint.x += 8;
                    networkLogic.SendData(myPoint);
                }
                
                if(s3d::KeyUp.pressed()){
                    myPoint.y -= 8;
                    networkLogic.SendData(myPoint);
                }
                
                if(s3d::KeyDown.pressed()){
                    myPoint.y += 8;
                    networkLogic.SendData(myPoint);
                }
                
                
                networkLogic.ReceiveData(otherPoint);
                
                s3d::Circle(myPoint, 16).draw(s3d::Palette::Red);
                s3d::Circle(otherPoint, 16).draw(s3d::Palette::Blue);
                
                break;
        }
    }
    
    networkLogic.disconnect();
    SPoint::deconstructClass();
}
