#ifndef __DALI_SLP_PLATFORM_ABSTRACTION_H__
#define __DALI_SLP_PLATFORM_ABSTRACTION_H__

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

#include <dali/integration-api/platform-abstraction.h>
#include <dali/public-api/common/dali-common.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

namespace Dali
{

/**
 * Construct a platform abstraction and return it.
 */
DALI_IMPORT_API Integration::PlatformAbstraction* CreatePlatformAbstraction();

namespace SlpPlatform
{

class DynamicsFactory;
class ResourceLoader;

/**
 * Concrete implementation of the platform abstraction class.
 */
class SlpPlatformAbstraction : public Integration::PlatformAbstraction
{

public: // Construction & Destruction

  /**
   * Constructor
   */
  SlpPlatformAbstraction();

  /**
   * Destructor
   */
  virtual ~SlpPlatformAbstraction();

public: // PlatformAbstraction overrides

  /**
   * @copydoc PlatformAbstraction::GetTimeMicroseconds()
   */
  virtual void GetTimeMicroseconds(unsigned int &seconds, unsigned int &microSeconds);

  /**
   * @copydoc PlatformAbstraction::Suspend()
   */
  virtual void Suspend();

  /**
   * @copydoc PlatformAbstraction::Resume()
   */
  virtual void Resume();

  /**
   * @copydoc PlatformAbstraction::GetClosestImageSize()
   */
  virtual void GetClosestImageSize( const std::string& filename,
                                    const ImageAttributes& attributes,
                                    Vector2& closestSize );

  /**
   * @copydoc PlatformAbstraction::GetClosestImageSize()
   */
  virtual void GetClosestImageSize( Integration::ResourcePointer resourceBuffer,
                                    const ImageAttributes& attributes,
                                    Vector2& closestSize );

  /**
   * @copydoc PlatformAbstraction::LoadResource()
   */
  virtual void LoadResource(const Integration::ResourceRequest& request);

  /**
   * @copydoc PlatformAbstraction::SaveResource()
   */
  virtual void SaveResource(const Integration::ResourceRequest& request);

  /**
   * @copydoc PlatformAbstraction::CancelLoad()
   */
  virtual void CancelLoad(Integration::ResourceId id, Integration::ResourceTypeId typeId);

  /**
   * @copydoc PlatformAbstraction::GetResources()
   */
  virtual void GetResources(Integration::ResourceCache& cache);

  /**
   * @copydoc PlatformAbstraction::IsLoading()
   */
  virtual bool IsLoading();

  /**
   * @copydoc PlatformAbstraction::JoinLoaderThreads()
   */
  virtual void JoinLoaderThreads();

  /**
   *@copydoc PlatformAbstraction::GetDefaultFontFamily()
   */
  virtual std::string GetDefaultFontFamily() const;

  /**
   *@copydoc PlatformAbstraction::GetDefaultFontSize()
   */
  virtual const float GetDefaultFontSize() const;

  /**
   *@copydoc PlatformAbstraction::GetFontLineHeightFromCapsHeight()
   */
  virtual const PixelSize GetFontLineHeightFromCapsHeight(const std::string fontFamily, const std::string& fontStyle, const CapsHeight& capsHeight) const;

  /**
   * @copydoc PlatformAbstraction::GetGlyphData()
   */
  virtual Integration::GlyphSet* GetGlyphData ( const Dali::Integration::TextResourceType& textRequest,
                                                const std::string& fontFamily,
                                                bool getBitmap) const;

  /**
   * @copydoc PlatformAbstraction::GetCachedGlyphData()
   */
  virtual Integration::GlyphSet* GetCachedGlyphData( const Integration::TextResourceType& textRequest,
                                                     const std::string& fontFamily ) const;

  /**
   * @copydoc PlatformAbstraction::GetGlobalMetrics()
   */
  virtual void GetGlobalMetrics( const std::string& fontFamily,
                                 const std::string& fontStyle,
                                 Integration::GlobalMetrics& globalMetrics ) const;

  /**
   * @copydoc PlatformAbstraction::SetDpi()
   */
  virtual void SetDpi (unsigned int DpiHorizontal, unsigned int DpiVertical);

  /**
   * @copydoc PlatformAbstraction::GetFontFamilyForChars()
   */
  std::string GetFontFamilyForChars(const TextArray& charsRequested) const;

  /**
   * @copydoc PlatformAbstraction::AllGlyphsSupported()
   */
  bool AllGlyphsSupported(const std::string &fontFamily, const std::string& fontStyle, const TextArray& charsRequested) const;

  /**
   * @copydoc PlatformAbstraction::ValidateFontFamilyName()
   */
  virtual bool ValidateFontFamilyName(const std::string& fontFamily, const std::string& fontStyle, bool& isDefaultSystemFont, std::string& closestMatch, std::string& closestStyleMatch) const;

  /**
   * @copydoc PlatformAbstraction::GetFontList()
   */
  virtual std::vector<std::string> GetFontList ( Dali::Integration::PlatformAbstraction::FontListMode mode ) const;

  /**
   * @copydoc PlatformAbstraction::LoadFile()
   */
  virtual bool LoadFile( const std::string& filename, std::vector< unsigned char >& buffer ) const;

  /**
   * @copydoc PlatformAbstraction::LoadFile()
   */
  virtual std::string LoadFile( const std::string& filename );

  /**
   * @copydoc PlatformAbstraction::SaveFile()
   */
  virtual bool SaveFile(const std::string& filename, std::vector< unsigned char >& buffer) const;

  /**
   * @copydoc PlatformAbstraction::UpdateDefaultsFromDevice();
   */
  virtual void UpdateDefaultsFromDevice();

  /**
   * @copydoc PlatformAbstraction::GetDynamicsFactory();
   */
  virtual Integration::DynamicsFactory* GetDynamicsFactory();

  /**
   * @copydoc PlatformAbstraction::ReadGlobalMetricsFromCacheFile
   */
  virtual bool ReadGlobalMetricsFromCache( const std::string& fontFamily,
                                           const std::string& fontStyle,
                                           Integration::GlobalMetrics& globalMetrics );

  /**
   * @copydoc PlatformAbstraction::WriteGlobalMetricsToCacheFile
   */
  virtual void WriteGlobalMetricsToCache( const std::string& fontFamily,
                                          const std::string& fontStyle,
                                          const Integration::GlobalMetrics& globalMetrics );

  /**
   * @copydoc PlatformAbstraction::ReadMetricsFromCacheFile
   */
  virtual bool ReadMetricsFromCache( const std::string& fontFamily,
                                     const std::string& fontStyle,
                                     std::vector<Integration::GlyphMetrics>& glyphMetricsContainer );

  /**
   * @copydoc PlatformAbstraction::WriteMetricsToCacheFile
   */
  virtual void WriteMetricsToCache( const std::string& fontFamily,
                                    const std::string& fontStyle,
                                    const Integration::GlyphSet& glyphSet );

private:
  ResourceLoader* mResourceLoader;
  FT_Library mFreeTypeHandle;       ///< Freetype library
  std::string mDefaultFontFamily;
  std::string mDefaultFontStyle;
  float mDefaultFontSize;
  std::string mDefaultThemeFile;
  DynamicsFactory* mDynamicsFactory;
};

}  // namespace SlpPlatform
}  // namespace Dali

#endif // __DALI_SLP_PLATFORM_ABSTRACTION_H__
