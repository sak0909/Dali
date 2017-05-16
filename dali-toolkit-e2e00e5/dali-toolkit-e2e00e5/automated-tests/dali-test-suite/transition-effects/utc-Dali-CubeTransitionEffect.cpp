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

#include <iostream>

#include <stdlib.h>
#include <tet_api.h>

#include <dali/public-api/dali-core.h>

#include <dali-toolkit/public-api/transition-effects/cube-transition-effect.h>
#include <dali-toolkit/public-api/transition-effects/cube-transition-wave-effect.h>
#include <dali-toolkit/public-api/transition-effects/cube-transition-cross-effect.h>
#include <dali-toolkit/public-api/transition-effects/cube-transition-fold-effect.h>

#include <dali-toolkit-test-suite-utils.h>

using namespace Dali;
using namespace Dali::Toolkit;

static void Startup();
static void Cleanup();

namespace
{
const unsigned int NUM_ROWS = 16;
const unsigned int NUM_COLUMNS = 10;
const Vector2 VIEW_AREA_SIZE( 480.0f, 800.0f );
const float TRANSITION_DURATION = 0.5f;
const float CUBE_DISPLACEMENT = 55.f;
const Vector2 PAN_POSITION1( VIEW_AREA_SIZE.x * 0.75f, VIEW_AREA_SIZE.y * 0.25f );
const Vector2 PAN_DISPLACEMENT1( -5.f, 5.f );
const Vector2 PAN_POSITION2( VIEW_AREA_SIZE.x * 0.25f, VIEW_AREA_SIZE.y * 0.75f );
const Vector2 PAN_DISPLACEMENT2( 5.f, 5.f );
const int RENDER_FRAME_INTERVAL = 16;
static const float ROTATION_EPSILON = 0.0001f;
const float OFFSCREEN_RENDER_DURATION = 0.05f;

static bool gObjectCreatedCallBackCalled;
static void TestCallback(BaseHandle handle)
{
  gObjectCreatedCallBackCalled = true;
}

/**
 * Simulate time passed by, waiting for certain process to finish
 * @param[in] application Test application instance
 * @param[in] durationToPass Time to pass in milliseconds.
 */
void Wait(ToolkitTestApplication& application, float durationToPass)
{
  int duration = static_cast<int>(durationToPass*1000.f);
  // wait 2 more frames to compensate the two frames used by the bitmapImage waiting for the loading succeeded signal
  for(int i = 0; i <=  duration/RENDER_FRAME_INTERVAL+2 ; i++)
  {
    application.SendNotification();
    application.Render(RENDER_FRAME_INTERVAL);
  }
}


ImageActor CreateSolidColorImageActor( ToolkitTestApplication& application, const Vector4& color, unsigned int width, unsigned int height )
{
  BitmapImage imageData = BitmapImage::New( width, height, Pixel::RGBA8888 );
  ImageActor imageActor = ImageActor::New( imageData );
  Stage::GetCurrent().Add( imageActor );

  // Create the image
  PixelBuffer* pixbuf = imageData.GetBuffer();
  unsigned int size = width * height;

  for( size_t i = 0; i < size; i++ )
    {
      pixbuf[i*4+0] = 0xFF * color.r;
      pixbuf[i*4+1] = 0xFF * color.g;
      pixbuf[i*4+2] = 0xFF * color.b;
      pixbuf[i*4+3] = 0xFF * color.a;
    }
  imageData.Update();

  application.GetGlAbstraction().SetCheckFramebufferStatusResult(GL_FRAMEBUFFER_COMPLETE );
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();

  return imageActor;
}

//Callback class to test whether transition completed signal is emitted when the transition animation is finished
class TransitionCompletedCallback : public Dali::ConnectionTracker
{
public:
  TransitionCompletedCallback( bool& signalReceived, CubeTransitionEffect& effect, ImageActor& imageActor )
  : mSignalVerified( signalReceived ),
    mCurrentEffect( effect ),
    mActorTransitTo( imageActor )
  {
  }

