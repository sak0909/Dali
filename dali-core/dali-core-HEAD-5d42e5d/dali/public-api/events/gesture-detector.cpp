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
#include <dali/public-api/events/gesture-detector.h>

// INTERNAL INCLUDES
#include <dali/internal/event/events/gesture-detector-impl.h>

namespace Dali
{

GestureDetector::GestureDetector(Internal::GestureDetector* internal)
: Handle(internal)
{
}

GestureDetector::GestureDetector()
{
}

GestureDetector GestureDetector::DownCast( BaseHandle handle )
{
  return GestureDetector( dynamic_cast<Dali::Internal::GestureDetector*>(handle.GetObjectPtr()) );
}

GestureDetector::~GestureDetector()
{
}

void GestureDetector::Attach(Actor actor)
{
  GetImplementation(*this).Attach(GetImplementation(actor));
}

void GestureDetector::Detach(Actor actor)
{
  GetImplementation(*this).Detach(GetImplementation(actor));
}

void GestureDetector::DetachAll()
{
  GetImplementation(*this).DetachAll();
}

std::vector<Actor> GestureDetector::GetAttachedActors() const
{
  return GetImplementation(*this).GetAttachedActors();
}

} // namespace Dali
