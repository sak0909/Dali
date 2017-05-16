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

using namespace Toolkit;

using namespace std;


namespace
{

Vector3 AlbumLayoutItemSizeFunction(const Vector3& layoutSize)
{
  float width = layoutSize.width * 0.2f;
  return Vector3(width, width, width);
}

float AlbumLayoutAlbumRadiusFunction(const Vector3& layoutSize)
{
  return layoutSize.width * 0.5f;
}
} // namespace

static void Startup();
static void Cleanup();

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

static void UtcDaliAlbumLayoutNew();
static void UtcDaliAlbumSetAndGetItemSizeFunction();
static void UtcDaliAlbumSetAndGetScrollSpeedFactor();
static void UtcDaliAlbumSetAndGetMaximumSwipeSpeed();
static void UtcDaliAlbumLayoutSetAndGetItemFlickAnimationDuration();
static void UtcDaliAlbumSetNumOfItems();
static void UtcDaliAlbumSetStackNum();
static void UtcDaliAlbumSetPosition();
static void UtcDaliAlbumSetRotationX();
static void UtcDaliAlbumSetRotationZ();
static void UtcDaliAlbumSetScale();
static void UtcDaliAlbumSetColor();
static void UtcDaliAlbumSetCenterPosition();
static void UtcDaliAlbumSetSetCenterScale();
static void UtcDaliAlbumSetSetCenterColor();
static void UtcDaliAlbumSetStackPosition();
static void UtcDaliAlbumSetSetStackScale();
static void UtcDaliAlbumSetStackColor();

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

// Add test functionality for all APIs in the class (Positive and Negative)
extern "C" {
  struct tet_testlist tet_testlist[] = {
    { UtcDaliAlbumLayoutNew, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetAndGetItemSizeFunction, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetAndGetScrollSpeedFactor, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetAndGetMaximumSwipeSpeed, POSITIVE_TC_IDX },
    { UtcDaliAlbumLayoutSetAndGetItemFlickAnimationDuration, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetNumOfItems, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetStackNum, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetPosition, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetRotationX, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetRotationZ, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetScale, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetColor, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetCenterPosition, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetSetCenterScale, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetSetCenterColor, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetStackPosition, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetSetStackScale, POSITIVE_TC_IDX },
    { UtcDaliAlbumSetStackColor, POSITIVE_TC_IDX },
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

static void UtcDaliAlbumLayoutNew()
{
  ToolkitTestApplication application;

  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  DALI_TEST_CHECK(albumLayout);
}

static void UtcDaliAlbumSetAndGetItemSizeFunction()
{
  ToolkitTestApplication application;

  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  // Set the item size function
  albumLayout->SetItemSizeFunction(AlbumLayoutItemSizeFunction);

  // Check whether we get the correct item size function
  DALI_TEST_CHECK(albumLayout->GetItemSizeFunction() == AlbumLayoutItemSizeFunction);
}

static void UtcDaliAlbumSetAndGetScrollSpeedFactor()
{
  ToolkitTestApplication application;

  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  // Set the scroll speed factor
  albumLayout->SetScrollSpeedFactor(0.05f);

  // Check whether we get the correct scroll speed factor
  DALI_TEST_EQUALS( albumLayout->GetScrollSpeedFactor(), 0.05f, TEST_LOCATION );
}

static void UtcDaliAlbumSetAndGetMaximumSwipeSpeed()
{
  ToolkitTestApplication application;

  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  // Set the maximum swipe speed
  albumLayout->SetMaximumSwipeSpeed(50.0f);

  // Check whether we get the correct maximum swipe speed
  DALI_TEST_EQUALS( albumLayout->GetMaximumSwipeSpeed(), 50.0f, TEST_LOCATION );
}

static void UtcDaliAlbumLayoutSetAndGetItemFlickAnimationDuration()
{
  ToolkitTestApplication application;

  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  // Set the flick animaiton duration
  albumLayout->SetItemFlickAnimationDuration(0.35f);

  // Check whether we get the correct flick animaiton duration
  DALI_TEST_EQUALS( albumLayout->GetItemFlickAnimationDuration(), 0.35f, TEST_LOCATION );
}

static void UtcDaliAlbumSetNumOfItems()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetNumOfItems(15);

  DALI_TEST_CHECK(albumLayout->GetNumOfItems() == 15);
}

static void UtcDaliAlbumSetStackNum()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetStackNum(30);

  DALI_TEST_CHECK(albumLayout->GetStackNum() == 30);
}

