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

// CLASS HEADER
#include "bloom-view-impl.h"
#include "../gaussian-blur-view/gaussian-blur-view-impl.h"

// EXTERNAL INCLUDES
#include <sstream>
#include <iomanip>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/controls/gaussian-blur-view/gaussian-blur-view.h>
#include <dali-toolkit/public-api/controls/bloom-view/bloom-view.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace
{

using namespace Dali;

BaseHandle Create()
{
  return Toolkit::BloomView::New();
}

TypeRegistration mType( typeid(Toolkit::BloomView), typeid(Toolkit::Control), Create );

// default parameters
const float BLOOM_THRESHOLD_DEFAULT = 0.25f;
const float BLOOM_BLUR_STRENGTH_DEFAULT = 1.0f;
const float BLOOM_INTENSITY_DEFAULT = 1.0f;
const float IMAGE_INTENSITY_DEFAULT = 1.0f;
const float BLOOM_SATURATION_DEFAULT = 1.0f;
const float IMAGE_SATURATION_DEFAULT = 1.0f;

// gaussian blur
const unsigned int BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_NUM_SAMPLES = 5;
const float BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_BLUR_BELL_CURVE_WIDTH = 1.5f;
const Pixel::Format BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_RENDER_TARGET_PIXEL_FORMAT = Pixel::RGBA8888;
const float BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_BLUR_FADE_IN = 1.0f;                                       // default, fully blurred
const float BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_DOWNSAMPLE_WIDTH_SCALE = 0.5f;
const float BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_DOWNSAMPLE_HEIGHT_SCALE = 0.5f;

const float ARBITRARY_FIELD_OF_VIEW = Math::PI / 4.0f;

const std::string BLOOM_BLUR_STRENGTH_PROPERTY_NAME( "BlurStrengthProperty" );

const std::string BLOOM_THRESHOLD_PROPERTY_NAME( "uBloomThreshold" );
const std::string RECIP_ONE_MINUS_BLOOM_THRESHOLD_PROPERTY_NAME( "uRecipOneMinusBloomThreshold" );
const std::string BLOOM_INTENSITY_PROPERTY_NAME( "uBloomIntensity" );
const std::string BLOOM_SATURATION_PROPERTY_NAME( "uBloomSaturation" );
const std::string IMAGE_INTENSITY_PROPERTY_NAME( "uImageIntensity" );
const std::string IMAGE_SATURATION_PROPERTY_NAME( "uImageSaturation" );

///////////////////////////////////////////////////////
//
// Bloom shaders
//

const char* const BLOOM_EXTRACT_FRAGMENT_SOURCE =
  "uniform float uBloomThreshold;\n"
  "uniform float uRecipOneMinusBloomThreshold;\n"
  "void main()\n"
  "{\n"
  "  mediump vec4 col;\n"
  "  col = texture2D(sTexture, vec2(vTexCoord.x, vTexCoord.y));\n"
  "  col = (col - uBloomThreshold) * uRecipOneMinusBloomThreshold;\n" // remove intensities lower than the thresold and remap intensities above the threshold to [0..1]
  "  gl_FragColor = clamp(col, 0.0, 1.0);\n"
  "}\n";

const char* const COMPOSITE_FRAGMENT_SOURCE =
  "uniform float uBloomIntensity;\n"
  "uniform float uImageIntensity;\n"
  "uniform float uBloomSaturation;\n"
  "uniform float uImageSaturation;\n"

  "vec4 ChangeSaturation(vec4 col, float sat)\n"
  "{\n"
  "  float grey = dot(col.rgb, vec3(0.3, 0.6, 0.1));\n"
  "  return mix(vec4(grey, grey, grey, 1.0), col, sat);\n"
  "}\n"

  "void main()\n"
  "{\n"
  "  mediump vec4 image;\n"
  "  mediump vec4 bloom;\n"
  "  image = texture2D(sTexture, vec2(vTexCoord.x, vTexCoord.y));\n"
  "  bloom = texture2D(sEffect, vec2(vTexCoord.x, vTexCoord.y));\n"
  "  image = ChangeSaturation(image, uImageSaturation) * uImageIntensity;\n"
  "  bloom = ChangeSaturation(bloom, uBloomSaturation) * uBloomIntensity;\n"
  "  image *= 1.0 - clamp(bloom, 0.0, 1.0);\n" // darken base where bloom is strong, to prevent excessive burn-out of result
  "  gl_FragColor = image + bloom;\n"
  "}\n";

} // namespace



