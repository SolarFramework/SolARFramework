#ifndef I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H
#define I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H

#ifndef _BCOM_SHARED
#define _BCOM_SHARED
#endif // _BCOM_SHARED

// Definition of I2Dto3DTransformDecomposerValidation Class //
// part of SolAR namespace //

#include "IComponentIntrospect.h"

namespace SolAR {

///
/// \brief The I2Dto3DTransformDecomposerValidation class
///
class  I2Dto3DTransformDecomposerValidation : public virtual org::bcom::xpcf::IComponentIntrospect {
public:
   I2Dto3DTransformDecomposerValidation() = default;

   ///
   /// \brief ~I2Dto3DTransformDecomposerValidation
   ///
   virtual ~I2Dto3DTransformDecomposerValidation() {};

   virtual void testMethod()=0;

   XPCF_DECLARE_UUID("ee990fc4-ec74-4365-8fa8-b2c94845fde6");
};

_BCOM_SHARED sptrnms::shared_ptr<I2Dto3DTransformDecomposerValidation> getI2Dto3DTransformDecomposerValidationInstance();


}  // end of namespace SolAR

#endif // I2DTO3DTRANSFORMDECOMPOSERVALIDATION_H
