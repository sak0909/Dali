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
#include <dali/integration-api/events/key-event-integ.h>
#include <dali/integration-api/events/touch-event-integ.h>
#include <dali-toolkit/dali-toolkit.h>

#include <dali-toolkit-test-suite-utils.h>

using namespace Dali;
using namespace Dali::Toolkit;

static void Startup();
static void Cleanup();

namespace
{
static bool gObjectCreatedCallBackCalled;

static void TestCallback(BaseHandle handle)
{
  gObjectCreatedCallBackCalled = true;
}
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
TEST_FUNCTION( UtcDaliAlignmentConstructorNegative, NEGATIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentConstructorPositive, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentConstructorRegister, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetAlignmentTypePositiveOffStage, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetAlignmentTypePositiveOnStage, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetAlignmentTypeNegative, NEGATIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentGetAlignmentType, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetScaling, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentGetScaling, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetPaddingPositive, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentSetPaddingNegative, NEGATIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentGetPadding, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentChildAddAndRemove, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentOnSizeSet, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentOnTouchEvent, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentOnKeyEvent, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentOnSizeAnimation, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAlignmentCopyAndAssignment, POSITIVE_TC_IDX );

// Called only once before first test is run.
static void Startup()
{
}

// Called only once after last test is run
static void Cleanup()
{
}

static void UtcDaliAlignmentConstructorNegative()
{
  ToolkitTestApplication application;

  Alignment alignment;

  try
  {
    Alignment::Padding padding;
    alignment.SetPadding(padding);
    tet_result(TET_FAIL);
  }
  catch (DaliException& exception)
  {
    if (exception.mCondition == "alignment")
    {
      tet_result(TET_PASS);
    }
  }
}

static void UtcDaliAlignmentConstructorPositive()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();

  try
  {
    Alignment::Padding padding;
    alignment.SetPadding(padding);
    tet_result(TET_PASS);
  }
  catch (DaliException& exception)
  {
    tet_result(TET_FAIL);
  }

  Actor actor = alignment;
  alignment = Alignment::DownCast( actor );

  DALI_TEST_CHECK( alignment );
}

static void UtcDaliAlignmentConstructorRegister()
{
  ToolkitTestApplication application;

  //Te ensure the object is registered after creation
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );

  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect(&TestCallback);
  {
    Alignment alignment = Alignment::New();
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
}

static void UtcDaliAlignmentSetAlignmentTypePositiveOffStage()
{
  ToolkitTestApplication application;

  // Default, HorizontalCenter, VerticalCenter - Ensure they do not change!
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalCenter | Alignment::VerticalCenter));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalLeft, VerticalCenter
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::HorizontalLeft);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalRight, VerticalCenter
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::HorizontalRight);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalLeft, VerticalTop
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalLeft | Alignment::VerticalTop));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalCenter, VerticalTop
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::VerticalTop);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalRight, VerticalTop
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalRight | Alignment::VerticalTop));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalLeft, VerticalBottom
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalLeft | Alignment::VerticalBottom));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalCenter, VerticalBottom
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::VerticalBottom);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }

  // HorizontalRight, VerticalBottom
  {
    Alignment alignment = Alignment::New();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalRight | Alignment::VerticalBottom));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);
  }
}

static void UtcDaliAlignmentSetAlignmentTypePositiveOnStage()
{
  ToolkitTestApplication application;

  // Default, HorizontalCenter, VerticalCenter - Ensure they do not change!
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalCenter | Alignment::VerticalCenter));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalCenter
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::HorizontalLeft);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalCenter
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::HorizontalRight);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalTop
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalLeft | Alignment::VerticalTop));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalCenter, VerticalTop
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::VerticalTop);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalTop
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalRight | Alignment::VerticalTop));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalBottom
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalLeft | Alignment::VerticalBottom));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalCenter, VerticalBottom
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::VerticalBottom);
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalBottom
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    // Check default values
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);

    Alignment::Type type(Alignment::Type(Alignment::HorizontalRight | Alignment::VerticalBottom));
    alignment.SetAlignmentType(type);
    DALI_TEST_CHECK(alignment.GetAlignmentType() & type);

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }
}

