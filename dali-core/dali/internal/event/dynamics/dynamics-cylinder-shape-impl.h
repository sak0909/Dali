#ifndef __DYNAMICS_CYLINDER_SHAPE_IMPL_H__
#define __DYNAMICS_CYLINDER_SHAPE_IMPL_H__

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

// BASE CLASS HEADERS
#include <dali/internal/event/dynamics/dynamics-shape-impl.h>

// INTERNAL HEADERS
#include <dali/internal/event/dynamics/dynamics-declarations.h>

namespace Dali
{

namespace Internal
{

/**
 * A cylinder
 */
class DynamicsCylinderShape : public DynamicsShape
{
public:
  /**
   * Constructor
   * @copydoc Dali::DynamicsShape::NewCylinder
   */
  DynamicsCylinderShape(const float radius, const float length);

protected:
  /**
   * Destructor.
   * A reference counted object may only be deleted by calling Unreference()
   */
  virtual ~DynamicsCylinderShape();

private:
  // unimplemented copy constructor and assignment operator
  DynamicsCylinderShape(const DynamicsCylinderShape&);
  DynamicsCylinderShape& operator=(const DynamicsCylinderShape&);

public:
  /**
   * Get an axis aligned bounding box for this shape
   * @return An axis aligned bounding box for this shape
   */
  virtual Vector3 GetAABB() const;
}; // class DynamicsCylinderShape

} // namespace Internal

} // namespace Dali

#endif // __DYNAMICS_CYLINDER_SHAPE_IMPL_H__
