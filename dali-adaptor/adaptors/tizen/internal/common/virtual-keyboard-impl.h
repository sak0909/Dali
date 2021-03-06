#ifndef __DALI_INTERNAL_VIRTUAL_KEYBOARD_H__
#define __DALI_INTERNAL_VIRTUAL_KEYBOARD_H__

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
#include <Ecore_IMF.h>

// INTERNAL INCLUDES
#include <dali/public-api/adaptor-framework/common/virtual-keyboard.h>

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

/**
 * Implementation of the virtual keyboard namespace
 */
namespace VirtualKeyboard
{

/**
 * Connect the virtual keyboard callbacks.
 * To get the virtual keyboard callbacks then you have to connect these callback.
 * If you don't connect callbacks, you can't get virtual keyboard signals.
 * The signals are StatusChangedSignal, ResizedSignal and LanguageChangedSignal.
 */
void ConnectCallbacks( Ecore_IMF_Context *imfContext );

/**
 * Disconnect the virtual keyboard callbacks.
 * The signals are StatusChangedSignal, ResizedSignal and LanguageChangedSignal.
 */
void DisconnectCallbacks( Ecore_IMF_Context *imfContext );

/**
 * @copydoc Dali::VirtualKeyboard::Show()
 */
void Show();

/**
 * @copydoc Dali::VirtualKeyboard::Hide()
 */
void Hide();

/**
 * @copydoc Dali::VirtualKeyboard::IsVisible()
 */
bool IsVisible();

/**
 * @copydoc Dali::VirtualKeyboard::SetReturnKeyType()
 */
void SetReturnKeyType( Dali::VirtualKeyboard::ReturnKeyType type );

/**
 * @copydoc Dali::VirtualKeyboard::GetReturnKeyType()
 */
Dali::VirtualKeyboard::ReturnKeyType GetReturnKeyType();

/**
 * @copydoc Dali::VirtualKeyboard::EnablePrediction()
 */
void EnablePrediction(const bool enable);

/**
 * @copydoc Dali::VirtualKeyboard::IsPredictionEnabled()
 */
bool IsPredictionEnabled();

/**
 * @copydoc Dali::VirtualKeyboard::GetSizeAndPosition()
 */
Rect<int> GetSizeAndPosition();

/**
 * @copydoc Dali::VirtualKeyboard::RotateKeyboard()
 */
void RotateTo(int angle);

/**
 * @copydox Dali::VirtualKeyboard::StatusChangedSignal()
 */
Dali::VirtualKeyboard::StatusSignalV2& StatusChangedSignal();

/**
 * @copydox Dali::VirtualKeyboard::ResizedSignal()
 */
Dali::VirtualKeyboard::VoidSignalV2& ResizedSignal();

/**
 * @copydox Dali::VirtualKeyboard::LanguageChangedSignal()
 */
Dali::VirtualKeyboard::VoidSignalV2& LanguageChangedSignal();

/**
 * @copydoc Dali::VirtualKeyboard::GetTextDirection
 */
Dali::VirtualKeyboard::TextDirection GetTextDirection();

} // namespace VirtualKeyboard

} // namespace Adaptor

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_VIRTUAL_KEYBOARD_H__