BloomView::BloomView()
  : ControlImpl( false )  // doesn't require touch events
  , mBlurNumSamples(BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_NUM_SAMPLES)
  , mBlurBellCurveWidth(BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_BLUR_BELL_CURVE_WIDTH)
  , mPixelFormat(BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_RENDER_TARGET_PIXEL_FORMAT)
  , mDownsampleWidthScale(BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_DOWNSAMPLE_WIDTH_SCALE)
  , mDownsampleHeightScale(BLOOM_GAUSSIAN_BLUR_VIEW_DEFAULT_DOWNSAMPLE_HEIGHT_SCALE)
  , mDownsampledWidth( 0.0f )
  , mDownsampledHeight( 0.0f )
  , mTargetSize(Vector2::ZERO)
  , mLastSize(Vector2::ZERO)
  , mChildrenRoot(Actor::New())
  , mBloomThresholdPropertyIndex(Property::INVALID_INDEX)
  , mBlurStrengthPropertyIndex(Property::INVALID_INDEX)
  , mBloomIntensityPropertyIndex(Property::INVALID_INDEX)
  , mBloomSaturationPropertyIndex(Property::INVALID_INDEX)
  , mImageIntensityPropertyIndex(Property::INVALID_INDEX)
  , mImageSaturationPropertyIndex(Property::INVALID_INDEX)
{
}

BloomView::BloomView( const unsigned int blurNumSamples, const float blurBellCurveWidth, const Pixel::Format renderTargetPixelFormat,
                                    const float downsampleWidthScale, const float downsampleHeightScale)
  : ControlImpl( false )  // doesn't require touch events
  , mBlurNumSamples(blurNumSamples)
  , mBlurBellCurveWidth(blurBellCurveWidth)
  , mPixelFormat(renderTargetPixelFormat)
  , mDownsampleWidthScale(downsampleWidthScale)
  , mDownsampleHeightScale(downsampleHeightScale)
  , mDownsampledWidth( 0.0f )
  , mDownsampledHeight( 0.0f )
  , mTargetSize(Vector2::ZERO)
  , mLastSize(Vector2::ZERO)
  , mChildrenRoot(Actor::New())
  , mBloomThresholdPropertyIndex(Property::INVALID_INDEX)
  , mBlurStrengthPropertyIndex(Property::INVALID_INDEX)
  , mBloomIntensityPropertyIndex(Property::INVALID_INDEX)
  , mBloomSaturationPropertyIndex(Property::INVALID_INDEX)
  , mImageIntensityPropertyIndex(Property::INVALID_INDEX)
  , mImageSaturationPropertyIndex(Property::INVALID_INDEX)
{
}

BloomView::~BloomView()
{
}

Toolkit::BloomView BloomView::New()
{
  BloomView* impl = new BloomView();

  Dali::Toolkit::BloomView handle = Dali::Toolkit::BloomView( *impl );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  impl->Initialize();

  return handle;
}

Toolkit::BloomView BloomView::New(const unsigned int blurNumSamples, const float blurBellCurveWidth, const Pixel::Format renderTargetPixelFormat,
                                                const float downsampleWidthScale, const float downsampleHeightScale)
{
  BloomView* impl = new BloomView( blurNumSamples, blurBellCurveWidth, renderTargetPixelFormat, downsampleWidthScale, downsampleHeightScale);

  Dali::Toolkit::BloomView handle = Dali::Toolkit::BloomView( *impl );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  impl->Initialize();

  return handle;
}

