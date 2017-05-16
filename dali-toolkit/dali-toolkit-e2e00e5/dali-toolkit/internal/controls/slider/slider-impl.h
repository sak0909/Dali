#ifndef __DALI_TOOLKIT_INTERNAL_SLIDER_H__
#define __DALI_TOOLKIT_INTERNAL_SLIDER_H__

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
#include <dali-toolkit/public-api/controls/control-impl.h>
#include <dali-toolkit/public-api/controls/slider/slider.h>
#include <dali-toolkit/public-api/controls/text-view/text-view.h>

namespace Dali
{

namespace Toolkit
{

class Button;

namespace Internal
{

class Slider;

typedef Dali::IntrusivePtr< Slider > SliderPtr;

/**
 * @copydoc Toolkit::Slider
 */
class Slider : public ControlImpl
{
public:

  typedef Property::Array MarkList;

  /**
   * Create a new Slider.
   *
   * @return A public handle to the newly allocated Slider.
   */
  static Dali::Toolkit::Slider New();

public:

  // Properties

  /**
   * Set marks from a list
   *
   * @param[in] marks The list of marks to set
   */
  void SetMarks( const MarkList& marks );

  /**
   * Get the list of marks
   *
   * @return The marks list
   */
  const MarkList& GetMarks() const;

  /**
   * Set if should snap to marks or not
   *
   * @param[in] snap Flag to snap to marks or not
   */
  void SetSnapToMarks( bool snap );

  /**
   * Return if snap to marks is set or not
   *
   * @return If snap to marks is set
   */
  bool GetSnapToMarks() const;

  /**
   * Set the value of the slider
   *
   * @param[in] value The value to set. Will be clamped to [lowerBound .. upperBound]
   */
  void SetValue( float value );

  /**
   * Get the value of the slider
   *
   * @return The current value of the slider
   */
  float GetValue() const;

  /**
   * Set hit region
   *
   * @param[in] region The hit region
   */
  void SetHitRegion( const Vector2& region );

  /**
   * Get hit region
   *
   * @return The hit region
   */
  Vector2 GetHitRegion() const;

  /**
   * Set backing region
   *
   * @param[in] region The backing region
   */
  void SetBackingRegion( const Vector2& region );

  /**
   * Get backing region
   *
   * @return The backing region
   */
  Vector2 GetBackingRegion() const;

  /**
   * Get backing scale9 border
   *
   * @return The backing scale9 border
   */
  Vector4 GetBackingScale9Border() const;

  /**
   * Get popup scale9 border
   *
   * @return The popup scale9 border
   */
  Vector4 GetPopupScale9Border() const;

  /**
   * Get disable color
   *
   * @return The disable color
   */
  Vector4 GetDisableColor() const;

  /**
   * Get popup text color
   *
   * @return The popup text color
   */
  Vector4 GetPopupTextColor() const;

  /**
   * Get value precision
   *
   * @return The value precision
   */
  int GetValuePrecision() const;

  /**
   * Show the popup
   *
   * @param[in] showPopup The show popup flag
   */
  void ShowPopup( bool showPopup );

  /**
   * Get show value in popup
   *
   * @return The show value flag
   */
  bool GetShowPopup() const;

  /**
   * Set show value on handle
   *
   * @param[in] showValue The show value flag
   */
  void ShowValue( bool showValue );

  /**
   * Get show value on handle
   *
   * @return The show value flag
   */
  bool GetShowValue() const;

  /**
   * Set enabled
   *
   * param[in] enabled Set the enabled flag
   */
  void SetEnabled( bool enabled );

  /**
   * Return if enabled or not
   *
   * @return If enabled
   */
  bool IsEnabled() const;

  /**
   * Return the mark tolerance
   *
   * @return The tolerance set for snapping to marks
   */
  float GetMarkTolerance() const;

public:
  //Signals

  /**
   * @copydoc Toolkit::Slider::ValueChangedSignal()
   */
  Toolkit::Slider::ValueChangedSignalType& ValueChangedSignal();

