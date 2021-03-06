#ifndef __DALI_INTEGRATION_DYNAMICS_COLLISION_DATA_H__
#define __DALI_INTEGRATION_DYNAMICS_COLLISION_DATA_H__

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

//INTERNAL HEADERS
#include <dali/public-api/math/vector3.h>

namespace Dali
{

struct Vector3;

namespace Integration
{

class DynamicsBody;

struct DynamicsCollisionData
{
public:
  DynamicsCollisionData(DynamicsBody* bodyA, DynamicsBody* bodyB, const Vector3& pointOnA, const Vector3& pointOnB, const Vector3& normal, const float impact)
  : mBodyA(bodyA),
    mBodyB(bodyB),
    mPointOnA(pointOnA),
    mPointOnB(pointOnB),
    mNormal(normal),
    mImpact(impact)
  {
  }

  DynamicsCollisionData(const DynamicsCollisionData& rhs)
  : mBodyA(rhs.mBodyA),
    mBodyB(rhs.mBodyB),
    mPointOnA(rhs.mPointOnA),
    mPointOnB(rhs.mPointOnB),
    mNormal(rhs.mNormal),
    mImpact(rhs.mImpact)
  {
  }

  DynamicsCollisionData()
  : mBodyA(NULL),
    mBodyB(NULL),
    mImpact(0.0f)
  {
  }

  ~DynamicsCollisionData()
  {
  }

  DynamicsCollisionData& operator=(const DynamicsCollisionData& rhs)
  {
    if( this != &rhs )
    {
      mBodyA = rhs.mBodyA;
      mBodyB = rhs.mBodyB;
      mPointOnA = rhs.mPointOnA;
      mPointOnB = rhs.mPointOnB;
      mNormal = rhs.mNormal;
      mImpact = rhs.mImpact;
    }
    return *this;
  }

  DynamicsBody* mBodyA;
  DynamicsBody* mBodyB;
  Vector3       mPointOnA;
  Vector3       mPointOnB;
  Vector3       mNormal;
  float         mImpact;
}; // struct DynamicsCollisionData

} // namespace Integration

} // namespace Dali

#endif // __DALI_INTEGRATION_DYNAMICS_COLLISION_DATA_H__
