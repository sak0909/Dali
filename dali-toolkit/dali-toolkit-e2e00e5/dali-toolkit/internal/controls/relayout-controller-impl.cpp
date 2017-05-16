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

// FILE HEADER

#include "relayout-controller-impl.h"

// EXTERNAL INCLUDES

#include <stack>
#include <sstream>
#include <dali/integration-api/debug.h>

// INTERNAL INCLUDES

#include "dali-toolkit/public-api/controls/control.h"
#include "dali-toolkit/public-api/controls/control-impl.h"
#include "dali-toolkit/public-api/controls/text-view/text-view.h"

namespace Dali
{

namespace Toolkit
{

typedef std::pair< Control, Vector2 > ControlSizePair;
typedef std::stack< ControlSizePair > ControlStack;

namespace Internal
{

namespace
{
#if defined(DEBUG_ENABLED)

Integration::Log::Filter* gLogFilter( Integration::Log::Filter::New(Debug::NoLogging, false, "LOG_RELAYOUT_CONTROLLER") );

/**
 * Prints out all the children of the given actor when debug is enabled.
 *
 * @param[in]  actor  The actor whose children to print.
 * @param[in]  level  The number of " | " to put in front of the children.
 */
void PrintChildren( Actor actor, int level )
{
  std::ostringstream output;

  for ( int t = 0; t < level; ++t )
  {
    output << " | ";
  }

  output << actor.GetTypeName();

  output << " - Pos: " << actor.GetCurrentPosition() << " Size: " << actor.GetCurrentSize() << ",";

  output << " (" << actor.GetObjectPtr() << ")" << std::endl;

  DALI_LOG_INFO( gLogFilter, Debug::Verbose, output.str().c_str() );

  ++level;
  unsigned int numChildren = actor.GetChildCount();
  for( unsigned int i=0; i<numChildren; ++i )
  {
    PrintChildren( actor.GetChildAt(i), level );
  }
  --level;
}

/**
 * Prints the entire hierarchy of the scene.
 */
void PrintHierarchy()
{
  PrintChildren( Stage().GetCurrent().GetRootLayer(), 0 );
}

#define PRINT_HIERARCHY PrintHierarchy()

#else // defined(DEBUG_ENABLED)

#define PRINT_HIERARCHY

#endif // defined(DEBUG_ENABLED)

/**
 * Sets the target to source if the individual elements of source are NOT zero.
 *
 * @param[out]  target  The Vector2 elements to set if the source Vector2 elements are not 0.
 * @param[in]   source  The Vector2 elements that are to be set to the target Vector2.
 */
void SetIfNotZero( Vector2& target, const Vector2& source )
{
  // Only set the width if it is non zero.
  if ( !EqualsZero( source.width ) )
  {
    target.width  = source.width;
  }

  // Only set the height if it is non zero.
  if ( !EqualsZero( source.height ) )
  {
    target.height = source.height;
  }
}

/**
 * Finds controls in the hierarchy of actor. It descends the tree if the actor has more Actors.
 * If it is a control, it no longer descends the tree.
 *
 * @param[in]  actor  The actor in which controls should be found.
 * @param[in]  size   The size that this actor and its children should be.
 */
void FindControls( Actor actor, ControlStack& controls, Vector2 size )
{
  Control control( Control::DownCast( actor ) );
  if( control )
  {
    // If the control size has been set by the application / control, then we should try and honour that.
    Vector2 controlSetSize( control.GetImplementation().GetSizeSet() );

    // Only set the width and height if they are non zero.
    SetIfNotZero( size, controlSetSize );

    controls.push( ControlSizePair( control, size ) );
  }
  else
  {
    unsigned int numChildren = actor.GetChildCount();
    for( unsigned int i=numChildren; i>0; --i )
    {
      FindControls( actor.GetChildAt(i-1), controls, size );
    }
  }
}

/**
 * Pushes the controls in the container, to the stack.
 *
 * @param[in,out]  controlStack  The stack to push controls to.
 * @param[in]      container     The container to push controls from.
 */
void PushToStack( ControlStack& controlStack, const ActorSizeContainer& container )
{
  for ( ActorSizeContainer::const_reverse_iterator iter = container.rbegin(), endIter = container.rend(); iter != endIter; ++iter )
  {
    FindControls( iter->first, controlStack, iter->second );
  }
}

} // unnamed namespace

RelayoutControllerImpl::~RelayoutControllerImpl()
{
}

void RelayoutControllerImpl::Request()
{
  //TODO use Relayout Request to set up logic to optimize relayout of the actors/controls in the scene

  if( !mRelayoutConnection )
  {
    Stage stage = Stage::GetCurrent();
    stage.EventProcessingFinishedSignal().Connect( this, &RelayoutControllerImpl::Relayout );
    mRelayoutConnection = true;
  }
}

void RelayoutControllerImpl::Relayout()
{
  PRINT_HIERARCHY;

  // 1. Finds all top-level controls from the root actor and allocate them the size of the stage
  //    These controls are paired with the stage size and added to the stack.
  ControlStack controlStack;
  FindControls( Stage().GetCurrent().GetRootLayer(), controlStack, Stage::GetCurrent().GetSize() );

  // 2. Iterate through the stack until it's empty.
  while ( !controlStack.empty() )
  {
    ControlSizePair pair ( controlStack.top() );
    Control control ( pair.first );
    Vector2 size ( pair.second );
    controlStack.pop();

    DALI_LOG_INFO( gLogFilter, Debug::General, "Allocating %p (%.2f, %.2f)\n", control.GetObjectPtr(), size.width, size.height );

    // 3. Negotiate the size with the current control. Pass it an empty container which the control
    //    has to fill with all the actors it has not done any size negotiation for.
    ActorSizeContainer container;
    control.GetImplementation().NegotiateSize( size, container );

    // 4. Push the controls from the actors in the container to the stack.
    PushToStack( controlStack, container );
  }

  //Disconnect so that we relayout only when requested to do so.
  Disconnect();
}

void RelayoutControllerImpl::Disconnect()
{
  if( mRelayoutConnection )
  {
    Stage stage = Stage::GetCurrent();
    stage.EventProcessingFinishedSignal().Disconnect( this, &RelayoutControllerImpl::Relayout );
    mRelayoutConnection = false;
  }
}

RelayoutControllerImpl::RelayoutControllerImpl()
: mRelayoutConnection( false )
{
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
