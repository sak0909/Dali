#ifndef __DALI_TOOLKIT_TEST_APPLICATION_H__
#define __DALI_TOOLKIT_TEST_APPLICATION_H__

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
#include <dali-test-suite-utils.h>

#include "toolkit-adaptor.h"
#include "toolkit-orientation.h"

namespace Dali
{

/**
 * Adds some functionality on top of TestApplication that is required by the Toolkit.
 */
class ToolkitTestApplication : public TestApplication
{
public:

  ToolkitTestApplication( size_t surfaceWidth  = DEFAULT_SURFACE_WIDTH,
                          size_t surfaceHeight = DEFAULT_SURFACE_HEIGHT,
                          float  horizontalDpi = DEFAULT_HORIZONTAL_DPI,
                          float  verticalDpi   = DEFAULT_VERTICAL_DPI )
  : TestApplication( false, surfaceWidth, surfaceHeight, horizontalDpi, verticalDpi )
  {
    Initialize();
  }

  ~ToolkitTestApplication()
  {
    // Need to delete core before we delete the adaptor.
    delete mCore;
    mCore = NULL;
  }

  ToolkitAdaptor& GetAdaptor()
  {
    return mAdaptor;
  }

  ToolkitOrientation& GetOrientation()
  {
    return mOrientation;
  }

private:
  ToolkitAdaptor mAdaptor;
  ToolkitOrientation mOrientation;
};

} // namespace Dali

#endif // __DALI_TOOLKIT_TEST_APPLICATION_H__
