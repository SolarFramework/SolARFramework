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

/** @file */

#ifndef SOLAR_GEOMETRYDEFINITIONS_H
#define SOLAR_GEOMETRYDEFINITIONS_H

#include <xpcf/xpcf.h>
#include <xpcf/core/helpers.h>
#include <datastructure/MathDefinitions.h>
#include <core/SolARFrameworkDefinitions.h>
#include <core/SerializationDefinitions.h>

// #include <fmt/ostream.h>
#include <spdlog/fmt/ostr.h>


namespace SolAR {
namespace datastructure {

/**
 * @class Point2Df
 * @brief <B>A 2D point with coordinates defined with floats.</B>
 *
 */
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

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */){
		ar & boost::serialization::make_array(this->data(), 2);
	}
};

/**
 * @class Point3Df
 * @brief <B>A 3D point with coordinates defined with floats.</B>
 *
 */
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

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */){
		ar & boost::serialization::make_array(this->data(), 3);
	}
};

DECLARESERIALIZE(Point3Df);
IMPLEMENTSERIALIZE(Point3Df);

 
/**
 * @class Point2Di
 * @brief <B>A 2D point with coordinates defined with integers.</B>
 *
 */
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

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & boost::serialization::make_array(this->data(), 2);
	}
};

/**
 * @class Point3Di
 * @brief <B>A 3D point with coordinates defined with integers.</B>
 *
 */
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

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */){
		ar & boost::serialization::make_array(this->data(), 3);
	}
};

/**
 * @class Edge2Df
 * @brief <B>A 2D edge with coordinates defined with floats.</B>
 *
 */
class Edge2Df {
public:
    Edge2Df() = default;
    Edge2Df(Point2Df point1, Point2Df point2) : p1(point1), p2(point2){}
    ~Edge2Df() = default;

    Point2Df p1;
    Point2Df p2;

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */){
		ar & p1;
		ar & p2;
	}
};

/**
 * @class Edge2Di
 * @brief <B>A 2D edge with coordinates defined with integers.</B>
 *
 */
class Edge2Di {
public:
    Edge2Di() = default;
    Edge2Di(Point2Di point1, Point2Di point2) : p1(point1), p2(point2){}
    ~Edge2Di() = default;

    Point2Di p1;
    Point2Di p2;

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version){
		ar & p1;
		ar & p2;
	}
};

/**
 * @class BBox3Df
 * @brief <B>A bounding box 3D with coordinates defined with integers.</B>
 *
 */
class BBox3Df {
public:
	BBox3Df() = default;
	BBox3Df(Point3Df corner, float width, float height, float depth) : corner(corner), width(width), height(height), depth(depth) {}
	~BBox3Df() = default;

	Point3Df corner;	// the corner point in the top under left
	float width;		// x-axis
	float height;		// y-axis
	float depth;		// z-axis

private:
	friend class boost::serialization::access;
	template<typename Archive>
    void serialize(Archive &ar, const unsigned int /* version */){
		ar & corner;
		ar & width;
		ar & height;
		ar & depth;
	}
};

/**
 * @typedef Contour2Df
 * @brief <B>A contours defined with 2D points with coordinates defined with floats.</B>
 *
 */
typedef std::vector<Point2Df> Contour2Df;

/**
 * @typedef Contour2Di
 * @brief <B>A contours defined with 2D points with coordinates defined with integers.</B>
 *
 */
typedef std::vector<Point2Di> Contour2Di;

/**
 * @typedef QuadContour2Df
 * @brief <B>A contours defined with 4 2D points with coordinates defined with floats.</B>
 *
 */
typedef Point2Df QuadContour2Df[4];

/**
 * @typedef QuadContour2Di
 * @brief <B>A contours defined with 4 2D points with coordinates defined with integers.</B>
 *
 */
typedef Point2Di QuadContour2Di[4];

/**
 * @struct Sizei
 * @brief <B>A 2D size defined with integers.</B>
 */
struct Sizei {
    uint32_t width;
    uint32_t height;
};

/**
 * @struct Sizef
 * @brief <B>A 2D size defined with floats.</B>
 */
struct Sizef {
    float width;
    float height;
};

/**
 * @struct Rectanglei
 * @brief <B>A 2D rectangle which size in defined with integers.</B>
 */
struct Rectanglei {
    uint32_t startX;
    uint32_t startY;
    Sizei size;
};

typedef Maths::Matrix<float, 3, 4, Eigen::RowMajor> ProjectionMatrix ;
typedef Maths::Matrix<float, 3, 3, Eigen::RowMajor> RotationMatrixf;

}
}

namespace boost { namespace serialization {

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::Sizef & size,
                      const unsigned int /* version */)
{
    ar & size.width;
    ar & size.height;
}

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::Sizei & size,
                      const unsigned int /* version */)
{
    ar & size.width;
    ar & size.height;
}

template<class Archive>
inline void serialize(Archive & ar,
                      SolAR::datastructure::Rectanglei & rect,
                      const unsigned int /* version */)
{
    ar & rect.startX;
    ar & rect.startY;
    ar & rect.size;
}

}} // namespace boost::serialization

template <> struct fmt::formatter<SolAR::datastructure::Point3Df> : ostream_formatter {};

#endif // SOLAR_GEOMETRYDEFINITIONS_H
