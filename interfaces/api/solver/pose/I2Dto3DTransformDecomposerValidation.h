#ifndef I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H
#define I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H


// Definition of I2Dto3DTransformDecomposerValidation Class //
// part of SolAR namespace //

#include "xpcf/api/IComponentIntrospect.h"

namespace SolAR {
namespace api {
namespace solver {
namespace pose {
/**
  * @class I2Dto3DTransformDecomposerValidation
  * @brief <B>Validates if a transform decomposition is correct.</B>
  * <TT>UUID: ee990fc4-ec74-4365-8fa8-b2c94845fde6</TT>
  */
class  I2Dto3DTransformDecomposerValidation : virtual public org::bcom::xpcf::IComponentIntrospect {
public:
   I2Dto3DTransformDecomposerValidation() = default;

   ///
   /// \brief ~I2Dto3DTransformDecomposerValidation
   ///
   virtual ~I2Dto3DTransformDecomposerValidation() = default;

   virtual void testMethod()=0;

};

}
}
}
}  // end of namespace SolAR

XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::solver::pose::I2Dto3DTransformDecomposerValidation,
                             "ee990fc4-ec74-4365-8fa8-b2c94845fde6",
                             "I2Dto3DTransformDecomposerValidation",
                             "SolAR::api::solver::pose::I2Dto3DTransformDecomposerValidation");

#endif // I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H
