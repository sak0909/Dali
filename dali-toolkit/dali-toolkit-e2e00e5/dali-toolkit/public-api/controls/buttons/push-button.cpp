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

// CLASS HEADER

#include <dali-toolkit/public-api/controls/buttons/push-button.h>

// INTERNAL INCLUDES

#include <dali-toolkit/internal/controls/buttons/push-button-impl.h>

namespace Dali
{

namespace Toolkit
{

const char* const PushButton::SIGNAL_TOGGLED = "toggled";
const char* const PushButton::SIGNAL_PRESSED = "pressed";
const char* const PushButton::SIGNAL_RELEASED = "released";

const char* const PushButton::ACTION_PUSH_BUTTON_CLICK = "push-button-click";

PushButton::PushButton()
: Button()
{
}

PushButton::PushButton( Internal::PushButton& implementation )
: Button( implementation )
{
}

PushButton::PushButton( const PushButton& pushButton )
: Button( pushButton )
{
}

PushButton& PushButton::operator=( const PushButton& pushButton )
{
  if( &pushButton != this )
  {
    Button::operator=( pushButton );
  }
  return *this;
}

PushButton::PushButton( Dali::Internal::CustomActor* internal )
: Button( internal )
{
  VerifyCustomActorPointer<Internal::PushButton>(internal);
}

PushButton::~PushButton()
{
}

PushButton PushButton::New()
{
  return Internal::PushButton::New();
}

PushButton PushButton::DownCast( BaseHandle handle )
{
  return Control::DownCast<PushButton, Internal::PushButton>(handle);
}

void PushButton::SetAutoRepeating( bool autoRepeating )
{
  Dali::Toolkit::GetImplementation( *this ).SetAutoRepeating( autoRepeating );
}

bool PushButton::IsAutoRepeating() const
{
  return Dali::Toolkit::GetImplementation( *this ).IsAutoRepeating();
}

void PushButton::SetInitialAutoRepeatingDelay( float initialAutoRepeatingDelay )
{
  Dali::Toolkit::GetImplementation( *this ).SetInitialAutoRepeatingDelay( initialAutoRepeatingDelay );
}

float PushButton::GetInitialAutoRepeatingDelay() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetInitialAutoRepeatingDelay();
}

void PushButton::SetNextAutoRepeatingDelay( float nextAutoRepeatingDelay )
{
  Dali::Toolkit::GetImplementation( *this ).SetNextAutoRepeatingDelay( nextAutoRepeatingDelay );
}

float PushButton::GetNextAutoRepeatingDelay() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetNextAutoRepeatingDelay();
}

void PushButton::SetToggleButton( bool toggle )
{
  Dali::Toolkit::GetImplementation( *this ).SetToggleButton( toggle );
}

bool PushButton::IsToggleButton() const
{
  return Dali::Toolkit::GetImplementation( *this ).IsToggleButton();
}

void PushButton::SetToggled( bool toggle )
{
  Dali::Toolkit::GetImplementation( *this ).SetToggled( toggle );
}

bool PushButton::IsToggled() const
{
  return Dali::Toolkit::GetImplementation( *this ).IsToggled();
}

void PushButton::SetButtonImage( Image image )
{
  Dali::Toolkit::GetImplementation( *this ).SetButtonImage( image );
}

void PushButton::SetButtonImage( Actor image )
{
  Dali::Toolkit::GetImplementation( *this ).SetButtonImage( image );
}

Actor PushButton::GetButtonImage() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetButtonImage();
}

void PushButton::SetBackgroundImage( Image image )
{
  Dali::Toolkit::GetImplementation( *this ).SetBackgroundImage( image );
}

void PushButton::SetBackgroundImage( Actor image )
{
  Dali::Toolkit::GetImplementation( *this ).SetBackgroundImage( image );
}

Actor PushButton::GetBackgroundImage() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetBackgroundImage();
}

void PushButton::SetPressedImage( Image image )
{
  Dali::Toolkit::GetImplementation( *this ).SetPressedImage( image );
}

void PushButton::SetPressedImage( Actor image )
{
  Dali::Toolkit::GetImplementation( *this ).SetPressedImage( image );
}

Actor PushButton::GetPressedImage() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetPressedImage();
}

void PushButton::SetDimmedBackgroundImage( Image image )
{
  Dali::Toolkit::GetImplementation( *this ).SetDimmedBackgroundImage( image );
}

void PushButton::SetDimmedBackgroundImage( Actor image )
{
  Dali::Toolkit::GetImplementation( *this ).SetDimmedBackgroundImage( image );
}

Actor PushButton::GetDimmedBackgroundImage() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetDimmedBackgroundImage();
}

void PushButton::SetDimmedImage( Image image )
{
  Dali::Toolkit::GetImplementation( *this ).SetDimmedImage( image );
}

void PushButton::SetDimmedImage( Actor image )
{
  Dali::Toolkit::GetImplementation( *this ).SetDimmedImage( image );
}

Actor PushButton::GetDimmedImage() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetDimmedImage();
}

void PushButton::SetLabelText( const std::string& text )
{
  Dali::Toolkit::GetImplementation( *this ).SetLabelText( text );
}

void PushButton::SetLabelText( Actor text )
{
  Dali::Toolkit::GetImplementation( *this ).SetLabelText( text );
}

Actor PushButton::GetLabelText() const
{
  return Dali::Toolkit::GetImplementation( *this ).GetLabelText();
}

PushButton::ToggledSignalV2& PushButton::ToggledSignal()
{
  return Dali::Toolkit::GetImplementation( *this ).ToggledSignal();
}

PushButton::PressedSignalV2& PushButton::PressedSignal()
{
  return Dali::Toolkit::GetImplementation( *this ).PressedSignal();
}

PushButton::ReleasedSignalV2& PushButton::ReleasedSignal()
{
  return Dali::Toolkit::GetImplementation( *this ).ReleasedSignal();
}

} // namespace Toolkit

} // namespace Dali
