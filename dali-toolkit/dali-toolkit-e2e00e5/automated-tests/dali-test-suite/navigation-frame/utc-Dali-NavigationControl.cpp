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

#include <dali/dali.h>
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

}

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

static void UtcDaliNavigationControlNew();
static void UtcDaliNavigationControlDownCast();
static void UtcDaliNavigationControlPushItem();
static void UtcDaliNavigationControlPopItem();
static void UtcDaliNavigationControlGetItemCount();
static void UtcDaliNavigationControlGetItem();
static void UtcDaliNavigationControlGetCurrentItem();
static void UtcDaliNavigationControlSetBackground();
static void UtcDaliNavigationControlCreateNavigationToolBar();
static void UtcDaliNavigationControlCreateNavigationTitleBar();

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

// Add test functionality for all APIs in the class (Positive and Negative)
extern "C" {
  struct tet_testlist tet_testlist[] = {
    { UtcDaliNavigationControlNew, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlDownCast, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlPushItem, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlPopItem, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlGetItemCount, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlGetItem, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlGetCurrentItem, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlSetBackground, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlCreateNavigationToolBar, POSITIVE_TC_IDX },
    { UtcDaliNavigationControlCreateNavigationTitleBar, POSITIVE_TC_IDX },
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


static void UtcDaliNavigationControlNew()
{
  ToolkitTestApplication application;
  tet_infoline("UtcDaliNavigationControlNew");

  NavigationControl naviControl;
  // Check that this handle is uninitialized
  DALI_TEST_CHECK( !naviControl );

  naviControl = NavigationControl::New();
  // Check that the Dali resource is successfully created
  DALI_TEST_CHECK( naviControl );

  NavigationControl naviControl2( naviControl );
  DALI_TEST_CHECK( naviControl2 == naviControl );

  //Additional check to ensure object is created by checking whether it is registered
  ObjectRegistry registry = Stage::GetCurrent().GetObjectRegistry();
  DALI_TEST_CHECK( registry );
  gObjectCreatedCallBackCalled = false;
  registry.ObjectCreatedSignal().Connect( TestCallback );
  {
    NavigationControl naviControl = NavigationControl::New();
  }
  DALI_TEST_CHECK( gObjectCreatedCallBackCalled );
}

static void UtcDaliNavigationControlDownCast()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlDownCast" );

  NavigationControl naviControl = NavigationControl::New();
  BaseHandle handle( naviControl );

  NavigationControl newNaviControl = NavigationControl::DownCast( handle );
  DALI_TEST_CHECK( naviControl );
  DALI_TEST_CHECK( newNaviControl == naviControl );
}

static void UtcDaliNavigationControlPushItem()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlPushItem" );

  // Create a NavigationControl object, and add it to stage
  NavigationControl naviControl = NavigationControl::New();
  Stage::GetCurrent().Add(naviControl);
  // Check there is no item in the stack
  DALI_TEST_CHECK( naviControl.GetItemCount() == 0 );

  // Create two NavigationItem objects
  Page firstItem = Page::New();
  Page secondItem = Page::New();

  // Push the first item into stack
  naviControl.PushItem( firstItem );
  // Check the item count in stack
  DALI_TEST_CHECK( naviControl.GetItemCount() == 1 );
  // Check the current item
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == firstItem );
  // Check that the newly pushed item is displayed on stage
  DALI_TEST_CHECK( firstItem.OnStage() );

  // Push the second item into stack
  naviControl.PushItem( secondItem );
  // Check the item count in stack
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  // Check the current item
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == secondItem );
  // Check the bottom item in the stack
  DALI_TEST_CHECK( naviControl.GetItem(0) == firstItem );
  // Check that the previous item is off stage
  DALI_TEST_CHECK( !firstItem.OnStage() );
  // Check that the newly pushed item is displayed on stage
  DALI_TEST_CHECK( secondItem.OnStage() );

  Page thirdItem;
  Page fourthItem(secondItem);
  naviControl.PushItem( thirdItem );
  // Check that an uninitialized item cannot be pushed into the stack
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  naviControl.PushItem( fourthItem );
  // Check that an duplicated item with the current item cannot be pushed into the stack
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  // Check that the current item and the item on the stage is still the secondItem
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == secondItem );
  DALI_TEST_CHECK( secondItem.OnStage() );
}

