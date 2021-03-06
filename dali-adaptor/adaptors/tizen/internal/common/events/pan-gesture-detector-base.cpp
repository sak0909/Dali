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
#include "pan-gesture-detector-base.h"

// EXTERNAL INCLUDES
#include <cmath>

#include <dali/public-api/events/touch-point.h>

#include <dali/integration-api/events/gesture-requests.h>
#include <dali/integration-api/events/touch-event-integ.h>

// INTERNAL INCLUDES

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

namespace
{
// TODO: Used DPD Value.
const float MINIMUM_MOTION_BEFORE_PAN_SQUARED( 10.0f * 10.0f );
const unsigned long MAXIMUM_TIME_DIFF_ALLOWED( 500 );
} // unnamed namespace

PanGestureDetectorBase::PanGestureDetectorBase(Vector2 screenSize, const Integration::PanGestureRequest& request)
: GestureDetector(screenSize, Gesture::Pan),
  mState(Clear),
  mPrimaryTouchDownTime(0),
  mMinimumTouchesRequired(request.minTouches),
  mMaximumTouchesRequired(request.maxTouches)
{
}

PanGestureDetectorBase::~PanGestureDetectorBase()
{
}

void PanGestureDetectorBase::SendEvent(const Integration::TouchEvent& event)
{
  TouchPoint::State primaryPointState(event.points[0].state);

  if (primaryPointState == TouchPoint::Interrupted)
  {
    if ( ( mState == Started ) || ( mState == Possible ) )
    {
      // If our pan had started and we are interrupted, then tell Core that pan is cancelled.
      mTouchEvents.push_back(event);
      SendPan(Gesture::Cancelled, event);
    }
    mState = Clear; // We should change our state to Clear.
    mTouchEvents.clear();
  }
  else
  {
    switch (mState)
    {
      case Clear:
      {
        if (primaryPointState == TouchPoint::Down)
        {
          mPrimaryTouchDownLocation = event.points[0].screen;
          mPrimaryTouchDownTime = event.time;
          if (event.GetPointCount() == mMinimumTouchesRequired)
          {
            // We have satisfied the minimum touches required for a pan, tell core that a gesture may be possible and change our state accordingly.
            mState = Possible;
            SendPan(Gesture::Possible, event);
          }

          mTouchEvents.push_back(event);
        }
        break;
      }

      case Possible:
      {
        unsigned int pointCount(event.GetPointCount());
        if ( (pointCount >= mMinimumTouchesRequired)&&(pointCount <= mMaximumTouchesRequired) )
        {
          if (primaryPointState == TouchPoint::Motion)
          {
            mTouchEvents.push_back(event);

            Vector2 delta(event.points[0].screen - mPrimaryTouchDownLocation);

            if (delta.LengthSquared() >= MINIMUM_MOTION_BEFORE_PAN_SQUARED)
            {
              // If the touch point(s) have moved enough distance to be considered a pan, then tell Core that the pan gesture has started and change our state accordingly.
              mState = Started;
              SendPan(Gesture::Started, event);
            }
          }
          else if (primaryPointState == TouchPoint::Up)
          {
            Vector2 delta(event.points[0].screen - mPrimaryTouchDownLocation);
            if(delta.LengthSquared() >= MINIMUM_MOTION_BEFORE_PAN_SQUARED)
            {
              SendPan(Gesture::Started, event);
              mTouchEvents.push_back(event);
              SendPan(Gesture::Finished, event);
            }
            else
            {
              // If we have lifted the primary touch point then tell core the pan is cancelled and change our state to Clear.
              SendPan(Gesture::Cancelled, event);
            }
            mState = Clear;
            mTouchEvents.clear();
          }
        }
        else
        {
          // We do not satisfy pan conditions, tell Core our Gesture has been cancelled.
          SendPan(Gesture::Cancelled, event);

          if (pointCount == 1 && primaryPointState == TouchPoint::Up)
          {
            // If we have lifted the primary touch point, then change our state to Clear...
            mState = Clear;
            mTouchEvents.clear();
          }
          else
          {
            // ...otherwise change it to Failed.
            mState = Failed;
          }
        }
        break;
      }

      case Started:
      {
        mTouchEvents.push_back(event);

        unsigned int pointCount(event.GetPointCount());
        if ( (pointCount >= mMinimumTouchesRequired)&&(pointCount <= mMaximumTouchesRequired) )
        {
          switch (primaryPointState)
          {
            case TouchPoint::Motion:
              // Pan is continuing, tell Core.
              SendPan(Gesture::Continuing, event);
              break;

            case TouchPoint::Up:
              // Pan is finally finished when our primary point is lifted, tell Core and change our state to Clear.
              SendPan(Gesture::Finished, event);
              mState = Clear;
              mTouchEvents.clear();
              break;

            case TouchPoint::Stationary:
              if (pointCount == mMinimumTouchesRequired)
              {
                std::vector<TouchPoint>::const_iterator iter = event.points.begin() + 1; // We already know the state of the first point
                for(; iter != event.points.end(); ++iter)
                {
                  if(iter->state == TouchPoint::Up)
                  {
                    // The number of touch points will be less than the minimum required.  Inform core and change our state to Finished.
                    SendPan(Gesture::Finished, event);
                    mState = Finished;
                    break;
                  }
                }
              }
              break;

            default:
              break;
          }
        }
        else
        {
          // We have gone outside of the pan requirements, inform Core that the gesture is finished.
          SendPan(Gesture::Finished, event);

          if (pointCount == 1 && primaryPointState == TouchPoint::Up)
          {
            // If this was the primary point being released, then we change our state back to Clear...
            mState = Clear;
            mTouchEvents.clear();
          }
          else
          {
            // ...otherwise we change it to Finished.
            mState = Finished;
          }
        }
        break;
      }

      case Finished:
      case Failed:
      {
        if (primaryPointState == TouchPoint::Up)
        {
          // Change our state back to clear when the primary touch point is released.
          mState = Clear;
          mTouchEvents.clear();
        }
        break;
      }
    }
  }
}

void PanGestureDetectorBase::Update(const Integration::GestureRequest& request)
{
  const Integration::PanGestureRequest& pan = static_cast<const Integration::PanGestureRequest&>(request);

  mMinimumTouchesRequired = pan.minTouches;
  mMaximumTouchesRequired = pan.maxTouches;
}

void PanGestureDetectorBase::SendPan(Gesture::State state, const Integration::TouchEvent& currentEvent)
{
  Integration::PanGestureEvent gesture(state);
  gesture.currentPosition = currentEvent.points[0].screen;
  gesture.numberOfTouches = currentEvent.GetPointCount();

  if ( mTouchEvents.size() > 1 )
  {
    // Get the second last event in the queue, the last one is the current event
    const Integration::TouchEvent& previousEvent( *( mTouchEvents.rbegin() + 1 ) );

    Vector2 previousPosition( previousEvent.points[0].screen );
    unsigned long previousTime( previousEvent.time );

    // If we've just started then we want to remove the threshold from Core calculations.
    if ( state == Gesture::Started )
    {
      previousPosition = mPrimaryTouchDownLocation;
      previousTime = mPrimaryTouchDownTime;
    }

    gesture.previousPosition = previousPosition;
    gesture.timeDelta = currentEvent.time - previousTime;
  }
  else
  {
    gesture.previousPosition = gesture.currentPosition;
    gesture.timeDelta = 0;
  }

  gesture.time = currentEvent.time;

  EmitPan(gesture);
}

} // namespace Adaptor

} // namespace Internal

} // namespace Dali
