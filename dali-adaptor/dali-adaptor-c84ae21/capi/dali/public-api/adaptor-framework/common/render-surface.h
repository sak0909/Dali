#ifndef __DALI_RENDER_SURFACE_H__
#define __DALI_RENDER_SURFACE_H__

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
#include <string>
#include <dali/public-api/math/rect.h>
#include <dali/public-api/object/any.h>

namespace Dali DALI_IMPORT_API
{

/**
 * @brief The position and size of the render surface.
 */
typedef Dali::Rect<int> PositionSize;

/**
 * @brief Interface for a render surface onto which Dali draws.
 *
 * Dali::Adaptor requires a render surface to draw on to. This is
 * usually a window in the native windowing system, or some other
 * mapped pixel buffer.
 *
 * Dali::Application will automatically create a render surface using a window.
 *
 * The implementation of the factory method below should choose an appropriate
 * implementation of RenderSurface for the given platform
 */
class RenderSurface
{
public:
  /**
   * @brief enumeration of surface types
   */
  enum SurfaceType
  {
    NO_SURFACE,     ///< not configured
    PIXMAP,         ///< Pixmap
    WINDOW,         ///< Window
    NATIVE_BUFFER   ///< Native Buffer
  };

  /**
   * @brief When application uses pixmap surface, it can select rendering mode.
   *
   * RENDER_SYNC : application should call RenderSync() after posting the offscreen to onscreen
   * RENDER_#FPS : the maximum performance will be limited designated number of frame
   */
  enum RenderMode
  {
    RENDER_DEFAULT = -1,
    RENDER_SYNC = 0,
    RENDER_24FPS = 24,
    RENDER_30FPS = 30,
    RENDER_60FPS = 60
  };

  /**
   * @brief Constructor
   *
   * Application or Adaptor needs to create the appropriate concrete RenderSurface type.
   * @see CreateDefaultSurface
   */
  RenderSurface();

  /**
   * @brief Virtual Destructor.
  */
  virtual ~RenderSurface();

  /**
   * @brief returns the surface type.
   * @return the surface type
   */
  virtual SurfaceType GetType() = 0;

  /**
   * @brief Returns the window or pixmap surface.
   * @return surface
   */
  virtual Any GetSurface() = 0;

  /**
   * @brief Returns the display.
   * @return display
   */
  virtual Any GetDisplay() = 0;

  /**
   * @brief Return the size and position of the surface.
   * @return The position and size
   */
  virtual PositionSize GetPositionSize() const = 0;

  /**
   * @brief Set frame update rate for pixmap surface type
   */
  virtual void SetRenderMode(RenderMode mode) = 0;

  /**
   * @brief Get current fps for pixmap surface type
   * @return The render mode
   */
  virtual RenderMode GetRenderMode() const = 0;

private:

  /**
   * @brief Undefined copy constructor. RenderSurface cannot be copied
   */
  RenderSurface( const RenderSurface& rhs );

  /**
   * @brief Undefined assignment operator. RenderSurface cannot be copied
   */
  RenderSurface& operator=( const RenderSurface& rhs );

};

/**
 * @brief Default surface factory function.
 *
 * A surface is created with the given type.
 *
 * @param [in] type the type of surface to create
 * @param [in] positionSize the position and size of the surface to create
 * @param [in] name optional name of surface passed in
 * @return The render surface
 */
RenderSurface* CreateDefaultSurface( RenderSurface::SurfaceType type, PositionSize positionSize, const std::string& name = "" );

} // namespace Dali

/**
 * @}
 */
#endif // __DALI_RENDER_SURFACE_H__