static void UtcDaliAlignmentSetAlignmentTypeNegative()
{
  ToolkitTestApplication application;

  // Setting HorizontalLeft, HorizontalCenter
  {
    Alignment alignment = Alignment::New();
    Alignment::Type type(Alignment::Type(Alignment::HorizontalLeft | Alignment::HorizontalCenter));

    try
    {
      alignment.SetAlignmentType(type);
      tet_result(TET_FAIL);
    }
    catch (DaliException& exception)
    {
      if (exception.mCondition == "!horizontalSet")
      {
        tet_result(TET_PASS);
      }
    }
  }

  // Setting HorizontalCenter, HorizontalRight
  {
    Alignment alignment = Alignment::New();
    Alignment::Type type(Alignment::Type(Alignment::HorizontalCenter | Alignment::HorizontalRight));

    try
    {
      alignment.SetAlignmentType(type);
      tet_result(TET_FAIL);
    }
    catch (DaliException& exception)
    {
      if (exception.mCondition == "!horizontalSet")
      {
        tet_result(TET_PASS);
      }
    }
  }

  // Setting VerticalTop, VerticalCenter
  {
    Alignment alignment = Alignment::New();
    Alignment::Type type(Alignment::Type(Alignment::VerticalTop | Alignment::VerticalCenter));

    try
    {
      alignment.SetAlignmentType(type);
      tet_result(TET_FAIL);
    }
    catch (DaliException& exception)
    {
      if (exception.mCondition == "!verticalSet")
      {
        tet_result(TET_PASS);
      }
    }
  }

  // Setting VerticalCenter, VerticalBottom
  {
    Alignment alignment = Alignment::New();
    Alignment::Type type(Alignment::Type(Alignment::VerticalTop | Alignment::VerticalBottom));

    try
    {
      alignment.SetAlignmentType(type);
      tet_result(TET_FAIL);
    }
    catch (DaliException& exception)
    {
      if (exception.mCondition == "!veritcalSet")
      {
        tet_result(TET_PASS);
      }
    }
  }
}

static void UtcDaliAlignmentGetAlignmentType()
{
  ToolkitTestApplication application;

  // Default, HorizonalCenter, VerticalCenter
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalCenter
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalLeft);
    DALI_TEST_EQUALS(Alignment::HorizontalLeft | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalCenter
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalRight);
    DALI_TEST_EQUALS(Alignment::HorizontalRight | Alignment::VerticalCenter, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalTop
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalLeft, Alignment::VerticalTop);
    DALI_TEST_EQUALS(Alignment::HorizontalLeft | Alignment::VerticalTop, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalCenter, VerticalTop
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalCenter, Alignment::VerticalTop);
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalTop, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalTop
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalRight, Alignment::VerticalTop);
    DALI_TEST_EQUALS(Alignment::HorizontalRight | Alignment::VerticalTop, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalLeft, VerticalBottom
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalLeft, Alignment::VerticalBottom);
    DALI_TEST_EQUALS(Alignment::HorizontalLeft | Alignment::VerticalBottom, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalCenter, VerticalBottom
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalCenter, Alignment::VerticalBottom);
    DALI_TEST_EQUALS(Alignment::HorizontalCenter | Alignment::VerticalBottom, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // HorizontalRight, VerticalBottom
  {
    Alignment alignment = Alignment::New(Alignment::HorizontalRight, Alignment::VerticalBottom);
    DALI_TEST_EQUALS(Alignment::HorizontalRight | Alignment::VerticalBottom, alignment.GetAlignmentType(), TEST_LOCATION);
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();
    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }
}

