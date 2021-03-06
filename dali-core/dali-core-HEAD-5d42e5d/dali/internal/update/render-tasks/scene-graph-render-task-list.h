#ifndef __DALI_INTERNAL_SCENE_GRAPH_RENDER_TASK_LIST_H__
#define __DALI_INTERNAL_SCENE_GRAPH_RENDER_TASK_LIST_H__

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
#include <dali/internal/common/event-to-update.h>
#include <dali/internal/common/message.h>
#include <dali/internal/common/owner-container.h>

namespace Dali
{

namespace Internal
{
class CompleteStatusManager;

namespace SceneGraph
{

class RenderTask;

/**
 * An ordered list of render-tasks.
 */
class RenderTaskList
{
public:

  typedef OwnerContainer< RenderTask* > RenderTaskContainer;

  /**
   * Constructor
   */
  RenderTaskList( CompleteStatusManager& completeStatusManager );

  /**
   * Destructor
   */
  ~RenderTaskList();

  /**
   * Add a new RenderTask to the list.
   * @param[in] newTask The RenderTaskList takes ownership of this task.
   */
  void AddTask( RenderTask* newTask );

  /**
   * Remove a RenderTask from the list.
   * @param[in] task The RenderTaskList will destroy this task.
   */
  void RemoveTask( RenderTask* task );

  /**
   * Retrieve the container of RenderTasks.
   * @return The container.
   */
  RenderTaskContainer& GetTasks();

  /**
   * Retrieve the container of RenderTasks.
   * @return The container.
   */
  const RenderTaskContainer& GetTasks() const;

private:

  // Undefined
  RenderTaskList(const RenderTaskList&);

  // Undefined
  RenderTaskList& operator=(const RenderTaskList&);

private:
  RenderTaskContainer mRenderTasks; ///< A container of owned RenderTasks
  CompleteStatusManager& mCompleteStatusManager; ///< The complete status tracker (render tasks need this)
};

// Messages for RenderTaskList

inline void AddTaskMessage( EventToUpdate& eventToUpdate, RenderTaskList& list, RenderTask& task )
{
  typedef MessageValue1< RenderTaskList, RenderTask* > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &list, &RenderTaskList::AddTask, &task );
}

inline void RemoveTaskMessage( EventToUpdate& eventToUpdate, RenderTaskList& list, const RenderTask& constTask )
{
  // Scene graph thread can destroy this object.
  RenderTask& task = const_cast< RenderTask& >( constTask );

  typedef MessageValue1< RenderTaskList, RenderTask* > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &list, &RenderTaskList::RemoveTask, &task );
}

} // namespace SceneGraph

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_SCENE_GRAPH_RENDER_TASK_LIST_H__