static void UtcDaliNavigationControlPopItem()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlPopItem" );

  // Create a NavigationControl object, and add it to stage
  NavigationControl naviControl = NavigationControl::New();
  Stage::GetCurrent().Add(naviControl);
  // Create three NavigationItem objects
  Page firstItem = Page::New();
  Page secondItem = Page::New();
  Page thirdItem = Page::New();
  naviControl.PushItem( firstItem );
  naviControl.PushItem( secondItem );
  naviControl.PushItem( thirdItem );

  DALI_TEST_CHECK( naviControl.GetItemCount() == 3 );

  // pop an item out from the stack
  Page poppedItem = naviControl.PopItem();
  // check that the item count is decrease by one
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  // check that the item popped out is the thirdItem
  DALI_TEST_CHECK( poppedItem == thirdItem );
  // check that the item popped out is disappeared from the stage
  DALI_TEST_CHECK( !poppedItem.OnStage() );
  // check that the new top item is displayed on the stage
  DALI_TEST_CHECK( secondItem.OnStage() );

  // repeat the above steps again
  poppedItem = naviControl.PopItem();
  DALI_TEST_CHECK( naviControl.GetItemCount() == 1 );
  DALI_TEST_CHECK( poppedItem == secondItem );
  DALI_TEST_CHECK( !poppedItem.OnStage() );
  DALI_TEST_CHECK( firstItem.OnStage() );

  // check that the bottom-most item can not be popped out from the stack
  poppedItem = naviControl.PopItem();
  // when trying to pop the bottom-most item, it returns an uninitialized handle and does nothing else
  DALI_TEST_CHECK( !poppedItem );
  DALI_TEST_CHECK( naviControl.GetItemCount() == 1 );
  DALI_TEST_CHECK( firstItem.OnStage() );
}

static void UtcDaliNavigationControlGetItemCount()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlGetItemCount" );

  // Create a NavigationControl object
  NavigationControl naviControl = NavigationControl::New();
  // Create three NavigationItem objects
  Page firstItem = Page::New();
  Page secondItem = Page::New();
  Page thirdItem = Page::New();

  DALI_TEST_CHECK( naviControl.GetItemCount() == 0 );
  naviControl.PushItem( firstItem );
  DALI_TEST_CHECK( naviControl.GetItemCount() == 1 );
  naviControl.PushItem( secondItem );
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  naviControl.PushItem( thirdItem );
  DALI_TEST_CHECK( naviControl.GetItemCount() == 3 );
  naviControl.PopItem();
  DALI_TEST_CHECK( naviControl.GetItemCount() == 2 );
  naviControl.PopItem();
  DALI_TEST_CHECK( naviControl.GetItemCount() == 1 );
}

static void UtcDaliNavigationControlGetItem()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlGetItem" );

  // Create a NavigationControl object
  NavigationControl naviControl = NavigationControl::New();
  // Create three NavigationItem objects and push them into stack
  Page firstItem = Page::New();
  Page secondItem = Page::New();
  Page thirdItem = Page::New();
  naviControl.PushItem( firstItem );
  naviControl.PushItem( secondItem );
  naviControl.PushItem( thirdItem );

  // check every item by get it by index
  DALI_TEST_CHECK( naviControl.GetItem(0) == firstItem );
  DALI_TEST_CHECK( naviControl.GetItem(1) == secondItem );
  DALI_TEST_CHECK( naviControl.GetItem(2) == thirdItem);
}

static void UtcDaliNavigationControlGetCurrentItem()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlGetCurrentItem" );

  // Create a NavigationControl object
  NavigationControl naviControl = NavigationControl::New();
  // Create three NavigationItem objects
  Page firstItem = Page::New();
  Page secondItem = Page::New();
  Page thirdItem = Page::New();

  naviControl.PushItem( firstItem );
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == firstItem );
  naviControl.PushItem( secondItem );
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == secondItem );
  naviControl.PushItem( thirdItem );
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == thirdItem );
  naviControl.PopItem();
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == secondItem );
  naviControl.PopItem();
  DALI_TEST_CHECK( naviControl.GetCurrentItem() == firstItem );
}

