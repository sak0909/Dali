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
#include <dali/public-api/adaptor-framework/common/imf-manager.h>

// INTERNAL INCLUDES
#include <internal/common/imf-manager-impl.h>
#include <internal/common/adaptor-impl.h>

namespace Dali
{

ImfManager::ImfManager()
{
}

ImfManager::~ImfManager()
{
}

ImfManager ImfManager::Get()
{
  return Internal::Adaptor::ImfManager::Get();
}

ImfContext ImfManager::GetContext()
{
  return reinterpret_cast<ImfContext>( Internal::Adaptor::ImfManager::GetImplementation(*this).GetContext() );
}

void ImfManager::Activate()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Activate();
}

void ImfManager::Deactivate()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Deactivate();
}

bool ImfManager::RestoreAfterFocusLost() const
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).RestoreAfterFocusLost();
}

void ImfManager::SetRestoreAferFocusLost( bool toggle )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetRestoreAferFocusLost( toggle );
}

void ImfManager::Reset()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).Reset();
}

void ImfManager::NotifyCursorPosition()
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).NotifyCursorPosition();
}

void ImfManager::SetCursorPosition( unsigned int SetCursorPosition )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetCursorPosition( SetCursorPosition );
}

int ImfManager::GetCursorPosition()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).GetCursorPosition();
}

void ImfManager::SetSurroundingText( std::string text )
{
  Internal::Adaptor::ImfManager::GetImplementation(*this).SetSurroundingText( text );
}

std::string ImfManager::GetSurroundingText()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).GetSurroundingText();
}

ImfManager::ImfManagerSignalV2& ImfManager::ActivatedSignal()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).ActivatedSignal();
}

ImfManager::ImfEventSignalV2& ImfManager::EventReceivedSignal()
{
  return Internal::Adaptor::ImfManager::GetImplementation(*this).EventReceivedSignal();
}

ImfManager::ImfManager(Internal::Adaptor::ImfManager *impl)
  : BaseHandle(impl)
{
}

} // namespace Dali
