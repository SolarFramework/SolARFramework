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

#ifndef MASK2D_H
#define MASK2D_H

#include "core/SerializationDefinitions.h"
#include "core/SolARFrameworkDefinitions.h"
#include "datastructure/Image.h"
#include <map>
#include <string>

namespace SolAR {
namespace datastructure {

/**
 * @class Mask2D
 * @brief <B>A 2D mask.</B>
 *
 * This class provides the definition of a 2D mask.
 */
class SOLARFRAMEWORK_API Mask2D {
public:
    /**
     * @enum class Segmentation2DType
     */
    enum class Segmentation2DType {
        INSTANCE,
        PANOPTIC,
        SEMANTIC,
        UNDEFINED
    };

    /**
     * @struct SegInfo
     * @brief this struct SegInfo is used to interpret pixel value in the segmentation mask
     * classId, the Id of the class, if classId < 0, it means that the current pixel is unsegmented (e.g. background)
     * instanceId, the instance Id of the detected object, if instanceId < 0, it means that the current pixel belongs to a "stuff" class which is uncountable, otherwise it belongs to a "thing" class
     * confidence, confidence score between 0 and 1, the confidence score of the segmentation, if confidence < 0, it means that the confidence score is not available
     */
    struct SegInfo {
        SegInfo() = default;
        SegInfo(int16_t c, int16_t i, float cf) : classId(c), instanceId(i), confidence(cf) {}
        int16_t classId = -1;
        int16_t instanceId = -1;
        float confidence = -1.f;

        friend class boost::serialization::access;
        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar& classId;
            ar& instanceId;
            ar& confidence;
        }
    };

    /// @brief default constructor
    Mask2D() = default;

    /// @brief constructor with args
    /// @param[in] id ID of the Mask2D
    /// @param[in] type segmentation type
    /// @param[in] mask mask
    /// @param[in] info mask info
    /// @param[in] label mapping from class ID to label
    Mask2D(uint32_t id, Segmentation2DType type, SRef<Image> mask, const std::map<uint8_t, SegInfo>& info, const std::map<int16_t, std::string>& label);

    /// @brief default destructor
    ~Mask2D() = default;

    /// @brief set Id
    /// @param[in] id Mask2D ID
    void setId(uint32_t id);

    /// @brief set mask
    /// @param[in] mask pointer to mask buffer
    void setMask(SRef<Image> mask);

    /// @brief set mask info
    /// @param[in] maskInfo mask info used to interpret the mask
    void setMaskInfo(const std::map<uint8_t, SegInfo>& maskInfo);

    /// @brief set mapping from class ID to label (string)
    /// @param[in] classIdToLabel mapping from class ID to label
    void setClassLabels(const std::map<int16_t, std::string>& classIdToLabel);

    /// @brief set segmentation type
    /// @param[in] type segmentation type
    void setSegmentationType(Segmentation2DType type);

    /// @brief get Id
    /// @return ID of the Mask2D object
    uint32_t getId() const;

    /// @brief get mask
    /// @return pointer to mask
    SRef<Image> getMask() const;

    /// @brief get const mask
    /// @return pointer to const mask
    SRef<const Image> getConstMask() const;

    /// @brief get mask info
    /// @return mask info
    const std::map<uint8_t, SegInfo>& getMaskInfo() const;

    /// @brief get labels of classes
    /// @return labels of classes
    const std::map<int16_t, std::string>& getClassLabels() const;

    /// @brief get segmentation type
    /// @return segmentation type
    Segmentation2DType getSegmentationType() const;

private:
    /// @brief serialize
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    uint32_t m_id = 0;
    SRef<Image> m_mask;
    std::map<uint8_t, SegInfo> m_maskInfo;
    std::map<int16_t, std::string> m_classIdToLabel;
    Segmentation2DType m_segmentationType = Segmentation2DType::UNDEFINED;
};

DECLARESERIALIZE(Mask2D);

} // datastructure
} // SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Mask2D);

#endif