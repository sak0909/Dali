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
#include "update-render-synchronization.h"

// INTERNAL INCLUDES
#include <dali/integration-api/debug.h>
#include <base/interfaces/adaptor-internal-services.h>

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

namespace
{

const unsigned int MICROSECONDS_PER_SECOND( 1000000 );
const unsigned int INPUT_EVENT_UPDATE_PERIOD( MICROSECONDS_PER_SECOND / 90 ); // period between ecore x event updates

} // unnamed namespace

UpdateRenderSynchronization::UpdateRenderSynchronization( AdaptorInternalServices& adaptorInterfaces )
: mMaximumUpdateCount( adaptorInterfaces.GetCore().GetMaximumUpdateCount()),
  mUpdateReadyCount( 0u ),
  mRunning( false ),
  mUpdateRequired( false ),
  mPaused( false ),
  mUpdateRequested( false ),
  mAllowUpdateWhilePaused( false ),
  mVSyncSleep( false ),
  mVSyncFrameNumber( 0u ),
  mVSyncSeconds( 0u ),
  mVSyncMicroseconds( 0u ),
  mCore( adaptorInterfaces.GetCore() ),
  mPerformanceInterface( adaptorInterfaces.GetPerformanceInterface() ),
  mSkipNextVSync( false )
{
}

UpdateRenderSynchronization::~UpdateRenderSynchronization()
{
}

void UpdateRenderSynchronization::Start()
{
  mRunning = true;
}

void UpdateRenderSynchronization::Stop()
{
  mRunning = false;

  // Wake if sleeping
  UpdateRequested();

  // we may be paused so need to resume
  Resume();

  // Notify all condition variables, so if threads are waiting
  // they can break out, and check the running status.
  mUpdateFinishedCondition.notify_one();
  mRenderFinishedCondition.notify_one();
  mVSyncSleepCondition.notify_one();
  mVSyncReceivedCondition.notify_one();
}

void UpdateRenderSynchronization::Pause()
{
  mPaused = true;

  AddPerformanceMarker( PerformanceMarker::PAUSED );

}

void UpdateRenderSynchronization::Resume()
{
  mPaused = false;
  mVSyncSleep = false;

  mPausedCondition.notify_one();
  mVSyncSleepCondition.notify_one();

  AddPerformanceMarker( PerformanceMarker::RESUME);
}

void UpdateRenderSynchronization::UpdateRequested()
{
  mUpdateRequested = true;

  // Wake update thread if sleeping
  mUpdateSleepCondition.notify_one();
}

void UpdateRenderSynchronization::UpdateWhilePaused()
{
  {
    boost::unique_lock< boost::mutex > lock( mMutex );

    mAllowUpdateWhilePaused = true;
  }

  // wake vsync if sleeping
  mVSyncSleepCondition.notify_one();
  // Wake update if sleeping
  mUpdateSleepCondition.notify_one();
  // stay paused but notify the pause condition
  mPausedCondition.notify_one();
}

void UpdateRenderSynchronization::UpdateReadyToRun()
{
  bool wokenFromPause( false );

  // atomic check first to avoid mutex lock in 99.99% of cases
  if( mPaused )
  {
    boost::unique_lock< boost::mutex > lock( mMutex );

    // wait while paused
    while( mPaused && !mAllowUpdateWhilePaused )
    {
      // this will automatically unlock mMutex
      mPausedCondition.wait( lock );

      wokenFromPause = true;
    }
  }

  if ( !wokenFromPause && !mSkipNextVSync)
  {
    // Wait for the next VSync
    WaitVSync();
  }

  mSkipNextVSync = false;

  AddPerformanceMarker( PerformanceMarker::UPDATE_START );
}

bool UpdateRenderSynchronization::UpdateSyncWithRender( bool& renderNeedsUpdate )
{

  AddPerformanceMarker( PerformanceMarker::UPDATE_END );

  boost::unique_lock< boost::mutex > lock( mMutex );

  // Another frame was prepared for rendering; increment counter
  ++mUpdateReadyCount;
  DALI_ASSERT_DEBUG( mUpdateReadyCount <= mMaximumUpdateCount );

  // Notify the render-thread that an update has completed
  mUpdateFinishedCondition.notify_one();

  // The update-thread must wait until a frame has been rendered, when mMaximumUpdateCount is reached
  while( mRunning && ( mMaximumUpdateCount == mUpdateReadyCount ) )
  {
    // Wait will atomically add the thread to the set of threads waiting on
    // the condition variable mRenderFinishedCondition and unlock the mutex.
    mRenderFinishedCondition.wait( lock );
  }

  renderNeedsUpdate = mUpdateRequired;

  // Flag is used to during UpdateThread::Stop() to exit the update/render loops
  return mRunning;
}

void UpdateRenderSynchronization::UpdateWaitForAllRenderingToFinish()
{
  boost::unique_lock< boost::mutex > lock( mMutex );

  // Wait for all of the prepared frames to be rendered
  while ( mRunning && ( 0u != mUpdateReadyCount ) && !mUpdateRequested )
  {
    // Wait will atomically add the thread to the set of threads waiting on
    // the condition variable mRenderFinishedCondition and unlock the mutex.
    mRenderFinishedCondition.wait( lock );
  }
}

