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

// CLASS HEADER
#include <dali/public-api/actors/actor.h>

// INTERNAL INCLUDES
#include <dali/public-api/actors/layer.h>
#include <dali/public-api/animation/constraint.h>
#include <dali/public-api/common/dali-common.h>
#include <dali/public-api/shader-effects/shader-effect.h>
#include <dali/public-api/math/degree.h>
#include <dali/public-api/math/radian.h>
#include <dali/public-api/math/vector2.h>

#include <dali/internal/event/actors/actor-impl.h>
#include <dali/internal/event/actors/layer-impl.h>
#include <dali/internal/event/actor-attachments/actor-attachment-impl.h>
#include <dali/internal/event/animation/constraint-impl.h>
#include <dali/internal/event/dynamics/dynamics-declarations.h>
#include <dali/internal/event/dynamics/dynamics-body-config-impl.h>
#include <dali/internal/event/dynamics/dynamics-body-impl.h>
#include <dali/internal/event/dynamics/dynamics-joint-impl.h>
#include <dali/internal/event/dynamics/dynamics-world-impl.h>
#include <dali/internal/event/effects/shader-effect-impl.h>

using namespace std;

namespace Dali
{

const char* const Actor::SIGNAL_TOUCHED = "touched";
const char* const Actor::SIGNAL_MOUSE_WHEEL_EVENT = "mouse-wheel-event";
const char* const Actor::SIGNAL_SET_SIZE = "set-size";
const char* const Actor::SIGNAL_ON_STAGE = "on-stage";
const char* const Actor::SIGNAL_OFF_STAGE = "off-stage";

const char* const Actor::ACTION_SHOW = "show";
const char* const Actor::ACTION_HIDE = "hide";

Actor::Actor()
{
}

Actor Actor::New()
{
  Internal::ActorPtr internal = Internal::Actor::New();

  return Actor(internal.Get());
}

Actor Actor::DownCast( BaseHandle handle )
{
  return Actor( dynamic_cast<Dali::Internal::Actor*>(handle.GetObjectPtr()) );
}

Actor::~Actor()
{
}

const std::string& Actor::GetName() const
{
  return GetImplementation(*this).GetName();
}

void Actor::SetName(const std::string& name)
{
  GetImplementation(*this).SetName(name);
}

unsigned int Actor::GetId() const
{
  return GetImplementation(*this).GetId();
}

bool Actor::IsRoot() const
{
  return GetImplementation(*this).IsRoot();
}

bool Actor::OnStage() const
{
  return GetImplementation(*this).OnStage();
}

bool Actor::IsLayer() const
{
  return GetImplementation(*this).IsLayer();
}

Layer Actor::GetLayer()
{
  return GetImplementation(*this).GetLayer();
}

void Actor::Add(Actor actor)
{
  GetImplementation(*this).Add(GetImplementation(actor));
}

void Actor::Remove(Actor actor)
{
  GetImplementation(*this).Remove(GetImplementation(actor));
}

void Actor::Unparent()
{
  GetImplementation(*this).Unparent();
}

unsigned int Actor::GetChildCount() const
{
  return GetImplementation(*this).GetChildCount();
}

Actor Actor::GetChildAt(unsigned int index) const
{
  return GetImplementation(*this).GetChildAt(index);
}

Actor Actor::FindChildByName(const std::string& actorName)
{
  Internal::ActorPtr child = GetImplementation(*this).FindChildByName(actorName);
  return Actor(child.Get());
}

Actor Actor::FindChildByAlias(const std::string& actorAlias)
{
  Actor child = GetImplementation(*this).FindChildByAlias(actorAlias);
  return child;
}

Actor Actor::FindChildById(const unsigned int id)
{
  Internal::ActorPtr child = GetImplementation(*this).FindChildById(id);
  return Actor(child.Get());
}

Actor Actor::GetParent() const
{
  Internal::Actor* parent = GetImplementation(*this).GetParent();

  return Actor(parent);
}

void Actor::SetParentOrigin(const Vector3& origin)
{
  GetImplementation(*this).SetParentOrigin(origin);
}

Vector3 Actor::GetCurrentParentOrigin() const
{
  return GetImplementation(*this).GetCurrentParentOrigin();
}

void Actor::SetAnchorPoint(const Vector3& anchorPoint)
{
  GetImplementation(*this).SetAnchorPoint(anchorPoint);
}

Vector3 Actor::GetCurrentAnchorPoint() const
{
  return GetImplementation(*this).GetCurrentAnchorPoint();
}

void Actor::SetSize(float width, float height)
{
  GetImplementation(*this).SetSize(width, height);
}

void Actor::SetSize(float width, float height, float depth)
{
  GetImplementation(*this).SetSize(width, height, depth);
}

void Actor::SetSize(const Vector2& size)
{
  GetImplementation(*this).SetSize(size);
}

void Actor::SetSize(const Vector3& size)
{
  GetImplementation(*this).SetSize(size);
}

Vector3 Actor::GetCurrentSize() const
{
  return GetImplementation(*this).GetCurrentSize();
}

void Actor::SetPosition(float x, float y)
{
  GetImplementation(*this).SetPosition(x, y);
}

void Actor::SetPosition(float x, float y, float z)
{
  GetImplementation(*this).SetPosition(x, y, z);
}

void Actor::SetPosition(const Vector3& position)
{
  GetImplementation(*this).SetPosition(position);
}

void Actor::SetX(float x)
{
  GetImplementation(*this).SetX(x);
}

void Actor::SetY(float y)
{
  GetImplementation(*this).SetY(y);
}

void Actor::SetZ(float z)
{
  GetImplementation(*this).SetZ(z);
}

void Actor::MoveBy(const Vector3& distance)
{
  GetImplementation(*this).MoveBy(distance);
}

Vector3 Actor::GetCurrentPosition() const
{
  return GetImplementation(*this).GetCurrentPosition();
}

Vector3 Actor::GetCurrentWorldPosition() const
{
  return GetImplementation(*this).GetCurrentWorldPosition();
}

void Actor::SetPositionInheritanceMode( PositionInheritanceMode mode )
{
  GetImplementation(*this).SetPositionInheritanceMode( mode );
}

PositionInheritanceMode Actor::GetPositionInheritanceMode() const
{
  return GetImplementation(*this).GetPositionInheritanceMode();
}

void Actor::SetRotation(const Degree& angle, const Vector3& axis)
{
  GetImplementation(*this).SetRotation(Radian(angle), axis);
}

void Actor::SetRotation(const Radian& angle, const Vector3& axis)
{
  GetImplementation(*this).SetRotation(angle, axis);
}

void Actor::SetRotation(const Quaternion& rotation)
{
  GetImplementation(*this).SetRotation(rotation);
}

void Actor::RotateBy(const Degree& angle, const Vector3& axis)
{
  GetImplementation(*this).RotateBy(Radian(angle), axis);
}

void Actor::RotateBy(const Radian& angle, const Vector3& axis)
{
  GetImplementation(*this).RotateBy(angle, axis);
}

void Actor::RotateBy(const Quaternion& relativeRotation)
{
  GetImplementation(*this).RotateBy(relativeRotation);
}

Quaternion Actor::GetCurrentRotation() const
{
  return GetImplementation(*this).GetCurrentRotation();
}

void Actor::SetInheritRotation(bool inherit)
{
  GetImplementation(*this).SetInheritRotation(inherit);
}

bool Actor::IsRotationInherited() const
{
  return GetImplementation(*this).IsRotationInherited();
}

Quaternion Actor::GetCurrentWorldRotation() const
{
  return GetImplementation(*this).GetCurrentWorldRotation();
}

void Actor::SetScale(float scale)
{
  GetImplementation(*this).SetScale(scale);
}

void Actor::SetScale(float scaleX, float scaleY, float scaleZ)
{
  GetImplementation(*this).SetScale(scaleX, scaleY, scaleZ);
}

void Actor::SetScale(const Vector3& scale)
{
  GetImplementation(*this).SetScale(scale);
}

void Actor::ScaleBy(const Vector3& relativeScale)
{
  GetImplementation(*this).ScaleBy(relativeScale);
}

Vector3 Actor::GetCurrentScale() const
{
  return GetImplementation(*this).GetCurrentScale();
}

Vector3 Actor::GetCurrentWorldScale() const
{
  return GetImplementation(*this).GetCurrentWorldScale();
}

void Actor::SetInheritScale( bool inherit )
{
  GetImplementation(*this).SetInheritScale( inherit );
}

bool Actor::IsScaleInherited() const
{
  return GetImplementation(*this).IsScaleInherited();
}

Matrix Actor::GetCurrentWorldMatrix() const
{
  return GetImplementation(*this).GetCurrentWorldMatrix();
}

void Actor::SetVisible(bool visible)
{
  GetImplementation(*this).SetVisible(visible);
}

bool Actor::IsVisible() const
{
  return GetImplementation(*this).IsVisible();
}

void Actor::SetOpacity(float opacity)
{
  GetImplementation(*this).SetOpacity(opacity);
}

void Actor::OpacityBy(float relativeOpacity)
{
  GetImplementation(*this).OpacityBy(relativeOpacity);
}

float Actor::GetCurrentOpacity() const
{
  return GetImplementation(*this).GetCurrentOpacity();
}

void Actor::SetColor(const Vector4& color)
{
  GetImplementation(*this).SetColor(color);
}

void Actor::ColorBy(const Vector4& relativeColor)
{
  GetImplementation(*this).ColorBy(relativeColor);
}

Vector4 Actor::GetCurrentColor() const
{
  return GetImplementation(*this).GetCurrentColor();
}

void Actor::SetColorMode( ColorMode colorMode )
{
  GetImplementation(*this).SetColorMode(colorMode);
}

ColorMode Actor::GetColorMode() const
{
  return GetImplementation(*this).GetColorMode();
}

Vector4 Actor::GetCurrentWorldColor() const
{
  return GetImplementation(*this).GetCurrentWorldColor();
}

void Actor::SetInheritShaderEffect(bool inherit)
{
  GetImplementation(*this).SetInheritShaderEffect(inherit);
}

bool Actor::GetInheritShaderEffect() const
{
  return GetImplementation(*this).GetInheritShaderEffect();
}

void Actor::SetShaderEffect(ShaderEffect effect)
{
  GetImplementation(*this).SetShaderEffect(GetImplementation(effect));
}

ShaderEffect Actor::GetShaderEffect() const
{
  Internal::ShaderEffectPtr internal = GetImplementation(*this).GetShaderEffect();

  return ShaderEffect(internal.Get());
}

void Actor::RemoveShaderEffect()
{
  GetImplementation(*this).RemoveShaderEffect();
}

void Actor::SetDrawMode( DrawMode::Type drawMode )
{
  GetImplementation(*this).SetDrawMode( drawMode );
}

DrawMode::Type Actor::GetDrawMode() const
{
  return GetImplementation(*this).GetDrawMode();
}

void Actor::SetSensitive(bool sensitive)
{
  GetImplementation(*this).SetSensitive(sensitive);
}

bool Actor::IsSensitive() const
{
  return GetImplementation(*this).IsSensitive();
}

bool Actor::ScreenToLocal(float& localX, float& localY, float screenX, float screenY) const
{
  return GetImplementation(*this).ScreenToLocal(localX, localY, screenX, screenY);
}

void Actor::SetLeaveRequired(bool required)
{
  GetImplementation(*this).SetLeaveRequired(required);
}

bool Actor::GetLeaveRequired() const
{
  return GetImplementation(*this).GetLeaveRequired();
}

void Actor::SetKeyboardFocusable( bool focusable )
{
  GetImplementation(*this).SetKeyboardFocusable(focusable);
}

bool Actor::IsKeyboardFocusable() const
{
  return GetImplementation(*this).IsKeyboardFocusable();
}

Actor::TouchSignalV2& Actor::TouchedSignal()
{
  return GetImplementation(*this).TouchedSignal();
}

Actor::MouseWheelEventSignalV2& Actor::MouseWheelEventSignal()
{
  return GetImplementation(*this).MouseWheelEventSignal();
}

Actor::SetSizeSignalV2& Actor::SetSizeSignal()
{
  return GetImplementation(*this).SetSizeSignal();
}

Actor::OnStageSignalV2& Actor::OnStageSignal()
{
  return GetImplementation(*this).OnStageSignal();
}

Actor::OffStageSignalV2& Actor::OffStageSignal()
{
  return GetImplementation(*this).OffStageSignal();
}

DynamicsBody Actor::EnableDynamics(DynamicsBodyConfig bodyConfig)
{
  Internal::DynamicsBodyConfig& internal = GetImplementation(bodyConfig);

  Internal::DynamicsBodyPtr body( GetImplementation(*this).EnableDynamics( &internal ) );

  return DynamicsBody( body.Get() );
}

DynamicsJoint Actor::AddDynamicsJoint( Actor attachedActor, const Vector3& offset )
{
  Internal::ActorPtr internalActor( &GetImplementation(attachedActor) );
  Internal::DynamicsJointPtr joint( GetImplementation(*this).AddDynamicsJoint( internalActor, offset) );

  return DynamicsJoint( joint.Get() );
}

DynamicsJoint Actor::AddDynamicsJoint( Actor attachedActor, const Vector3& offsetA, const Vector3& offsetB )
{
  Internal::ActorPtr internalActor( &GetImplementation(attachedActor) );
  Internal::DynamicsJointPtr joint( GetImplementation(*this).AddDynamicsJoint( internalActor, offsetA, offsetB) );

  return DynamicsJoint( joint.Get() );
}

const int Actor::GetNumberOfJoints() const
{
  return GetImplementation(*this).GetNumberOfJoints();
}

DynamicsJoint Actor::GetDynamicsJointByIndex( const int index )
{
  Internal::DynamicsJointPtr joint( GetImplementation(*this).GetDynamicsJointByIndex( index ) );

  return DynamicsJoint( joint.Get() );
}

DynamicsJoint Actor::GetDynamicsJoint( Actor attachedActor )
{
  Internal::DynamicsJointPtr joint( GetImplementation(*this).GetDynamicsJoint( &GetImplementation(attachedActor) ) );

  return DynamicsJoint( joint.Get() );
}

void Actor::RemoveDynamicsJoint( DynamicsJoint joint )
{
  GetImplementation(*this).RemoveDynamicsJoint( &GetImplementation(joint) );
}

void Actor::DisableDynamics()
{
  GetImplementation(*this).DisableDynamics();
}

DynamicsBody Actor::GetDynamicsBody()
{
  Internal::DynamicsBodyPtr internal(GetImplementation(*this).GetDynamicsBody());
  return DynamicsBody( internal.Get() );
}

Actor::Actor(Internal::Actor* internal)
: Constrainable(internal)
{
}

void UnparentAndReset( Actor& actor )
{
  if( actor )
  {
    actor.Unparent();
    actor.Reset();
  }
}

} // namespace Dali
