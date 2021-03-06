#ifndef __DALI_INTERNAL_VSYNC_MONITOR_IMPL_H__
#define __DALI_INTERNAL_VSYNC_MONITOR_IMPL_H__

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

// EXTERNAL INCLUDES
#include <xf86drm.h>

// INTERNAL INCLUDES
#include <base/interfaces/vsync-monitor-interface.h>

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

/**
 * Tizen interface for monitoring VSync
 */
class VSyncMonitor : public VSyncMonitorInterface
{
public:
  /**
   * Default constructor
   */
  VSyncMonitor();

  /**
   * Destructor
   */
  virtual ~VSyncMonitor();

public:

  /**
   * Set the use hardware flag
   * @param[in] useHardware The new state for the use hardware flag.
   */
  void SetUseHardware( bool useHardware );

private: // From Dali::Internal::Adaptor::VSyncMonitorInterface

  /**
   * copydoc Dali::Internal::Adaptor::VSyncMonitorInterface::Initialize
   */
  virtual void Initialize();

  /**
   * copydoc Dali::Internal::Adaptor::VSyncMonitorInterface::Terminate
   */
  virtual void Terminate();

  /**
   * copydoc Dali::Internal::Adaptor::VSyncMonitorInterface::UseHardware
   */
  virtual bool UseHardware();

  /**
   * copydoc Dali::Internal::Adaptor::VSyncMonitorInterface::DoSync
   */
  virtual bool DoSync( unsigned int& frameNumber, unsigned int& seconds, unsigned int& microseconds );

private:

  int       mFileDescriptor;  ///< DRM dev node file descriptor
  drmVBlank mVBlankInfo;
  bool      mUseHardware;     ///< Hardware VSyncs available flag

};

} // namespace Adaptor

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_VSYNC_MONITOR_IMPL_H__
