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
#include <boost/bind.hpp>

#include <dali/public-api/dali-core.h>

#include <dali-test-suite-utils.h>

using namespace Dali;

static void Startup();
static void Cleanup();

namespace {

static bool gCallBackCalled;

static void TestCallback(PropertyNotification& source)
{
  gCallBackCalled = true;
}

const int RENDER_FRAME_INTERVAL(16);                           ///< Duration of each frame in ms. (at approx 60FPS)
const int DEFAULT_WAIT_PERIOD(100);                            ///< Default waiting period for check.

} // unnamed namespace

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
TEST_FUNCTION( UtcDaliPropertyNotificationDownCast, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationDownCastNegative, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAddPropertyNotification, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAddPropertyNotificationCallback, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliAddPropertyNotificationTypeProperty, NEGATIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGetCondition, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGetConditionConst, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGetTarget, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGetProperty, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGetNotifyMode, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationGreaterThan, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationLessThan, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationInside, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationOutside, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationVectorComponentGreaterThan, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationVectorComponentLessThan, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationVectorComponentInside, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationVectorComponentOutside, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyConditionGetArguments, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyConditionGetArgumentsConst, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationStep, POSITIVE_TC_IDX );
TEST_FUNCTION( UtcDaliPropertyNotificationVariableStep, POSITIVE_TC_IDX );

class TestClass : public ConnectionTracker
{
public:

  TestClass()
  {
  }

  ~TestClass()
  {
  }

  void Initialize()
  {
    mActor = Actor::New();
    Stage::GetCurrent().Add( mActor );
    mNotification = mActor.AddPropertyNotification( Actor::POSITION_X, GreaterThanCondition(100.0f) );
    mNotification.NotifySignal().Connect( this, &TestClass::OnPropertyNotify );
  }

  void RemovePropertyNotification()
  {
    mActor.RemovePropertyNotification( mNotification );
  }

  void RemovePropertyNotifications()
  {
    mActor.RemovePropertyNotifications();
  }

  void Terminate()
  {
    Stage::GetCurrent().Remove( mActor );
    mActor.Reset();
    mNotification.Reset();
  }

  void OnPropertyNotify( PropertyNotification& source )
  {
    tet_infoline(" OnPropertyNotify");
    gCallBackCalled = true;
  }

  Actor mActor;
  PropertyNotification mNotification;
};


/*
 * Simulate time passed by.
 *
 * @note this will always process at least 1 frame (1/60 sec)
 *
 * @param application Test application instance
 * @param duration Time to pass in milliseconds.
 * @return The actual time passed in milliseconds
 */
int Wait(TestApplication& application, int duration = 0)
{
  int time = 0;

  for(int i = 0; i <= ( duration / RENDER_FRAME_INTERVAL); i++)
  {
    application.SendNotification();
    application.Render(RENDER_FRAME_INTERVAL);
    time += RENDER_FRAME_INTERVAL;
  }

  return time;
}

// Called only once before first test is run.
static void Startup()
{
}

// Called only once after last test is run
static void Cleanup()
{
}

// Positive test case for a method
static void UtcDaliPropertyNotificationDownCast()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationDownCast");

  Actor actor = Actor::New();
  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X, GreaterThanCondition(100.0f));
  BaseHandle handle = notification;
  PropertyNotification notificationHandle;

  DALI_TEST_CHECK(notification);
  DALI_TEST_CHECK(handle);
  DALI_TEST_CHECK(!notificationHandle);

  notificationHandle = PropertyNotification::DownCast( handle );
  DALI_TEST_CHECK(notificationHandle);
}


// Negative test case for a method
static void UtcDaliPropertyNotificationDownCastNegative()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationDownCastNegative");

  // Create something derived from BaseHandle other than a PropertyNotification.
  Actor somethingElse = Actor::New();

  Actor actor = Actor::New();
  actor.AddPropertyNotification(Actor::POSITION_X, GreaterThanCondition(100.0f));
  BaseHandle handle = somethingElse;
  PropertyNotification notificationHandle;

  notificationHandle = PropertyNotification::DownCast( handle );
  DALI_TEST_CHECK(!notificationHandle);
}

