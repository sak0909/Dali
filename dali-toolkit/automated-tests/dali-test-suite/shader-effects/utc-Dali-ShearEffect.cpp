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
#include <dali-toolkit/dali-toolkit.h>

#include <dali-toolkit-test-suite-utils.h>

using namespace Dali;

static void Startup();
static void Cleanup();

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

static void UtcDaliShearEffectUninitialized();
static void UtcDaliShearEffectPropertyNames();
static void UtcDaliShearEffectDefaultValues();
static void UtcDaliShearEffectCustomValues();

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

// Add test functionality for all APIs in the class (Positive and Negative)
extern "C" {
  struct tet_testlist tet_testlist[] = {
    { UtcDaliShearEffectUninitialized, NEGATIVE_TC_IDX },
    { UtcDaliShearEffectPropertyNames, POSITIVE_TC_IDX },
    { UtcDaliShearEffectDefaultValues, POSITIVE_TC_IDX },
    { UtcDaliShearEffectCustomValues, POSITIVE_TC_IDX },
    { NULL, 0 }
  };
}

// Called only once before first test is run.
static void Startup()
{
}

// Called only once after last test is run
static void Cleanup()
{
}

// Create bitmap image
BitmapImage CreateBitmapImage()
{
  BitmapImage image = BitmapImage::New(4,4,Pixel::RGBA8888);

  PixelBuffer* pixbuf = image.GetBuffer();

  // Using a 4x4 image gives a better blend with the GL implementation
  // than a 3x3 image
  for(size_t i=0; i<16; i++)
  {
    pixbuf[i*4+0] = 0xFF;
    pixbuf[i*4+1] = 0xFF;
    pixbuf[i*4+2] = 0xFF;
    pixbuf[i*4+3] = 0xFF;
  }

  return image;
}

static void UtcDaliShearEffectUninitialized()
{
  ToolkitTestApplication application;

  Toolkit::ShearEffect effect;

  try
  {
    // New() must be called to create a ShearEffect or it wont be valid.
    effect.SetAngleXAxis( 45.0f );
    DALI_TEST_CHECK( false );
  }
  catch (Dali::DaliException& e)
  {
    // Tests that a negative test of an assertion succeeds
    tet_printf("Assertion %s failed at %s\n", e.mCondition.c_str(), e.mLocation.c_str());
    DALI_TEST_CHECK(!effect);
  }
}

static void UtcDaliShearEffectPropertyNames()
{
  ToolkitTestApplication application;

  Toolkit::ShearEffect effect = Toolkit::ShearEffect::New();

  // Check the names, these names are used in the shaders code,
  // if they change the shader code has to be updated
  DALI_TEST_EQUALS( effect.GetAngleXAxisPropertyName(), "uAngleXAxis", TEST_LOCATION );
  DALI_TEST_EQUALS( effect.GetAngleYAxisPropertyName(), "uAngleYAxis", TEST_LOCATION );
  DALI_TEST_EQUALS( effect.GetCenterPropertyName(), "uCenter", TEST_LOCATION );
}

/**
 * Converts value to screen position in the same way that
 * the core does under COORDINATE_TYPE_SCREEN_POSITION
 *
 * @param[in] value the input position value.
 * @return The translated position value ready for gl.
 */
Vector2 ToScreenPosition(Vector2 value)
{
  Vector2 stageSize = Dali::Stage::GetCurrent().GetSize();
  value.x = stageSize.x * 0.5f - value.x;
  value.y = value.y - stageSize.y * 0.5f;

  return value;
}

static void UtcDaliShearEffectDefaultValues()
{
  ToolkitTestApplication application;

  Toolkit::ShearEffect effect = Toolkit::ShearEffect::New();
  DALI_TEST_CHECK( effect );

  BitmapImage image = CreateBitmapImage();

  ImageActor actor = ImageActor::New( image );
  actor.SetSize( 100.0f, 100.0f );

  const float angleXAxis(0.0f);
  const float angleYAxis(0.0f);
  const Vector2 centerValue(0.0f, 0.0f);

  actor.SetShaderEffect( effect );
  Stage::GetCurrent().Add( actor );

  application.SendNotification();
  application.Render();

  TestGlAbstraction& gl = application.GetGlAbstraction();
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetAngleXAxisPropertyName().c_str(), angleXAxis ) );
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetAngleYAxisPropertyName().c_str(), angleYAxis ) );
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetCenterPropertyName().c_str(), ToScreenPosition(centerValue) ) );
}

static void UtcDaliShearEffectCustomValues()
{
  ToolkitTestApplication application;

  Toolkit::ShearEffect effect = Toolkit::ShearEffect::New();
  DALI_TEST_CHECK( effect );

  BitmapImage image = CreateBitmapImage();

  ImageActor actor = ImageActor::New( image );
  actor.SetSize( 100.0f, 100.0f );

  const float angleXAxis(10.0f);
  const float angleYAxis(22.5f);
  const Vector2 centerValue(50.0f, 100.0f);

  effect.SetAngleXAxis( angleXAxis );
  effect.SetAngleYAxis( angleYAxis );
  effect.SetCenter( centerValue );

  actor.SetShaderEffect(effect);
  Stage::GetCurrent().Add(actor);

  application.SendNotification();
  application.Render();

  TestGlAbstraction& gl = application.GetGlAbstraction();
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetAngleXAxisPropertyName().c_str(), angleXAxis ) );
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetAngleYAxisPropertyName().c_str(), angleYAxis ) );
  DALI_TEST_CHECK( gl.CheckUniformValue( effect.GetCenterPropertyName().c_str(), ToScreenPosition(centerValue) ) );
}
