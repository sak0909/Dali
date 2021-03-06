#ifndef __DALI_INTEGRATION_BITMAP_H__
#define __DALI_INTEGRATION_BITMAP_H__

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

// INTERNAL INCLUDES
#include <dali/integration-api/debug.h>
#include <dali/public-api/common/intrusive-ptr.h>
#include <dali/public-api/images/pixel.h>
#include <dali/public-api/object/ref-object.h>

namespace Dali
{

namespace Integration
{

/**
 * Returns GL data type and internal format for specified pixel format
 * @param[in]  pixelformat    pixel format (eg. Pixel::RGBA32)
 * @param[out] pixelDataType  pixel data type (eg. GL_UNSIGNED_BYTE)
 * @param[out] internalFormat pixel internal format (eg. GL_RGBA)
 */
DALI_IMPORT_API void ConvertToGlFormat(Pixel::Format pixelformat, unsigned& pixelDataType, unsigned& internalFormat);

class Bitmap;
typedef IntrusivePtr<Bitmap>    BitmapPtr;
typedef unsigned char                 PixelBuffer;  ///< Pixel data buffers are composed of these

/**
 * Bitmap class.
 * An abstract container for image data.
 * \sa{BitmapPackedPixel BitmapCompressed BitmapExternal} for concrete
 * subclasses.
 */
class DALI_IMPORT_API Bitmap : public Dali::RefObject
{
protected:
  /**
   * Constructor
   * Use the static function Bitmap::Create() to create instances.
   * @param[in] discardable Flag to tell the bitmap if it can delete the buffer with the pixel data.
   * @param[in] pixBuf External buffer of pixel data or null.
   */
  Bitmap( bool discardable = false, Dali::Integration::PixelBuffer* pixBuf = 0 );

  /**
   * Initializes internal class members
   * @param[in] pixelFormat   pixel format
   * @param[in] width         Image width in pixels
   * @param[in] height        Image height in pixels
   */
  void Initialize(Pixel::Format pixelFormat,
                           unsigned int width,
                           unsigned int height);


public:
  /** Defines the characteristics of the Bitmap returned from the factory
   *  function. */
  enum Profile
  {
    /** A 2D array of pixels where each pixel is a whole number of bytes
     * and each scanline of the backing memory buffer may have additional
     * bytes off the right edge if requested, and there may be additional
     * scanlines past the bottom of the image in the buffer if requested.*/
    BITMAP_2D_PACKED_PIXELS,
    /** The data for the bitmap is buffered in an opaque form.*/
    BITMAP_COMPRESSED
  };

  /**
   * Create a new instance of a Bitmap with the profile asked for.
   * @return Pointer to created Bitmap subclass. Clients should immediately
   * wrap this in a reference-counting smart pointer or store it in a similarly
   * automatic owning collection.
   * @param[in] profile Defines required features of the bitmap (\sa Profile).
   * @param[in] managePixelBuffer If true, the bitmap object owns it's own
   * buffer of pixel data and can delete it, else the lifetime of the pixel
   * buffer is managed by an external component and is guaranteed to remain
   * dereferenceable at least as long as the Bitmap remains alive.
   **/
  static Bitmap* New(Profile profile, bool managePixelBuffer);

  /** \name GeneralFeatures
   * Features that are generic between profiles. */
  /**@{*/

  /**
   * Get the width of the image
   * @return The width of the image
   */
  unsigned int GetImageWidth() const
  {
    return mImageWidth;
  }

  /**
   * Get the height of the image
   * @return The height of the image
   */
  unsigned int GetImageHeight() const
  {
    return mImageHeight;
  }

  /**
   * Get the pixel format
   * @return The pixel format
   */
  Pixel::Format GetPixelFormat() const
  {
    return mPixelFormat;
  }

  /**
   * Get the pixel buffer
   * @return The buffer. You can modify its contents.
   * @sa ReserveBuffer GetBufferSize
   */
  virtual PixelBuffer* GetBuffer()
  {
    DALI_ASSERT_DEBUG(mData != NULL);
    return mData;
  }

  /**
   * Get the pixel buffer size in bytes
   * @return The buffer size in bytes.
   * @sa ReserveBuffer GetBuffer
   */
  virtual size_t GetBufferSize() const = 0;

  /**
   * Queries if the bitmap has an alpha channel
   * @return true if there is an alpha channel
   */
  bool HasAlphaChannel() const
  {
    return mHasAlphaChannel;
  }

  /**
   * Queries if the bitmap has any transparent data
   * @return true if the bitmap has alpha data
   */
  bool IsFullyOpaque() const
  {
    // check pixel format for alpha channel
    return !(HasAlphaChannel() && mAlphaChannelUsed);
  }

  /**@}*/ ///< End of generic features


  /** \name PackedPixelsProfile
   * Features that are active only if the Bitmap was created with a
   * BITMAP_2D_PACKED_PIXELS profile. */
  /**@{*/

  class PackedPixelsProfile
  {
  public:

    /**
     * (Re-)Allocate pixel buffer for the Bitmap. Any previously allocated pixel buffer is deleted.
     * Dali has ownership of the buffer, but its contents can be modified.
     * Bitmap stores given size information about the image.
     * @pre bufferWidth, bufferHeight have to be power of two
     * @param[in] pixelFormat   pixel format
     * @param[in] width         Image width in pixels
     * @param[in] height        Image height in pixels
     * @param[in] bufferWidth   Buffer width (stride) in pixels
     * @param[in] bufferHeight  Buffer height in pixels
     * @return pixel buffer pointer
     */
    virtual PixelBuffer* ReserveBuffer(Pixel::Format pixelFormat,
                                       unsigned int width,
                                       unsigned int height,
                                       unsigned int bufferWidth = 0,
                                       unsigned int bufferHeight = 0) = 0;

