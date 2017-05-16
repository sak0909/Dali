#ifndef __DALI_TOOLKIT_SCROLL_VIEW_PAGE_CUBE_EFFECT_H__
#define __DALI_TOOLKIT_SCROLL_VIEW_PAGE_CUBE_EFFECT_H__

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
#include <dali-toolkit/public-api/controls/scrollable/scroll-view/scroll-view-effect.h>

namespace Dali DALI_IMPORT_API
{

class Actor;

namespace Toolkit
{

namespace Internal DALI_INTERNAL
{
class ScrollViewPageCubeEffect;
}

/**
 * ScrollView Inner Cube-Effect.
 *
 * This effect cause each page in a scroll-view to rotate round an inner 3D cube.
 * It should be used on the following Actor hierarchy:
 *
 * ScrollView
 * |
 * Page (1..n)
 *
 * You should ensure ScrollView's default constraints have been removed,
 * by calling ScrollView::RemoveConstraintsFromChildren() before applying
 * this effect to ScrollView.
 *
 * Manual operation:
 * ApplyToPage(...) method should be called on every page.
 *
 * Automatic operation:
 * not implemented.
 */
class ScrollViewPageCubeEffect : public ScrollViewEffect
{

public:

  /**
   * Create an initialized ScrollViewPageCubeEffect.
   * @return A handle to a newly allocated Dali resource.
   */
  static ScrollViewPageCubeEffect New();

  /**
   * Create an uninitialized ScrollViewPageCubeEffect; this can be initialized with ScrollViewPageCubeEffect::New()
   * Calling member functions with an uninitialized Toolkit::ScrollViewPageCubeEffect is not allowed.
   */
  ScrollViewPageCubeEffect();

  /**
   * Downcast an Object handle to ScrollViewPageCubeEffect. If handle points to a ScrollViewPageCubeEffect the
   * downcast produces valid handle. If not the returned handle is left uninitialized.
   * @param[in] handle Handle to an object
   * @return handle to a ScrollViewPageCubeEffect or an uninitialized handle
   */
  static ScrollViewPageCubeEffect DownCast( BaseHandle handle );

  /**
   * Manually apply effect to a page in the scroll-view.
   * @param[in] page The page to be affected by this effect.
   * @param[in] angleSwing The maximum amount the child actor should
   * rotate in radians for each axis (X and Y) as the page is scrolled.
   */
  void ApplyToPage( Actor page, const Vector2& angleSwing );

protected:

  /**
   * This constructor is used by Dali New() methods.
   * @param [in] impl A pointer to a newly allocated Dali resource
   */
  ScrollViewPageCubeEffect( Internal::ScrollViewPageCubeEffect *impl );

};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_SCROLL_VIEW_PAGE_CUBE_EFFECT_H__
