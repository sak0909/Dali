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
#include <dali/public-api/adaptor-framework/common/orientation.h>

// INTERNAL INCLUDES
#include <internal/common/orientation-impl.h>

namespace Dali
{

Orientation::Orientation()
{
}

Orientation::~Orientation()
{
}

int Orientation::GetDegrees() const
{
  return Internal::Adaptor::GetImplementation(*this).GetDegrees();
}

float Orientation::GetRadians() const
{
  return Internal::Adaptor::GetImplementation(*this).GetRadians();
}

Orientation::OrientationSignalV2& Orientation::ChangedSignal()
{
  return Internal::Adaptor::GetImplementation(*this).ChangedSignal();
}

Orientation::Orientation( Internal::Adaptor::Orientation* orientation )
: BaseHandle(orientation)
{
}

} // namespace Dali
