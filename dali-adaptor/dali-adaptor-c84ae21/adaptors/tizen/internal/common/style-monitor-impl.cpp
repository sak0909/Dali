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
#include "style-monitor-impl.h"

// EXTERNAL INCLUDES
#include <vconf.h>

// INTERNAL INCLUDES
#include <dali/public-api/object/type-registry.h>
#include <internal/common/adaptor-impl.h>

namespace Dali
{

namespace Internal
{

namespace Adaptor
{

namespace
{

void DefaultFontSizeChangeNotification(keynode_t* node, void* data)
{
  StyleMonitor* styleMonitor = static_cast<StyleMonitor*>(data);

  StyleChange styleChange;
  styleChange.defaultFontSizeChange = true;
  styleMonitor->StyleChanged(styleChange);
}

BaseHandle Create()
{
  BaseHandle handle( StyleMonitor::Get() );

  if ( !handle && Adaptor::IsAvailable() )
  {
    Adaptor& adaptorImpl( Adaptor::GetImplementation( Adaptor::Get() ) );
    Dali::StyleMonitor styleMonitor = Dali::StyleMonitor( new StyleMonitor( adaptorImpl.GetPlatformAbstraction() ) );
    adaptorImpl.RegisterSingleton( typeid( styleMonitor ), styleMonitor );
    handle = styleMonitor;
  }

  return handle;
}
TypeRegistration STYLE_MONITOR_TYPE( typeid(Dali::StyleMonitor), typeid(Dali::BaseHandle), Create, true /* Create Instance At Startup */ );

} // unnamed namespace

Dali::StyleMonitor StyleMonitor::Get()
{
  Dali::StyleMonitor styleMonitor;

  if ( Adaptor::IsAvailable() )
  {
    // Check whether the singleton is already created
    Dali::BaseHandle handle = Dali::Adaptor::Get().GetSingleton( typeid( Dali::StyleMonitor ) );
    if(handle)
    {
      // If so, downcast the handle
      styleMonitor = Dali::StyleMonitor( dynamic_cast< StyleMonitor* >( handle.GetObjectPtr() ) );
    }
  }

  return styleMonitor;
}

StyleMonitor::StyleMonitor(Integration::PlatformAbstraction& platformAbstraction)
: mPlatformAbstraction(platformAbstraction)
{
  vconf_notify_key_changed( VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, DefaultFontSizeChangeNotification, this );
}

StyleMonitor::~StyleMonitor()
{
  vconf_ignore_key_changed( VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, DefaultFontSizeChangeNotification );
}

void StyleMonitor::StyleChanged(StyleChange styleChange)
{
  if (styleChange.defaultFontChange || styleChange.defaultFontSizeChange)
  {
    mPlatformAbstraction.UpdateDefaultsFromDevice();
  }

  EmitStyleChangeSignal(styleChange);
}

std::string StyleMonitor::GetDefaultFontFamily() const
{
  return mPlatformAbstraction.GetDefaultFontFamily();
}

float StyleMonitor::GetDefaultFontSize() const
{
  return mPlatformAbstraction.GetDefaultFontSize();
}

const std::string& StyleMonitor::GetTheme() const
{
  return mUserDefinedThemeFilePath;
}

void StyleMonitor::SetTheme(const std::string& path)
{
  StyleChange styleChange;
  styleChange.themeChange = true;
  styleChange.themeFilePath = path;
  mUserDefinedThemeFilePath = path;

  EmitStyleChangeSignal(styleChange);
}

Dali::StyleMonitor::StyleChangeSignalV2& StyleMonitor::StyleChangeSignal()
{
  return mStyleChangeSignalV2;
}

void StyleMonitor::EmitStyleChangeSignal(StyleChange styleChange)
{
  if( !mStyleChangeSignalV2.Empty() )
  {
    Dali::StyleMonitor handle( this );
    mStyleChangeSignalV2.Emit( handle, styleChange );
  }
}

} // namespace Adaptor

} // namespace Internal

} // namespace Dali