static void UtcDaliAddPropertyNotification()
{
  TestApplication application; // Reset all test adapter return codes
  tet_infoline(" UtcDaliAddPropertyNotification");

  Actor actor = Actor::New();

  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X, GreaterThanCondition(100.0f));
  DALI_TEST_CHECK( notification );
}

static void UtcDaliAddPropertyNotificationCallback()
{
  TestApplication application; // Reset all test adapter return codes

  TestClass* object = new TestClass;

  object->Initialize();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();

  gCallBackCalled = false;

  tet_infoline(" UtcDaliAddPropertyNotificationCallback - Forcing notification condition true, should receive a notification");
  object->mActor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  DALI_TEST_CHECK( gCallBackCalled );
  gCallBackCalled = false;

  tet_infoline(" UtcDaliAddPropertyNotificationCallback - Forcing notification condition false, should not receive a notification");
  object->mActor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  DALI_TEST_CHECK( !gCallBackCalled );
  gCallBackCalled = false;

  tet_infoline(" UtcDaliAddPropertyNotificationCallback - Deleting notification and it's owning object, should not receive a notification");
  object->mActor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  object->Terminate();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  DALI_TEST_CHECK( !gCallBackCalled );

  tet_infoline(" UtcDaliAddPropertyNotificationCallback - Removing notification and it's owning object, should not receive a notification");
  object->Initialize();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  gCallBackCalled = false;

  object->RemovePropertyNotification();

  object->mActor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  DALI_TEST_CHECK( !gCallBackCalled );

  tet_infoline(" UtcDaliAddPropertyNotificationCallback - Removing all notifications and it's owning object, should not receive a notification");
  object->Initialize();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  gCallBackCalled = false;

  object->RemovePropertyNotifications();

  object->mActor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  application.Render(RENDER_FRAME_INTERVAL);
  application.SendNotification();
  DALI_TEST_CHECK( !gCallBackCalled );


  delete object;
}

void UtcDaliAddPropertyNotificationTypeProperty()
{
  TestApplication application;

  Actor actor = Actor::New();

  // Currently, Type registry properties cannot be animated
  try
  {
    actor.AddPropertyNotification( PROPERTY_REGISTRATION_START_INDEX, GreaterThanCondition( 100.0f ) );
  }
  catch ( DaliException& e )
  {
    DALI_TEST_ASSERT_CONDITION_STARTS_WITH_SUBSTRING( e, "false && \"Property notification added to non animatable property", TEST_LOCATION );
  }
}

static void UtcDaliPropertyNotificationGetCondition()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGetCondition");

  Actor actor = Actor::New();

  PropertyCondition condition = GreaterThanCondition(100.0f);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X, condition);
  DALI_TEST_CHECK( condition == notification.GetCondition() );
}

class PropertyNotificationConstWrapper
{
public:

  PropertyNotificationConstWrapper(PropertyNotification propertyNotification)
  :mPropertyNotification(propertyNotification)
  {

  }

  /**
   * Returns const reference to property notification.
   * @return const reference.
   */
  const PropertyCondition& GetCondition() const
  {
    return mPropertyNotification.GetCondition();
  }

  PropertyNotification mPropertyNotification;
};

static void UtcDaliPropertyNotificationGetConditionConst()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGetConditionConst");

  Actor actor = Actor::New();

  PropertyCondition condition = GreaterThanCondition(100.0f);
  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X, condition);
  PropertyNotificationConstWrapper notificationConst(notification);
  const PropertyCondition& conditionReference1 = notificationConst.GetCondition();
  const PropertyCondition& conditionReference2 = notificationConst.GetCondition();

  DALI_TEST_CHECK( (&conditionReference1) == (&conditionReference2) );
  DALI_TEST_CHECK( conditionReference1 == condition );
}

static void UtcDaliPropertyNotificationGetTarget()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGetTarget");

  Actor actor = Actor::New();
  Actor actor2 = Actor::New();

  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X,
                                                                    GreaterThanCondition(100.0f));
  Actor targetActor = Actor::DownCast( notification.GetTarget() );

  DALI_TEST_CHECK( targetActor == actor );
}

