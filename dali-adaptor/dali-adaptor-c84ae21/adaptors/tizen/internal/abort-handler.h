#ifndef __DALI_INTERNAL_ADAPTOR_ABORT_HANDLER_H__
#define __DALI_INTERNAL_ADAPTOR_ABORT_HANDLER_H__

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

#include <signal.h>
#include "public-api/adaptor-framework/application.h"

namespace Dali
{
namespace Internal
{
namespace Adaptor
{

/**
 * Class to listen to system signals and trigger an abort callback
 * when they occur.
 *
 * This class maintains a process wide singleton, as the signal(2) system
 * call is process specific, not thread specific.
 *
 * Currently, this precludes having multiple DALi instances in the same process.
 */
class AbortHandler
{
public:
  /**
   * Constructor
   * @param[in] callback The function to call when abort signals occur
   */
  AbortHandler(boost::function<void(void)> callback);

  /**
   * Destructor
   */
  ~AbortHandler();

  /**
   * Add a signal you want to be handled by this abort handler.
   * @param[in] signum The signal number (from signum.h)
   * @return true if the signal handler was installed ok
   */
  bool AbortOnSignal( int signum );

private:
  /**
   * Signal handler - Called when signal is received.
   * Stops the application.
   */
  static void SignalHandler( int signum );

  /**
   * Default constructor - undefined
   */
  AbortHandler();

  /**
   * Copy constructor - undefined
   */
  AbortHandler(const AbortHandler& rhs);

  /**
   * Assignment operator - undefined
   */
  AbortHandler& operator=(const AbortHandler& rhs);

private:
  typedef void (*SignalHandlerFuncPtr )( int );

  // _NSIG comes from the signal.h linux system header, defining the number of signals.
  SignalHandlerFuncPtr        mSignalOldHandlers[_NSIG-1];
  unsigned long long          mSignalMask;

  boost::function<void(void)> mCallback;

  static AbortHandler*        gInstance;
};

} // Namespace Adaptor
} // Namespace Internal
} // Namespace Dali

#endif //  __DALI_INTERNAL_ADAPTOR_ABORT_HANDLER_H__
