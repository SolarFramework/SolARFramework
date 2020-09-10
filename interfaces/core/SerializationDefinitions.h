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

#ifndef SOLAR_SERIALIZATIONDEFINITIONS_H
#define SOLAR_SERIALIZATIONDEFINITIONS_H


#include <core/SolARFrameworkDefinitions.h>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include <boost/uuid/uuid_serialize.hpp>

// Important note: to change the serialization format used throughout the framework
// one of the following definitions must be uncommented dependeing on the desired format
// The definition MUST NOT BE PROVIDED with compile time definitions, otherwise the framework users will not have
// InputArchive and OutputArchive types matching the framework compiled ones
// When both definitions are uncommented, text serialization is used

// -> uncomment to use text serialization
//#define SOLAR_USE_TEXT_SERIALIZATION

// -> uncomment to use xml serialization
//#define SOLAR_USE_XML_SERIALIZATION

#ifdef SOLAR_USE_TEXT_SERIALIZATION
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using OutputArchive = ::boost::archive::text_oarchive;
using InputArchive = ::boost::archive::text_iarchive;
#elif SOLAR_USE_XML_SERIALIZATION
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
using OutputArchive = ::boost::archive::xml_oarchive;
using InputArchive = ::boost::archive::xml_iarchive;
#else
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
using OutputArchive = ::boost::archive::binary_oarchive;
using InputArchive = ::boost::archive::binary_iarchive;
#endif

#ifdef _MSC_VER
#define DECLARESERIALIZE(T) \
    template SOLARFRAMEWORK_API void T::serialize<OutputArchive>(OutputArchive &ar, const unsigned int version);\
    template SOLARFRAMEWORK_API void T::serialize<InputArchive>(InputArchive &ar, const unsigned int version);
#else
#define DECLARESERIALIZE(T) \
    template <> SOLARFRAMEWORK_API void T::serialize<OutputArchive>(OutputArchive &ar, const unsigned int version);\
    template <> SOLARFRAMEWORK_API void T::serialize<InputArchive>(InputArchive &ar, const unsigned int version);
#endif


#endif // SOLAR_SERIALIZATIONDEFINITIONS_H
