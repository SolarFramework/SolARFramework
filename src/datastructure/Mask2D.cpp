/**
 * @copyright Copyright (c) 2017-2025 B-com http://www.b-com.com/
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

#include "datastructure/Mask2D.h"

BOOST_CLASS_EXPORT_IMPLEMENT(SolAR::datastructure::Mask2D);

namespace SolAR {
namespace datastructure {

Mask2D::Mask2D(uint32_t id, Mask2D::Segmentation2DType type, SRef<Image> mask, const std::map<uint8_t, Mask2D::SegInfo>& info, const std::map<int16_t, std::string>& label)
{
    m_id = id;
    m_segmentationType = type;
    m_mask = mask;
    m_maskInfo = info;
    m_classIdToLabel = label;
}

void Mask2D::setId(uint32_t id)
{
    m_id = id;
}

void Mask2D::setMask(SRef<Image> mask)
{
    m_mask = mask;
}

void Mask2D::setMaskInfo(const std::map<uint8_t, SegInfo>& maskInfo)
{
    m_maskInfo = maskInfo;
}

void Mask2D::setClassLabels(const std::map<int16_t, std::string>& classIdToLabel)
{
    m_classIdToLabel = classIdToLabel;
}

uint32_t Mask2D::getId() const
{
    return m_id;
}

SRef<Image> Mask2D::getMask() const
{
    return m_mask;
}

SRef<const Image> Mask2D::getConstMask() const
{
    return m_mask;
}

const std::map<uint8_t, Mask2D::SegInfo>& Mask2D::getMaskInfo() const
{
    return m_maskInfo;
}

const std::map<int16_t, std::string>& Mask2D::getClassLabels() const
{
    return m_classIdToLabel;
}

void Mask2D::setSegmentationType(Segmentation2DType type)
{
    m_segmentationType = type;
}

Mask2D::Segmentation2DType Mask2D::getSegmentationType() const
{
    return m_segmentationType;
}

template<typename Archive>
void Mask2D::serialize(Archive &ar, const unsigned int /* version */) {
    ar& m_id;
    ar& m_mask;
    ar& m_maskInfo;
    ar& m_classIdToLabel;
    ar& m_segmentationType;
}

IMPLEMENTSERIALIZE(Mask2D);

}
}