/////////////////////////////////////////////////////////////
// for creating a subtree for all user added child actors, so that we can have them exclusive to the mRenderChildrenTask and our other actors exclusive to our other tasks
// TODO: overloading Actor::Add()/Remove() not nice since breaks polymorphism. Need another method to pass ownership of added child actors to our internal actor root.
void BloomView::Add(Actor child)
{
  mChildrenRoot.Add(child);
}

void BloomView::Remove(Actor child)
{
  mChildrenRoot.Remove(child);
}






///////////////////////////////////////////////////////////
//
// Private methods
//

void BloomView::OnInitialize()
{
  // root actor to parent all user added actors, needed to allow us to set that subtree as exclusive for our child render task
  mChildrenRoot.SetPositionInheritanceMode( Dali::USE_PARENT_POSITION );
  mChildrenRoot.ApplyConstraint( Constraint::New<Vector3>( Actor::SIZE, ParentSource( Actor::SIZE ), EqualToConstraint() ) ); // same size as BloomView object


  //////////////////////////////////////////////////////
  // Create shaders

  // Create shader used for extracting the bright parts of an image
  mBloomExtractShader = ShaderEffect::New( "", BLOOM_EXTRACT_FRAGMENT_SOURCE );

  // Create shader used to composite bloom and original image to output render target
  mCompositeShader = ShaderEffect::New( "", COMPOSITE_FRAGMENT_SOURCE );


  //////////////////////////////////////////////////////
  // Create actors

  // Create an ImageActor for rendering from the scene texture to the bloom texture
  mBloomExtractImageActor = ImageActor::New();
  mBloomExtractImageActor.SetPositionInheritanceMode( Dali::USE_PARENT_POSITION );
  mBloomExtractImageActor.ScaleBy( Vector3(1.0f, -1.0f, 1.0f) ); // FIXME
  mBloomExtractImageActor.SetShaderEffect( mBloomExtractShader );

  // Create an ImageActor for compositing the result (scene and bloom textures) to output
  mCompositeImageActor = ImageActor::New();
  mCompositeImageActor.SetPositionInheritanceMode( Dali::USE_PARENT_POSITION );
  mCompositeImageActor.ApplyConstraint( Constraint::New<Vector3>( Actor::SIZE, ParentSource( Actor::SIZE ), EqualToConstraint() ) ); // same size as BloomView object
  mCompositeImageActor.SetShaderEffect( mCompositeShader );
  mCompositeImageActor.ScaleBy( Vector3(1.0f, -1.0f, 1.0f) ); // FIXME

  // Create an ImageActor for holding final result, i.e. the blurred image. This will get rendered to screen later, via default / user render task
  mTargetImageActor = ImageActor::New();
  mTargetImageActor.SetPositionInheritanceMode( Dali::USE_PARENT_POSITION );
  mTargetImageActor.ApplyConstraint( Constraint::New<Vector3>( Actor::SIZE, ParentSource( Actor::SIZE ), EqualToConstraint() ) ); // same size as BloomView object
  mTargetImageActor.ScaleBy( Vector3(1.0f, -1.0f, 1.0f) ); // FIXME


  // Create the Gaussian Blur object + render tasks
  // Note that we use mBloomExtractTarget as the source image and also re-use this as the gaussian blur final render target. This saves the gaussian blur code from creating it
  // render targets etc internally, so we make better use of resources
  // Note, this also internally creates the render tasks used by the Gaussian blur, this must occur after the bloom extraction and before the compositing
  mGaussianBlurView = Dali::Toolkit::GaussianBlurView::New(mBlurNumSamples, mBlurBellCurveWidth, mPixelFormat, mDownsampleWidthScale, mDownsampleHeightScale, true);
  mGaussianBlurView.SetPositionInheritanceMode( Dali::USE_PARENT_POSITION );


  //////////////////////////////////////////////////////
  // Create cameras for the renders corresponding to the (potentially downsampled) render targets' size
  mRenderDownsampledCamera = CameraActor::New();
  mRenderDownsampledCamera.SetParentOrigin(ParentOrigin::CENTER);

  mRenderFullSizeCamera = CameraActor::New();
  mRenderFullSizeCamera.SetParentOrigin(ParentOrigin::CENTER);


  ////////////////////////////////
  // Connect to actor tree
  Self().Add( mChildrenRoot );
  Self().Add( mBloomExtractImageActor );
  Self().Add( mGaussianBlurView );
  Self().Add( mCompositeImageActor );
  Self().Add( mTargetImageActor );
  Self().Add( mRenderDownsampledCamera );
  Self().Add( mRenderFullSizeCamera );

  // bind properties for / set shader constants to defaults
  SetupProperties();
}

