//
//  Vector.h
//  ReseachProject
//
//  Created by admin on 2018/02/15.
//  Copyright © 2018年 sekibotbot. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

typedef struct VECTOR3 {
public:
    
    float x, y, z;
    VECTOR3(){ };
    VECTOR3(float x, float y, float z) {
        (this->x) = x;
        (this->y) = y;
        (this->z) = z;
    };
    
    VECTOR3 operator + (const VECTOR3 dvec) const {
        VECTOR3 v3;
        
        v3.x = ((this)->x) + dvec.x;
        v3.y = ((this)->y) + dvec.y;
        v3.z = ((this)->z) + dvec.z;
        return v3;
    };
    
    VECTOR3 operator - (const VECTOR3 dvec) const {
        VECTOR3 v3;
        
        v3.x = ((this)->x) - dvec.x;
        v3.y = ((this)->y) - dvec.y;
        v3.z = ((this)->z) - dvec.z;
        return v3;
    };
    
    VECTOR3 operator * (float fDat) const {
        VECTOR3 v3;
        
        v3.x = ((this)->x) * fDat;
        v3.y = ((this)->y) * fDat;
        v3.z = ((this)->z) * fDat;
        
        return v3;
    };
    
    VECTOR3 operator / (float fDat) const {
        VECTOR3 v3;
        
        if(fDat == 0.0f){
            return *this;
        }
        
        v3.x = ((this)->x) / fDat;
        v3.y = ((this)->y) / fDat;
        v3.z = ((this)->z) / fDat;
        return v3;
    };
    
    VECTOR3& operator += (const VECTOR3 dvec) {
        ((this)->x) += dvec.x;
        ((this)->y) += dvec.y;
        ((this)->z) += dvec.z;
        return *this;
    };
    
    VECTOR3& operator -= (const VECTOR3 dvec) {
        ((this)->x) -= dvec.x;
        ((this)->y) -= dvec.y;
        ((this)->z) -= dvec.z;
        return *this;
    };
    
    VECTOR3& operator *= (float fDat) {
        ((this)->x) *= fDat;
        ((this)->y) *= fDat;
        ((this)->z) *= fDat;
        return *this;
    };
    
    VECTOR3& operator /= (float fDat) {
        
        if(fDat == 0.0f){
            return *this;
        }
        
        ((this)->x) /= fDat;
        ((this)->y) /= fDat;
        ((this)->z) /= fDat;
        return *this;
    };
    
} VECTOR3;




#endif /* Vector_h */
