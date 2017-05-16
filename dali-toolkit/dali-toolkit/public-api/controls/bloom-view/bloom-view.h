#ifndef __DALI_TOOLKIT_BLOOM_VIEW_H__
#define __DALI_TOOLKIT_BLOOM_VIEW_H__

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
#include <dali-toolkit/public-api/controls/control.h>
#include <dali-toolkit/public-api/controls/gaussian-blur-view/gaussian-blur-view.h>

namespace Dali DALI_IMPORT_API
{

namespace Toolkit
{

namespace Internal DALI_INTERNAL
{

/**
 * BloomView implementation class
 */
class BloomView;

} // namespace Internal

/**
 *
 * BloomView is a class for applying a render process that intensifies and blurs the bright parts of an image, bleeding bright areas into darker ones and making bright
 * light look more realistic.
 *
 * Basic idea:-
 *
 * 1) The BloomView object will render all its child actors offscreen.\n
 * 2) The BloomView object then extract the parts of that image that are brighter than the bloom threshold.\n
 * 3) The BloomView object then blurs the result of step 2), which makes the brightness bleed into surrounding areas.\n
 * 3) The BloomView object then composites the bloom from step 3) with the child actors image from step 1), using parameters that can be set by the user.
 * The compositing is additive (image + bloom).\n
 * 4) The BloomView object gets rendered automatically, either to the screen via the default render task, or via a RenderTask the user has created for
 * e.g. further offscreen rendering.
 *
 * Fundamentally, the BloomView is simply an Actor in the normal actor tree that affects all of its children. It should be added to your Actor tree and manipulated in the
 * normal ways. It can be considered a 'portal' in the sense that all child actors are clipped to the BloomView actor bounds.
 *
 * ************\n
 * NB: It is essential to remove the BloomView from the stage and also to call Deactivate() on it when you are not using it. This will ensure that resources are freed and
 * rendering stops.\n
 * ************\n
 *
 *
 * Usage example:-
 *
 *  // initialise\n
 *  BloomView bloomView = BloomView::New();\n
 *
 *  // create and add some visible actors to the BloomView, all these child actors will therefore get bloomed\n
 *  Image image = Image::New(...);\n
 *  ImageActor imageActor = ImageActor::New(image);\n
 *  bloomView.Add(imageActor);\n
 *  ...\n
 *
 *  // Start rendering the BloomView\n
 *  Stage::GetCurrent().Add(bloomView);\n
 *  bloomView.Activate();\n
 *  ...\n
 *
 *  // animate the strength of the bloom - this can fade between no bloom and your desired max bloom. See GetBloomIntensityPropertyIndex().\n
 *  Animation blurAnimation = Animation::New( ... );\n
 *  blurAnimation.AnimateTo( Property( bloomView, bloomView.GetBloomIntensityPropertyIndex() ), ... );\n
 *  blurAnimation.Play();\n
 *
 *  ...\n
 *  // Stop rendering the BloomView\n
 *  Stage::GetCurrent().Remove(bloomView);\n
 *  bloomView.Deactivate();\n
 */
class BloomView : public Control
{
public:

  /**
   * Create an uninitialized BloomView; this can be initialized with BloomView::New()
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  BloomView();

  /**
   * Copy constructor. Creates another handle that points to the same real object
   */
  BloomView(const BloomView& handle);

  /**
   * Assignment operator. Changes this handle to point to another real object
   */
  BloomView& operator=(const BloomView& ZoomView);

  /**
   * Virtual destructor.
   */
  virtual ~BloomView();

  /**
   * Downcast an Object handle to BloomView. If handle points to a BloomView the
   * downcast produces valid handle. If not the returned handle is left uninitialized.
   * @param[in] handle Handle to an object
   * @return handle to a BloomView or an uninitialized handle
   */
  static BloomView DownCast( BaseHandle handle );

  /**
   * Create an initialized BloomView, using default settings. The default settings are:-\n
   *
   * numSamples = 5\n
   * blurBellCurveWidth = 1.5\n
   * renderTargetPixelFormat = RGB888\n
   * downsampleWidthScale = 0.5\n
   * downsampleHeightScale = 0.5\n
   * @return A handle to a newly allocated Dali resource
   */
  static BloomView New();