/**
 * ZrelativeToYconstraint
 *
 * f(current, property, scale) = Vector3(current.x, current.y, property.y * scale)
 */
struct ZrelativeToYconstraint
{
  ZrelativeToYconstraint( float scale )
    : mScale( scale )
  {}

  Vector3 operator()(const Vector3&    current,
                     const PropertyInput& property)
  {
    Vector3 v;

    v.x = current.x;
    v.y = current.y;
    v.z = property.GetVector3().y * mScale;

    return v;
  }

  float mScale;
};

void BloomView::OnControlSizeSet(const Vector3& targetSize)
{
  mTargetSize = Vector2(targetSize);

  // if we are already on stage, need to update render target sizes now to reflect the new size of this actor
  if(Self().OnStage())
  {
    AllocateResources();
  }
}

void BloomView::AllocateResources()
{
  // size of render targets etc is based on the size of this actor, ignoring z
  if(mTargetSize != mLastSize)
  {
    mLastSize = mTargetSize;

    // get size of downsampled render targets
    mDownsampledWidth = mTargetSize.width * mDownsampleWidthScale;
    mDownsampledHeight = mTargetSize.height * mDownsampleHeightScale;


    //////////////////////////////////////////////////////
    // Create cameras

    // Create and place a camera for the renders corresponding to the (potentially downsampled) render targets' size
    mRenderDownsampledCamera.SetFieldOfView(ARBITRARY_FIELD_OF_VIEW);
    // TODO: how do we pick a reasonable value for near clip? Needs to relate to normal camera the user renders with, but we don't have a handle on it
    mRenderDownsampledCamera.SetNearClippingPlane(1.0f);
    mRenderDownsampledCamera.SetAspectRatio(mDownsampledWidth / mDownsampledHeight);
    mRenderDownsampledCamera.SetType(Dali::Camera::FREE_LOOK); // camera orientation based solely on actor
    mRenderDownsampledCamera.SetRotation(Quaternion(M_PI, Vector3::YAXIS)); // Rotate to look at origin

    mRenderDownsampledCamera.SetPosition(0.0f, 0.0f, ((mDownsampledHeight * 0.5f) / tanf(ARBITRARY_FIELD_OF_VIEW * 0.5f)));

    // Create and place a camera for the children render, corresponding to its render target size
    mRenderFullSizeCamera.SetFieldOfView(ARBITRARY_FIELD_OF_VIEW);
    // TODO: how do we pick a reasonable value for near clip? Needs to relate to normal camera the user renders with, but we don't have a handle on it
    mRenderFullSizeCamera.SetNearClippingPlane(1.0f);
    mRenderFullSizeCamera.SetAspectRatio(mTargetSize.width / mTargetSize.height);
    mRenderFullSizeCamera.SetType(Dali::Camera::FREE_LOOK); // camera orientation based solely on actor
    mRenderFullSizeCamera.SetRotation(Quaternion(M_PI, Vector3::YAXIS)); // Rotate to look at origin

    float cameraPosConstraintScale = 0.5f / tanf(ARBITRARY_FIELD_OF_VIEW * 0.5f);
    mRenderFullSizeCamera.SetPosition(0.0f, 0.0f, mTargetSize.height * cameraPosConstraintScale);


    // Children render camera must move when GaussianBlurView object is
    // resized. This is since we cannot change render target size - so we need
    // to remap the child actors' rendering accordingly so they still exactly
    // fill the render target. Note that this means the effective resolution of
    // the child render changes as the GaussianBlurView object changes size,
    // this is the trade off for not being able to modify render target size
    // Change camera z position based on GaussianBlurView actor height

    mRenderFullSizeCamera.RemoveConstraints();
    mRenderFullSizeCamera.ApplyConstraint( Constraint::New<Vector3>( Actor::POSITION, ParentSource( Actor::SIZE ), ZrelativeToYconstraint(cameraPosConstraintScale) ) );


    //////////////////////////////////////////////////////
    // Pass size change onto GaussianBlurView, so it matches
    mGaussianBlurView.SetSize(mTargetSize);
    GetImpl(mGaussianBlurView).AllocateResources();


    //////////////////////////////////////////////////////
    // Create render targets

    // create off screen buffer of new size to render our child actors to
    mRenderTargetForRenderingChildren = FrameBufferImage::New( mTargetSize.width, mTargetSize.height, mPixelFormat, Dali::Image::Unused );
    mBloomExtractTarget = FrameBufferImage::New( mDownsampledWidth, mDownsampledHeight, mPixelFormat, Dali::Image::Unused );
    mOutputRenderTarget = FrameBufferImage::New( mTargetSize.width, mTargetSize.height, mPixelFormat, Dali::Image::Unused );


    //////////////////////////////////////////////////////
    // Point actors and render tasks at new render targets

    mBloomExtractImageActor.SetImage( mRenderTargetForRenderingChildren );
    mBloomExtractImageActor.SetSize(mDownsampledWidth, mDownsampledHeight); // size needs to match render target

    // set GaussianBlurView to blur our extracted bloom
    mGaussianBlurView.SetUserImageAndOutputRenderTarget(mBloomExtractTarget, mBloomExtractTarget);

    // use the completed blur in the first buffer and composite with the original child actors render
    mCompositeImageActor.SetImage( mRenderTargetForRenderingChildren );
    mCompositeShader.SetEffectImage( mBloomExtractTarget );

    // set up target actor for rendering result, i.e. the blurred image
    mTargetImageActor.SetImage(mOutputRenderTarget);
  }
}

