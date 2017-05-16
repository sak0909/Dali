#ifndef __DALI_TOOLKIT_MIRROR_EFFECT_H__
#define __DALI_TOOLKIT_MIRROR_EFFECT_H__

//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// INTERNAL INCLUDES
#include <dali/dali.h>

namespace Dali DALI_IMPORT_API
{

namespace Toolkit
{

/**
 * MirrorEffect is a custom shader effect to achieve square effects in Image actors
 */
class MirrorEffect : public ShaderEffect
{
public:

  /**
   * Create an uninitialized MirrorEffect; this can be initialized with MirrorEffect::New()
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  MirrorEffect();

  /**
   * Virtual destructor.
   */
  virtual ~MirrorEffect();

  /**
   * Create an initialized MirrorEffect.
   * @return A handle to a newly allocated Dali resource.
   */
  static MirrorEffect New();

  /**
   * Set the depth of the mirror effect.
   * @param [in] depth The new mirror depth value.
   */
  void SetDepth(float depth);

  /**
   * Set the alpha of the mirror effect.
   * @param [in] alpha The new mirror alpha value.
   */
  void SetAlpha(float alpha);

  /**
   * Get the name for the depth property
   * which can be used in Animation API's
   * @return A std::string containing the property name
   */
  const std::string& GetDepthPropertyName() const;

  /**
   * Get the name for the alpha property
   * which can be used in Animation API's
   * @return A std::string containing the property name
   */
  const std::string& GetAlphaPropertyName() const;

private: // Not intended for application developers
  MirrorEffect(ShaderEffect handle);
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_MIRROR_EFFECT_H__

