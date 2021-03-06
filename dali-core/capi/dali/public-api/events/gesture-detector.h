#ifndef __DALI_GESTURE_DETECTOR_H__
#define __DALI_GESTURE_DETECTOR_H__

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
 * @addtogroup CAPI_DALI_EVENTS_MODULE
 * @{
 */

// INTERNAL INCLUDES
#include <dali/public-api/common/vector-wrapper.h>
#include <dali/public-api/object/handle.h>

namespace Dali DALI_IMPORT_API
{

namespace Internal DALI_INTERNAL
{
class GestureDetector;
}

class Actor;

/**
 * @brief GestureDetectors analyse a stream of touch events and attempt to determine the intention of the user.
 *
 * An actor is attached to a gesture detector and if the detector recognises a pattern in its analysis, it will
 * emit a detected signal to the application.
 *
 * This is the base class for different gesture detectors available and provides functionality that is common
 * to all the gesture detectors.
 *
 * @see Gesture
 */
class GestureDetector : public Handle
{
public: // Creation & Destruction

  /**
   * @brief Create an uninitialized GestureDetector; this can be initialized with one of the derived gestures' New() methods.
   *
   * Calling member functions with an uninitialized Dali::Object is not allowed.
   */
  GestureDetector();

  /**
   * @brief Downcast an Object handle to GestureDetector handle.
   *
   * If handle points to a GestureDetector object the
   * downcast produces valid handle. If not the returned handle is left uninitialized.
   * @param[in] handle to An object
   * @return handle to a GestureDetector object or an uninitialized handle
   */
  static GestureDetector DownCast( BaseHandle handle );

  /**
   * @brief Virtual destructor.
   *
   * Dali::Object derived classes typically do not contain member data.
   */
  virtual ~GestureDetector();

  /**
   * @copydoc Dali::BaseHandle::operator=
   */
  using BaseHandle::operator=;

public: // Actor related

  /**
   * @brief Attaches an actor to the gesture.
   *
   * The detected signal will be dispatched when the gesture occurs on
   * the attached actor.
   * @note You can attach several actors to a gesture detector.
   * @param[in]  actor  The actor to attach to the gesture detector
   * @pre The gesture detector has been initialized.
   */
  void Attach(Actor actor);

  /**
   * @brief Detaches the attached actor from the gesture detector.
   *
   * @param[in]  actor  The actor to detach from the gesture detector.
   * @pre The gesture detector has been initialized.
   * @pre The specified actor has been attached to the gesture detector.
   */
  void Detach(Actor actor);

  /**
   * @brief Detaches all the actors that have been attached to the gesture detector.
   *
   * @pre The gesture detector has been initialized.
   * @pre At least one actor has been attached to the gesture detector.
   */
  void DetachAll();

  /**
   * @brief Returns a vector of actors attached to the gesture detector.
   *
   * @return The attached actor vector.
   * @pre The gesture detector has been initialized.
   */
  std::vector<Actor> GetAttachedActors() const;

protected:

  /**
   * @brief This constructor is used by Dali New() methods of derived classes.
   *
   * @param [in]  internal  A pointer to a newly allocated Dali resource.
   */
  explicit DALI_INTERNAL GestureDetector(Internal::GestureDetector* internal);
};

} // namespace Dali

/**
 * @}
 */
#endif // __DALI_GESTURE_DETECTOR_H__
