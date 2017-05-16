#ifndef __DALI_TOOLKIT_ROLL_LAYOUT_H__
#define __DALI_TOOLKIT_ROLL_LAYOUT_H__

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

#include <dali-toolkit/public-api/controls/scrollable/item-view/item-layout.h>

namespace Dali DALI_IMPORT_API
{

namespace Toolkit
{

class RollLayout;

typedef IntrusivePtr<RollLayout> RollLayoutPtr;

/**
 * An ItemView layout which arranges items in a roll.
 */
class RollLayout : public ItemLayout
{
public:

  typedef boost::function<Vector3 (float layoutWidth, float layoutHeight, float rowSpacing)> ItemSizeFunction;

  /**
   * Create a new roll layout
   */
  static RollLayoutPtr New();

  /**
   * Virtual destructor.
   */
  virtual ~RollLayout();

  /**
   * Set the spacing between rows.
   * @param[in] spacing The row spacing.
   */
  void SetRowSpacing(float spacing);

  /**
   * Get the spacing between rows.
   * @return The row spacing.
   */
  float GetRowSpacing() const;

  /**
   * Set the function used to calculate the item-size, for a given layout-size.
   * @param[in] function The item-size function.
   */
  void SetItemSizeFunction(ItemSizeFunction function);

  /**
   * Get the function used to calculate the item-size.
   * @return The item-size function.
   */
  ItemSizeFunction GetItemSizeFunction() const;

  /**
   * Set the factor used to customise the scroll speed while dragging and swiping the layout.
   * @param[in] scrollSpeed The scroll speed factor.
   */
  void SetScrollSpeedFactor(float scrollSpeed);

  /**
   * Set the maximum swipe speed in pixels per second.
   * @param[in] speed The maximum swipe speed.
   */
  void SetMaximumSwipeSpeed(float speed);

  /**
   * Set the duration of the flick animation in second. This is the time taken to animate each
   * item to its next layout position (e.g. from 1.0 to 2.0) when a flick animation is triggered
   * by a swipe gesture.
   * @pre durationSeconds must be greater than zero.
   * @param[in] durationSeconds The duration of flick animation in seconds.
   */
  void SetItemFlickAnimationDuration(float durationSeconds);

  /**
   * @copydoc ItemLayout::GetScrollSpeedFactor()
   */
  virtual float GetScrollSpeedFactor() const;

  /**
   * @copydoc ItemLayout::GetMaximumSwipeSpeed()
   */
  virtual float GetMaximumSwipeSpeed() const;

  /**
   * @copydoc ItemLayout::GetItemFlickAnimationDuration()
   */
  virtual float GetItemFlickAnimationDuration() const;

private:

  /**
   * @copydoc ItemLayout::GetMinimumLayoutPosition()
   */
  virtual float GetMinimumLayoutPosition(unsigned int numberOfItems, Vector3 layoutSize) const;

  /**
   * @copydoc ItemLayout::GetClosestAnchorPosition()
   */
  virtual float GetClosestAnchorPosition(float layoutPosition) const;

  /**
   * @copydoc ItemLayout::GetItemScrollToPosition()
   */
  virtual float GetItemScrollToPosition(unsigned int itemId) const;

  /**
   * @copydoc ItemLayout::GetItemsWithinArea()
   */
  virtual ItemRange GetItemsWithinArea(float firstItemPosition, Vector3 layoutSize) const;

  /**
   * @copydoc ItemLayout::GetReserveItemCount()
   */
  virtual unsigned int GetReserveItemCount(Vector3 layoutSize) const;

  /**
   * @copydoc ItemLayout::GetItemSize()
   */
  virtual bool GetItemSize(unsigned int itemId, Vector3 layoutSize, Vector3& itemSize) const;

  /**
   * @copydoc ItemLayout::GetResizeAnimation()
   */
  virtual void GetResizeAnimation(Animation& animation, Actor actor, Vector3 size, float durationSeconds) const;

  /**
   * @copydoc ItemLayout::GetPositionConstraint()
   */
  virtual bool GetPositionConstraint(unsigned int itemId, ItemLayout::Vector3Function& constraint) const;

  /**
   * @copydoc ItemLayout::GetRotationConstraint()
   */
  virtual bool GetRotationConstraint(unsigned int itemId, ItemLayout::QuaternionFunction& constraint) const;

  /**
   * @copydoc ItemLayout::GetScaleConstraint()
   */
  virtual bool GetScaleConstraint(unsigned int itemId, ItemLayout::Vector3Function& constraint) const;

  /**
   * @copydoc ItemLayout::GetColorConstraint()
   */
  virtual bool GetColorConstraint(unsigned int itemId, ItemLayout::Vector4Function& constraint) const;

  /**
   * @copydoc ItemLayout::GetVisibilityConstraint()
   */
  virtual bool GetVisibilityConstraint(unsigned int itemId, ItemLayout::BoolFunction& constraint) const;

  /**
   * @copydoc ItemLayout::GetScrollDirection()
   */
  virtual Degree GetScrollDirection() const;

protected:

  /**
   * Protected constructor; see also RollLayout::New()
   */
  RollLayout();

private:

  struct Impl;
  Impl* mImpl;
};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_ROLL_LAYOUT_H__
