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
#include <dali/public-api/animation/constraint.h>

// INTERNAL INCLUDES
#include <dali/public-api/animation/time-period.h>
#include <dali/internal/event/animation/constraint-impl.h>
#include <dali/internal/event/animation/constraint-source-impl.h>

namespace Dali
{

const AlphaFunction            Constraint::DEFAULT_ALPHA_FUNCTION = AlphaFunctions::Linear;
const Constraint::RemoveAction Constraint::DEFAULT_REMOVE_ACTION  = Constraint::Bake;

Constraint::Constraint()
{
}

Constraint::Constraint(Internal::Constraint* constraint)
: BaseHandle(constraint)
{
}

Constraint::~Constraint()
{
}

void Constraint::SetApplyTime( TimePeriod timePeriod )
{
  GetImplementation(*this).SetApplyTime( timePeriod );
}

TimePeriod Constraint::GetApplyTime() const
{
  return GetImplementation(*this).GetApplyTime();
}

void Constraint::SetRemoveTime( TimePeriod timePeriod )
{
  GetImplementation(*this).SetRemoveTime( timePeriod );
}

TimePeriod Constraint::GetRemoveTime() const
{
  return GetImplementation(*this).GetRemoveTime();
}

void Constraint::SetAlphaFunction( AlphaFunction func )
{
  GetImplementation(*this).SetAlphaFunction( func );
}

AlphaFunction Constraint::GetAlphaFunction()
{
  return GetImplementation(*this).GetAlphaFunction();
}

void Constraint::SetRemoveAction(Constraint::RemoveAction action)
{
  GetImplementation(*this).SetRemoveAction(action);
}

Constraint::RemoveAction Constraint::GetRemoveAction() const
{
  return GetImplementation(*this).GetRemoveAction();
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources; // empty

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            ConstraintSource source2,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );
  sources.push_back( Internal::Source( source2 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            ConstraintSource source2,
                            ConstraintSource source3,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );
  sources.push_back( Internal::Source( source2 ) );
  sources.push_back( Internal::Source( source3 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            ConstraintSource source2,
                            ConstraintSource source3,
                            ConstraintSource source4,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );
  sources.push_back( Internal::Source( source2 ) );
  sources.push_back( Internal::Source( source3 ) );
  sources.push_back( Internal::Source( source4 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            ConstraintSource source2,
                            ConstraintSource source3,
                            ConstraintSource source4,
                            ConstraintSource source5,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );
  sources.push_back( Internal::Source( source2 ) );
  sources.push_back( Internal::Source( source3 ) );
  sources.push_back( Internal::Source( source4 ) );
  sources.push_back( Internal::Source( source5 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::New( Property::Index target,
                            Property::Type targetType,
                            ConstraintSource source1,
                            ConstraintSource source2,
                            ConstraintSource source3,
                            ConstraintSource source4,
                            ConstraintSource source5,
                            ConstraintSource source6,
                            AnyFunction func,
                            AnyFunction interpolator )
{
  Internal::SourceContainer sources;
  sources.push_back( Internal::Source( source1 ) );
  sources.push_back( Internal::Source( source2 ) );
  sources.push_back( Internal::Source( source3 ) );
  sources.push_back( Internal::Source( source4 ) );
  sources.push_back( Internal::Source( source5 ) );
  sources.push_back( Internal::Source( source6 ) );

  return Constraint( new Internal::Constraint( target,
                                               targetType,
                                               sources,
                                               func,
                                               interpolator ) );
}

Constraint Constraint::DownCast( BaseHandle handle )
{
  return Constraint( dynamic_cast<Dali::Internal::Constraint*>(handle.GetObjectPtr()) );
}

} // namespace Dali
