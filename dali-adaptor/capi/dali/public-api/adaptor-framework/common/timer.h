#ifndef __DALI_TIMER_H__
#define __DALI_TIMER_H__

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

/**
 * @addtogroup CAPI_DALI_ADAPTOR_MODULE
 * @{
 */

// EXTERNAL INCLUDES

#include <dali/public-api/object/base-handle.h>
#include <dali/public-api/signals/dali-signal-v2.h>

namespace Dali DALI_IMPORT_API
{

namespace Internal DALI_INTERNAL
{
namespace Adaptor
{
class Timer;
}
}

/**
 * @brief Mechanism to issue simple periodic or one-shot events.
 *
 * Timer is provided for application developers to be able to issue
 * simple periodic or one-shot events.  Please note that timer
 * callback functions should return as soon as possible, because they
 * block the next SignalTick.  Please note that timer signals are not
 * in sync with Dali's render timer.
 *
 * This class is a handle class so it can be stack allocated and used
 * as a member.
 */
class Timer : public BaseHandle
{
public: // Signal typedefs

  typedef SignalV2< bool () > TimerSignalV2; ///< Timer finished signal callback type

public: // API

  /**
   * @brief Constructor, creates an uninitialized timer.
   *
   * Call New to fully construct a timer.
   */
  Timer();

  /**
   * @brief Create an tick Timer that emits periodic signal.
   *
   * @param[in] milliSec Interval in milliseconds.
   * @return a new timer
   */
  static Timer New( unsigned int milliSec );

  /**
   * @brief Copy constructor.
   *
   * @param[in] timer The handle to copy. The copied handle will point at the same implementation
   */
  Timer( const Timer& timer );

  /**
   * @brief Assignment operator.
   *
   * @param[in] timer The handle to copy. This handle will point at the same implementation
   * as the copied handle.
   * @return Reference to this timer handle
   */
  Timer& operator=( const Timer& timer );

  /**
   * @brief Destructor.
   */
  virtual ~Timer();

  /**
   * @brief Downcast an Object handle to Timer handle.
   *
   * If handle points to a Timer object the downcast produces a valid
   * handle. If not the returned handle is left uninitialized.
   *
   * @param[in] handle to An object
   * @return handle to a Timer object or an uninitialized handle
   */
  static Timer DownCast( BaseHandle handle );

  /**
   * @copydoc Dali::BaseHandle::operator=
   */
  using BaseHandle::operator=;

  /**
   * @brief Start timer.
   *
   * In case a Timer is already running it's time is reset and timer is restarted.
   */
  void Start();

  /**
   * @brief Stop timer.
   */
  void Stop();

  /**
   * @brief Sets a new interval on the timer and starts the timer.
   *
   * Cancels the previous timer.
   * @param  milliSec Interval in milliseconds.
   */
  void SetInterval( unsigned int milliSec );

  /**
   * @brief Get the interval of timer.
   * @returns  Interval in milliseconds.
   */
  unsigned int GetInterval() const;

  /**
   * @brief  Tells whether timer is running.
   * @return Whether Timer is started or not.
   */
  bool IsRunning() const;

public: // Signals

  /**
   * @brief Signal emitted after specified time interval.
   *
   * The return of the callback decides whether signal emission stops or continues.
   * If the callback function returns false emission will stop, if true it will continue
   * This return value is ignored for one-shot events, which will always stop after the first execution.
   * @returns The signal to Connect() with.
   */
  TimerSignalV2& TickSignal();

public: // Not intended for application developers
  explicit DALI_INTERNAL Timer(Internal::Adaptor::Timer* timer);
};

} // namespace Dali

/**
 * @}
 */
#endif // __DALI_TIMER_H__