  /**
   * copydoc Toolkit::Slider::SlidingFinishedSignal()
   */
  Toolkit::Slider::ValueChangedSignalType& SlidingFinishedSignal();

  /**
   * @copydoc Toolkit::Slider::MarkSignal()
   */
  Toolkit::Slider::MarkSignalType& MarkSignal();

  /**
   * Connects a callback function with the object's signals.
   * @param[in] object The object providing the signal.
   * @param[in] tracker Used to disconnect the signal.
   * @param[in] signalName The signal to connect to.
   * @param[in] functor A newly allocated FunctorDelegate.
   * @return True if the signal was connected.
   * @post If a signal was connected, ownership of functor was passed to CallbackBase. Otherwise the caller is responsible for deleting the unused functor.
   */
  static bool DoConnectSignal( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName,
                               FunctorDelegate* functor );

protected:

  /**
   * Construct a new Slider.
   */
  Slider();

  /**
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~Slider();

  /**
   * @copydoc Toolkit::ControlImpl::OnControlSizeSet( const Vector3& size )
   */
  virtual void OnControlSizeSet( const Vector3& size );

private:

  /**
   * Domain is a from/to pair
   */
  struct Domain
  {
    Vector2 from;
    Vector2 to;

    Domain()
    {
    }
    Domain( Vector2 fromVal, Vector2 toVal )
        : from( fromVal ), to( toVal )
    {
    }
  };

  /**
   * Slider states
   */
  enum SliderState
  {
    NORMAL,
    DISABLED,
    PRESSED,
    FOCUSED
  };

private:

  /**
   * @copydoc Toolkit::Control::OnInitialize()
   */
  virtual void OnInitialize();

  /**
   * Hit region touch event
   *
   * @param[in] actor The actor the event is raised for
   * @param[in] event The touch event info
   * @return If the event is handled or not
   */
  bool OnTouchEvent( Actor actor, const TouchEvent& event );

  /**
   * Pan gesture event
   *
   * @param[in] actor The actor the event is raised for
   * @param[in] gesture The pan event info
   */
  void OnPan( Actor actor, PanGesture gestur );

  /**
   * Map a position onto a domain and return the result as a percentage
   *
   * @param[in] point The point to map onto the domain
   * @return The result as a percentage [0..1]
   */
  float MapPercentage( const Vector2& point );

  /**
   * Map a value in the range to a percentage
   *
   * @param[in] point The value in range [lowerBound..upperBound]
   * @return The result as a percentage [0..1]
   */
  float MapValuePercentage( float value );

  /**
   * Convert a point in local hit space into domain space
   *
   * @param[in] x The x position to convert
   * @return The x position in domain space
   */
  float HitSpaceToDomain( float x );

  /**
   * Map a percentage onto the slider's bounds
   *
   * @param[in] percent The current value of slider in percent
   * @param[in] lowerBound The lower bound to map onto
   * @param[in] upperBound The upper bound to map onto
   * @return The value of percent mapped from lowerBound to upperBound
   */
  float MapBounds( float percent, float lowerBound, float upperBound );

  /**
   * Get the range of the valid values the slider handle can move between
   *
   * @param[in] currentSize The current size of the slider
   * @return The range as a domain pair
   */
  Domain CalcDomain( const Vector2& currentSize );

  /**
   * Create the hit region
   *
   * @return The hit region actor
   */
  Actor CreateHitRegion();

  /**
   * Create the backing for the slider
   *
   * @return The backing actor
   */
  ImageActor CreateBacking();

  /**
   * Create the progress backing for the slider
   *
   * @return The backing actor
   */
  ImageActor CreateProgress();

  /**
   * Create the handle for the slider
   *
   * @return The created image handle
   */
  ImageActor CreateHandle();

  /**
   * Create the popup arrow
   *
   * @return The created image handle
   */
  ImageActor CreatePopupArrow();

  /**
   * Create the popup
   *
   * @return The created image handle
   */
  ImageActor CreatePopup();

  /**
   * Create the textview for the popup
   *
   * @return The textview created for the popup
   */
  Toolkit::TextView CreatePopupText();

