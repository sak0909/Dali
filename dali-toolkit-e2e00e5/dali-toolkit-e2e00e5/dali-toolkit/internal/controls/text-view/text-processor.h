#ifndef __DALI_TOOLKIT_TEXT_PROCESSOR_H__
#define __DALI_TOOLKIT_TEXT_PROCESSOR_H__

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
#include <dali-toolkit/public-api/markup-processor/markup-processor.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

namespace TextProcessor
{

/**
 * Splits the given text in lines.
 *
 * @note Assumes the StyledTextArray has 1 Character per Text element. (which is the case for text in TextInput, but
 * not necessarily the case for text in TextView)
 *
 * @param [in] text The given text.
 * @param [out] lines The text split in lines.
 */
void SplitInLines( const MarkupProcessor::StyledTextArray& text,
                   std::vector<MarkupProcessor::StyledTextArray>& lines );

/**
 * Splits the given line in words.
 *
 * @note Assumes the StyledTextArray has 1 Character per Text element. (which is the case for text in TextInput, but
 * not necessarily the case for text in TextView)
 *
 * @param [in] line The given line.
 * @param [out] words The line split in words.
 */
void SplitInWords( const MarkupProcessor::StyledTextArray& line,
                   std::vector<MarkupProcessor::StyledTextArray>& words );

/**
 * Whether the text begins with right-to-left (bidirectional) character.
 * @param [in] text The given text.
 * @return \e true if the text begins right-to-left character.
 */
bool BeginsRightToLeftCharacter( const Text& text );

/**
 * @copydoc BeginsRightToLeftCharacter( const Text& text )
 */
bool BeginsRightToLeftCharacter( const MarkupProcessor::StyledTextArray& text );

/**
 * Whether the text contains any right-to-left (bidirectional) character.
 * @param [in] text The given text.
 * @return \e true if the text contains right-to-left character.
 */
bool ContainsRightToLeftCharacter( const Text& text );

/**
 * @copydoc ContainsRightToLeftCharacter( const Text& text )
 */
bool ContainsRightToLeftCharacter( const MarkupProcessor::StyledTextArray& text );

/**
 * Convert the text as specified by the Unicode Bidirectional Algorithm.
 * The text is converted only if it is bidirectional.
 * @param[in] line The line of text to be converted.
 * @param[out] convertedText The text converted. Text is grouped in chunks which only have one direction.
 * @param[out] logicalToVisualMap The character position map from the logical input text to the visual output text.
 * @param[out] visualToLogicalMap The character position map from the visual output text to the logical input text.
 */
 void ConvertBidirectionalText( const MarkupProcessor::StyledTextArray& line,
                                std::vector<MarkupProcessor::StyledTextArray>& convertedText,
                                std::vector<int>& logicalToVisualMap,
                                std::vector<int>& visualToLogicalMap );

/**
 * Finds the nearest word in a string to a specified
 * offset (in Characters).
 *
 * @note Assumes the StyledTextArray has 1 Character per Text element. (which is the case for text in TextInput, but
 * not necessarily the case for text in TextView)
 *
 * @param[in] text The text to search through.
 * @param[in] offset The current offset position to begin search from.
 * @param[out] start The start position of nearest word
 * @param[out] end The end position of nearest word
 */
void FindNearestWord( const MarkupProcessor::StyledTextArray& text, size_t offset, size_t& start, size_t& end);

} // namespace TextProcessor

} // namespace Internal

} // namespace DaliToolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_TEXT_PROCESSOR_H__