 /**
  * Create an initialized BloomView.
  * @param numSamples The size of the Gaussian blur kernel (number of samples in horizontal / vertical blur directions) that is used to blur the bloom
  * @param blurBellCurveWidth The constant controlling the Gaussian function, must be > 0.0. Controls the width of the bell curve, i.e. the look of the blur and also indirectly
  * the amount of blurriness Smaller numbers for a tighter curve. Useful values in the range [0.5..3.0] - near the bottom of that range the curve is weighted heavily towards
  * the centre pixel of the kernel (so there won't be much blur), near the top of that range the pixels have nearly equal weighting (closely approximating a box filter
  * therefore). Values close to zero result in the bell curve lying almost entirely within a single pixel, in other words there will be basically no blur as neighbouring pixels
  * have close to zero weights.
  * @param renderTargetPixelFormat The pixel format of the render targets we are using to perform the bloom.
  * @param downsampleWidthScale The width scale factor applied during the blur process, scaling the size of the source image to the size of the final blurred image output.
  * Useful for downsampling - trades visual quality for processing speed. A value of 1.0f results in no scaling applied.
  * @param downsampleHeightScale The height scale factor applied during the blur process, scaling the size of the source image to the size of the final blurred image output.
  * Useful for downsampling - trades visual quality for processing speed. A value of 1.0f results in no scaling applied.
  * @return A handle to a newly allocated Dali resource
  */
  static BloomView New(const unsigned int numSamples, const float blurBellCurveWidth, const Pixel::Format renderTargetPixelFormat,
                              const float downsampleWidthScale, const float downsampleHeightScale);

  /**
   * Adds a child Actor to this Actor.
   * NOTE! if the child already has a parent, it will be removed from old parent
   * and reparented to this actor. This may change childs position, color, shader effect,
   * scale etc as it now inherits them from this actor
   * @pre This Actor (the parent) has been initialized.
   * @pre The child actor has been initialized.
   * @pre The child actor is not the same as the parent actor.
   * @pre The actor is not the Root actor
   * @param [in] child The child.
   * @post The child will be referenced by its parent. This means that the child will be kept alive,
   * even if the handle passed into this method is reset or destroyed.
   * @post This may invalidate ActorContainer iterators.
   */
  void Add(Actor child);

  /**
   * Removes a child Actor from this Actor.
   * If the actor was not a child of this actor, this is a no-op.
   * @pre This Actor (the parent) has been initialized.
   * @pre The child actor is not the same as the parent actor.
   * @param [in] child The child.
   * @post This may invalidate ActorContainer iterators.
   */
  void Remove(Actor child);

  /**
   * Start rendering the BloomView. Must be called after you Add() it to the stage.
   */
  void Activate();

  /**
   * Stop rendering the BloomView. Must be called after you Remove() it from the stage.
   */
  void Deactivate();

  /**
   * Get the property index that controls the intensity threshold above which the pixels will be bloomed. Useful for animating this property.
   * This property represents a value such that pixels brighter than this threshold will be bloomed. Values are normalised, i.e. RGB 0.0 = 0, 1.0 = 255.  Default 0.25.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetBloomThresholdPropertyIndex() const;

  /**
   * Get the property index that controls the strength of the blur applied to the bloom. Useful for animating this property.
   * This property represents a value in the range [0.0 - 1.0] where 0.0 is no blur and 1.0 is full blur. Default 1.0.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetBlurStrengthPropertyIndex() const;

  /**
   * Get the property index that controls the intensity of the child actor render texture used during compositing. Useful for animating this property.
   * This property represents a multiplier on the intensity of the bloom texture. Default 1.0.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetBloomIntensityPropertyIndex() const;

  /**
   * Get the property index that controls the saturation of the child actor render texture used during compositing. Useful for animating this property.
   * This property represents a multiplier on the saturation of the bloom texture. Default 1.0.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetBloomSaturationPropertyIndex() const;

  /**
   * Get the property index that controls the intensity of the child actor render texture used during compositing. Useful for animating this property.
   * This property represents a multiplier on the intensity of the image texture. Default 1.0.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetImageIntensityPropertyIndex() const;

  /**
   * Get the property index that controls the saturation of the child actor render texture used during compositing. Useful for animating this property.
   * This property represents a multiplier on the saturation of the image texture. Default 1.0.
   * @return The property index that can be used with e.g. AnimateTo( ... )
   */
  Property::Index GetImageSaturationPropertyIndex() const;

public:

  /**
   * Creates a handle using the Toolkit::Internal implementation.
   * @param[in]  implementation  The UI Control implementation.
   */
  BloomView( Internal::BloomView& implementation );

  /**
   * Allows the creation of this UI Control from an Internal::CustomActor pointer.
   * @param[in]  internal  A pointer to the internal CustomActor.
   */
  BloomView( Dali::Internal::CustomActor* internal );

private:

};

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_BLOOM_VIEW_H__
