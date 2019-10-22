#include <iostream>
#include <type_traits>
#include <cmath>
#include "vector_type_trait.h"
// A structure representing a type of 3D vector  
class threeDVec {
    public:
    float getX() {
        return vals_[0];
    }
    
    float getY() {
        return vals_[1];
    }
    
    float getZ() {
        return vals_[2];
    }
    
    threeDVec() = default;
    
    threeDVec(float x, float y, float z) : vals_{x,y,z} {};
    
    private:
    float vals_[3];
};

class VecThreeD {
    public:
    float x() {
        return vals_[0];
    }
    
    float y() {
        return vals_[1];
    }
    
    float z() {
        return vals_[2];
    }
    
    VecThreeD() = default;
    
    VecThreeD(float x, float y, float z) : vals_{x,y,z} {};
    
    private:
    float vals_[3];
};


static_assert(Has_Xaxis<threeDVec>::value, "threeDVec"); 
static_assert(Has_MFunc_getX<threeDVec, float(void)>::value, "threeDVec");
static_assert(Is_Vector3D<threeDVec>::value, "threeDVec");


class VectorOps {
    public:
    // Function specializations for getting "x" axis
    template<typename T>
    static typename std::enable_if<Has_MFunc_getX<T, float(void)>::value, float>::type getX(T v) {
        return v.getX();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MFunc_x<T, float(void)>::value, float>::type getX(T v) {
        return v.x();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MVar_x<T, float(void)>::value, float>::type getX(T v) {
        return v.x;
    }
    // Function specializations for getting "y" axis 
    template<typename T>
    static typename std::enable_if<Has_MFunc_getY<T, float(void)>::value, float>::type getY(T v) {
        return v.getY();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MFunc_y<T, float(void)>::value, float>::type getY(T v) {
        return v.y();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MVar_y<T, float(void)>::value, float>::type getY(T v) {
        return v.y;
    }
    // Function specializations for getting "z" axis 
    template<typename T>
    static typename std::enable_if<Has_MFunc_getZ<T, float(void)>::value, float>::type getZ(T v) {
        return v.getZ();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MFunc_z<T, float(void)>::value, float>::type getZ(T v) {
        return v.z();
    }
    
    template<typename T>
    static typename std::enable_if<Has_MVar_z<T, float(void)>::value, float>::type getZ(T v) {
        return v.z;
    }
    
    // Get magnitude of a vector for any type which conforms to "Is_Vector3D<T>"
    template<typename T>
    static typename std::enable_if<Is_Vector3D<T>::value, float>::type getMagnitude(T v) {
        return std::sqrt(VectorOps::getX(v)*VectorOps::getX(v) + VectorOps::getY(v)*VectorOps::getY(v) + VectorOps::getZ(v)*VectorOps::getZ(v));
    }
    
    // Get normalized vector for any type which conforms to "Is_Vector3D<T>"
    
    template<typename T>
    static typename std::enable_if<Is_Vector3D<T>::value, T>::type getNormalized(T v) {
        float magnitude = VectorOps::getMagnitude(v);
        return {VectorOps::getX(v)/magnitude, VectorOps::getY(v)/magnitude, VectorOps::getZ(v)/magnitude};
    }
};


int main()
{
    // A vector of type `threeDVec`
    threeDVec v{1,2,3};
    std::cout<<"v.x = "<<VectorOps::getX(v)<<"\n";
    std::cout<<"v.y = "<<VectorOps::getY(v)<<"\n";
    std::cout<<"v.z = "<<VectorOps::getZ(v)<<"\n";
    
    threeDVec v_normalized = VectorOps::getNormalized(v);
    
    std::cout<<"v_normalized.x = "<<VectorOps::getX(v_normalized)<<"\n";
    std::cout<<"v_normalized.y = "<<VectorOps::getY(v_normalized)<<"\n";
    std::cout<<"v_normalized.z = "<<VectorOps::getZ(v_normalized)<<"\n";
    
    // A vector of different type `VecThreeD`

    VecThreeD v1{1,2,3};
    std::cout<<"v1.x = "<<VectorOps::getX(v1)<<"\n";
    std::cout<<"v1.y = "<<VectorOps::getY(v1)<<"\n";
    std::cout<<"v1.z = "<<VectorOps::getZ(v1)<<"\n";
    
    VecThreeD v1_normalized = VectorOps::getNormalized(v1);
    
    std::cout<<"v1_normalized.x = "<<VectorOps::getX(v1_normalized)<<"\n";
    std::cout<<"v1_normalized.y = "<<VectorOps::getY(v1_normalized)<<"\n";
    std::cout<<"v1_normalized.z = "<<VectorOps::getZ(v1_normalized)<<"\n";
    return 0;
}
