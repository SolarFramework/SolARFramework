/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SOLAR_GEOMETRYDEFINITIONS_H
#define SOLAR_GEOMETRYDEFINITIONS_H

#include "xpcf/xpcf.h"
#include "datastructure/MathDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"

namespace SolAR {
namespace datastructure {

// class Point2Df;
class  Point2Df : public Vector<float,2> {
public:
    Point2Df(float x=0,float y=0):Vector<float,2>(x,y){};
    inline ~Point2Df() {};
    inline float getX() const { return (this->data())[0];}
    inline float getY() const { return (this->data())[1];}
    inline void setX(float x) { this->data()[0]=x;}
    inline void setY(float y) { this->data()[1]=y;}

    inline Point2Df operator+(const Point2Df& a) const { return Point2Df(getX()+a.getX(), getY()+a.getY());}
    inline Point2Df operator-(const Point2Df& a) const { return Point2Df(getX()-a.getX(), getY()-a.getY());}
};

// class Point3Df;
class  Point3Df : public Vector<float,3> {
public:
    Point3Df(float x=0,float y=0, float z= 0):Vector<float,3>(x,y, z){};
    inline ~Point3Df() {};
    inline float getX() const { return (this->data())[0];}
    inline float getY() const { return (this->data())[1];}
    inline float getZ() const { return (this->data())[2];}

    inline float magnitude() const { return std::sqrt(this->getX()*this->getX()+ this->getY()*this->getY() +this->getZ()*this->getZ()) ;}

    inline void setX(float x) { this->data()[0]=x;}
    inline void setY(float y) { this->data()[1]=y;}
    inline void setZ(float z) { this->data()[2]=z;}

    inline Point3Df operator+(const Point3Df& a) const { return Point3Df(getX()+a.getX(), getY()+a.getY(), getZ()+a.getZ());}
    inline Point3Df operator-(const Point3Df& a) const { return Point3Df(getX()-a.getX(), getY()-a.getY(), getZ()-a.getZ());}
    inline Point3Df operator*(const float & f) const {{ return Point3Df(getX()*f, getY()*f, getZ()*f);} }
};

// class Point2Di;
class  Point2Di : public Vector<int,2> {
public:
    Point2Di(int x=0,int y=0):Vector<int,2>(x,y){};
    inline ~Point2Di() {};
    inline int getX() const { return (this->data())[0];}
    inline int getY() const { return (this->data())[1];}
    inline void setX(int x) { this->data()[0]=x;}
    inline void setY(int y) { this->data()[1]=y;}

    inline Point2Di operator+(const Point2Di& a) const { return Point2Di(getX()+a.getX(), getY()+a.getY());}
    inline Point2Di operator-(const Point2Di& a) const { return Point2Di(getX()-a.getX(), getY()-a.getY());}
};

// class Point3Di;
class  Point3Di : public Vector<int,3> {
public:
    Point3Di(int x=0,int y=0, int z= 0):Vector<int,3>(x,y, z){};
    inline ~Point3Di() {};
    inline int getX() const { return (this->data())[0];}
    inline int getY() const { return (this->data())[1];}
    inline int getZ() const { return (this->data())[2];}

    inline void setX(int x) { this->data()[0]=x;}
    inline void setY(int y) { this->data()[1]=y;}
    inline void setZ(int z) { this->data()[2]=z;}

    inline Point3Di operator+(const Point3Di& a) const { return Point3Di(getX()+a.getX(), getY()+a.getY(), getZ()+a.getZ());}
    inline Point3Di operator-(const Point3Di& a) const { return Point3Di(getX()-a.getX(), getY()-a.getY(), getZ()-a.getZ());}
};

class Edge2Df {
public:
    Edge2Df() = default;
    Edge2Df(Point2Df point1, Point2Df point2) : p1(point1), p2(point2){}
    ~Edge2Df() = default;

    Point2Df p1;
    Point2Df p2;
};

class Edge2Di {
public:
    Edge2Di() = default;
    Edge2Di(Point2Di point1, Point2Di point2) : p1(point1), p2(point2){}
    ~Edge2Di() = default;

    Point2Di p1;
    Point2Di p2;
};

typedef std::vector<SRef<Point2Df>> Contour2Df;
typedef std::vector<SRef<Point2Di>> Contour2Di;
typedef Point2Df QuadContour2Df[4];
typedef Point2Di QuadContour2Di[4];

struct Sizei {
    uint32_t width;
    uint32_t height;
};

struct Sizef {
    float width;
    float height;
};

struct Rectanglei {
    uint32_t startX;
    uint32_t startY;
    Sizei size;
};

}
}

#endif // SOLAR_GEOMETRYDEFINITIONS_H
