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

#include <dali-toolkit/public-api/controls/popup/popup.h>
#include <dali-toolkit/internal/controls/popup/popup-impl.h>
#include <dali-toolkit/public-api/controls/buttons/button.h>

using namespace Dali;

namespace Dali
{

namespace Toolkit
{

///////////////////////////////////////////////////////////////////////////////////////////////////
// Popup
///////////////////////////////////////////////////////////////////////////////////////////////////

const char* const Popup::SIGNAL_TOUCHED_OUTSIDE = "touched-outside";
const char* const Popup::SIGNAL_HIDDEN = "hidden";

Popup::Popup()
{
}

Popup::Popup( const Popup& handle )
: Control( handle )
{
}

Popup& Popup::operator=( const Popup& handle )
{
  if( &handle != this )
  {
    Control::operator=( handle );
  }
  return *this;
}

Popup::Popup(Internal::Popup& implementation)
: Control(implementation)
{
}

Popup::Popup( Dali::Internal::CustomActor* internal )
: Control( internal )
{
  VerifyCustomActorPointer<Internal::Popup>(internal);
}

Popup Popup::New()
{
  return Internal::Popup::New();
}

Popup::~Popup()
{
}

Popup Popup::DownCast( BaseHandle handle )
{
  return Control::DownCast<Popup, Internal::Popup>(handle);
}

void Popup::SetBackgroundImage( Actor image )
{
  GetImpl(*this).SetBackgroundImage( image );
}

void Popup::SetTitle( const std::string& text )
{
  GetImpl(*this).SetTitle( text );
}

void Popup::SetTitle( TextView titleActor )
{
  GetImpl(*this).SetTitle( titleActor );
}

TextView Popup::GetTitle() const
{
  return GetImpl(*this).GetTitle();
}

void Popup::AddButton( Button button )
{
  GetImpl(*this).AddButton( button );
}

void Popup::SetState( PopupState state )
{
  GetImpl(*this).SetState( state );
}

void Popup::SetState( PopupState state, float duration )
{
  GetImpl(*this).SetState( state, duration );
}

Popup::PopupState Popup::GetState() const
{
  return GetImpl(*this).GetState();
}

void Popup::Show()
{
  GetImpl(*this).SetState( POPUP_SHOW );
}

void Popup::Hide()
{
  GetImpl(*this).SetState( POPUP_HIDE );
}

void Popup::ShowTail(const Vector3& position)
{
  GetImpl(*this).ShowTail( position );
}

void Popup::HideTail()
{
  GetImpl(*this).HideTail();
}

Popup::TouchedOutsideSignalV2& Popup::OutsideTouchedSignal()
{
  return GetImpl(*this).OutsideTouchedSignal();
}

Popup::HiddenSignalV2& Popup::HiddenSignal()
{
  return GetImpl(*this).HiddenSignal();
}

} // namespace Toolkit

} // namespace Dali
