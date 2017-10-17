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

#ifndef ISOLARIMAGEFILTER_H
#define ISOLARIMAGEFILTER_H


#include "ISolARFilter.h"
#include "SolARImage.h"
#include "SolARMessages.h"

namespace SolAR {

class ISolARImageFilter : public virtual SolAR::ISolARFilter {
public:
    ISolARImageFilter() = default;
    virtual ~ISolARImageFilter() = default;
    virtual void threshold(SRef<SolARImage>input,
                           SRef<SolARImage>output,
                           int threshold) = 0;

    virtual void binarize(SRef<SolARImage>input,
                          SRef<SolARImage>output,
                          int min,
                          int max) = 0;

    virtual void blur(SRef<SolARImage>input,
                    SRef<SolARImage>output,
                    int kernerl_id,
                    int kernel_width,
                    int kernel_height,
                    int direction) = 0;

   virtual  void gradient(SRef<SolARImage>input,
                          SRef<SolARImage>output,
                          int x_order,
                          int y_order) = 0;

  virtual  void laplacian(SRef<SolARImage>input,
                          SRef<SolARImage>output,
                          int method) = 0;

  virtual  void erode(SRef<SolARImage>input,
                      SRef<SolARImage>output,
                      int erode_type,
                      int erode_size) = 0;


  virtual   void dilate(SRef<SolARImage>input,
                        SRef<SolARImage>output,
                        int dilate_type,
                        int dilate_size) = 0;

  virtual   void equalize(SRef<SolARImage>input,
                          SRef<SolARImage>output,
                          int method) = 0;

      XPCF_DECLARE_UUID("f7948ae2-e994-416f-be40-dd404ca03a83");
};
}

#endif // ISOLARIMAGEFILTER_H