bool UpdateRenderSynchronization::UpdateTryToSleep()
{
  if ( !mUpdateRequired && !mUpdateRequested )
  {
    // there's nothing to update in the scene, so wait for render to finish processing
    UpdateWaitForAllRenderingToFinish();
  }

  boost::mutex sleepMutex;
  boost::unique_lock< boost::mutex > lock( sleepMutex );

  while( mRunning && !mUpdateRequired && !mUpdateRequested )
  {
    //
    // Going to sleep
    //

    // 1. put VSync thread to sleep.
    mVSyncSleep = true;

    // 2. inform Core
    mCore.Sleep();

    // 3. block thread and wait for wakeup event
    mUpdateSleepCondition.wait( lock );

    //
    // Woken up
    //

    // 1. inform Core
    mCore.WakeUp();

    // 2. wake VSync thread.
    mVSyncSleep = false;
    mVSyncSleepCondition.notify_one();

    // 3. Update shouldn't wait for next VSync
    mSkipNextVSync = true;
  }

  mUpdateRequested = false;

  return mRunning;
}

void UpdateRenderSynchronization::RenderFinished( bool updateRequired )
{
  {
    boost::unique_lock< boost::mutex > lock( mMutex );

    // Set the flag to say if update needs to run again.
    mUpdateRequired = updateRequired;

    // A frame has been rendered; decrement counter
    --mUpdateReadyCount;
    DALI_ASSERT_DEBUG( mUpdateReadyCount < mMaximumUpdateCount );
  }

  // Notify the update-thread that a render has completed
  mRenderFinishedCondition.notify_one();

  AddPerformanceMarker( PerformanceMarker::RENDER_END );
}

bool UpdateRenderSynchronization::RenderSyncWithUpdate()
{
  boost::unique_lock< boost::mutex > lock( mMutex );

  // Wait for update to produce a buffer, or for the mRunning state to change
  while ( mRunning && ( 0u == mUpdateReadyCount ) )
  {
    // Wait will atomically add the thread to the set of threads waiting on
    // the condition variable mUpdateFinishedCondition and unlock the mutex.
    mUpdateFinishedCondition.wait( lock );
  }

  if( mRunning )
  {
    AddPerformanceMarker( PerformanceMarker::RENDER_START );
  }
  // Flag is used to during UpdateThread::Stop() to exit the update/render loops
  return mRunning;
}

void UpdateRenderSynchronization::WaitVSync()
{
  // Block until the start of a new vsync.
  // If we're experiencing slowdown and are behind by more than a frame
  // then we should wait for the next frame as the Video output will also
  // do this (lock-step to 60Hz)

  unsigned int updateFrameNumber = mVSyncFrameNumber;

  boost::unique_lock< boost::mutex > lock( mMutex );

  while ( mRunning && ( updateFrameNumber == mVSyncFrameNumber ) )
  {
    // Wait will atomically add the thread to the set of threads waiting on
    // the condition variable mVSyncReceivedCondition and unlock the mutex.
    mVSyncReceivedCondition.wait( lock );
  }

  // reset update while paused flag
  mAllowUpdateWhilePaused = false;
}

bool UpdateRenderSynchronization::VSyncNotifierSyncWithUpdateAndRender( unsigned int frameNumber, unsigned int seconds, unsigned int microseconds )
{
  boost::unique_lock< boost::mutex > lock( mMutex );

  mVSyncFrameNumber = frameNumber;
  mVSyncSeconds = seconds;
  mVSyncMicroseconds = microseconds;

  mVSyncReceivedCondition.notify_all();

  AddPerformanceMarker( PerformanceMarker::V_SYNC );

  while( mRunning && // sleep on condition variable WHILE still running
         !mAllowUpdateWhilePaused &&             // AND NOT allowing updates while paused
         ( mVSyncSleep || mPaused ) )            // AND sleeping OR paused
  {
    // Wait will atomically add the thread to the set of threads waiting on
    // the condition variable mVSyncSleepCondition and unlock the mutex.
    mVSyncSleepCondition.wait( lock );
  }

  return mRunning;
}

unsigned int UpdateRenderSynchronization::GetFrameNumber() const
{
  return mVSyncFrameNumber;
}

uint64_t UpdateRenderSynchronization::GetTimeMicroseconds()
{
  uint64_t currentTime(0);

  {
    boost::unique_lock< boost::mutex > lock( mMutex );

    currentTime = mVSyncSeconds;
    currentTime *= MICROSECONDS_PER_SECOND;
    currentTime += mVSyncMicroseconds;
  }

  return currentTime;
}

inline void UpdateRenderSynchronization::AddPerformanceMarker( PerformanceMarker::MarkerType type )
{
  if( mPerformanceInterface )
  {
    mPerformanceInterface->AddMarker( type );
  }
}

} // namespace Adaptor

} // namespace Internal

} // namespace Dali
