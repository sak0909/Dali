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

#include <dali/integration-api/events/touch-event-integ.h>
#include <dali-test-suite-utils.h>

using namespace Dali;
using namespace std;

static void Startup();
static void Cleanup();

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

static const char* TestTextHelloWorld = "Hello World";

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

#define MAX_NUMBER_OF_TESTS 10000
extern "C" {
  struct tet_testlist tet_testlist[MAX_NUMBER_OF_TESTS];
}

// Add test functionality for all APIs in the class (Positive and Negative)
TEST_FUNCTION( UtcDaliRenderableActorDownCast,            POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetSortModifier,     POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorGetSortModifier,     POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetGetBlendMode,     POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetCullFace,         POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorGetCullFace,         POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetGetBlendFunc,     POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetGetBlendEquation, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetGetBlendColor,    POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorSetGetAlpha,         POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliRenderableActorCreateDestroy,       POSITIVE_TC_IDX );

// Called only once before first test is run.
static void Startup()
{
  // THERE IS NO MAINLOOP IN THE TEST APPLICATION
}

// Called only once after last test is run
static void Cleanup()
{
}


static void UtcDaliRenderableActorDownCast()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::DownCast()");

  TextActor textActor = TextActor::New(TestTextHelloWorld);

  Actor anActor = Actor::New();
  anActor.Add( textActor );

  Actor child = anActor.GetChildAt(0);
  RenderableActor renderableActor = RenderableActor::DownCast( child );
  DALI_TEST_CHECK( renderableActor );

  renderableActor = NULL;
  DALI_TEST_CHECK( !renderableActor );

  renderableActor = DownCast< RenderableActor >( child );
  DALI_TEST_CHECK( renderableActor );

  renderableActor = DownCast< RenderableActor >( anActor );
  DALI_TEST_CHECK( !renderableActor );

  Actor unInitialzedActor;
  renderableActor = RenderableActor::DownCast( unInitialzedActor );
  DALI_TEST_CHECK( !renderableActor );

  renderableActor = DownCast< RenderableActor >( unInitialzedActor );
  DALI_TEST_CHECK( !renderableActor );
}

static bool gIsActor1SortModifierCorrect;
static bool gIsActor2SortModifierCorrect;
const float gActor1SortModifierValue = 96.0f;
const float gActor2SortModifierValue = 53.0f;

static float TestSortFunction(const Vector3& position, float sortModifier)
{
  if ( fabs(sortModifier - gActor1SortModifierValue) < 0.01)
    gIsActor1SortModifierCorrect = true;

  if ( fabs(sortModifier - gActor2SortModifierValue) < 0.01)
    gIsActor2SortModifierCorrect = true;

  return 0.0f;
}

static void UtcDaliRenderableActorSetSortModifier()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::SetSortModifier()");

  float val = -500.0f;

  TextActor actor = TextActor::New(TestTextHelloWorld);
  Stage::GetCurrent().Add(actor);

  actor.SetSortModifier( val );

  float returnValue = actor.GetSortModifier();

  //Verify through actor api
  DALI_TEST_EQUALS(returnValue, val, TEST_LOCATION);

  Stage::GetCurrent().Remove(actor);


  //Verify through layer SetSortFunction
  gIsActor1SortModifierCorrect = false;
  gIsActor2SortModifierCorrect = false;
  BitmapImage img = BitmapImage::New( 1,1 );
  // create two transparent actors so there is something to sort
  ImageActor actor1 = ImageActor::New( img );
  ImageActor actor2 = ImageActor::New( img );
  actor1.SetSize(1,1);
  actor1.SetPosition( 0, 0, 0);
  actor1.SetSortModifier( gActor1SortModifierValue );
  actor1.SetColor( Vector4(1, 1, 1, 0.5f ) ); // 50% transparent
  actor2.SetSize(1,1);
  actor2.SetPosition( 0, 0, 1);
  actor2.SetSortModifier( gActor2SortModifierValue );
  actor2.SetColor( Vector4(1, 1, 1, 0.5f ) ); // 50% transparent

  // add to stage
   Stage::GetCurrent().Add( actor1 );
   Stage::GetCurrent().Add( actor2 );

   Layer root = Stage::GetCurrent().GetLayer( 0 );
   root.SetSortFunction( TestSortFunction );

   // flush the queue and render once
   application.SendNotification();
   application.Render();

   DALI_TEST_CHECK( gIsActor1SortModifierCorrect && gIsActor2SortModifierCorrect );
}

static void UtcDaliRenderableActorGetSortModifier()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::GetSortModifier()");

  TextActor actor = TextActor::New(TestTextHelloWorld);
  Stage::GetCurrent().Add(actor);

  DALI_TEST_EQUALS(actor.GetSortModifier(), 0.0f, TEST_LOCATION);

  Stage::GetCurrent().Remove(actor);
}

