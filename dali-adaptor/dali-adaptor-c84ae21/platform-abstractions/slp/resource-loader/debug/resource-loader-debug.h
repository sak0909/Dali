#ifndef __DALI_SLP_PLATFORM_RESOURCE_LOADER_DEBUG_H__
#define __DALI_SLP_PLATFORM_RESOURCE_LOADER_DEBUG_H__

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

#include <dali/integration-api/debug.h>
#if defined(DEBUG_ENABLED)

#include <platform-abstractions/slp/resource-loader/resource-loader.h>
#include <dali/integration-api/resource-cache.h>


namespace Dali
{
namespace SlpPlatform
{

extern Debug::Filter* gLoaderFilter;

std::string DebugRequestList(Integration::TextResourceType::CharacterList& chars);
std::string DebugResourceList(LoadedResource& partialResource);

} // SlpPlatform
} // Dali

#endif // defined(DEBUG_ENABLED)
#endif //__DALI_SLP_PLATFORM_RESOURCE_LOADER_DEBUG_H__
