#ifndef __DALI_INTERNAL_ADAPTOR_BASE_EGL_INTERFACE_H__
#define __DALI_INTERNAL_ADAPTOR_BASE_EGL_INTERFACE_H__

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

namespace Dali
{
namespace Internal
{
namespace Adaptor
{

/**
 * EglInterface provides an interface for managing EGL contexts
 */
class EglInterface
{
public:
  enum  SyncMode
  {
    NO_SYNC      = 0,  ///< not synchronised to display (driver might over-ride?)
    FULL_SYNC    = 1,  ///< redraw at display refresh rate
    HALF_SYNC    = 2,  ///< redraw at half display refresh rate
    QUARTER_SYNC = 4   ///< redraw at quarter display refresh rate
  };

  /**
    * Create the OpenGL context.
    * @return true if successful
    */
  virtual bool CreateContext() = 0;

  /**
   * Make the OpenGL context current
   */
  virtual void MakeContextCurrent() = 0;

  /**
   * Terminate GL
   */
  virtual void TerminateGles() = 0;

  /**
   * Sets the refresh sync mode.
   * @see SyncMode
   */
  virtual bool SetRefreshSync( SyncMode mode ) = 0;

  /**
   * Performs an OpenGL swap buffers command
   */
  virtual void SwapBuffers() = 0;

  /**
   * Performs an OpenGL copy buffers command
   */
  virtual void CopyBuffers() = 0;

  /**
   * Performs an EGL wait GL command
   */
  virtual void WaitGL() = 0;

protected:
  /**
   * Virtual protected destructor, no deletion through this interface
   */
  virtual ~EglInterface() {}
};

} // namespace Adaptor

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_ADAPTOR_BASE_EGL_INTERFACE_H__

