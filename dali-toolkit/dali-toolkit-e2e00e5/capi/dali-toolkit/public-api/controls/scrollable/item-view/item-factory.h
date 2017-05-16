#ifndef __DALI_TOOLKIT_ITEM_FACTORY_H__
#define __DALI_TOOLKIT_ITEM_FACTORY_H__

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

/**
 * @addtogroup CAPI_DALI_TOOLKIT_ITEM_VIEW_MODULE
 * @{
 */

// INTERNAL INCLUDES
#include <dali/dali.h>

namespace Dali DALI_IMPORT_API
{

namespace Toolkit
{

/**
 * @brief ItemFactory is an abstract interface for providing actors to ItemView.
 * Each actor is identified by a unique ID, and has a linear order from 0 to GetNumberOfItems()-1.
 */
class ItemFactory
{
public:

  /**
   * @brief Virtual destructor.
   */
  virtual ~ItemFactory() = 0;

  /**
   * @brief Query the number of items available from the factory.
   *
   * The maximum available item has an ID of GetNumberOfItems() - 1.
   * @return the number of items
   */
  virtual unsigned int GetNumberOfItems() = 0;

  /**
   * @brief Create an Actor to represent a visible item.
   *
   * @param[in] itemId The ID of the newly visible item.
   * @return An actor, or an uninitialized pointer if the ID is out of range.
   */
  virtual Actor NewItem(unsigned int itemId) = 0;
};

} // namespace Toolkit

} // namespace Dali

/**
 * @}
 */
#endif // __DALI_TOOLKIT_ITEM_FACTORY_H__
