#ifndef __DALI_TOOLKIT_INTERNAL_TEXT_VIEW_PROCESSOR_TYPES_H__
#define __DALI_TOOLKIT_INTERNAL_TEXT_VIEW_PROCESSOR_TYPES_H__

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
#include <dali/dali.h>
#include <dali-toolkit/public-api/markup-processor/markup-processor.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace TextViewProcessor
{

/**
 * Whether the direction is Right To Left or Left To Right.
 */
enum Direction
{
  LTR, ///< Left To Right direction.
  RTL  ///< Right To Left direction.
};

/**
 * Whether the text is a new line character, a white space or normal text.
 */
enum TextSeparatorType
{
  LineSeparator,
  WordSeparator,
  NoSeparator
};

/**
 * Whether to clear the text of the text-actors when text is removed.
 */
enum TextOperationOnRemove
{
  CLEAR_TEXT,
  KEEP_TEXT
};


/**
 * Stores text info indices.
 */
struct TextInfoIndices
{
  /**
   * Default constructor.
   */
  TextInfoIndices();

  /**
   * Constructor.
   */
  TextInfoIndices( std::size_t lineIndex,
                   std::size_t groupIndex,
                   std::size_t wordIndex,
                   std::size_t characterIndex );

  /**
   * Equality operator.
   * @param [in] indices The text-info indices to be compared.
   *
   * @return \e true if both indices are equal.
   */
  bool operator==( const TextInfoIndices& indices ) const;

  std::size_t mLineIndex;
  std::size_t mGroupIndex;
  std::size_t mWordIndex;
  std::size_t mCharacterIndex;
};

/**
 * Layout information for a character.
 * It stores the position, size and ascender of its respective text-actor.
 */
struct CharacterLayoutInfo
{
  /**
   * Default constructor.
   *
   * Initializes all members to their default values.
   */
  CharacterLayoutInfo();

  /**
   * Copy constructor.
   */
  CharacterLayoutInfo( const CharacterLayoutInfo& character );

  /**
   * Assignment operator.
   */
  CharacterLayoutInfo& operator=( const CharacterLayoutInfo& character );

  // Natural size (metrics) of the glyph.
  float       mHeight;             ///< Natural height of the character.
  float       mAdvance;            ///< Natural horizontal distance from origin of current character and the next one.
  float       mBearing;            ///< Natural vertical distance from the baseline to the top of the glyph's bbox.

  // Size of the text-actor (may be modified by a scale factor).
  Vector3     mPosition;           ///< Position within the text-view
  Vector2     mOffset;             ///< Alignment and justification offset.
  Size        mSize;               ///< Size of this character.
  float       mAscender;           ///< Distance from the base line to the top of the line.
  float       mUnderlineThickness; ///< The underline's thickness.
  float       mUnderlinePosition;  ///< The underline's position.

  TextActor                   mTextActor;     ///< Handle to a text-actor.
  MarkupProcessor::StyledText mStyledText;    ///< Stores the text and its style.
  float                       mColorAlpha;    ///< Alpha component for the initial text color when text is faded.
  Vector4                     mGradientColor; ///< Gradient color.
  Vector2                     mStartPoint;    ///< Gradient start point.
  Vector2                     mEndPoint;      ///< Gradient end point.

  bool                        mIsVisible:1;   ///< Whether the text-actor is visible.
  bool                        mSetText:1;     ///< Whether a new text needs to be set in the text-actor.
  bool                        mSetStyle:1;    ///< Whether a new style needs to be set in the text-actor.
};
typedef std::vector<CharacterLayoutInfo> CharacterLayoutInfoContainer;

/**
 * Layout information for a word.
 */
struct WordLayoutInfo
{
  /**
   * Default constructor.
   *
   * Initializes all members to their default values.
   */
  WordLayoutInfo();

  /**
   * Copy constructor.
   */
  WordLayoutInfo( const WordLayoutInfo& word );

  /**
   * Assignment operator.
   */
  WordLayoutInfo& operator=( const WordLayoutInfo& word );

  Size                              mSize;                      ///< Size of the word.
  float                             mAscender;                  ///< Max of all ascenders of all characters.
  TextSeparatorType                 mType;                      ///< Whether this word is a word separator, a line separator or is not a separator.
  CharacterLayoutInfoContainer      mCharactersLayoutInfo;      ///< Layout info for all characters.
};
typedef std::vector<WordLayoutInfo> WordLayoutInfoContainer;

/**
 * Layout information for a group of words.
 */
struct WordGroupLayoutInfo
{
  /**
   * Default constructor.
   *
   * Initializes all members to their default values.
   */
  WordGroupLayoutInfo();

  /**
   * Copy constructor.
   */
  WordGroupLayoutInfo( const WordGroupLayoutInfo& group );

  /**
   * Assignment operator.
   */
  WordGroupLayoutInfo& operator=( const WordGroupLayoutInfo& group );

  Size                    mSize;               ///< Size of the group of words.
  float                   mAscender;           ///< Max of all ascenders of all words.
  Direction               mDirection;          ///< Whether this group of words is Right To Left or Left To Right.
  WordLayoutInfoContainer mWordsLayoutInfo;    ///< Layout info for all words.
  std::size_t             mNumberOfCharacters; ///< Stores the number of characters.
};
typedef std::vector<WordGroupLayoutInfo> WordGroupLayoutInfoContainer;

/**
 * Layout information for a line.
 */
struct LineLayoutInfo
{
  /**
   * Default constructor.
   *
   * Initializes all members to their default values.
   */
  LineLayoutInfo();

  /**
   * Copy constructor.
   */
  LineLayoutInfo( const LineLayoutInfo& line );

  /**
   * Assignment operator.
   */
  LineLayoutInfo& operator=( const LineLayoutInfo& line );

  Size                         mSize;                 ///< Size of the line.
  float                        mAscender;             ///< Max of all ascenders of all groups of words.
  float                        mLineHeightOffset;     ///< Line height offset.
  WordGroupLayoutInfoContainer mWordGroupsLayoutInfo; ///< Layout info for all groups of words.
  std::size_t                  mNumberOfCharacters;   ///< Stores the number of characters.
};
typedef std::vector<LineLayoutInfo> LineLayoutInfoContainer;

/**
 * Layout information for the whole text.
 */
struct TextLayoutInfo
{
  /**
   * Default constructor.
   *
   * Initializes all members to their default values.
   */
  TextLayoutInfo();

  /**
   * Copy constructor.
   */
  TextLayoutInfo( const TextLayoutInfo& text );

  /**
   * Assignment operator.
   */
  TextLayoutInfo& operator=( const TextLayoutInfo& text );

  Size                    mWholeTextSize;                 ///< width and height of the whole text.
  float                   mMaxWordWidth;                  ///< maximum width between all words.
  LineLayoutInfoContainer mLinesLayoutInfo;               ///< Layout information for all lines.
  std::size_t             mNumberOfCharacters;            ///< Stores the number of characters.
  float                   mMaxItalicsOffset;              ///< When rendering text-view in offscreen an extra width offset is needed to prevent italic characters to be cut if they are in the right edge.
  WordLayoutInfo          mEllipsizeLayoutInfo;           ///< Layout information for the ellipsize text.
};

} // namespace TextViewProcessor

} // namespace Internal

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_TEXT_VIEW_PROCESSOR_TYPES_H__
