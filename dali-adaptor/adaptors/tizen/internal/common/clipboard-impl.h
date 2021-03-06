#ifndef __DALI_INTERNAL_CLIPBOARD_H__
#define __DALI_INTERNAL_CLIPBOARD_H__

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
#include <dali/public-api/adaptor-framework/common/clipboard.h>
#include <dali/public-api/object/base-object.h>
#include <Ecore_X.h>



namespace Dali
{

namespace Internal
{

namespace Adaptor
{

/**
 * Implementation of the Clip Board
 */

class Clipboard :  public Dali::BaseObject
{
public:

  /**
   * @copydoc Dali::ClipboardEventNotifier::Get()
   */
  static Dali::Clipboard Get();

  /**
   * Constructor
   * @param[in] ecoreXwin, The window is created by application.
   */

  Clipboard(Ecore_X_Window ecoreXwin);
  virtual ~Clipboard();

  /**
   * @copydoc Dali::Clipboard::SetItem()
   */
  bool SetItem(const std::string &itemData);

  /**
   * @copydoc Dali::Clipboard::GetItem()
   */
  std::string GetItem( unsigned int index );

  /**
   * @copydoc Dali::Clipboard::NumberOfClipboardItems()
   */
  unsigned int NumberOfItems();

  /**
   * @copydoc Dali::Clipboard::ShowClipboard()
   */
  void ShowClipboard();

  /**
   * @copydoc Dali::Clipboard::HideClipboard()
   */
  void HideClipboard();

  
private:
  Ecore_X_Window mApplicationWindow;
  Clipboard( const Clipboard& );
  Clipboard& operator=( Clipboard& );

}; // class clipboard


} // namespace Adaptor

} // namespace Internal

  inline static Internal::Adaptor::Clipboard& GetImplementation(Dali::Clipboard& clipboard)
  {
    DALI_ASSERT_ALWAYS( clipboard && "Clipboard handle is empty" );
    BaseObject& handle = clipboard.GetBaseObject();
    return static_cast<Internal::Adaptor::Clipboard&>(handle);
  }

  inline static const  Internal::Adaptor::Clipboard& GetImplementation(const Dali::Clipboard& clipboard)
  {
    DALI_ASSERT_ALWAYS( clipboard && "Clipboard handle is empty" );
    const BaseObject& handle = clipboard.GetBaseObject();
    return static_cast<const Internal::Adaptor::Clipboard&>(handle);
  }

} // namespace Dali

#endif // __DALI_INTERNAL_CLIPBOARD_H__