  void Callback( CubeTransitionEffect effect, ImageActor imageActor )
  {
    tet_infoline( "Verifying TransitionCompletedSignal" );

    if( mCurrentEffect == effect && mActorTransitTo == imageActor )
    {
      mSignalVerified = true;
    }
  }

  void Reset()
  {
    mSignalVerified = false;
  }

  bool&                  mSignalVerified;
  CubeTransitionEffect&  mCurrentEffect;
  ImageActor&            mActorTransitTo;
};

} // namespace

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

#define MAX_NUMBER_OF_TESTS 10000
extern "C" {
  struct tet_testlist tet_testlist[MAX_NUMBER_OF_TESTS];
}

// Add test functionality for all APIs in the class (Positive and Negative)
TEST_FUNCTION( UtcDaliCubeTransitionWaveEffectNew,                       POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionCrossEffectNew,                      POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionFoldEffectNew,                       POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectSetGetTransitionDuration,      POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectSetGetCubeDisplacement,        POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectGetRoot,                       POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectIsTransiting,                  POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectSetCurrentImage,               POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectSetTargetImage,                POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionWaveEffectStartTransition,           POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionCrossEffectStartTransition,          POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionFoldEffectStartTransition,           POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectSignalTransitionCompleted,     POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionEffectPauseResumeTransition,         POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionWaveEffectStopTransition,            POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionCrossEffectStopTransition,           POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliCubeTransitionFoldEffectStopTransition,            POSITIVE_TC_IDX );


// Called only once before first test is run.
static void Startup()
{
}

// Called only once after last test is run
static void Cleanup()
{
}

static void UtcDaliCubeTransitionWaveEffectNew()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionWaveEffectNew ");

  CubeTransitionEffect waveEffect;

  DALI_TEST_CHECK( !waveEffect );

  waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );

  DALI_TEST_CHECK( waveEffect );

  waveEffect = NULL;

  //Additional check to ensure object is created by checking if it's registered
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );

  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect( &TestCallback );
  {
    CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
}

static void UtcDaliCubeTransitionCrossEffectNew()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionCrossEffectNew ");

  CubeTransitionEffect crossEffect;

  DALI_TEST_CHECK( !crossEffect );

  crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );

  DALI_TEST_CHECK( crossEffect );

  crossEffect = NULL;

  //Additional check to ensure object is created by checking if it's registered
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );

  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect( &TestCallback );
  {
    CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
}

static void UtcDaliCubeTransitionFoldEffectNew()
{
  ToolkitTestApplication application;
  tet_infoline( " UtcDaliCubeTransitionFoldEffectNew " );

  CubeTransitionEffect foldEffect;

  DALI_TEST_CHECK( !foldEffect );

  foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );

  DALI_TEST_CHECK( foldEffect );

  foldEffect = NULL;

  //Additional check to ensure object is created by checking if it is registered
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );

  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect( &TestCallback );
  {
    CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
}

static void UtcDaliCubeTransitionEffectSetGetTransitionDuration()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectSetGetTransitionDuration ");

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  DALI_TEST_EQUALS( TRANSITION_DURATION, waveEffect.GetTransitionDuration(), TEST_LOCATION );

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  DALI_TEST_EQUALS( TRANSITION_DURATION, crossEffect.GetTransitionDuration(), TEST_LOCATION );

  CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  DALI_TEST_EQUALS( TRANSITION_DURATION, foldEffect.GetTransitionDuration(), TEST_LOCATION );
}

static void UtcDaliCubeTransitionEffectSetGetCubeDisplacement()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectSetGetTransitionDuration ");

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  DALI_TEST_EQUALS( CUBE_DISPLACEMENT, waveEffect.GetCubeDisplacement(), TEST_LOCATION );

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  DALI_TEST_EQUALS( CUBE_DISPLACEMENT, crossEffect.GetCubeDisplacement(), TEST_LOCATION );

  //Cube displacement is not used in CubeTransitionFoldEffect
}