static void UtcDaliNavigationControlSetBackground()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlSetBackground" );

  try
  {
    NavigationControl naviControl = NavigationControl::New();
    Stage::GetCurrent().Add( naviControl );

    ImageActor background = CreateSolidColorActor( Color::RED );
    naviControl.SetBackground( background );
  }
  catch (Dali::DaliException& e)
  {
    tet_printf("Assertion %s failed at %s\n", e.mCondition.c_str(), e.mLocation.c_str());
    DALI_TEST_EQUALS(e.mCondition, "segmentIndex+1 < mKnots.size() && segmentIndex < mKnots.size()", TEST_LOCATION);
    tet_result(TET_FAIL);
  }

  tet_result(TET_PASS);
}

static void UtcDaliNavigationControlCreateNavigationToolBar()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlCreateNavigationToolBar" );

  ImageActor background = CreateSolidColorActor( Color::RED );
  Stage stage = Stage::GetCurrent();

  NavigationControl naviControl = NavigationControl::New();
  stage.Add( naviControl );

  Toolkit::NaviToolBarStyle toolbarStyle( background, 720, 98, 496, 182, 72, 16, 63, 26);

  naviControl.CreateNavigationToolBar( toolbarStyle, toolbarStyle);

  Page naviItem = Page::New();
  PushButton firstControl = PushButton::New();
  naviItem.AddControlToToolBar(firstControl, Alignment::HorizontalLeft);
  PushButton secondControl = PushButton::New();
  naviItem.AddControlToToolBar(secondControl, Alignment::HorizontalCenter);
  PushButton thirdControl = PushButton::New();
  naviItem.AddControlToToolBar(thirdControl, Alignment::HorizontalCenter);
  PushButton fourthControl = PushButton::New();
  naviItem.AddControlToToolBar(fourthControl, Alignment::HorizontalRight);
  PushButton fifthControl = PushButton::New();
  naviItem.AddControlToToolBar(fifthControl, Alignment::HorizontalRight);

  naviControl.PushItem( naviItem );

  DALI_TEST_CHECK( firstControl.OnStage() );
  // Can add multiple controls to the central group
  DALI_TEST_CHECK( secondControl.OnStage() );
  DALI_TEST_CHECK( thirdControl.OnStage() );
  // Can only have one control in the side groups
  DALI_TEST_CHECK( !fourthControl.OnStage() );
  DALI_TEST_CHECK( fifthControl.OnStage() );

}

static void UtcDaliNavigationControlCreateNavigationTitleBar()
{
  ToolkitTestApplication application;
  tet_infoline( "UtcDaliNavigationControlCreateNavigationTitleBar" );

  ImageActor background = CreateSolidColorActor( Color::RED );
  TextStyle textStyle;
  Stage stage = Stage::GetCurrent();

  NavigationControl naviControl = NavigationControl::New();
  stage.Add( naviControl );

  Toolkit::NaviTitleBarStyle titleBarStyle( background, textStyle, textStyle, 720, 111, 68, 48, 34, 16, 11, 45, 63, 26, 14, 22 );
  naviControl.CreateNavigationTitleBar( titleBarStyle, titleBarStyle );

  Page naviItem = Page::New();

  PushButton firstControl = PushButton::New();
  naviItem.AddControlToTitleBar( firstControl );
  PushButton secondControl = PushButton::New();
  naviItem.AddControlToTitleBar( secondControl );

  Actor titleIcon = Actor::New();
  naviItem.SetTitleIcon( titleIcon );

  naviControl.PushItem( naviItem );

  DALI_TEST_CHECK( firstControl.OnStage() );
  DALI_TEST_CHECK( secondControl.OnStage() );
  DALI_TEST_CHECK( titleIcon.OnStage() );
}