static void UtcDaliRenderableActorSetGetBlendMode()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::SetBlendMode() / Dali::RenderableActor::GetBlendMode()");

  TextActor actor = TextActor::New(TestTextHelloWorld);

  actor.SetBlendMode( BlendingMode::OFF );
  DALI_TEST_CHECK( BlendingMode::OFF == actor.GetBlendMode() );

  actor.SetBlendMode( BlendingMode::AUTO );
  DALI_TEST_CHECK( BlendingMode::AUTO == actor.GetBlendMode() );

  actor.SetBlendMode( BlendingMode::ON );
  DALI_TEST_CHECK( BlendingMode::ON == actor.GetBlendMode() );
}

static void UtcDaliRenderableActorSetCullFace()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::SetCullFace()");

  BitmapImage img = BitmapImage::New( 1,1 );
  ImageActor actor = ImageActor::New( img );
  ImageActor actor2 = ImageActor::New( img );

  actor.SetSize(100.0f, 100.0f);
  actor.SetParentOrigin(ParentOrigin::CENTER);
  actor.SetAnchorPoint(AnchorPoint::CENTER);

  actor2.SetSize(100.0f, 100.0f);
  actor2.SetParentOrigin(ParentOrigin::CENTER);
  actor2.SetAnchorPoint(AnchorPoint::CENTER);

  Stage::GetCurrent().Add(actor);
  Stage::GetCurrent().Add(actor2);

  //Verify whether the correct GL calls are made when actor is face culled in front and back, and
  // face culling is disabled for actor2
  TraceCallStack& cullFaceTrace = application.GetGlAbstraction().GetCullFaceTrace();
  cullFaceTrace.Enable(true);
  actor.SetCullFace( CullFrontAndBack );

  // flush the queue and render once
  application.SendNotification();
  application.Render();

  cullFaceTrace.Enable(false);
  std::stringstream out;

  //Verify actor gl state
  out.str("");
  out << GL_BLEND;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(0, "Enable", out.str()), true, TEST_LOCATION);

  out.str("");
  out << GL_CULL_FACE;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(1, "Enable", out.str()), true, TEST_LOCATION);

  out.str("");
  out << GL_FRONT_AND_BACK;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(2, "CullFace", out.str()), true, TEST_LOCATION);

  //Verify actor2 gl state
  out.str("");
  out << GL_CULL_FACE;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(3, "Disable", out.str()), true, TEST_LOCATION);

  //Verify state through the actor api
  DALI_TEST_CHECK( CullFrontAndBack == actor.GetCullFace() );
  DALI_TEST_CHECK( CullNone == actor2.GetCullFace() );

  /**************************************************************/

  //Verify whether the correct GL calls are made when actor2 is face culled in the front
  cullFaceTrace.Reset();
  cullFaceTrace.Enable(true);
  actor2.SetCullFace( CullFront );

  // flush the queue and render once
  application.SendNotification();
  application.Render();

  cullFaceTrace.Enable(false);

  //Verify actor gl state
  out.str("");
  out << GL_CULL_FACE;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(0, "Enable", out.str()), true, TEST_LOCATION);

  out.str("");
  out << GL_FRONT_AND_BACK;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(1, "CullFace", out.str()), true, TEST_LOCATION);

  //Verify actor2 gl state
  out.str("");
  out << GL_CULL_FACE;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(2, "Enable", out.str()), true, TEST_LOCATION);

  out.str("");
  out << GL_FRONT;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(3, "CullFace", out.str()), true, TEST_LOCATION);

  //Verify state through the actor api
  DALI_TEST_CHECK( CullFrontAndBack == actor.GetCullFace() );
  DALI_TEST_CHECK( CullFront == actor2.GetCullFace() );

  /**************************************************************/
  //Verify whether the correct GL calls are made when face culling is disabled for both actors
  cullFaceTrace.Reset();
  cullFaceTrace.Enable(true);
  actor.SetCullFace( CullNone );
  actor2.SetCullFace( CullNone );

  // flush the queue and render once
  application.SendNotification();
  application.Render();

  cullFaceTrace.Enable(false);

  out.str("");
  out << GL_CULL_FACE;
  DALI_TEST_EQUALS( cullFaceTrace.TestMethodAndParams(0, "Disable", out.str()), true, TEST_LOCATION);

  //Verify state through the actor api
  DALI_TEST_CHECK( CullNone == actor.GetCullFace() );
  DALI_TEST_CHECK( CullNone == actor2.GetCullFace() );

  Stage::GetCurrent().Remove(actor);
  Stage::GetCurrent().Remove(actor2);
}