static void UtcDaliAlignmentSetScaling()
{
  ToolkitTestApplication application;

  // ScaleToFill
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    DALI_TEST_EQUALS(Alignment::ScaleNone, alignment.GetScaling(), TEST_LOCATION);
    alignment.SetScaling(Alignment::ScaleToFill);
    DALI_TEST_EQUALS(Alignment::ScaleToFill, alignment.GetScaling(), TEST_LOCATION);
    application.Render();
    application.SendNotification();

    // For complete line coverage
    alignment.SetAlignmentType(Alignment::HorizontalLeft);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::HorizontalRight);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalTop);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalBottom);
    application.Render();
    application.SendNotification();

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // ScaleToFitKeepAspect
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    DALI_TEST_EQUALS(Alignment::ScaleNone, alignment.GetScaling(), TEST_LOCATION);
    alignment.SetScaling(Alignment::ScaleToFitKeepAspect);
    DALI_TEST_EQUALS(Alignment::ScaleToFitKeepAspect, alignment.GetScaling(), TEST_LOCATION);
    application.Render();
    application.SendNotification();

    // For complete line coverage
    alignment.SetAlignmentType(Alignment::HorizontalLeft);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::HorizontalRight);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalTop);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalBottom);
    application.Render();
    application.SendNotification();

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // ScaleToFillKeepAspect
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    DALI_TEST_EQUALS(Alignment::ScaleNone, alignment.GetScaling(), TEST_LOCATION);
    alignment.SetScaling(Alignment::ScaleToFillKeepAspect);
    DALI_TEST_EQUALS(Alignment::ScaleToFillKeepAspect, alignment.GetScaling(), TEST_LOCATION);
    application.Render();
    application.SendNotification();

    // For complete line coverage
    alignment.SetAlignmentType(Alignment::HorizontalLeft);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::HorizontalRight);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalTop);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalBottom);
    application.Render();
    application.SendNotification();

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // ShrinkToFit
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    DALI_TEST_EQUALS(Alignment::ScaleNone, alignment.GetScaling(), TEST_LOCATION);
    alignment.SetScaling(Alignment::ShrinkToFit);
    DALI_TEST_EQUALS(Alignment::ShrinkToFit, alignment.GetScaling(), TEST_LOCATION);
    application.Render();
    application.SendNotification();

    // For complete line coverage
    alignment.SetAlignmentType(Alignment::HorizontalLeft);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::HorizontalRight);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalTop);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalBottom);
    application.Render();
    application.SendNotification();

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }

  // ShrinkToFitKeepAspect
  {
    Alignment alignment = Alignment::New();
    alignment.Add(RenderableActor::New());
    Stage::GetCurrent().Add(alignment);
    application.Render();
    application.SendNotification();

    DALI_TEST_EQUALS(Alignment::ScaleNone, alignment.GetScaling(), TEST_LOCATION);
    alignment.SetScaling(Alignment::ShrinkToFitKeepAspect);
    DALI_TEST_EQUALS(Alignment::ShrinkToFitKeepAspect, alignment.GetScaling(), TEST_LOCATION);
    application.Render();
    application.SendNotification();

    // For complete line coverage
    alignment.SetAlignmentType(Alignment::HorizontalLeft);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::HorizontalRight);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalTop);
    application.Render();
    application.SendNotification();
    alignment.SetAlignmentType(Alignment::VerticalBottom);
    application.Render();
    application.SendNotification();

    Stage::GetCurrent().Remove(alignment);
    application.Render();
    application.SendNotification();
  }
}

static void UtcDaliAlignmentGetScaling()
{
  ToolkitTestApplication application;

  // ScaleToFill
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleNone);

    alignment.SetScaling(Alignment::ScaleToFill);
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleToFill);
  }

  // ScaleToFitKeepAspect
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleNone);

    alignment.SetScaling(Alignment::ScaleToFitKeepAspect);
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleToFitKeepAspect);
  }

  // ScaleToFillKeepAspect
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleNone);

    alignment.SetScaling(Alignment::ScaleToFillKeepAspect);
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleToFillKeepAspect);
  }

  // ShrinkToFit
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleNone);

    alignment.SetScaling(Alignment::ShrinkToFit);
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ShrinkToFit);
  }

  // ShrinkToFitKeepAspect
  {
    Alignment alignment = Alignment::New();
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ScaleNone);

    alignment.SetScaling(Alignment::ShrinkToFitKeepAspect);
    DALI_TEST_CHECK(alignment.GetScaling() == Alignment::ShrinkToFitKeepAspect);
  }

}