    /**
     * Assign a pixel buffer. Any previously allocated pixel buffer is deleted.
     * Dali has ownership of the buffer, but it iss allowable to modify its
     * contents after it is assigned, but before it is used.
     * Bitmap stores the provided size information about the image.
     *
     * The buffer must have been allocated with the C++ array new operator, not
     * with malloc or as a local or static object. The precise form is as follows:
     *
     *    PixelBuffer * buffer = new PixelBuffer[bufSize];
     *
     * @pre bufferWidth, bufferHeight have to be power of two
     * @param[in] pixelFormat   pixel format
     * @param[in] buffer        the pixel buffer
     * @param[in] bufferSize    size of the pixel buffer
     * @param[in] width         Image width in pixels
     * @param[in] height        Image height in pixels
     * @param[in] bufferWidth   Buffer width (stride) in pixels
     * @param[in] bufferHeight  Buffer height in pixels
     */
    virtual void AssignBuffer(Pixel::Format pixelFormat,
                              PixelBuffer* buffer,
                              std::size_t bufferSize,
                              unsigned int width,
                              unsigned int height,
                              unsigned int bufferWidth = 0,
                              unsigned int bufferHeight = 0) = 0;
    /**
     * Get the width of the buffer (stride)
     * @return The width of the buffer in pixels
     */
    virtual unsigned int GetBufferWidth() const = 0;

    /**
     * Get the height of the buffer
     * @return The height of the buffer in pixels
     */
    virtual unsigned int GetBufferHeight() const = 0;

    /**
     * Get the pixel buffer stride.
     * @return The buffer stride (in bytes) if this is bitmap of non-compressed
     * packed pixels for which a stride is meaningful or 0 otherwise.
     */
    virtual unsigned int GetBufferStride() const = 0;

    /**
     * Check the bitmap data and test whether it has any transparent pixels.
     * This property can then be tested for with IsFullyOpaque().
     */
    virtual void TestForTransparency() = 0;
  };

  /**
   * Get interface to features that are active only if the Bitmap was created
   * with a BITMAP_2D_PACKED_PIXELS profile. */
  virtual const PackedPixelsProfile* GetPackedPixelsProfile() const { return 0; }
  /**
   * Get interface to features that are active only if the Bitmap was created
   * with a BITMAP_2D_PACKED_PIXELS profile. */
  virtual PackedPixelsProfile* GetPackedPixelsProfile() { return 0; }

  /**@}*/ ///< End of packed pixel features.


  /** \name CompressedProfile
   * Features that only apply to opaque/compressed formats. */
  /**@{*/

  class CompressedProfile
  {
  public:
    /**
     * (Re-)Allocate pixel buffer for the Bitmap. Any previously allocated pixel buffer
     * is deleted.
     * Dali has ownership of the buffer, and contents are opaque and immutable.
     * Bitmap stores given size information about the image which the client is assumed
     * to have retrieved from out-of-band image metadata.
     * @param[in] pixelFormat   pixel format
     * @param[in] width         Image width in pixels
     * @param[in] height        Image height in pixels
     * @param[in] bufferSize    Buffer size in bytes
     * @return pixel buffer pointer
     */
    virtual PixelBuffer* ReserveBufferOfSize( Pixel::Format pixelFormat,
                                       const unsigned width,
                                       const unsigned height,
                                       const size_t numBytes ) = 0;
  };

  virtual const CompressedProfile* GetCompressedProfile() const { return 0; }
  virtual CompressedProfile* GetCompressedProfile() { return 0; }
  /**@}*/


  /**
   * Inform the bitmap that its pixel buffer is no longer required and can be
   * deleted to free up memory if the bitmap owns the buffer.
   */
  void DiscardBuffer();

  /**
   * @return True if the buffer of pixel data is owned by this Bitmap itself,
   * or false if the buffer is owned by an external component.
   **/
  bool BufferIsOwned() const
  {
    return mDataIsOwned;
  }

 /**
   * Transfer ownership of the pixel buffer to the calling function.
   * @post bitmaps pixel data is set to NULL
   * @return the bitmaps pixel buffer
   */
  PixelBuffer* ReleaseBuffer();
  /**
   * Delete the pixel buffer data
   */
  void DeletePixelBuffer();

  /**
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~Bitmap();

protected:

  unsigned int  mImageWidth;          ///< Image width in pixels
  unsigned int  mImageHeight;         ///< Image height in pixels
  Pixel::Format mPixelFormat;         ///< Pixel format
  bool          mHasAlphaChannel;   ///< Whether the image has an alpha channel
  bool          mAlphaChannelUsed;  ///< Whether the alpha channel is used in case the image owns one.
  PixelBuffer*  mData;            ///< Raw pixel data

private:

  bool          mDataIsOwned;     ///< Should delete the buffer when discard buffer is called.

  Bitmap(const Bitmap& other);  ///< defined private to prevent use
  Bitmap& operator = (const Bitmap& other); ///< defined private to prevent use

  // Changes scope, should be at end of class
  DALI_LOG_OBJECT_STRING_DECLARATION;
};

} // namespace Integration

} // namespace Dali

#endif // __DALI_INTEGRATION_BITMAP_H__
