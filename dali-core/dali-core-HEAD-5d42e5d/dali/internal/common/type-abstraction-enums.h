#ifndef __DALI_INTERNAL_TYPE_ABSTRACTION_ENUMS_H__
#define __DALI_INTERNAL_TYPE_ABSTRACTION_ENUMS_H__

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


//PUBLIC INCLUDES
#include <dali/public-api/actors/renderable-actor.h>
#include <dali/public-api/actors/blending.h>
#include <dali/public-api/shader-effects/shader-effect.h>

// INTERNAL INCLUDES
#include <dali/internal/common/type-abstraction.h>
#include <dali/internal/event/effects/shader-declarations.h>

namespace Dali
{

namespace Internal
{

template <> struct ParameterType< CullFaceMode > : public BasicType< CullFaceMode > {};
template <> struct ParameterType< BlendingMode::Type > : public BasicType< BlendingMode::Type > {};
template <> struct ParameterType< GeometryType > : public BasicType< GeometryType > {};
template <> struct ParameterType< ShaderSubTypes > : public BasicType< ShaderSubTypes > {};

} //namespace Internal

} //namespace Dali

#endif // __DALI_INTERNAL_TYPE_ABSTRACTION_ENUMS_H__