static void UtcDaliAlignmentSetPaddingPositive()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();

  Alignment::Padding padding(1.0f, 1.5f, 2.f, 0.5f);
  DALI_TEST_CHECK( fabs( padding.left - alignment.GetPadding().left ) > GetRangedEpsilon( padding.left, alignment.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( padding.right - alignment.GetPadding().right ) > GetRangedEpsilon( padding.right, alignment.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( padding.top - alignment.GetPadding().top ) > GetRangedEpsilon( padding.top, alignment.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( padding.bottom - alignment.GetPadding().bottom ) > GetRangedEpsilon( padding.bottom, alignment.GetPadding().bottom ) );

  alignment.SetPadding(padding);
  DALI_TEST_CHECK( fabs( padding.left - alignment.GetPadding().left ) < GetRangedEpsilon( padding.left, alignment.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( padding.right - alignment.GetPadding().right ) < GetRangedEpsilon( padding.right, alignment.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( padding.top - alignment.GetPadding().top ) < GetRangedEpsilon( padding.top, alignment.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( padding.bottom - alignment.GetPadding().bottom ) < GetRangedEpsilon( padding.bottom, alignment.GetPadding().bottom ) );
}

static void UtcDaliAlignmentSetPaddingNegative()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();

  try
  {
    Alignment::Padding padding(-1.0f, 1.5f, 2.f, 0.f);
    alignment.SetPadding(padding);
    tet_result(TET_FAIL);
  }
  catch (DaliException& exception)
  {
    if (exception.mCondition == "( padding.left >= 0.f ) && ( padding.top >= 0.f ) && ( padding.right >= 0.f ) && ( padding.bottom >= 0.f )")
    {
      tet_result(TET_PASS);
    }
  }

  try
  {
    Alignment::Padding padding(1.0f, 1.5f, -2.f, 0.f);
    alignment.SetPadding(padding);
    tet_result(TET_FAIL);
  }
  catch (DaliException& exception)
  {
    if (exception.mCondition == "( padding.left >= 0.f ) && ( padding.top >= 0.f ) && ( padding.right >= 0.f ) && ( padding.bottom >= 0.f )")
    {
      tet_result(TET_PASS);
    }
  }

  try
  {
    Alignment::Padding padding(1.0f, 1.5f, 2.f, -1.f);
    alignment.SetPadding(padding);
    tet_result(TET_FAIL);
  }
  catch (DaliException& exception)
  {
    if (exception.mCondition == "( padding.left >= 0.f ) && ( padding.top >= 0.f ) && ( padding.right >= 0.f ) && ( padding.bottom >= 0.f )")
    {
      tet_result(TET_PASS);
    }
  }

  try
  {
    Alignment::Padding padding(1.0f, -1.5f, 2.f, 0.f);
    alignment.SetPadding(padding);
    tet_result(TET_FAIL);
  }
  catch (DaliException& exception)
  {
    if (exception.mCondition == "( padding.left >= 0.f ) && ( padding.top >= 0.f ) && ( padding.right >= 0.f ) && ( padding.bottom >= 0.f )")
    {
      tet_result(TET_PASS);
    }
  }
}

static void UtcDaliAlignmentGetPadding()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  DALI_TEST_CHECK( fabs( alignment.GetPadding().left ) < GetRangedEpsilon( 0.f, alignment.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( alignment.GetPadding().right ) < GetRangedEpsilon( 0.f, alignment.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( alignment.GetPadding().top ) < GetRangedEpsilon( 0.f, alignment.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( alignment.GetPadding().bottom ) < GetRangedEpsilon( 0.f, alignment.GetPadding().bottom ) );

  Alignment::Padding padding(1.0f, 1.5f, 2.f, 0.f);
  alignment.SetPadding(padding);
  DALI_TEST_CHECK( fabs( padding.left - alignment.GetPadding().left ) < GetRangedEpsilon( padding.left, alignment.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( padding.right - alignment.GetPadding().right ) < GetRangedEpsilon( padding.right, alignment.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( padding.top - alignment.GetPadding().top ) < GetRangedEpsilon( padding.top, alignment.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( padding.bottom - alignment.GetPadding().bottom ) < GetRangedEpsilon( padding.bottom, alignment.GetPadding().bottom ) );
}

static void UtcDaliAlignmentChildAddAndRemove()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  Stage::GetCurrent().Add(alignment);

  application.Render();
  application.SendNotification();

  Actor actor = RenderableActor::New();
  alignment.Add(actor);

  DALI_TEST_EQUALS(alignment.GetChildCount(), 1u, TEST_LOCATION);

  application.Render();
  application.SendNotification();

  alignment.Remove(actor);

  DALI_TEST_EQUALS(alignment.GetChildCount(), 0u, TEST_LOCATION);

  application.Render();
  application.SendNotification();

  Stage::GetCurrent().Remove(alignment);
}

static void UtcDaliAlignmentOnSizeSet()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  Stage::GetCurrent().Add(alignment);

  application.Render();
  application.SendNotification();

  Vector3 size(100.0f, 200.0f, 0.0f);
  alignment.SetSize(size);

  application.Render();
  application.SendNotification();
  application.Render();
  application.SendNotification();

  DALI_TEST_EQUALS(size, alignment.GetImplementation().GetControlSize(), TEST_LOCATION);

  Stage::GetCurrent().Remove(alignment);
}

///////////////////////////////////////////////////////////////////////////////
static bool TouchEventCallback(Actor actor, const TouchEvent& event)
{
  return false;
}

///////////////////////////////////////////////////////////////////////////////

static void UtcDaliAlignmentOnTouchEvent()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  alignment.SetSize(100.0f, 100.0f);
  alignment.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  Stage::GetCurrent().Add(alignment);

  alignment.TouchedSignal().Connect(&TouchEventCallback);

  application.Render();
  application.SendNotification();
  application.Render();
  application.SendNotification();

  Integration::TouchEvent touchEvent(1);
  TouchPoint point(1, TouchPoint::Down, 20.0f, 20.0f);
  touchEvent.AddPoint(point);
  application.ProcessEvent(touchEvent);

  tet_result(TET_PASS); // For line coverage, as long as there are no exceptions, we assume passed.
}

static void UtcDaliAlignmentOnKeyEvent()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  Stage::GetCurrent().Add(alignment);

  alignment.SetKeyInputFocus();

  application.Render();
  application.SendNotification();
  application.Render();
  application.SendNotification();

  Integration::KeyEvent keyEvent;
  application.ProcessEvent(keyEvent);

  tet_result(TET_PASS); // For line coverage, as long as there are no exceptions, we assume passed.
}

static void UtcDaliAlignmentOnSizeAnimation()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  Stage::GetCurrent().Add(alignment);

  Animation animation = Animation::New(100.0f);
  animation.Resize(alignment, Vector3(100.0f, 150.0f, 200.0f));
  animation.Play();

  application.Render();
  application.SendNotification();
  application.Render();
  application.SendNotification();

  tet_result(TET_PASS); // For line coverage, as long as there are no exceptions, we assume passed.
}

static void UtcDaliAlignmentCopyAndAssignment()
{
  ToolkitTestApplication application;

  Alignment alignment = Alignment::New();
  Alignment emptyAlignment;

  Alignment::Padding padding(100.0f, 150.0f, 200.f, 0.f);
  alignment.SetPadding(padding);

  Alignment alignmentCopy(alignment);
  DALI_TEST_CHECK( fabs( padding.left - alignmentCopy.GetPadding().left ) < GetRangedEpsilon( padding.left, alignmentCopy.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( padding.right - alignmentCopy.GetPadding().right ) < GetRangedEpsilon( padding.right, alignmentCopy.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( padding.top - alignmentCopy.GetPadding().top ) < GetRangedEpsilon( padding.top, alignmentCopy.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( padding.bottom - alignmentCopy.GetPadding().bottom ) < GetRangedEpsilon( padding.bottom, alignmentCopy.GetPadding().bottom ) );

  Alignment alignmentEmptyCopy(emptyAlignment);
  DALI_TEST_CHECK(emptyAlignment == alignmentEmptyCopy);

  Alignment alignmentEquals;
  alignmentEquals = alignment;
  DALI_TEST_CHECK( fabs( padding.left - alignmentEquals.GetPadding().left ) < GetRangedEpsilon( padding.left, alignmentEquals.GetPadding().left ) );
  DALI_TEST_CHECK( fabs( padding.right - alignmentEquals.GetPadding().right ) < GetRangedEpsilon( padding.right, alignmentEquals.GetPadding().right ) );
  DALI_TEST_CHECK( fabs( padding.top - alignmentEquals.GetPadding().top ) < GetRangedEpsilon( padding.top, alignmentEquals.GetPadding().top ) );
  DALI_TEST_CHECK( fabs( padding.bottom - alignmentEquals.GetPadding().bottom ) < GetRangedEpsilon( padding.bottom, alignmentEquals.GetPadding().bottom ) );

  Alignment alignmentEmptyEquals;
  alignmentEmptyEquals = emptyAlignment;
  DALI_TEST_CHECK(emptyAlignment == alignmentEmptyEquals);

  // Self assignment
  alignment = alignment;
  DALI_TEST_CHECK(alignment == alignmentCopy);
}