//Test common codes in base class
static void UtcDaliCubeTransitionEffectGetRoot()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectGetRoot ");

  unsigned int totalNum = NUM_ROWS*NUM_COLUMNS;

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  Actor rootActor = waveEffect.GetRoot();

  // check that we have a total of NUM_ROWS*NUM_COLUMNS cubes;
  DALI_TEST_CHECK( totalNum == rootActor.GetChildCount() );

  // check that every cube has two children
  DALI_TEST_CHECK( 2 == rootActor.GetChildAt(0).GetChildCount() );
  DALI_TEST_CHECK( 2 == rootActor.GetChildAt(totalNum/2).GetChildCount() );
  DALI_TEST_CHECK( 2 == rootActor.GetChildAt(totalNum-1).GetChildCount() );
}

static void UtcDaliCubeTransitionEffectIsTransiting()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectIsTransiting ");

  ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,30,30);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  DALI_TEST_CHECK( !waveEffect.IsTransiting() );

  waveEffect.SetCurrentImage(imageActor);
  waveEffect.SetTargetImage(imageActor);
  //transition is started
  waveEffect.StartTransition();
  DALI_TEST_CHECK( waveEffect.IsTransiting() );
  //transition is finished
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK( !waveEffect.IsTransiting() );

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  DALI_TEST_CHECK( !crossEffect.IsTransiting() );

  crossEffect.SetCurrentImage(imageActor);
  crossEffect.SetTargetImage(imageActor);
  //transition is started
  crossEffect.StartTransition(false);
  DALI_TEST_CHECK( crossEffect.IsTransiting() );
  //transition is finished
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK( !crossEffect.IsTransiting() );

  CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  DALI_TEST_CHECK( !foldEffect.IsTransiting() );

  foldEffect.SetCurrentImage( imageActor );
  foldEffect.SetTargetImage( imageActor );
  //transition is started
  foldEffect.StartTransition(true);
  DALI_TEST_CHECK(foldEffect.IsTransiting() );
  //transition is finished
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK( !foldEffect.IsTransiting() );

}

//Test common codes in base class
static void UtcDaliCubeTransitionEffectSetCurrentImage()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectSetCurrentImage ");

  ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,40,40) ;

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetCurrentImage( imageActor );

  // the current image content is set to the tiles facing the camera
  ImageActor tile = ImageActor::DownCast( (waveEffect.GetRoot().GetChildAt(0).GetChildAt(0)));

  //check the pixel area set to the cube
  ImageActor::PixelArea pixelAreaDef( 0, 0, VIEW_AREA_SIZE.x / NUM_COLUMNS, VIEW_AREA_SIZE.y / NUM_ROWS);
  ImageActor::PixelArea pixelArea = tile.GetPixelArea();
  DALI_TEST_CHECK ( pixelAreaDef == pixelArea );

  //check the size of the off screen rendered image
  Wait( application, OFFSCREEN_RENDER_DURATION );
  ImageAttributes attributes( tile.GetImage().GetAttributes() );
  DALI_TEST_EQUALS( static_cast<float>(attributes.GetWidth()), VIEW_AREA_SIZE.x, TEST_LOCATION  );
  DALI_TEST_EQUALS( static_cast<float>(attributes.GetHeight()), VIEW_AREA_SIZE.y, TEST_LOCATION  );
}

//Test common codes in base class
static void UtcDaliCubeTransitionEffectSetTargetImage()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectSetTargetImage ");

 ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,30,30);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  waveEffect.SetCurrentImage( imageActor );
  waveEffect.SetTargetImage( imageActor );

  // the target image content is set to the tiles currently invisible to the camera
  ImageActor tile = ImageActor::DownCast( (rootActor.GetChildAt(0).GetChildAt(1)));

  //check the pixel area set to the cube
  ImageActor::PixelArea pixelAreaDef( 0, 0, VIEW_AREA_SIZE.x / NUM_COLUMNS, VIEW_AREA_SIZE.y / NUM_ROWS);
  ImageActor::PixelArea pixelArea = tile.GetPixelArea();
  DALI_TEST_CHECK ( pixelAreaDef == pixelArea );

  //check the size of the off screen rendered image
  Wait( application, OFFSCREEN_RENDER_DURATION );
  ImageAttributes attributes( tile.GetImage().GetAttributes() );
  DALI_TEST_EQUALS( static_cast<float>(attributes.GetWidth()), VIEW_AREA_SIZE.x, TEST_LOCATION  );
  DALI_TEST_EQUALS( static_cast<float>(attributes.GetHeight()), VIEW_AREA_SIZE.y, TEST_LOCATION  );
}

