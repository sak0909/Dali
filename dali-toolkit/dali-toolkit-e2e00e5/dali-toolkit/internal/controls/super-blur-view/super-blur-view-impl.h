#ifndef __DALI_TOOLKIT_INTERNAL_SUPER_BLUR_VIEW_H__
#define __DALI_TOOLKIT_INTERNAL_SUPER_BLUR_VIEW_H__

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
#include <dali-toolkit/public-api/controls/super-blur-view/super-blur-view.h>
#include <dali-toolkit/public-api/controls/gaussian-blur-view/gaussian-blur-view.h>

namespace Dali
{

namespace Toolkit
{

class SuperBlurView;

namespace Internal
{

/**
 * SuperBlurView implementation class
 */
class SuperBlurView : public ControlImpl
{
public:

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::New
   */
  static Toolkit::SuperBlurView New( unsigned int blurLevels );

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::SetImage
   */
  void SetImage(Image inputImage);

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::GetBlurStrengthPropertyIndex
   */
  Property::Index GetBlurStrengthPropertyIndex() const;

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::SetBlurStrength
   */
  void SetBlurStrength( float blurStrength );

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::GetCurrentBlurStrength
   */
  float GetCurrentBlurStrength() const;

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::BlurFinishedSignal
   */
  Dali::Toolkit::SuperBlurView::SuperBlurViewSignal& BlurFinishedSignal();

  /**
   * @copydoc Dali::Toolkit::SuperBlurView::GetBlurredImage
   */
  Image GetBlurredImage( unsigned int level );

protected:

  /**
   * Constructor. It initializes the SuperBlurView members
   */
  SuperBlurView( unsigned int blurLevels );

  /**
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~SuperBlurView();

private: // from ControlImpl

  /**
   * @copydoc Toolkit::Control::OnInitialize
   */
  virtual void OnInitialize();

  /**
   * @copydoc Toolkit::Control::OnControlSizeSet
   */
  virtual void OnControlSizeSet(const Vector3& targetSize);

  /**
   * @copydoc Toolkit::ControlImpl::OnRelaidOut()
   */
  virtual void OnRelaidOut( Vector2 size, ActorSizeContainer& container );

private:

  /**
   * Carry out the idx-th pass of blurring
   * @param[in] idx The blur pass index
   * @param[in] image The input image for the current blurring, it is either the original image or the blurred image from the previous pass
   */
  void BlurImage( unsigned int idx, Image image );

  /**
   * Signal handler to tell when the last blur view completes
   * @param[in] blurView The blur view that just completed
   */
  void OnBlurViewFinished( Toolkit::GaussianBlurView blurView );

  /**
   * Clear the resources used to create the blurred image
   */
  void ClearBlurResource();

private:

  unsigned int                           mBlurLevels;

  Property::Index                        mBlurStrengthPropertyIndex;

  std::vector<Toolkit::GaussianBlurView> mGaussianBlurView;
  std::vector<FrameBufferImage>          mBlurredImage;
  std::vector<ImageActor>                mImageActors;
  bool                                   mResourcesCleared;

  Vector2                                mTargetSize;
  Toolkit::SuperBlurView::SuperBlurViewSignal mBlurFinishedSignal; ///< Signal emitted when blur has completed.
};

}

// Helpers for public-api forwarding methods
inline Toolkit::Internal::SuperBlurView& GetImpl( Toolkit::SuperBlurView& obj )
{
  DALI_ASSERT_ALWAYS(obj);
  Dali::RefObject& handle = obj.GetImplementation();
  return static_cast<Toolkit::Internal::SuperBlurView&>(handle);
}

inline const Toolkit::Internal::SuperBlurView& GetImpl( const Toolkit::SuperBlurView& obj )
{
  DALI_ASSERT_ALWAYS(obj);
  const Dali::RefObject& handle = obj.GetImplementation();
  return static_cast<const Toolkit::Internal::SuperBlurView&>(handle);
}

}

}

#endif /* __DALI_TOOLKIT_INTERNALSUPER_BLUR_VIEW_H__ */