  /**
   * Create the value display for the slider
   *
   * @return The created root actor of the display
   */
  Actor CreateValueDisplay();

  /**
   * Set the skin based on the current state
   */
  void UpdateSkin();

  /**
   * Create all the children
   */
  void CreateChildren();

  /**
   * Resize the hit area
   *
   * @param[in] size The new size of the hit area
   */
  void ResizeHitRegion( const Vector2& size );

  /**
   * Create value popup
   */
  void AddPopup();

  /**
   * Remove value popup
   */
  void RemovePopup();

  /**
   * Display the popup for a set duration with the given value
   *
   * @param[in] value The value to display in the popup
   */
  void DisplayPopup( float value );

  /**
   * If there are marks present, filter the incoming percent based on snapping to any nearby marks
   *
   * @param[in] value The incoming value on the slider to filter
   * @return The filtered percentage snapped to any nearby marks
   */
  float MarkFilter( float value );

  /**
   * If there are marks present, snap the incoming percent to the nearest mark
   *
   * @param[in] value The incoming value on the slider to snap
   * @return The filtered percentage snapped to the nearest mark
   */
  float SnapToMark( float value );

  /**
   * Search for if a mark has been reached
   *
   * @param[in] value The value to search against
   * @param[out] outIndex The index of the mark if found
   * @return If a mark has been found to match percent
   */
  bool MarkReached( float value, int& outIndex );

  /**
   * Handler for when the value view needs to be hidden
   *
   * @return If handled or not
   */
  bool HideValueView();

  /**
   * Set value choosing whether to fire signals or not
   *
   * @paramp[in] value The value to set
   * @param[in] raiseSignals Configure signals to be raised or not.
   */
  void DisplayValue( float value, bool raiseSignals );

  /**
   * Create the image for the backing
   *
   * @param[in] imageName The name of the image to load and set
   */
  void CreateBackingImage( const std::string& imageName );

  /**
   * Set the backing image to be a scale-9 image
   *
   * @param[in] border The scale-9 border to use
   */
  void SetBackingScale9( const Vector4& border );

  /**
   * Resize the backing region
   *
   * @param[in] region The size of the region to set
   */
  void ResizeBackingRegion( const Vector2& region );

  /**
   * Size the backing region
   *
   * @param[in] region The size of the region to set
   */
  void SetBackingRegionSize( const Vector2& region );

  /**
   * Create the image for the progress bar
   *
   * @param[in] imageName The name of the image to load and set
   */
  void CreateProgressImage( const std::string& imageName );

  /**
   * Create the image for the popup
   *
   * @param[in] imageName The name of the image to load and set
   */
  void CreatePopupImage( const std::string& imageName );

  /**
   * Create the image for the popup arrow
   *
   * @param[in] imageName The name of the image to load and set
   */
  void CreatePopupArrowImage( const std::string& imageName );

  /**
   * Set the progress image to be a scale-9 image
   *
   * @param[in] border The scale-9 border to use
   */
  void SetProgressScale9( const Vector4& border );

  /**
   * Set the popup image to be a scale-9 image
   *
   * @param[in] border The scale-9 border to use
   */
  void SetPopupScale9( const Vector4& border );

  /**
   * Set the size of the progress bar region
   *
   * @param[in] region The size of the region to set
   */
  void ResizeProgressRegion( const Vector2& region );

  /**
   * Create the image for the handle
   *
   * @param[in] imageName The name of the image to load and set
   */
  void CreateHandleImage( const std::string& imageName );

  /**
   * Set the size of the handle region
   *
   * @param[in] region The size of the region to set
   */
  void ResizeHandleRegion( const Vector2& region );

  /**
   * Create and display the value on the handle
   */
  void CreateHandleValueDisplay();

  /**
   * Remove and destroy the handle value display
   */
  void DestroyHandleValueDisplay();

  /**
   * Update the color of the popup text
   *
   * @param[in] color The new color
   */
  void UpdatePopupTextColor( const Vector4& color );

  /**
   * Set handle region
   *
   * @param[in] region The handle region
   */
  void UpdateHandleRegion( const Vector2& region );

