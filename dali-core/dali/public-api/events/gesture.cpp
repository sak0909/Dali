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
#include <dali/public-api/events/gesture.h>

namespace Dali
{

Gesture::Gesture( const Gesture& rhs )
: type(rhs.type),
  state(rhs.state),
  time(rhs.time)
{
}

Gesture& Gesture::operator=( const Gesture& rhs )
{
  type = rhs.type;
  state = rhs.state;
  time = rhs.time;

  return *this;
}

Gesture::~Gesture()
{
}

Gesture::Gesture(Type gestureType, State gestureState)
: type(gestureType),
  state(gestureState),
  time(0)
{
}

} // namespace Dali
