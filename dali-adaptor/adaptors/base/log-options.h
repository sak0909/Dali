#ifndef __DALI_INTERNAL_ADAPTOR_LOG_OPTIONS_H__
#define __DALI_INTERNAL_ADAPTOR_LOG_OPTIONS_H__

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

#include <dali/integration-api/debug.h>

namespace Dali
{
namespace Internal
{
namespace Adaptor
{

/**
 * Contains log settings and the ability to install a log function.
 */
class LogOptions
{

public:

  /**
   * Constructor
   */
  LogOptions();

  /**
   * non-virtual destructor, not intended as a base class
   */
  ~LogOptions();

  /**
   * @param logFunction logging function
   * @param logFilterOptions bitmask of the logging options defined in intergration/debug.h (e.g.
   * @param logFrameRateFrequency frequency of how often FPS is logged out (e.g. 0 = off, 2 = every 2 seconds).
   * @param logupdateStatusFrequency frequency of how often the update status is logged in number of frames
   * @param logPerformanceLevel performance logging, 0 = disabled,  1+ =  enabled
   */
  void SetOptions( const Dali::Integration::Log::LogFunction& logFunction,
                   unsigned int logFrameRateFrequency,
                   unsigned int logupdateStatusFrequency,
                   unsigned int logPerformanceLevel );

  /**
   * Install the log function for the current thread.
   */
  void InstallLogFunction() const;

  /**
   * Un-install the log function for the current thread.
   */
  void UnInstallLogFunction() const;

  /**
   * @return frequency of how often FPS is logged out (e.g. 0 = off, 2 = every 2 seconds).
   */
  unsigned int GetFrameRateLoggingFrequency() const;

  /**
   * @return frequency of how often Update Status is logged out (e.g. 0 = off, 60 = log every 60 frames = 1 second @ 60FPS).
   */
  unsigned int GetUpdateStatusLoggingFrequency() const;

  /**
   * @return logPerformanceLevel performance log level ( 0 = off )
   */
  unsigned int GetPerformanceLoggingLevel() const;

private:

  unsigned int mFpsFrequency;                     ///< how often fps is logged out in seconds
  unsigned int mUpdateStatusFrequency;            ///< how often update status is logged out in frames
  unsigned int mPerformanceLoggingLevel;          ///< performance log level

  Dali::Integration::Log::LogFunction mLogFunction;

  // Undefined copy constructor.
  LogOptions( const LogOptions& );

  // Undefined assignment operator.
  LogOptions& operator=( const LogOptions& );

};

} // Adaptor
} // Internal
} // Dali

#endif // __DALI_INTERNAL_ADAPTOR_LOG_OPTIONS_H__
