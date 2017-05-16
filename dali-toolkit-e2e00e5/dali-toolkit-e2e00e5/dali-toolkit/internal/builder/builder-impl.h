#ifndef __DALI_TOOLKIT_INTERNAL_BUILDER_H__
#define __DALI_TOOLKIT_INTERNAL_BUILDER_H__

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
#include <string>
#include <list>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <dali/dali.h>
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES
#include <dali-toolkit/public-api/builder/json-parser.h>
#include <dali-toolkit/public-api/builder/builder.h>

// Warning messages usually displayed
#define DALI_SCRIPT_WARNING(format, args...) \
  DALI_LOG_WARNING("Script:" format, ## args)

// Info messages are usually debug build
#define DALI_SCRIPT_INFO(format, args...) \
  DALI_LOG_INFO(Dali::Toolkit::Internal::gFilterScript, Debug::General, "Script:" format, ## args)

// Info Verbose need to be swiched on in gFilterScript filter constructor (by default set to General)
#define DALI_SCRIPT_VERBOSE(format, args...) \
  DALI_LOG_INFO(Dali::Toolkit::Internal::gFilterScript, Debug::Verbose, "Script:" format, ## args)

namespace Dali
{

namespace Toolkit
{
  class TreeNode;
}

namespace Toolkit
{

namespace Internal
{

#if defined(DEBUG_ENABLED)
extern Dali::Integration::Log::Filter* gFilterScript;
#endif

class Builder;

/**
 * @copydoc Toolkit::Builder
 */
class Builder : public Dali::BaseObject
{
public:

  Builder();

  /**
   * @copydoc Toolkit::Builder::LoadFromString
   */
  void LoadFromString( const std::string &data,
                       Dali::Toolkit::Builder::UIFormat rep = Dali::Toolkit::Builder::JSON );

  /**
   * @copydoc Toolkit::Builder::CreateAnimation
   */
  Animation CreateAnimation( const std::string& animationName );

  /**
   * @copydoc Toolkit::Builder::CreateFromStyle
   */
  BaseHandle CreateFromStyle( const std::string& styleName );

  /**
   * @copydoc Toolkit::Builder::GetFont
   */
  Font GetFont(const std::string &name) const;

  /**
   * @copydoc Toolkit::Builder::GetTextStyle
   */
  TextStyle GetTextStyle(const std::string &name) const;

  /**
   * @copydoc Toolkit::Builder::GetImage
   */
  Image GetImage(const std::string &name) const;

  /**
   * @copydoc Toolkit::Builder::GetActor
   */
  Actor GetActor( const std::string &name ) const;

  /**
   * @copydoc Toolkit::Builder::ApplyStyle
   */
  void ApplyStyle( const std::string& styleName, Handle& handle );

  /**
   * @copydoc Toolkit::Builder::AddActors
   */
  void AddActors( Actor toActor );

  /**
   * @copydoc Toolkit::Builder::AddActors
   */
  void AddActors( const std::string &sectionName, Actor toActor );

  /**
   * @copydoc Toolkit::Builder::GetAnimation
   */
  Animation GetAnimation( const std::string &name ) const;

  /**
   * @copydoc Toolkit::Builder::CreateRenderTask
   */
  void CreateRenderTask( const std::string &name );

  /**
   * @copydoc Toolkit::Builder::GetShaderEffect
   */
  ShaderEffect GetShaderEffect( const std::string &name );

  /**
   * @copydoc Toolkit::Builder::GetFrameBufferImage
   */
  FrameBufferImage GetFrameBufferImage( const std::string &name );

  /**
   * @copydoc Toolkit::Builder::GetTopLevelActors
   */
  ActorContainer GetTopLevelActors( void ) const;

protected:

  virtual ~Builder();

private:
  // Undefined
  Builder(const Builder&);
  Builder& operator=(const Builder& rhs);

  void SetupTask( RenderTask& task, const Toolkit::TreeNode& node );

private:
  Toolkit::JsonParser mParser;

  typedef std::map<const std::string, FrameBufferImage> ImageLut;
  ImageLut mFrameBufferImageLut;

  typedef std::map<const std::string, ShaderEffect> ShaderEffectLut;
  ShaderEffectLut mShaderEffectLut;

  SlotDelegate<Builder> mSlotDelegate;
};

} // namespace Internal

inline Internal::Builder& GetImpl(Dali::Toolkit::Builder& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  Dali::BaseObject& handle = obj.GetBaseObject();

  return static_cast<Internal::Builder&>(handle);
}

inline const Internal::Builder& GetImpl(const Dali::Toolkit::Builder& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  const Dali::BaseObject& handle = obj.GetBaseObject();

  return static_cast<const Internal::Builder&>(handle);
}

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_BUILDER_H__