static void UtcDaliRenderableActorGetCullFace()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::GetCullFace()");

  TextActor textActor = TextActor::New(TestTextHelloWorld);

  DALI_TEST_CHECK( CullNone == textActor.GetCullFace() );

  ImageActor imageActor = ImageActor::New();

  DALI_TEST_CHECK( CullNone == imageActor.GetCullFace() );

  MeshActor meshActor = MeshActor::New();

  DALI_TEST_CHECK( CullBack == meshActor.GetCullFace() );
}

static void UtcDaliRenderableActorSetGetBlendFunc()
{
  TestApplication application;
  TestGlAbstraction& glAbstraction = application.GetGlAbstraction();

  tet_infoline("Testing Dali::RenderableActor::UtcDaliRenderableActorSetGetBlendFunc()");

  BitmapImage img = BitmapImage::New( 1,1 );
  ImageActor actor = ImageActor::New( img );
  Stage::GetCurrent().Add( actor );
  application.SendNotification();
  application.Render();

  // Test the defaults as documented int blending.h
  {
    BlendingFactor::Type srcFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type srcFactorAlpha( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorAlpha( BlendingFactor::ZERO );
    actor.GetBlendFunc( srcFactorRgb, destFactorRgb, srcFactorAlpha, destFactorAlpha );
    DALI_TEST_EQUALS( BlendingFactor::SRC_ALPHA,           srcFactorRgb,    TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_SRC_ALPHA, destFactorRgb,   TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE,                 srcFactorAlpha,  TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_SRC_ALPHA, destFactorAlpha, TEST_LOCATION );
  }

  // Set to non-default values
  actor.SetBlendFunc( BlendingFactor::ONE_MINUS_SRC_COLOR, BlendingFactor::SRC_ALPHA_SATURATE );

  // Test that Set was successful
  {
    BlendingFactor::Type srcFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type srcFactorAlpha( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorAlpha( BlendingFactor::ZERO );
    actor.GetBlendFunc( srcFactorRgb, destFactorRgb, srcFactorAlpha, destFactorAlpha );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_SRC_COLOR, srcFactorRgb,    TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::SRC_ALPHA_SATURATE,  destFactorRgb,   TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_SRC_COLOR, srcFactorAlpha,  TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::SRC_ALPHA_SATURATE,  destFactorAlpha, TEST_LOCATION );
  }

  // Render & check GL commands
  application.SendNotification();
  application.Render();
  DALI_TEST_EQUALS( (GLenum)GL_ONE_MINUS_SRC_COLOR, glAbstraction.GetLastBlendFuncSrcRgb(),   TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_SRC_ALPHA_SATURATE,  glAbstraction.GetLastBlendFuncDstRgb(),   TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_ONE_MINUS_SRC_COLOR, glAbstraction.GetLastBlendFuncSrcAlpha(), TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_SRC_ALPHA_SATURATE,  glAbstraction.GetLastBlendFuncDstAlpha(), TEST_LOCATION );

  // Set using separate alpha settings
  actor.SetBlendFunc( BlendingFactor::CONSTANT_COLOR, BlendingFactor::ONE_MINUS_CONSTANT_COLOR,
                      BlendingFactor::CONSTANT_ALPHA, BlendingFactor::ONE_MINUS_CONSTANT_ALPHA );

  // Test that Set was successful
  {
    BlendingFactor::Type srcFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorRgb( BlendingFactor::ZERO );
    BlendingFactor::Type srcFactorAlpha( BlendingFactor::ZERO );
    BlendingFactor::Type destFactorAlpha( BlendingFactor::ZERO );
    actor.GetBlendFunc( srcFactorRgb, destFactorRgb, srcFactorAlpha, destFactorAlpha );
    DALI_TEST_EQUALS( BlendingFactor::CONSTANT_COLOR,            srcFactorRgb,    TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_CONSTANT_COLOR,  destFactorRgb,   TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::CONSTANT_ALPHA,            srcFactorAlpha,  TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingFactor::ONE_MINUS_CONSTANT_ALPHA,  destFactorAlpha, TEST_LOCATION );
  }

  // Render & check GL commands
  application.SendNotification();
  application.Render();
  DALI_TEST_EQUALS( (GLenum)GL_CONSTANT_COLOR,           glAbstraction.GetLastBlendFuncSrcRgb(),   TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_ONE_MINUS_CONSTANT_COLOR, glAbstraction.GetLastBlendFuncDstRgb(),   TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_CONSTANT_ALPHA,           glAbstraction.GetLastBlendFuncSrcAlpha(), TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_ONE_MINUS_CONSTANT_ALPHA, glAbstraction.GetLastBlendFuncDstAlpha(), TEST_LOCATION );
}

static void UtcDaliRenderableActorSetGetBlendEquation()
{
  TestApplication application;
  TestGlAbstraction& glAbstraction = application.GetGlAbstraction();

  tet_infoline("Testing Dali::RenderableActor::SetBlendEquation()");

  BitmapImage img = BitmapImage::New( 1,1 );
  ImageActor actor = ImageActor::New( img );
  Stage::GetCurrent().Add( actor );
  application.SendNotification();
  application.Render();

  // Test the defaults as documented int blending.h
  {
    BlendingEquation::Type equationRgb( BlendingEquation::SUBTRACT );
    BlendingEquation::Type equationAlpha( BlendingEquation::SUBTRACT );
    actor.GetBlendEquation( equationRgb, equationAlpha );
    DALI_TEST_EQUALS( BlendingEquation::ADD, equationRgb, TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingEquation::ADD, equationAlpha, TEST_LOCATION );
  }

  // Test the single blending equation setting
  {
    actor.SetBlendEquation( BlendingEquation::REVERSE_SUBTRACT );
    BlendingEquation::Type equationRgba( BlendingEquation::SUBTRACT );
    actor.GetBlendEquation( equationRgba, equationRgba );
    DALI_TEST_EQUALS( BlendingEquation::REVERSE_SUBTRACT, equationRgba, TEST_LOCATION );
  }

  actor.SetBlendEquation( BlendingEquation::REVERSE_SUBTRACT, BlendingEquation::REVERSE_SUBTRACT );

  // Test that Set was successful
  {
    BlendingEquation::Type equationRgb( BlendingEquation::SUBTRACT );
    BlendingEquation::Type equationAlpha( BlendingEquation::SUBTRACT );
    actor.GetBlendEquation( equationRgb, equationAlpha );
    DALI_TEST_EQUALS( BlendingEquation::REVERSE_SUBTRACT, equationRgb, TEST_LOCATION );
    DALI_TEST_EQUALS( BlendingEquation::REVERSE_SUBTRACT, equationAlpha, TEST_LOCATION );
  }

  // Render & check GL commands
  application.SendNotification();
  application.Render();
  DALI_TEST_EQUALS( (GLenum)GL_FUNC_REVERSE_SUBTRACT, glAbstraction.GetLastBlendEquationRgb(),   TEST_LOCATION );
  DALI_TEST_EQUALS( (GLenum)GL_FUNC_REVERSE_SUBTRACT, glAbstraction.GetLastBlendEquationAlpha(), TEST_LOCATION );
}

static void UtcDaliRenderableActorSetGetBlendColor()
{
  TestApplication application;
  TestGlAbstraction& glAbstraction = application.GetGlAbstraction();

  tet_infoline("Testing Dali::RenderableActor::SetBlendColor()");

  BitmapImage img = BitmapImage::New( 1,1 );
  ImageActor actor = ImageActor::New( img );
  Stage::GetCurrent().Add( actor );
  application.SendNotification();
  application.Render();

  // Test the defaults as documented int blending.h
  DALI_TEST_EQUALS( Vector4::ZERO, actor.GetBlendColor(), TEST_LOCATION );

  actor.SetBlendColor( Color::RED );

  // Test that Set was successful
  DALI_TEST_EQUALS( Color::RED, actor.GetBlendColor(), TEST_LOCATION );

  // Render & check GL commands
  application.SendNotification();
  application.Render();
  DALI_TEST_EQUALS( Color::RED, glAbstraction.GetLastBlendColor(),   TEST_LOCATION );
}

static void UtcDaliRenderableActorSetGetAlpha()
{
  TestApplication application;

  tet_infoline("Testing Dali::RenderableActor::SetGetAlpha()");

  BitmapImage img = BitmapImage::New( 1,1 );
  ImageActor actor = ImageActor::New( img );
  Stage::GetCurrent().Add( actor );
  application.SendNotification();
  application.Render();

  // use the image alpha on actor
  actor.SetBlendMode(BlendingMode::ON);

  // Test that Set was successful
  DALI_TEST_EQUALS( BlendingMode::ON, actor.GetBlendMode(), TEST_LOCATION );

  // Now test that it can be set to false
  actor.SetBlendMode(BlendingMode::OFF);
  DALI_TEST_EQUALS(BlendingMode::OFF, actor.GetBlendMode(), TEST_LOCATION );
}

static void UtcDaliRenderableActorCreateDestroy()
{
  tet_infoline("Testing Dali::RenderableActor::CreateDestroy()");
  RenderableActor* ractor = new RenderableActor;
  RenderableActor ractor2( *ractor );
  DALI_TEST_CHECK( ractor );
  delete ractor;
}