  /**
   * Get handle region
   *
   * @return The handle region
   */
  Vector2 GetHandleRegion() const;

  /**
   * Set the lower bound of the slider's value
   *
   * @param[in] bound The value to set for the lower bound
   */
  void UpdateLowerBound( float bound );

  /**
   * Get the lower bound of the slider's value
   *
   * @return The lower bound value
   */
  float GetLowerBound() const;

  /**
   * Set the upper bound of the slider's value
   *
   * @param[in] bound The value to set for the upper bound
   */
  void UpdateUpperBound( float bound );

  /**
   * Get the upper bound of the slider's value
   *
   * @return The upper bound value
   */
  float GetUpperBound() const;

private:
  // From ControlImpl

  /**
   * @copydoc Dali::CustomActorImpl::OnPropertySet()
   */
  virtual void OnPropertySet( Property::Index index, Property::Value propertyValue );

private:

  // Undefined
  Slider( const Slider& );

  // Undefined
  Slider& operator=( const Slider& rhs );

private:

  Domain mDomain;                           ///< Current domain of the handle

  Actor mHitArea;                           ///< The input handler
  ImageActor mBacking;                      ///< Backing image
  ImageActor mHandle;                       ///< Slider handle
  ImageActor mProgress;                     ///< Progress backing
  Actor mValueDisplay;                      ///< Display of the value
  ImageActor mPopup;                        ///< Popup backing
  ImageActor mPopupArrow;                   ///< Popup arrow backing

  Toolkit::TextView mValueTextView;         //< The text value in popup
  Toolkit::TextView mHandleValueTextView;   ///< The text value on handle
  Vector2 mHandleLastTouchPoint;            ///< The last touch point for the handle
  Timer mValueTimer;                        ///< Timer used to hide value view

  Toolkit::Slider::ValueChangedSignalType mValueChangedSignal;    ///< Signal emitted when the value is changed
  Toolkit::Slider::ValueChangedSignalType mSlidingFinishedSignal;    ///< Signal emitted when a sliding is finished
  Toolkit::Slider::MarkSignalType mMarkSignal;                    ///< Signal emitted when a mark is reached

  SliderState mState;                 ///< The state of the slider

  PanGestureDetector mPanDetector;    ///< Hit region pan detector

  MarkList mMarks;                    ///< List of discreet marks

  // Properties
  Property::Index mPropertyLowerBound;
  Property::Index mPropertyUpperBound;
  Property::Index mPropertyValue;
  Property::Index mPropertyHitRegion;
  Property::Index mPropertyBackingRegion;
  Property::Index mPropertyHandleRegion;

  Property::Index mPropertyBackingImageName;
  Property::Index mPropertyHandleImageName;
  Property::Index mPropertyProgressImageName;
  Property::Index mPropertyPopupImageName;
  Property::Index mPropertyPopupArrowImageName;

  Property::Index mPropertyBackingScale9Border;
  Property::Index mPropertyProgressScale9Border;
  Property::Index mPropertyPopupScale9Border;

  Property::Index mPropertyDisableColor;
  Property::Index mPropertyPopupTextColor;

  Property::Index mPropertyValuePrecision;

  Property::Index mPropertyShowPopup;
  Property::Index mPropertyShowValue;

  Property::Index mPropertyEnabled;

  Property::Index mPropertyMarks;
  Property::Index mPropertySnapToMarks;
  Property::Index mPropertyMarkTolerance;

};

} // namespace Internal

// Helpers for public-api forwarding methods

inline Toolkit::Internal::Slider& GetImpl( Toolkit::Slider& pub )
{
  DALI_ASSERT_ALWAYS( pub );

  Dali::RefObject& handle = pub.GetImplementation();

  return static_cast< Toolkit::Internal::Slider& >( handle );
}

inline const Toolkit::Internal::Slider& GetImpl( const Toolkit::Slider& pub )
{
  DALI_ASSERT_ALWAYS( pub );

  const Dali::RefObject& handle = pub.GetImplementation();

  return static_cast< const Toolkit::Internal::Slider& >( handle );
}

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_SLIDER_H__
