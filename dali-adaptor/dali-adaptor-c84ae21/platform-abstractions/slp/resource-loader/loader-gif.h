#ifndef __DALI_SLP_PLATFORM_LOADER_GIF_H__
#define __DALI_SLP_PLATFORM_LOADER_GIF_H__

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

#include <cstdio>

namespace Dali
{

namespace Integration
{
  class Bitmap;
}

struct ImageAttributes;

namespace SlpPlatform
{

namespace Gif
{
const unsigned char MAGIC_BYTE_1 = 0x47;
const unsigned char MAGIC_BYTE_2 = 0x49;
} // namespace Gif

/**
 * Loads the bitmap from a GIF file.  This function checks the header first
 * and if it is not a GIF file, then it returns straight away.
 * @note For animated GIFs, only the first image is displayed
 * @param[in]  fp      Pointer to the Image file
 * @param[in]  bitmap  The bitmap class where the decoded image will be stored
 * @param[in]  attributes  Describes the dimensions, pixel format and other details for loading the image data
 * @return  true if file decoded successfully, false otherwise
 */
bool LoadBitmapFromGif(FILE *fp, Integration::Bitmap& bitmap, ImageAttributes& attributes);

/**
 * Loads the header of a GIF file and fills in the width and height appropriately.
 * @param[in]   fp      Pointer to the Image file
 * @param[in]  attributes  Describes the dimensions, pixel format and other details for loading the image data
 * @param[in/out]  width   Is set with the width of the image
 * @param[in/out]  height  Is set with the height of the image
 * @return true if the file's header was read successully, false otherwise
 */
bool LoadGifHeader(FILE *fp, const ImageAttributes& attributes, unsigned int &width, unsigned int &height );

} // namespace SlpPlatform

} // namespace Dali

#endif // __DALI_SLP_PLATFORM_LOADER_GIF_H__
