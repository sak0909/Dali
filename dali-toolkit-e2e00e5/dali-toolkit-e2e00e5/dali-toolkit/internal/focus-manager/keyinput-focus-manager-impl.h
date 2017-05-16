#ifndef __DALI_TOOLKIT_INTERNAL_KEYINPUT_FOCUS_MANAGER_H__
#define __DALI_TOOLKIT_INTERNAL_KEYINPUT_FOCUS_MANAGER_H__

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
#include <deque>

// INTERNAL INCLUDES
#include <dali/dali.h>
#include <dali-toolkit/public-api/focus-manager/keyinput-focus-manager.h>
#include <dali-toolkit/public-api/controls/control.h>

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

class KeyInputFocusManager;

/**
 * @copydoc Toolkit::KeyInputFocusManager
 */
class KeyInputFocusManager : public Dali::BaseObject
{
public:

  typedef std::deque< unsigned int > ActorQueue;
  typedef std::deque< unsigned int >::iterator ActorQueueIterator;
  typedef std::deque< unsigned int >::const_iterator ActorQueueConstIterator;

  /**
   * Construct a new KeyInputFocusManager.
   */
  KeyInputFocusManager();

  /**
   * @copydoc Toolkit::SetFocus
   */
  void SetFocus(Toolkit::Control control);

  /**
   * @copydoc Toolkit::GetCurrentFocusControl
   */
  Toolkit::Control GetCurrentFocusControl() const;

  /**
   * @copydoc Toolkit::RemoveFocus
   */
  void RemoveFocus(Toolkit::Control control);

  /**
   * @copydoc Toolkit::IsKeyboardListener
   */
  bool IsKeyboardListener(Toolkit::Control control) const;

public:

  /**
   * @copydoc Toolkit::KeyInputFocusManager::KeyInputFocusChangedSignal()
   */
  Toolkit::KeyInputFocusManager::KeyInputFocusChangedSignalV2& KeyInputFocusChangedSignal();

  /**
   * @copydoc Toolkit::KeyInputFocusManager::UnhandledKeyEventSignal()
   */
  Toolkit::KeyInputFocusManager::UnhandledKeyEventSignalV2& UnhandledKeyEventSignal();

  /**
   * Connects a callback function with the object's signals.
   * @param[in] object The object providing the signal.
   * @param[in] tracker Used to disconnect the signal.
   * @param[in] signalName The signal to connect to.
   * @param[in] functor A newly allocated FunctorDelegate.
   * @return True if the signal was connected.
   * @post If a signal was connected, ownership of functor was passed to CallbackBase. Otherwise the caller is responsible for deleting the unused functor.
   */
  static bool DoConnectSignal( BaseObject* object, ConnectionTrackerInterface* tracker, const std::string& signalName, FunctorDelegate* functor );

protected:

  /**
   * Destructor
   */
  virtual ~KeyInputFocusManager();

private:

  /**
   * Callback for the key event when no actor in the stage has gained the key input focus
   * @param[in] event The KeyEvent event.
   */
  void OnKeyEvent(const KeyEvent& event);

  /**
   * Signal handler called when a focused Actor is removed from Stage.
   * @param[in]  actor  The actor removed from stage.
   */
  void OnFocusActorStageDisconnection( Dali::Actor actor );

private:

  // Undefined
  KeyInputFocusManager(const KeyInputFocusManager&);

  KeyInputFocusManager& operator=(const KeyInputFocusManager& rhs);

private:

  // The key input focus change signal
  Toolkit::KeyInputFocusManager::KeyInputFocusChangedSignalV2 mKeyInputFocusChangedSignalV2;

  // The un-handled key event signal
  Toolkit::KeyInputFocusManager::UnhandledKeyEventSignalV2 mUnhandledKeyEventSignalV2;

  // Keyboard events are sent to the current focus actor, which will be the actor on the top of the focus actors stack.
  ActorQueue mFocusActorsQueue;

  SlotDelegate< KeyInputFocusManager > mSlotDelegate;
};

} // namespace Internal

inline Internal::KeyInputFocusManager& GetImpl(Dali::Toolkit::KeyInputFocusManager& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  Dali::BaseObject& handle = obj.GetBaseObject();

  return static_cast<Internal::KeyInputFocusManager&>(handle);
}

inline const Internal::KeyInputFocusManager& GetImpl(const Dali::Toolkit::KeyInputFocusManager& obj)
{
  DALI_ASSERT_ALWAYS(obj);

  const Dali::BaseObject& handle = obj.GetBaseObject();

  return static_cast<const Internal::KeyInputFocusManager&>(handle);
}

} // namespace Toolkit

} // namespace Dali

#endif // __DALI_TOOLKIT_INTERNAL_KEYINPUT_FOCUS_MANAGER_H__
