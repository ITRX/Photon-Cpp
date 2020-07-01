#ifndef _S_POINT_H_
#define _S_POINT_H_

#include "Main.h"

class SPoint : public CustomType<1>, public CustomTypeFactory<1>, public s3d::Point {
public:
    SPoint();
    SPoint(int _x, int _y);
    ~SPoint();
    
    SPoint& operator = (const s3d::Point& other);
    bool operator == (const SPoint& other) const;
    bool operator == (const s3d::Point& other) const;
    
    void cleanup();
    bool compare(const CustomTypeBase &other) const;
    void duplicate (CustomTypeBase *pRetVal) const;
    void deserialize (const nByte *pData, short length);
    short serialize (nByte *pRetVal) const;
    JString& toString (JString &retStr, bool withTypes = false) const;
    
    CustomTypeFactory<1>* copyFactory() const;
    void destroyFactory();
    CustomType<1>* create(short amount) const;
    CustomType<1>* copy(const CustomType<1>* pToCopy, short amount) const;
    void destroy(const CustomType<1>* pToDestroy) const;
    unsigned int sizeOf() const;
};

#endif