static void UtcDaliCubeTransitionWaveEffectStartTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionWaveEffectStartTransition ");

  ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,30,30);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  Actor cube = rootActor.GetChildAt(0);

  waveEffect.SetCurrentImage( imageActor );

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation value and color values after different transitions
  waveEffect.SetTargetImage( imageActor );
  waveEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == fullBrightness );

  waveEffect.SetTargetImage( imageActor );
  waveEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == halfBrightness );

  waveEffect.SetTargetImage( imageActor );
  waveEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == fullBrightness );

  waveEffect.SetTargetImage( imageActor );
  waveEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == halfBrightness );
}

static void UtcDaliCubeTransitionCrossEffectStartTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionCrossEffectStartTransition ");

  ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,30,30);

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = crossEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  crossEffect.SetCurrentImage( imageActor );
  Actor cube0 = rootActor.GetChildAt(0);
  Actor cube1 = rootActor.GetChildAt(1);

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation values and color values after different transitions
  crossEffect.SetTargetImage( imageActor );
  crossEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  crossEffect.SetTargetImage( imageActor );
  crossEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 2.f*Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );


  crossEffect.SetTargetImage( imageActor );
  crossEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  crossEffect.SetTargetImage( imageActor );
  crossEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 0.f,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );
}

static void UtcDaliCubeTransitionFoldEffectStartTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionFoldEffectStartTransition ");

  ImageActor imageActor = CreateSolidColorImageActor(application, Color::BLUE,30,30);

  CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  Actor rootActor = foldEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  foldEffect.SetCurrentImage( imageActor );
  Actor cube0 = rootActor.GetChildAt(0);
  Actor cube1 = rootActor.GetChildAt(1);

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation values and color values after different transitions
  foldEffect.SetTargetImage( imageActor );
  foldEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  foldEffect.SetTargetImage( imageActor );
  foldEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );


  foldEffect.SetTargetImage( imageActor );
  foldEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  foldEffect.SetTargetImage( imageActor );
  foldEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );
}

static void UtcDaliCubeTransitionEffectSignalTransitionCompleted()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectSignalTransitionCompleted ");

  ImageActor firstImageActor = CreateSolidColorImageActor(application, Color::RED,30,30);
  ImageActor secondImageActor = CreateSolidColorImageActor(application, Color::GREEN,20,20);
  ImageActor thirdImageActor = CreateSolidColorImageActor(application, Color::BLUE,40,40);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  rootActor = crossEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  CubeTransitionEffect foldEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  rootActor = foldEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  bool signalVerified = false;
  CubeTransitionEffect currentEffect;
  ImageActor actorTransitTo;
  TransitionCompletedCallback callback(signalVerified, currentEffect, actorTransitTo);
  waveEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );
  crossEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );
  foldEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );

  //check that the wave effect is used to transit to secondImageActor
  currentEffect = waveEffect;
  actorTransitTo = secondImageActor;
  waveEffect.SetCurrentImage( firstImageActor );
  waveEffect.SetTargetImage( secondImageActor );
  waveEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  //check that the wave effect is used to transit to thirdImageActor
  actorTransitTo = thirdImageActor;
  waveEffect.SetTargetImage( thirdImageActor );
  waveEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  //check that the cross effect is used to transit to secondImageActor
  currentEffect = crossEffect;
  actorTransitTo = secondImageActor;
  crossEffect.SetCurrentImage( thirdImageActor );
  crossEffect.SetTargetImage( secondImageActor );
  crossEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  //check that the cross effect is used to transit to firstImageActor
  actorTransitTo = firstImageActor;
  crossEffect.SetTargetImage( firstImageActor );
  crossEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  //check that the fold effect is used to transit to secondImageActor
  currentEffect = foldEffect;
  actorTransitTo = secondImageActor;
  foldEffect.SetCurrentImage( firstImageActor );
  foldEffect.SetTargetImage( secondImageActor );
  foldEffect.StartTransition();
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK( callback.mSignalVerified );
  callback.Reset();

  //check that the fold effect is used to transit to thirdImageActor
  actorTransitTo = thirdImageActor;
  foldEffect.SetTargetImage( thirdImageActor );
  foldEffect.StartTransition( false );
  Wait( application, TRANSITION_DURATION );
  DALI_TEST_CHECK( callback.mSignalVerified );
}

