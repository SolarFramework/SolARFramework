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
     * @struct SegInfo
     * @brief this struct SegInfo is used to interpret pixel value in the segmentation mask
     * * classId, the Id of the class, if classId < 0, it means that the current pixel is unsegmented (e.g. background)
     * * instanceId, the instance Id of the detected object, if instanceId < 0, it means that the current pixel belongs to a "stuff" class which is uncountable, otherwise it belongs to a "thing" class
     * * confidence, confidence score between 0 and 1, the confidence score of the segmentation, if confidence < 0, it means that the confidence score is not available
     */
    struct SegInfo {
        SegInfo() = default;
        SegInfo(int16_t c, int16_t i, float cf) : classId(c), instanceId(i), confidence(cf) {}
        bool operator==(const SegInfo& other) const {
            return classId == other.classId && instanceId == other.instanceId && confidence == other.confidence;
        }
        bool operator!=(const SegInfo& other) const {
            return !(*this == other);
        }

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
    using MaskInfoType = std::map<uint8_t, SegInfo>;

    /// @brief default constructor
    Mask2D() = default;

    /// @brief constructor with args
    /// @param[in] mask mask
    /// @param[in] info mask info
    Mask2D(SRef<Image> mask, const MaskInfoType& info);

    /// @brief default destructor
    ~Mask2D() = default;

    /// @brief set mask
    /// @param[in] mask pointer to mask buffer
    void setMask(SRef<Image> mask);

    /// @brief set mask info
    /// @param[in] maskInfo mask info used to interpret the mask
    void setMaskInfo(const MaskInfoType& maskInfo);

    /// @brief get mask
    /// @return pointer to mask
    SRef<Image> getMask() const;

    /// @brief get const mask
    /// @return pointer to const mask
    SRef<const Image> getConstMask() const;

    /// @brief get mask info
    /// @return mask info
    const MaskInfoType& getMaskInfo() const;

    /// @brief print info
    void print() const;

    /// @brief save to PNG and json
    /// @param[in] filePng filename PNG used to save mask image
    /// @param[in] fileJson filename json used to save other information of the mask
    /// @return boolean true (success) or false (failure)
    bool save(const std::string& filePng, const std::string& fileJson) const;

    /// @brief overload operator == 
    /// @param[in] other other mask
    /// @return true (the content of current mask object is the same as that of other) or false (otherwise)
    bool operator==(const Mask2D& other) const;

    /// @brief overload operator != 
    /// @param[in] other other mask
    /// @return false (the content of current mask object is the same as that of other) or true (otherwise)
    bool operator!=(const Mask2D& other) const;

private:
    /// @brief to string
    /// @return string describing the current Mask2D object
    std::string toString() const;

    /// @brief serialize
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    SRef<Image> m_mask;
    MaskInfoType m_maskInfo;
};

DECLARESERIALIZE(Mask2D);

} // datastructure
} // SolAR

BOOST_CLASS_EXPORT_KEY(SolAR::datastructure::Mask2D);

#endif