static void UtcDaliAlbumSetPosition()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  std::vector<Vector3> position_list;

  /*(0.0f)*/
  Vector3 pos = Vector3(850.0f,-250.0f,0.0);
  position_list.push_back(pos);

  /*(1.0f)*/
  pos = Vector3(700.0f,50.0f,0.0);
  position_list.push_back(pos);

  /*(2.0f)*/
  pos = Vector3(440.0f,227.0f,0.0);
  position_list.push_back(pos);

  /*(4.0f)*/
  pos = Vector3(-440.0f,227.0f,0.0);
  position_list.push_back(pos);

  /*(5.0f)*/
  pos = Vector3(-700.0f,50.0f,0.0);
  position_list.push_back(pos);

  /*(6.0f)*/
  pos = Vector3(-850.0f,-250.0f,0.0);
  position_list.push_back(pos);

  albumLayout->SetPosition(position_list);

  DALI_TEST_CHECK(albumLayout->GetPosition() == position_list);
}

static void UtcDaliAlbumSetRotationX()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetRotationX(Math::PI/4.0f);

  DALI_TEST_CHECK(albumLayout->GetRotationX() == Math::PI/4.0f);
}

static void UtcDaliAlbumSetRotationZ()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  std::vector<float> rotation_list;

  /*(0.0f)*/
  float rotate = Math::PI/6.0f;
  rotation_list.push_back(rotate);

  /*(1.0f)*/
  rotate = 0.0f;
  rotation_list.push_back(rotate);

  /*(2.0f)*/
  rotate = Math::PI/6.0f;
  rotation_list.push_back(rotate);

  /*(4.0f)*/
  rotate = -Math::PI/6.0f;
  rotation_list.push_back(rotate);

  /*(5.0f)*/
  rotate = 0.0f;
  rotation_list.push_back(rotate);

  /*(6.0f)*/
  rotate = -Math::PI/6.0f;
  rotation_list.push_back(rotate);

  albumLayout->SetRotationZ(rotation_list);

  DALI_TEST_CHECK(albumLayout->GetRotationZ() == rotation_list);
}

static void UtcDaliAlbumSetScale()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  std::vector<float> scale_list;

  /*(0.0f)*/
  float scale = 1.0f;
  scale_list.push_back(scale);

  /*(1.0f)*/
  scale = 0.0f;
  scale_list.push_back(scale);

  /*(2.0f)*/
  scale = Math::PI/6.0f;
  scale_list.push_back(scale);

  /*(4.0f)*/
  scale = -Math::PI/6.0f;
  scale_list.push_back(scale);

  /*(5.0f)*/
  scale = 0.0f;
  scale_list.push_back(scale);

  /*(6.0f)*/
  scale = -Math::PI/6.0f;
  scale_list.push_back(scale);

  albumLayout->SetScale(scale_list);

  DALI_TEST_CHECK(albumLayout->GetScale() == scale_list);
}

static void UtcDaliAlbumSetColor()
{
  // Create a album layout
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  std::vector<Vector2> color_list;

  /*(0.0f)*/
  Vector2 color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  /*(1.0f)*/
  color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  /*(2.0f)*/
  color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  /*(4.0f)*/
  color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  /*(5.0f)*/
  color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  /*(6.0f)*/
  color = Vector2(1.0f,1.0f);
  color_list.push_back(color);

  albumLayout->SetColor(color_list);

  DALI_TEST_CHECK(albumLayout->GetColor() == color_list);
}

static void UtcDaliAlbumSetCenterPosition()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetCenterPosition(Vector3( 0.0f,-80.0f,100.0f));

  DALI_TEST_CHECK(albumLayout->GetCenterPosition() == Vector3( 0.0f,-80.0f,100.0f));
}

static void UtcDaliAlbumSetSetCenterScale()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetCenterScale(1.75f);

  DALI_TEST_CHECK(albumLayout->GetCenterScale() == 1.75f);
}

static void UtcDaliAlbumSetSetCenterColor()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetCenterColor(Vector2(1.0f,1.0f));

  DALI_TEST_CHECK(albumLayout->GetCenterColor() == Vector2(1.0f,1.0f));
}

static void UtcDaliAlbumSetStackPosition()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetStackPosition(Vector3(750.0f,-500.0f,0.0f),Vector3(-750.0f,-500.0f,0.0f));

  DALI_TEST_CHECK(albumLayout->GetRightStackPosition() == Vector3(750.0f,-500.0f,0.0f) && albumLayout->GetLeftStackPosition() == Vector3(-750.0f,-500.0f,0.0f));
}

static void UtcDaliAlbumSetSetStackScale()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetStackScale(1.0f,1.0f);

  DALI_TEST_CHECK(albumLayout->GetRightStackScale() == 1.0f && albumLayout->GetLeftStackScale() == 1.0f);
}

static void UtcDaliAlbumSetStackColor()
{
  AlbumLayoutPtr albumLayout = AlbumLayout::New();

  albumLayout->SetStackColor(Vector2(1.0f,1.0f),Vector2(1.0f,1.0f));

  DALI_TEST_CHECK(albumLayout->GetRightStackColor() == Vector2(1.0f,1.0f) && albumLayout->GetLeftStackColor() == Vector2(1.0f,1.0f));
}