static void UtcDaliCubeTransitionEffectPauseResumeTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionEffectPauseResumeTransition ");

  ImageActor firstImageActor = CreateSolidColorImageActor(application, Color::RED,30,30);
  ImageActor secondImageActor = CreateSolidColorImageActor(application, Color::GREEN,20,20);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  rootActor = crossEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  rootActor = crossEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );

  bool signalVerified = false;
  CubeTransitionEffect currentEffect;
  ImageActor actorTransitTo;
  TransitionCompletedCallback callback(signalVerified, currentEffect, actorTransitTo);
  waveEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );
  crossEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );
  foldEffect.TransitionCompletedSignal().Connect( &callback, &TransitionCompletedCallback::Callback );

  currentEffect = waveEffect;
  actorTransitTo = secondImageActor;
  waveEffect.SetCurrentImage( firstImageActor );
  waveEffect.SetTargetImage( secondImageActor );
  // start transition; transit for 0.5*duration; pause for 0.5*duration;
  // resume for 0.25*duration; pause for 0.25*duration; resume for another 0.25*duration;
  // only until now the transition finished signal can be received
  waveEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION*0.5f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  waveEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.5f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  waveEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  waveEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  waveEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  currentEffect = crossEffect;
  actorTransitTo = firstImageActor;
  crossEffect.SetCurrentImage( secondImageActor );
  crossEffect.SetTargetImage( firstImageActor );
  // start transition; transit for 0.25*duration; pause for 0.2*duration;
  // resume for 0.5*duration; pause for 0.2*duration; resume for another 0.25*duration;
  // only until now the transition finished signal can be received
  crossEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  crossEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.2f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  crossEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.5f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  crossEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.2f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  crossEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(callback.mSignalVerified);
  callback.Reset();

  currentEffect = foldEffect;
  actorTransitTo = secondImageActor;
  foldEffect.SetCurrentImage( firstImageActor );
  foldEffect.SetTargetImage( secondImageActor );
  // start transition; transit for 0.5*duration; pause for 0.5*duration;
  // resume for 0.25*duration; pause for 0.25*duration; resume for another 0.25*duration;
  // only until now the transition finished signal can be received
  foldEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION*0.5f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  foldEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.5f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  foldEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  foldEffect.PauseTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(!callback.mSignalVerified);
  foldEffect.ResumeTransition();
  Wait( application, TRANSITION_DURATION*0.25f );
  DALI_TEST_CHECK(callback.mSignalVerified);
}

static void UtcDaliCubeTransitionWaveEffectStopTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionWaveEffectStopTransition ");

  ImageActor firstImageActor = CreateSolidColorImageActor(application, Color::RED,30,30);
  ImageActor secondImageActor = CreateSolidColorImageActor(application, Color::GREEN,20,20);

  CubeTransitionEffect waveEffect = CubeTransitionWaveEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  waveEffect.SetTransitionDuration( TRANSITION_DURATION );
  waveEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = waveEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  Actor cube = rootActor.GetChildAt(0);
  waveEffect.SetCurrentImage( firstImageActor );

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation value and color values after stopping different transitions in the middle
  waveEffect.SetTargetImage( secondImageActor );
  waveEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION*0.2f );
  waveEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == fullBrightness );

  waveEffect.SetTargetImage( firstImageActor );
  waveEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION*0.4f );
  waveEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == halfBrightness );

  waveEffect.SetTargetImage( secondImageActor );
  waveEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION*0.6f );
  waveEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == fullBrightness );

  waveEffect.SetTargetImage( firstImageActor );
  waveEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION*0.8f );
  waveEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube.GetChildAt(1).GetCurrentColor() == halfBrightness );
}