static void UtcDaliPropertyNotificationGetProperty()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGetProperty");

  Actor actor = Actor::New();

  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X,
                                                                    GreaterThanCondition(100.0f));
  Property::Index targetProperty = notification.GetTargetProperty();

  DALI_TEST_EQUALS( targetProperty, Actor::POSITION_X, TEST_LOCATION );
}

static void UtcDaliPropertyNotificationGetNotifyMode()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGetNotifyMode");

  Actor actor = Actor::New();

  PropertyNotification notification = actor.AddPropertyNotification(Actor::POSITION_X,
                                                                    GreaterThanCondition(100.0f));
  notification.SetNotifyMode(PropertyNotification::NotifyOnChanged);
  PropertyNotification::NotifyMode notifyMode = notification.GetNotifyMode();

  DALI_TEST_EQUALS( notifyMode, PropertyNotification::NotifyOnChanged, TEST_LOCATION );
}

static void UtcDaliPropertyNotificationGreaterThan()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGreaterThan");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION_X, GreaterThanCondition(100.0f) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move right to satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move left to un-satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( !gCallBackCalled );

  // Move right to satisfy condition again.
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationLessThan()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationLessThan");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION_X, LessThanCondition(100.0f ) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move left to satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move right to un-satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( !gCallBackCalled );

  // Move left to satisfy condition again.
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationInside()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationInside");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION_X, InsideCondition(100.0f, 200.0f) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move inside to satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(150.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move outside (right) to un-satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(300.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( !gCallBackCalled );

  // Move inside to satisfy condition again.
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(150.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationOutside()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationOutside");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION_X, OutsideCondition(100.0f, 200.0f) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(150.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move outside (left) to satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move inside to un-satisfy condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(150.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( !gCallBackCalled );

  // Move outside (right) to satisfy condition again.
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(300.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationVectorComponentGreaterThan()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationGreaterThan");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, GreaterThanCondition(100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 1, GreaterThanCondition(100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 2, GreaterThanCondition(100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::COLOR, 3, GreaterThanCondition(0.5f) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move right to satisfy XAxis condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move down to satisfy YAxis condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move forward to satisfy ZAxis
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(200.0f, 200.0f, 200.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Change alpha Colour to satisfy w/alpha component condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationVectorComponentLessThan()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationLessThan");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, LessThanCondition(-100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 1, LessThanCondition(-100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 2, LessThanCondition(-100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::COLOR, 3, LessThanCondition(0.5f) );
  notification.NotifySignal().Connect( &TestCallback );

  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move left to satisfy XAxis condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(-200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move up to satisfy YAxis condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(-200.0f, -200.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move back to satisfy ZAxis
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(-200.0f, -200.0f, -200.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Change alpha Colour to satisfy w/alpha component condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationVectorComponentInside()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationInside");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, InsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 1, InsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 2, InsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::COLOR, 3, InsideCondition(0.25f, 0.75f) );
  notification.NotifySignal().Connect( &TestCallback );

  // set outside all conditions
  actor.SetPosition(Vector3(200.0f, 200.0f, 200.0f));
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move x to inside condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(0.0f, 200.0f, 200.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move y to inside condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(0.0f, 0.0f, 200.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move z to inside condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // change alpha to inside condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.5f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyNotificationVectorComponentOutside()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationOutside");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, OutsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 1, OutsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::POSITION, 2, OutsideCondition(-100.0f, 100.0f) );
  notification.NotifySignal().Connect( &TestCallback );
  notification = actor.AddPropertyNotification( Actor::COLOR, 3, OutsideCondition(0.25f, 0.75f) );
  notification.NotifySignal().Connect( &TestCallback );

  // set inside all conditions
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.5f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // Move x to outside condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move y to outside condition
  gCallBackCalled = false;
  actor.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // Move z to outside condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetPosition(Vector3(200.0f, 200.0f, 200.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );

  // change alpha to outside condition
  gCallBackCalled = false;
  Wait(application, DEFAULT_WAIT_PERIOD);
  actor.SetColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);
  DALI_TEST_CHECK( gCallBackCalled );
}

static void UtcDaliPropertyConditionGetArguments()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyConditionGetArguments");

  PropertyCondition condition = GreaterThanCondition( 50.0f );
  PropertyCondition::ArgumentContainer arguments = condition.GetArguments();

  DALI_TEST_EQUALS( arguments.size(), 1u, TEST_LOCATION );
  Property::Value value = arguments[0];
  DALI_TEST_EQUALS( value.Get<float>(), 50.0f, TEST_LOCATION );

  condition = InsideCondition( 125.0f, 250.0f );
  arguments = condition.GetArguments();

  DALI_TEST_EQUALS( arguments.size(), 2u, TEST_LOCATION );
  Property::Value value1 = arguments[0];
  Property::Value value2 = arguments[1];
  DALI_TEST_EQUALS( value1.Get<float>(), 125.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( value2.Get<float>(), 250.0f, TEST_LOCATION );
}

class PropertyConditionConstWrapper
{
public:

  PropertyConditionConstWrapper(PropertyCondition propertyCondition)
  :mPropertyCondition(propertyCondition)
  {

  }

  /**
   * Returns const reference to property arguments.
   * @return const reference.
   */
  const PropertyCondition::ArgumentContainer& GetArguments() const
  {
    return mPropertyCondition.GetArguments();
  }

  PropertyCondition mPropertyCondition;
};

static void UtcDaliPropertyConditionGetArgumentsConst()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyConditionGetArgumentsConst");

  PropertyCondition condition = GreaterThanCondition( 50.0f );
  PropertyConditionConstWrapper conditionConst(condition);
  const PropertyCondition::ArgumentContainer& argumentsRef1 = conditionConst.GetArguments();
  const PropertyCondition::ArgumentContainer& argumentsRef2 = conditionConst.GetArguments();

  DALI_TEST_CHECK( (&argumentsRef1) == (&argumentsRef2) );
  DALI_TEST_EQUALS( argumentsRef1.size(), 1u, TEST_LOCATION );
  Property::Value value = argumentsRef1[0];
  DALI_TEST_EQUALS( value.Get<float>(), 50.0f, TEST_LOCATION );
}

static void UtcDaliPropertyNotificationStep()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationStep");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  const float step = 100.0f;
  // float
  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, StepCondition(step, 50.0f) );
  notification.NotifySignal().Connect( &TestCallback );

  // set initial position
  actor.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  // test both directions
  for( int i = 1 ; i < 10 ; ++i )
  {
    // Move x to negative position
    gCallBackCalled = false;
    actor.SetPosition(Vector3((i * step), 0.0f, 0.0f));
    Wait(application, DEFAULT_WAIT_PERIOD);
    DALI_TEST_CHECK( gCallBackCalled );
  }

  for( int i = 1 ; i < 10 ; ++i )
  {
    // Move x to negative position
    gCallBackCalled = false;
    actor.SetPosition(Vector3(-(i * step), 0.0f, 0.0f));
    Wait(application, DEFAULT_WAIT_PERIOD);
    DALI_TEST_CHECK( gCallBackCalled );
  }
}

static void UtcDaliPropertyNotificationVariableStep()
{
  TestApplication application;
  tet_infoline(" UtcDaliPropertyNotificationStep");

  Actor actor = Actor::New();
  Stage::GetCurrent().Add(actor);

  std::vector<float> values;

  const float averageStep = 100.0f;

  for( int i = 1 ; i < 10 ; i++ )
  {
    values.push_back(i * averageStep + (i % 2 == 0 ? -(averageStep * 0.2f) : (averageStep * 0.2f)));
  }
  // float
  PropertyNotification notification = actor.AddPropertyNotification( Actor::POSITION, 0, VariableStepCondition(values) );
  notification.NotifySignal().Connect( &TestCallback );

  // set initial position lower than first position in list
  actor.SetPosition(Vector3(values[0] - averageStep, 0.0f, 0.0f));
  Wait(application, DEFAULT_WAIT_PERIOD);

  for( int i = 0 ; i < values.size() - 1 ; ++i )
  {
    gCallBackCalled = false;
    // set position half way between the current values
    float position = values[i] + (0.5f * (values[i + 1] - values[i]));
    actor.SetPosition(Vector3(position, 0.0f, 0.0f));
    Wait(application, DEFAULT_WAIT_PERIOD);
    DALI_TEST_CHECK( gCallBackCalled );
  }
}