void BloomView::CreateRenderTasks()
{
  RenderTaskList taskList = Stage::GetCurrent().GetRenderTaskList();

  // create render task to render our child actors to offscreen buffer
  mRenderChildrenTask = taskList.CreateTask();
  mRenderChildrenTask.SetSourceActor( mChildrenRoot );
  mRenderChildrenTask.SetExclusive(true);
  mRenderChildrenTask.SetInputEnabled( false );
  mRenderChildrenTask.SetClearEnabled( true );

  // Extract the bright part of the image and render to a new buffer. Downsampling also occurs at this stage to save pixel fill, if it is set up.
  mBloomExtractTask = taskList.CreateTask();
  mBloomExtractTask.SetSourceActor( mBloomExtractImageActor );
  mBloomExtractTask.SetExclusive(true);
  mBloomExtractTask.SetInputEnabled( false );
  mBloomExtractTask.SetClearEnabled( true );

  // GaussianBlurView tasks must be created here, so they are executed in the correct order with respect to BloomView tasks
  GetImpl(mGaussianBlurView).CreateRenderTasks();

  // Use an image actor displaying the children render and composite it with the blurred bloom buffer, targeting the output
  mCompositeTask = taskList.CreateTask();
  mCompositeTask.SetSourceActor( mCompositeImageActor );
  mCompositeTask.SetExclusive(true);
  mCompositeTask.SetInputEnabled( false );
  mCompositeTask.SetClearEnabled( true );

  mRenderChildrenTask.SetCameraActor(mRenderFullSizeCamera); // use camera that covers render target exactly
  mBloomExtractTask.SetCameraActor(mRenderDownsampledCamera);
  mCompositeTask.SetCameraActor(mRenderFullSizeCamera);

  mRenderChildrenTask.SetTargetFrameBuffer( mRenderTargetForRenderingChildren );
  mBloomExtractTask.SetTargetFrameBuffer( mBloomExtractTarget );
  mCompositeTask.SetTargetFrameBuffer( mOutputRenderTarget );
}

