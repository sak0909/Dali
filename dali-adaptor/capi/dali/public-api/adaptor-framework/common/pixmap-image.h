#ifndef __DALI_PIXMAP_IMAGE_H__
#define __DALI_PIXMAP_IMAGE_H__

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
#include <dali/public-api/common/vector-wrapper.h>
#include <dali/public-api/images/native-image.h>
#include <dali/public-api/object/any.h>

namespace Dali DALI_IMPORT_API
{
class Adaptor;

namespace Internal DALI_INTERNAL
{
namespace Adaptor
{
class PixmapImage;
}
}

class PixmapImage;
/**
 * @brief Pointer to Dali::PixmapImage.
 */
typedef IntrusivePtr<PixmapImage> PixmapImagePtr;

/**
 * @brief Used for displaying native Pixmap images.
 *
 * The native pixmap can be created internally or
 * externally by X11 or ECORE-X11.
 *
 */
class PixmapImage : public NativeImage
{
public:

   /**
    * @brief PixmapImage can use pixmaps created by X11 or ECORE X11.
    */
   enum PixmapAPI
   {
     X11,        ///< X types
     ECORE_X11,  ///< EFL e-core x11 types
   };

   /**
    * @brief When creating a pixmap the color depth has to be specified.
    */
   enum ColorDepth
   {
     COLOR_DEPTH_DEFAULT,     ///< Uses the current X screen default depth (recommended)
     COLOR_DEPTH_8,           ///< 8 bits per pixel
     COLOR_DEPTH_16,          ///< 16 bits per pixel
     COLOR_DEPTH_24,          ///< 24 bits per pixel
     COLOR_DEPTH_32           ///< 32 bits per pixel
   };

  /**
   * @brief Create a new PixmapImage.
   *
   * Depending on hardware the width and height may have to be a power of two.
   * @param[in] width The width of the image.
   * @param[in] height The height of the image.
   * @param[in] depth color depth of the pixmap
   * @param[in] adaptor reference to dali adaptor
   * @return A smart-pointer to a newly allocated image.
   */
  static PixmapImagePtr New( unsigned int width, unsigned int height, ColorDepth depth,  Adaptor& adaptor );

  /**
   * @brief Create a new PixmapImage from an existing pixmap.
   *
   * @param[in] pixmap must be a X11 pixmap or a Ecore_X_Pixmap
   * @param[in] adaptor reference to dali adaptor
   * @return A smart-pointer to a newly allocated image.
   */
  static PixmapImagePtr New( Any pixmap, Adaptor& adaptor );

  /**
   * @brief Retrieve the internal pixmap
   *
   * @param api whether to return a pixmap that can be used with X11 or EFL
   * @return pixmap any object containing a pixmap of the type specified PixmapAPI
   */
  Any GetPixmap( PixmapAPI api );

  /**
   * @brief Retrieve the display used to create the pixmap.
   *
   * If the pixmap was created outside of Dali, then this display
   * is the one Dali uses internally.
   * @return Any object containing the display
   */
  Any GetDisplay();

  /**
   * @brief Get a copy of the pixels used by PixmapImage.
   *
   * This is only supported for 24 bit RGB and 32 bit RGBA internal formats
   * (COLOR_DEPTH_24 and COLOR_DEPTH_32).
   * @param[out] pixbuf a vector to store the pixels in
   * @param[out] width  width of image
   * @param[out] height height of image
   * @param[out] pixelFormat pixel format used by image
   * @return     True if the pixels were gotten, and false otherwise.
   */
  bool GetPixels( std::vector<unsigned char>& pixbuf, unsigned int& width, unsigned int& height, Pixel::Format& pixelFormat ) const;

  /**
   * @brief Convert the current pixel contents to either a JPEG or PNG format
   * and write that to the filesytem.
   *
   * @param[in] filename Identify the filesytem location at which to write the
   *                     encoded image. The extension determines the encoding used.
   *                     The two valid encoding are (".jpeg"|".jpg") and ".png".
   * @return    True if the pixels were written, and false otherwise.
   */
  bool EncodeToFile(const std::string& filename) const;

private:   // native image

  /**
   * @copydoc Dali::NativeImage::GlExtensionCreate()
   */
  virtual bool GlExtensionCreate();

  /**
   * @copydoc Dali::NativeImage::GlExtensionDestroy()
   */
  virtual void GlExtensionDestroy();

  /**
   * @copydoc Dali::NativeImage::TargetTexture()
   */
  virtual unsigned int TargetTexture();

  /**
   * @copydoc Dali::NativeImage::PrepareTexture()
   */
  virtual void PrepareTexture();

  /**
   * @copydoc Dali::NativeImage::GetWidth()
   */
  virtual unsigned int GetWidth() const;

  /**
   * @copydoc Dali::NativeImage::GetHeight()
   */
  virtual unsigned int GetHeight() const;

  /**
   * @copydoc Dali::NativeImage::GetPixelFormat()
   */
  virtual Pixel::Format GetPixelFormat() const;

private:

  /**
   * @brief Private constructor
   * @param[in] width The width of the image.
   * @param[in] height The height of the image.
   * @param[in] depth color depth of the pixmap
   * @param[in] adaptor a reference to Dali adaptor
   * @param[in] pixmap contains either: pixmap of type X11 Pixmap , a Ecore_X_Pixmap or is empty
   */
  PixmapImage(unsigned int width, unsigned int height, ColorDepth depth, Adaptor& adaptor, Any pixmap);

  /**
   * @brief A reference counted object may only be deleted by calling Unreference().
   *
   * The implementation should destroy the NativeImage resources.
   */
  virtual ~PixmapImage();

  /**
   * @brief Undefined assignment operator.
   *
   * This avoids accidental calls to a default assignment operator.
   * @param[in] rhs A reference to the object to copy.
   */
  PixmapImage& operator=(const PixmapImage& rhs);

private:

  Internal::Adaptor::PixmapImage* mImpl; ///< Implementation pointer
};

} // namespace Dali

/**
 * @}
 */
#endif // __DALI_PIXMAP_IMAGE_H__