static void UtcDaliCubeTransitionCrossEffectStopTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionCrossEffectStopTransition ");

  ImageActor firstImageActor = CreateSolidColorImageActor(application, Color::RED,30,30);
  ImageActor secondImageActor = CreateSolidColorImageActor(application, Color::GREEN,20,20);

  CubeTransitionEffect crossEffect = CubeTransitionCrossEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  crossEffect.SetTransitionDuration( TRANSITION_DURATION );
  crossEffect.SetCubeDisplacement( CUBE_DISPLACEMENT );
  Actor rootActor = crossEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  crossEffect.SetCurrentImage( firstImageActor );
  Actor cube0 = rootActor.GetChildAt(0);
  Actor cube1 = rootActor.GetChildAt(1);

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation values and color values after stop the different transitions in the middle
  crossEffect.SetTargetImage( secondImageActor );
  crossEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION*0.2f );
  crossEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );

  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  crossEffect.SetTargetImage( firstImageActor );
  crossEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION*0.4f );
  crossEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 2.f*Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );

  crossEffect.SetTargetImage( secondImageActor );
  crossEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION*0.6f );
  crossEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  crossEffect.SetTargetImage( firstImageActor );
  crossEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION*0.8f );
  crossEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 0.f,  Vector3::XAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );
}

static void UtcDaliCubeTransitionFoldEffectStopTransition()
{
  ToolkitTestApplication application;
  tet_infoline(" UtcDaliCubeTransitionFoldEffectStopTransition ");

  ImageActor firstImageActor = CreateSolidColorImageActor(application, Color::RED,30,30);
  ImageActor secondImageActor = CreateSolidColorImageActor(application, Color::GREEN,20,20);

  CubeTransitionEffect foldEffect = CubeTransitionFoldEffect::New( NUM_ROWS, NUM_COLUMNS, VIEW_AREA_SIZE );
  foldEffect.SetTransitionDuration( TRANSITION_DURATION );
  Actor rootActor = foldEffect.GetRoot();
  Stage::GetCurrent().Add( rootActor );
  foldEffect.SetCurrentImage( firstImageActor );
  Actor cube0 = rootActor.GetChildAt(0);
  Actor cube1 = rootActor.GetChildAt(1);

  Vector4 fullBrightness = Vector4(1.f,1.f,1.f,1.f);
  Vector4 halfBrightness = Vector4(0.5f, 0.5f, 0.5f, 1.f);

  //check the cube rotation values and color values after stop the different transitions in the middle
  foldEffect.SetTargetImage( secondImageActor );
  foldEffect.StartTransition(true);
  Wait( application, TRANSITION_DURATION*0.2f );
  foldEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  foldEffect.SetTargetImage( firstImageActor );
  foldEffect.StartTransition(PAN_POSITION1, PAN_DISPLACEMENT1);
  Wait( application, TRANSITION_DURATION*0.4f );
  foldEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 2.f*Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );

  foldEffect.SetTargetImage( secondImageActor );
  foldEffect.StartTransition(false);
  Wait( application, TRANSITION_DURATION*0.6f );
  foldEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( -Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( Math::PI_2,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == halfBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == fullBrightness );

  foldEffect.SetTargetImage( firstImageActor );
  foldEffect.StartTransition(PAN_POSITION2, PAN_DISPLACEMENT2);
  Wait( application, TRANSITION_DURATION*0.8f );
  foldEffect.StopTransition();
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  DALI_TEST_EQUALS( cube1.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_EQUALS( cube0.GetCurrentRotation(), Quaternion( 0.f,  Vector3::YAXIS), ROTATION_EPSILON, TEST_LOCATION  );
  DALI_TEST_CHECK( cube0.GetChildAt(0).GetCurrentColor() == fullBrightness );
  DALI_TEST_CHECK( cube0.GetChildAt(1).GetCurrentColor() == halfBrightness );
}