void BloomView::RemoveRenderTasks()
{
  RenderTaskList taskList = Stage::GetCurrent().GetRenderTaskList();

  taskList.RemoveTask(mRenderChildrenTask);
  taskList.RemoveTask(mBloomExtractTask);

  GetImpl(mGaussianBlurView).RemoveRenderTasks();

  taskList.RemoveTask(mCompositeTask);
}

void BloomView::OnStageDisconnection()
{
  // TODO: can't call this here, since SetImage() calls fails similarly to above
  // Need to fix the stage connection so this callback can be used arbitrarily. At that point we  can simplify the API by removing the need for Activate() / Deactivate()
  //Deactivate();
}

void BloomView::OnControlStageConnection()
{
  // TODO: can't call this here, since SetImage() calls fail to connect images to stage, since parent chain not fully on stage yet
  // Need to fix the stage connection so this callback can be used arbitrarily. At that point we  can simplify the API by removing the need for Activate() / Deactivate()
  //Activate();
}

void BloomView::Activate()
{
  // make sure resources are allocated and start the render tasks processing
  AllocateResources();
  CreateRenderTasks();
}

void BloomView::Deactivate()
{
  // stop render tasks processing
  // Note: render target resources are automatically freed since we set the Image::Unused flag
  RemoveRenderTasks();
}

/**
 * EqualToConstraintFloat
 *
 * f(current, property) = property
 */
struct EqualToConstraintFloat
{
  EqualToConstraintFloat(){}

  float operator()(const float current, const PropertyInput& property) {return property.GetFloat();}
};

/**
 * RecipOneMinusConstraint
 *
 * f(current, property) = property
 */
struct RecipOneMinusConstraint
{
  RecipOneMinusConstraint(){}

  float operator()(const float current, const PropertyInput& property)
  {
    return 1.0f / (1.0f - property.GetFloat());
  }
};

