/**
 * @copyright Copyright (c) 2020 B-com http://www.b-com.com/
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

#include "datastructure/StorageWorldAnchor.h"
#include "core/Log.h"

#include "xpcf/core/helpers.h"

namespace SolAR {
namespace datastructure {

    StorageWorldAnchor::StorageWorldAnchor(org::bcom::xpcf::uuids::uuid author, Transform3Df localCrs,
                                           UnitSystem unitSystem, Vector3d scale,
                                           std::multimap<std::string, std::string> tags) : StorageWorldElement(tags)
    {
        m_author = author;
        m_LocalCrs = localCrs;
        m_unitSystem = unitSystem;
        m_scale = scale;
        m_tags = tags;
    }

    const org::bcom::xpcf::uuids::uuid &StorageWorldAnchor::getAuthor() const
    {
        return m_author;
    }

    void StorageWorldAnchor::setAuthor(const org::bcom::xpcf::uuids::uuid &newAuthor){
        m_author = newAuthor;
    }

    const Transform3Df &StorageWorldAnchor::getLocalCrs() const{
        return m_LocalCrs;
    }

    void StorageWorldAnchor::setLocalCrs(const Transform3Df &newLocalCrs){
        m_LocalCrs = newLocalCrs;
    }

    UnitSystem StorageWorldAnchor::getUnitSystem() const{
        return m_unitSystem;
    }

    void StorageWorldAnchor::setUnitSystem(UnitSystem newUnitSystem){
        m_unitSystem = newUnitSystem;
    }

    const Vector3d &StorageWorldAnchor::getScale() const{
        return m_scale;
    }

    void StorageWorldAnchor::setScale(const Vector3d &newScale){
        m_scale = newScale;
    }

    template<typename Archive>
    void StorageWorldAnchor::serialize(Archive &ar, ATTRIBUTE(maybe_unused) const unsigned int version) {


        ar & boost::serialization::base_object<StorageWorldElement>(*this);
        ar & m_author;
        ar & m_LocalCrs;
        ar & m_unitSystem;
        ar & m_scale;
    }

    bool StorageWorldAnchor::isWorldAnchor() {
        return true;
    }

    bool StorageWorldAnchor::isTrackable() {
        return false;
    }

    IMPLEMENTSERIALIZE(StorageWorldAnchor);

}
}

