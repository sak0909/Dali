#ifndef __DALI_TOOLKIT_INTERNAL_SCROLL_VIEW_CAROUSEL_EFFECT_H__
#define __DALI_TOOLKIT_INTERNAL_SCROLL_VIEW_CAROUSEL_EFFECT_H__

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
#include <dali/public-api/animation/animation.h>
#include <dali/public-api/animation/alpha-functions.h>
#include <dali/public-api/animation/time-period.h>
#include <dali/public-api/object/ref-object.h>
#include <dali-toolkit/public-api/controls/scrollable/scroll-view/scroll-view.h>
#include <dali-toolkit/public-api/controls/scrollable/scroll-view/scroll-view-effect.h>
#include <dali-toolkit/public-api/controls/scrollable/scroll-view/scroll-view-carousel-effect.h>

namespace Dali
{

class Animation;

namespace Toolkit
{

class ScrollView;

namespace Internal
{

class ScrollViewEffect;

/**
 * @copydoc Toolkit::ScrollViewCarouselEffect
 */
class ScrollViewCarouselEffect : public ScrollViewEffect
{

public:

  /**
   * Constructor
   */
  ScrollViewCarouselEffect();

public:

  /**
   * @copydoc ScrollViewEffect::ApplyToActor
   */
  void ApplyToActor(Actor child, const Vector2& angleSwing);

public:

  /**
   * @copydoc ScrollViewEffect::OnAttach
   */
  virtual void OnAttach(Toolkit::ScrollView& scrollView);

  /**
   * @copydoc ScrollViewEffect::OnDetach
   */
  virtual void OnDetach(Toolkit::ScrollView& scrollView);

protected:

  /**
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~ScrollViewCarouselEffect();

private:

  Property::Index mPropertyActivate;                      ///< Activation property (0.0 - deactivated, 1.0 - fully activated)

};

} // namespace Internal

// Helpers for public-api forwarding methods

inline Internal::ScrollViewCarouselEffect& GetImpl(Dali::Toolkit::ScrollViewCarouselEffect& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  Dali::RefObject& handle = obj.GetBaseObject();

  return static_cast<Internal::ScrollViewCarouselEffect&>(handle);
}

inline const Internal::ScrollViewCarouselEffect& GetImpl(const Dali::Toolkit::ScrollViewCarouselEffect& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  const Dali::RefObject& handle = obj.GetBaseObject();

  return static_cast<const Internal::ScrollViewCarouselEffect&>(handle);
}

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_SCROLL_VIEW_CAROUSEL_EFFECT_H__
