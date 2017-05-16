#ifndef __DALI_INTERNAL_GLYPH_RESOURCE_REQUEST_H__
#define __DALI_INTERNAL_GLYPH_RESOURCE_REQUEST_H__

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
#include <dali/public-api/common/vector-wrapper.h>
#include <dali/internal/event/text/resource/font-id.h>
#include <dali/integration-api/resource-cache.h>

namespace Dali
{

namespace Internal
{

/**
 * Structure for requesting an array of characters to be loaded
 * at a certain quality, for a certain font.
 * Resource requests are generated by glyph-atlas
 */
class GlyphResourceRequest
{
public:
  typedef Integration::TextResourceType::CharacterList CharacterList;
  typedef Integration::ResourceId ResourceId;

  /**
   * Glyph quality
   */
  enum GlyphQuality
  {
    LOW_QUALITY,
    HIGH_QUALITY
  };

  /**
   * Constructor
   * @param[in] fontId font id
   * @param[in] quality
   */
  GlyphResourceRequest( FontId fontId, GlyphQuality quality );

  /**
   * non-virtual destructor
   */
  ~GlyphResourceRequest()
  {
  }

  /**
   * Copy constructor
   */
  GlyphResourceRequest( const GlyphResourceRequest& );

  /**
   * Assignment operator
   */
  GlyphResourceRequest& operator=( const GlyphResourceRequest& );

  /**
   * Get the font id
   * @return the font id of the request
   */
  FontId GetFontId() const;

  /**
   * Get the request quality
   * @return quality
   */
  GlyphQuality GetQuality() const;

  /**
   * Inserts a character in to the request
   * @param[in] code character code
   */
  void InsertCharacter( unsigned int code, unsigned int xPos, unsigned int yPos );

  /**
   * Get the character list in the request
   * @return character list
   */
  const CharacterList& GetCharacterList() const;

private:

  /**
   * constructor
   */
  GlyphResourceRequest()
  {
  }

  FontId mFontId;                  ///< font id
  GlyphQuality mQuality;           ///< quality
  CharacterList mCharacterList;    ///< character list
};

typedef std::vector< GlyphResourceRequest > GlyphRequestList;

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_GLYPH_RESOURCE_REQUEST_H__