// create properties and constraints to tie internal shader etc settings to BloomView object. User can therefore animate / set them via BloomView object without knowing about
// internal implementation classes
void BloomView::SetupProperties()
{
  CustomActor self = Self();


  ///////////////////////////////////////////
  // bloom threshold

  // set defaults, makes sure properties are registered with shader
  mBloomExtractShader.SetUniform( BLOOM_THRESHOLD_PROPERTY_NAME, BLOOM_THRESHOLD_DEFAULT );
  mBloomExtractShader.SetUniform( RECIP_ONE_MINUS_BLOOM_THRESHOLD_PROPERTY_NAME, 1.0f / (1.0f - BLOOM_THRESHOLD_DEFAULT) );

  // Register a property that the user can control to change the bloom threshold
  mBloomThresholdPropertyIndex = self.RegisterProperty(BLOOM_THRESHOLD_PROPERTY_NAME, BLOOM_THRESHOLD_DEFAULT);
  Property::Index shaderBloomThresholdPropertyIndex = mBloomExtractShader.GetPropertyIndex(BLOOM_THRESHOLD_PROPERTY_NAME);
  Constraint bloomThresholdConstraint = Constraint::New<float>(shaderBloomThresholdPropertyIndex, Source(self, mBloomThresholdPropertyIndex), EqualToConstraintFloat());
  mBloomExtractShader.ApplyConstraint(bloomThresholdConstraint);

  // precalc 1.0 / (1.0 - threshold) on CPU to save shader insns, using constraint to tie to the normal threshold property
  Property::Index shaderRecipOneMinusBloomThresholdPropertyIndex = mBloomExtractShader.GetPropertyIndex(RECIP_ONE_MINUS_BLOOM_THRESHOLD_PROPERTY_NAME);
  Constraint thresholdConstraint = Constraint::New<float>( shaderRecipOneMinusBloomThresholdPropertyIndex, LocalSource(shaderBloomThresholdPropertyIndex), RecipOneMinusConstraint());
  mBloomExtractShader.ApplyConstraint(thresholdConstraint);


  ////////////////////////////////////////////
  // bloom strength

  // Register a property that the user can control to fade the blur in / out via internal GaussianBlurView object
  mBlurStrengthPropertyIndex = self.RegisterProperty(BLOOM_BLUR_STRENGTH_PROPERTY_NAME, BLOOM_BLUR_STRENGTH_DEFAULT);
  Constraint blurStrengthConstraint = Constraint::New<float>( mGaussianBlurView.GetBlurStrengthPropertyIndex(), Source(self, mBlurStrengthPropertyIndex), EqualToConstraintFloat());
  mGaussianBlurView.ApplyConstraint(blurStrengthConstraint);


  ////////////////////////////////////////////
  // bloom intensity

  // Register a property that the user can control to fade the bloom intensity via internally hidden shader
  mBloomIntensityPropertyIndex = self.RegisterProperty(BLOOM_INTENSITY_PROPERTY_NAME, BLOOM_INTENSITY_DEFAULT);
  mCompositeShader.SetUniform( BLOOM_INTENSITY_PROPERTY_NAME, BLOOM_INTENSITY_DEFAULT );
  Property::Index shaderBloomIntensityPropertyIndex = mCompositeShader.GetPropertyIndex(BLOOM_INTENSITY_PROPERTY_NAME);
  Constraint bloomIntensityConstraint = Constraint::New<float>( shaderBloomIntensityPropertyIndex, Source(self, mBloomIntensityPropertyIndex), EqualToConstraintFloat());
  mCompositeShader.ApplyConstraint(bloomIntensityConstraint);


  ////////////////////////////////////////////
  // bloom saturation

  // Register a property that the user can control to fade the bloom saturation via internally hidden shader
  mBloomSaturationPropertyIndex = self.RegisterProperty(BLOOM_SATURATION_PROPERTY_NAME, BLOOM_SATURATION_DEFAULT);
  mCompositeShader.SetUniform( BLOOM_SATURATION_PROPERTY_NAME, BLOOM_SATURATION_DEFAULT );
  Property::Index shaderBloomSaturationPropertyIndex = mCompositeShader.GetPropertyIndex(BLOOM_SATURATION_PROPERTY_NAME);
  Constraint bloomSaturationConstraint = Constraint::New<float>( shaderBloomSaturationPropertyIndex, Source(self, mBloomSaturationPropertyIndex), EqualToConstraintFloat());
  mCompositeShader.ApplyConstraint(bloomSaturationConstraint);


  ////////////////////////////////////////////
  // image intensity

  // Register a property that the user can control to fade the image intensity via internally hidden shader
  mImageIntensityPropertyIndex = self.RegisterProperty(IMAGE_INTENSITY_PROPERTY_NAME, IMAGE_INTENSITY_DEFAULT);
  mCompositeShader.SetUniform( IMAGE_INTENSITY_PROPERTY_NAME, IMAGE_INTENSITY_DEFAULT );
  Property::Index shaderImageIntensityPropertyIndex = mCompositeShader.GetPropertyIndex(IMAGE_INTENSITY_PROPERTY_NAME);
  Constraint imageIntensityConstraint = Constraint::New<float>( shaderImageIntensityPropertyIndex, Source(self, mImageIntensityPropertyIndex), EqualToConstraintFloat());
  mCompositeShader.ApplyConstraint(imageIntensityConstraint);


  ////////////////////////////////////////////
  // image saturation

  // Register a property that the user can control to fade the image saturation via internally hidden shader
  mImageSaturationPropertyIndex = self.RegisterProperty(IMAGE_SATURATION_PROPERTY_NAME, IMAGE_SATURATION_DEFAULT);
  mCompositeShader.SetUniform( IMAGE_SATURATION_PROPERTY_NAME, IMAGE_SATURATION_DEFAULT );
  Property::Index shaderImageSaturationPropertyIndex = mCompositeShader.GetPropertyIndex(IMAGE_SATURATION_PROPERTY_NAME);
  Constraint imageSaturationConstraint = Constraint::New<float>( shaderImageSaturationPropertyIndex, Source(self, mImageSaturationPropertyIndex), EqualToConstraintFloat());
  mCompositeShader.ApplyConstraint(imageSaturationConstraint);
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
