#include "SPoint.h"

SPoint::SPoint(){
    x = 0;
    y = 0;
}

SPoint::SPoint(int _x, int _y){
    x = _x;
    y = _y;
}

SPoint::~SPoint(){}

SPoint& SPoint::operator = (const s3d::Point& other){
    this->x = other.x;
    this->y = other.y;
    return *this;
}

bool SPoint::operator == (const SPoint& other) const {
    return x == other.x && y == other.y;
}

bool SPoint::operator == (const s3d::Point& other) const {
    return x == other.x && y == other.y;
}

void SPoint::cleanup(){}

bool SPoint::compare(const CustomTypeBase &other) const {
    cout << "compare called" << endl;
    return typeid(*this) == typeid(other) && *this == (SPoint&)other;
}

void SPoint::duplicate (CustomTypeBase *pRetVal) const {
    *reinterpret_cast<SPoint*>(pRetVal) = *this;
}

void SPoint::deserialize (const nByte *pData, short length) {
    int *xp, *yp;
    
    cout << "deserialize called " << length << endl;
    if(length == sizeof(x) + sizeof(y)){
        xp = (int*)pData;
        pData += sizeof(x);
        yp = (int*)pData;
        
        x = *xp;
        y = *yp;
    }
}

short SPoint::serialize (nByte *pRetVal) const {
    short length = 0;
    nByte *tmp = (nByte*)&x;
    
    if(pRetVal){
        for(int i = 0; i < sizeof(x); i++)
            pRetVal[length++] = tmp[i];
        
        tmp = (nByte*)&y;
        for(int i = 0; i < sizeof(y); i++)
            pRetVal[length++] = tmp[i];
        
        //cout << "serialize called " << length << endl;
        return length;
    }
    else
        return sizeof(x) + sizeof(y);
}

JString& SPoint::toString (JString &retStr, bool withTypes) const {
    std::string str = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    if(withTypes)
        str += ":Type is SPoint";
    
    retStr = str.c_str();
    return retStr;
}

CustomTypeFactory<1>* SPoint::copyFactory() const {
    return new SPoint(*this);
}

void SPoint::destroyFactory() {
    delete this;
}

CustomType<1>* SPoint::create(short amount) const {
    return new SPoint[amount];
}

CustomType<1>* SPoint::copy(const CustomType<1>* pToCopy, short amount) const {
    SPoint* tmp = static_cast<SPoint*>(create(amount));
    for(short i = 0; i < amount; i++)
        tmp[i] = static_cast<const SPoint*>(pToCopy)[i];
    return tmp;
}

void SPoint::destroy(const CustomType<1>* pToDestroy) const {
    delete [] (SPoint*)pToDestroy;
}

unsigned int SPoint::sizeOf(void) const {
    return sizeof(SPoint);
}
