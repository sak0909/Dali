#ifndef __DALI_INTERNAL_ADAPTOR_INTERNAL_SERVICES_H__
#define __DALI_INTERNAL_ADAPTOR_INTERNAL_SERVICES_H__

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

// INTERNAL INCLUDES
#include <slp-platform-abstraction.h>
#include <dali/integration-api/core.h>
#include <dali/integration-api/gl-abstraction.h>
#include <base/interfaces/egl-factory-interface.h>
#include <base/interfaces/trigger-event-interface.h>
#include <base/interfaces/performance-interface.h>
#include <base/interfaces/vsync-monitor-interface.h>
#include <base/interfaces/kernel-trace-interface.h>
#include <internal/common/render-surface-impl.h> // @todo move to base/interfaces


namespace Dali
{

namespace Internal
{

namespace Adaptor
{

/**
 * A class to contain various interfaces provided by the adaptor which
 * can be used by the cross platform parts of adaptor.
 * E.g. any files held in adaptors/base/ directory
 *
 */
class AdaptorInternalServices
{

public:

  /**
   * @return core
   */
  virtual Dali::Integration::Core& GetCore() = 0;

  /**
   * @return platform abstraction
   */
  virtual Dali::Integration::PlatformAbstraction& GetPlatformAbstractionInterface()  = 0;

  /**
   * @return gles abstraction
   */
  virtual Dali::Integration::GlAbstraction& GetGlesInterface()  = 0;

  /**
   * @return egl factory
   */
  virtual EglFactoryInterface& GetEGLFactoryInterface() const  = 0;

  /**
   * @return trigger event
   */
  virtual TriggerEventInterface& GetTriggerEventInterface()  = 0;

  /**
   * @return render surface
   */
  virtual RenderSurface* GetRenderSurfaceInterface()  = 0;

  /**
   * @return vsync monitor interface
   */
  virtual VSyncMonitorInterface* GetVSyncMonitorInterface()  = 0;

  /**
   * @return performance interface
   */
  virtual PerformanceInterface* GetPerformanceInterface()  = 0;

  /**
   * @return kernel trace interface
   */
  virtual KernelTraceInterface& GetKernelTraceInterface()  = 0;

protected:

  /**
   * constructor
   */
  AdaptorInternalServices()
  {
  };

  /**
   * virtual destructor
   */
  virtual ~AdaptorInternalServices()
  {
  };

  // Undefined copy constructor.
  AdaptorInternalServices( const AdaptorInternalServices& );

  // Undefined assignment operator.
  AdaptorInternalServices& operator=( const AdaptorInternalServices& );
};

} // namespace Internal

} // namespace Adaptor

} // namespace Dali

#endif // __DALI_INTERNAL_ADAPTOR_INTERNAL_SERVICES_H__
