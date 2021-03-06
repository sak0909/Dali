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
#include "clipboard-event-notifier-impl.h"

// EXTERNAL INCLUDES
#include <dali/public-api/dali-core.h>

// INTERNAL INCLUDES
#include <internal/common/adaptor-impl.h>

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

namespace
{
BaseHandle Create()
{
  BaseHandle handle( ClipboardEventNotifier::Get() );

  if ( !handle && Adaptor::IsAvailable() )
  {
    Adaptor& adaptorImpl( Adaptor::GetImplementation( Adaptor::Get() ) );
    Dali::ClipboardEventNotifier notifier( ClipboardEventNotifier::New() );
    adaptorImpl.RegisterSingleton( typeid( notifier ), notifier );
    handle = notifier;
  }

  return handle;
}
TypeRegistration CLIPBOARD_EVENT_NOTIFIER_TYPE( typeid(Dali::ClipboardEventNotifier), typeid(Dali::BaseHandle), Create, true /* Create Instance At Startup */ );

} // unnamed namespace

Dali::ClipboardEventNotifier ClipboardEventNotifier::New()
{
  Dali::ClipboardEventNotifier notifier = Dali::ClipboardEventNotifier(new ClipboardEventNotifier());

  return notifier;
}

Dali::ClipboardEventNotifier ClipboardEventNotifier::Get()
{
  Dali::ClipboardEventNotifier notifier;

  if ( Adaptor::IsAvailable() )
  {
    // Check whether the singleton is already created
    Dali::BaseHandle handle = Adaptor::Get().GetSingleton( typeid( Dali::ClipboardEventNotifier ) );
    if(handle)
    {
      // If so, downcast the handle
      notifier = Dali::ClipboardEventNotifier( dynamic_cast< ClipboardEventNotifier* >( handle.GetObjectPtr() ) );
    }
  }

  return notifier;
}

const std::string& ClipboardEventNotifier::GetContent() const
{
  return mContent;
}

void ClipboardEventNotifier::SetContent( const std::string& content )
{
  mContent = content;
}

void ClipboardEventNotifier::ClearContent()
{
  mContent.clear();
}

void ClipboardEventNotifier::EmitContentSelectedSignal()
{
  if ( !mContentSelectedSignalV2.Empty() )
  {
    Dali::ClipboardEventNotifier handle( this );
    mContentSelectedSignalV2.Emit( handle );
  }
}

ClipboardEventNotifier::ClipboardEventNotifier()
: mContent()
{
}

ClipboardEventNotifier::~ClipboardEventNotifier()
{
}

} // namespace Adaptor

} // namespace Internal

} // namespace Dali
