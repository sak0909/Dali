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
#include "dali-toolkit/internal/controls/table-view/table-view-impl.h"
#include <dali-toolkit/internal/focus-manager/keyboard-focus-manager-impl.h>

// EXTERNAL INCLUDES
#include <dali/public-api/object/ref-object.h>
#include <dlog.h>

using namespace Dali;
using namespace std;

namespace
{
// Type registration
BaseHandle Create()
{
  return Toolkit::TableView::New(0, 0);
}
TypeRegistration mType( typeid(Toolkit::TableView), typeid(Toolkit::Control), Create );

const float DEFAULT_CONSTRAINT_DURATION = 0.0f;

/**
 * Constraint that sets a child property relative to parents Width or Height
 */
struct RelativeToWidthOrHeight
{
  /**
   * Constraint that is relative (%) to parent width/height and applies a
   * unit based padding before the relative calculation.
   * @param scale of parent minus padding between 0 and 1
   * @param padding in world coordinate units
   * @param fixed part in world coordinate units
   */
  RelativeToWidthOrHeight( float scale, float padding, float fixed )
  : mScaleFactor( scale ),
    mPadding( padding ),
    mFixed( fixed )
  {
  }

  inline float operator()( const float& parentWidthOrHeight )
  {
    return mFixed  + ( parentWidthOrHeight - mPadding  ) * mScaleFactor;
  }

  float operator()( const float& current,
                    const PropertyInput& parentWidthOrHeight )
  {
    return operator()( parentWidthOrHeight.GetFloat() );
  }

  float mScaleFactor;
  float mPadding;
  float mFixed;
};

#if defined(DEBUG_ENABLED)
// debugging support, very useful when new features are added or bugs are hunted down
// currently not called from code so compiler will optimize these away, kept here for future debugging

#define TABLEVIEW_TAG "DALI Toolkit::TableView"
#define TV_LOG(fmt, args...) LOG(LOG_INFO, TABLEVIEW_TAG, fmt, ## args)

void PrintArray( Array2d<Dali::Toolkit::Internal::TableView::CellData>& array )
{
  TV_LOG( "Array2d<CellData> size [%d,%d] \n", array.GetRows(), array.GetColumns() );
  // print values
  for( unsigned int i = 0; i < array.GetRows(); ++i )
  {
    for( unsigned int j = 0; j < array.GetColumns(); ++j )
    {
      Dali::Toolkit::Internal::TableView::CellData data = array[i][j];
      char actor = ' ';
      if( data.actor )
      {
        actor = 'A';
      }
      TV_LOG("Array[%d,%d]=%c %d,%d,%d,%d  ", i, j, actor,
          data.position.rowIndex, data.position.columnIndex,
          data.position.rowSpan, data.position.columnSpan );
    }
    TV_LOG( "\n" );
  }
}

// debugging support, very useful when new features are added or bugs are hunted down
// currently not called from code so compiler will optimize these away, kept here for future debugging
void PrintArray( Array2d<Size>& array )
{
  TV_LOG( "Array2d<Size> size [%d,%d] \n", array.GetRows(), array.GetColumns() );
  // print values
  for( unsigned int i = 0; i < array.GetRows(); ++i )
  {
    for( unsigned int j = 0; j < array.GetColumns(); ++j )
    {
      TV_LOG( "Array[%d,%d]=%.2f,%.2f ", i, j, array[i][j].width, array[i][j].height );
    }
    TV_LOG( "\n" );
  }
}
// debugging support, very useful when new features are added or bugs are hunted down
// currently not called from code so compiler will optimize these away, kept here for future debugging
void PrintVector( vector<float>& array )
{
  TV_LOG( "vector, size [%d]\n", array.size() );
  // print values
  for( unsigned int i = 0; i < array.size(); ++i )
  {
    TV_LOG( "vector[%d]=%.2f ", i, array[i] );
  }
  TV_LOG( "\n" );
}
#endif // defined(DEBUG_ENABLED)

} // namespace

namespace Dali
{

namespace Toolkit
{

namespace Internal
{

Toolkit::TableView TableView::New( unsigned int initialRows, unsigned int initialColumns )
{
  // Create the implementation, temporarily owned by this handle on stack
  IntrusivePtr< TableView > impl = new TableView( initialRows, initialColumns );

  // Pass ownership to CustomActor handle
  Toolkit::TableView handle( *impl );

  // Second-phase init of the implementation
  // This can only be done after the CustomActor connection has been made...
  impl->Initialize();

  return handle;
}

bool TableView::AddChild( Actor child, Toolkit::TableView::CellPosition position )
{
  // check that the child is valid
  DALI_ASSERT_ALWAYS( child );

  // if child is already parented, we adopt it
  if( child.GetParent() )
  {
    child.GetParent().Remove( child );
  }
  // check if we need to expand our data array
  if( position.rowIndex >= mCellData.GetRows() )
  {
    // only adding new rows
    ResizeContainers( position.rowIndex + 1, mCellData.GetColumns() );
  }
  if( position.columnIndex >= mCellData.GetColumns() )
  {
    // only adding new columns
    ResizeContainers( mCellData.GetRows(), position.columnIndex + 1 );
  }
  // check if there already is something in this cell
  if( mCellData[ position.rowIndex ][ position.columnIndex ].actor )
  {
    return false; // cannot share a cell, it would complicate all logic and not bring much benefit
  }
  RelayoutingLock lock( *this );
  // adopt the child
  Self().Add( child );

  // put the actor to the main cell
  CellData data;
  data.actor = child;
  data.position = position;
  mCellData[ position.rowIndex ][ position.columnIndex ] = data;
  // if child spans multiple rows of columns
  bool spanned = false;
  if( position.rowSpan > 1 )
  {
    // span might go outside table
    if( position.rowIndex + position.rowSpan > mCellData.GetRows() )
    {
      // increase table size for the full span, only increasing rows
      ResizeContainers( position.rowIndex + position.rowSpan, mCellData.GetColumns() );
    }
    spanned = true;
  }
  if( position.columnSpan > 1 )
  {
    // span might go outside table
    if( position.columnIndex + position.columnSpan > mCellData.GetColumns() )
    {
      // increase table size for the full span, only increasing columns
      ResizeContainers( mCellData.GetRows(), position.columnIndex + position.columnSpan );
    }
    spanned = true;
  }
  // if it spanned multiple rows, put the cellinfo in all of those
  if( spanned )
  {
    for( unsigned int row = position.rowIndex; row < ( position.rowIndex + position.rowSpan ); ++row )
    {
      // store same information to all cells, this way we can identify
      // if a cell is the prime location of an actor or a spanned one
      for( unsigned int column = position.columnIndex; column < ( position.columnIndex + position.columnSpan ); ++column )
      {
        // store same information to all cells, this way we can identify
        // if a cell is the prime location of an actor or a spanned one
        mCellData[ row ][ column ] = data;
      }
    }
  }
  // relayout the whole table
  RelayoutRequest();
  return true; // addition successful
}

Actor TableView::GetChildAt( Toolkit::TableView::CellPosition position )
{
  // check if we have this row and column in the table
  if( ( position.columnIndex >= mCellData.GetColumns() )||
      ( position.rowIndex >= mCellData.GetRows() ) )
  {
    // return an empty handle
    return Actor();
  }
  // return the child handle
  return mCellData[ position.rowIndex ][ position.columnIndex ].actor;
}

Actor TableView::RemoveChildAt( Toolkit::TableView::CellPosition position )
{
  // get the child handle
  Actor child = GetChildAt( position );
  // if no real actor there, nothing else to be done
  if( child )
  {
    RelayoutingLock lock( *this );
    // Remove the child, this will trigger a call to OnControlChildRemove
    Self().Remove( child );

    // relayout the table only if instances were found
    if( RemoveAllInstances( child ) )
    {
      RelayoutRequest();
    }
  }
  // return the child back to caller
  return child;
}

bool TableView::FindChildPosition( Actor child, Toolkit::TableView::CellPosition& position )
{
  // only find valid child actors
  if( child )
  {
    // walk through the layout data
    const unsigned int rowCount = mCellData.GetRows();
    const unsigned int columnCount = mCellData.GetColumns();
    for( unsigned int row = 0; row < rowCount; ++row )
    {
      for( unsigned int column = 0; column < columnCount; ++column )
      {
        if( mCellData[ row ][ column ].actor == child )
        {
          position = mCellData[ row ][ column ].position;
          return true;
        }
      }
    }
  }
  return false;
}

void TableView::InsertRow( unsigned int rowIndex )
{
  RelayoutingLock lock( *this );
  mCellData.InsertRow( rowIndex );
  // need to update the cellinfos for the items that moved
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      Toolkit::TableView::CellPosition& position = mCellData[ row ][ column ].position;
      // if cell is spanning and above and spans to inserted row
      if( ( position.rowSpan > 1 )&&( position.rowIndex <= rowIndex )&&
          ( position.rowIndex + position.rowSpan > rowIndex ) )
      {
        // increase span by one
        position.rowSpan++;
        // copy cell to occupy the new column
        mCellData[ rowIndex ][ column ] = mCellData[ row ][ column ];
      }
      // if below of inserted row, increase row index
      else if( row > rowIndex )
      {
        // increase index by one
        position.rowIndex++;
      }
    }
  }
  mRelativeSizes.InsertRow( rowIndex );
  // inserting a row requires adjusting the height vectors
  mFixedHeights.insert( mFixedHeights.begin() + rowIndex, 0 );
  mRelativeHeights.insert( mRelativeHeights.begin() + rowIndex, 0 );
  RelayoutRequest();
}

void TableView::DeleteRow( unsigned int rowIndex )
{
  vector< Actor > ignored;
  DeleteRow( rowIndex, ignored );
}

void TableView::DeleteRow( unsigned int rowIndex, vector<Actor>& removed )
{
  RelayoutingLock lock( *this );
  vector< CellData > lost;
  mCellData.DeleteRow( rowIndex, lost );
  // need to update the cellinfos for the items that moved
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      Toolkit::TableView::CellPosition& position = mCellData[ row ][ column ].position;
      // if cell is spanning and above and spans to deleted row
      if( ( position.rowSpan > 1 )&&( position.rowIndex <= rowIndex )&&
          ( position.rowIndex + position.rowSpan > rowIndex ) )
      {
        // decrease span by one
        if( position.rowSpan > 1 )
        {
          position.rowSpan--;
        }
      }
      // if below of or at the inserted row, decrease row index
      else if( row >= rowIndex )
      {
        // decrease index by one
        if( position.rowIndex > 1 )
        {
          position.rowIndex--;
        }
      }
    }
  }
  // 1 row removed, 0 columns
  RemoveAndGetLostActors( lost, removed, 1u, 0u );
  // resize the data structures
  mRelativeSizes.DeleteRow( rowIndex );
  // deleting a row requires adjusting the height vectors
  mFixedHeights.erase( mFixedHeights.begin() + rowIndex );
  mRelativeHeights.erase( mRelativeHeights.begin() + rowIndex );
  RelayoutRequest();
}

void TableView::InsertColumn( unsigned int columnIndex )
{
  RelayoutingLock lock( *this );
  mCellData.InsertColumn( columnIndex );
  // need to update the cellinfos for the items that moved
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      Toolkit::TableView::CellPosition& position = mCellData[ row ][ column ].position;
      // if cell is spanning and left side and spans to inserted column
      if( ( position.columnSpan > 1 )&&( position.columnIndex <= columnIndex )&&
          ( position.columnIndex + position.columnSpan > columnIndex ) )
      {
        // increase span by one
        position.columnSpan++;
        // copy cell to occupy the new column
        mCellData[ row ][ columnIndex ] = mCellData[ row ][ column ];
      }
      // if on the right side of inserted column, increase column index
      else if( column > columnIndex )
      {
        // increase index by one
        position.columnIndex++;
      }
    }
  }
  // relative sizes gets recalculated on Relayout
  mRelativeSizes.InsertColumn( columnIndex );
  // inserting a column requires adjusting the width vectors
  mFixedWidths.insert( mFixedWidths.begin() + columnIndex, 0 );
  mRelativeWidths.insert( mRelativeWidths.begin() + columnIndex, 0 );
  RelayoutRequest();
}

void TableView::DeleteColumn( unsigned int columnIndex )
{
  vector< Actor > ignored;
  DeleteColumn( columnIndex, ignored );
}

void TableView::DeleteColumn( unsigned int columnIndex, vector<Actor>& removed )
{
  RelayoutingLock lock( *this );
  vector< CellData > lost;
  mCellData.DeleteColumn( columnIndex, lost );
  // need to update the cellinfos for the items that moved
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      Toolkit::TableView::CellPosition& position = mCellData[ row ][ column ].position;
      // if cell is spanning and left side and spans to inserted column
      if( ( position.columnSpan > 1 )&&( position.columnIndex <= columnIndex )&&
          ( position.columnIndex + position.columnSpan > columnIndex ) )
      {
        // decrease span by one
        if( position.columnSpan > 1 )
        {
          position.columnSpan--;
        }
      }
      // if on the right side of or at the inserted column, decrease column index
      else if( column >= columnIndex )
      {
        // decrease index by one
        if( position.columnIndex > 0 )
        {
          position.columnIndex--;
        }
      }
    }
  }
  // 0 rows, 1 column removed
  RemoveAndGetLostActors( lost, removed, 0u, 1u );
  // resize the data structures
  mRelativeSizes.DeleteColumn( columnIndex );
  // deleting a column requires adjusting the width vectors
  mFixedWidths.erase( mFixedWidths.begin() + columnIndex );
  mRelativeWidths.erase( mRelativeWidths.begin() + columnIndex );
  // relayout
  RelayoutRequest();
}

void TableView::Resize( unsigned int rows, unsigned int columns )
{
  vector< Actor > ignored;
  Resize( rows, columns, ignored );
}

void TableView::Resize( unsigned int rows, unsigned int columns, vector<Actor>& removed )
{
  RelayoutingLock lock( *this );
  unsigned int oldRows = GetRows();
  unsigned int oldColumns = GetColumns();
  // resize data array
  vector< CellData > lost;
  ResizeContainers( rows, columns, lost );
  // calculate if we lost rows or columns
  unsigned int rowsRemoved = 0;
  unsigned int newRows = GetRows();
  if( oldRows < newRows )
  {
    rowsRemoved = newRows - oldRows;
  }
  unsigned int columnsRemoved = 0;
  unsigned int newColumns = GetColumns();
  if( oldColumns < newColumns )
  {
    rowsRemoved = newColumns - oldColumns;
  }
  RemoveAndGetLostActors( lost, removed, rowsRemoved, columnsRemoved );
  // finally relayout once all actors are removed
  RelayoutRequest();
}

void TableView::SetCellPadding( Size padding )
{
  // if padding really changed
  if( padding != mPadding )
  {
    mPadding = padding;
    // do a relayout
    RelayoutRequest();
  }
}

Size TableView::GetCellPadding()
{
  return mPadding;
}

void TableView::SetFixedHeight( unsigned int rowIndex, float height )
{
  DALI_ASSERT_ALWAYS( rowIndex < mFixedHeights.size() );
  // add the fixed height to the array of fixed heights
  mFixedHeights[ rowIndex ] = height;
  // relayout all cells, no lock needed as nothing added or removed
  RelayoutRequest();
}

float TableView::GetFixedHeight( unsigned int rowIndex ) const
{
  DALI_ASSERT_ALWAYS( rowIndex < mFixedHeights.size() );

  return mFixedHeights[ rowIndex ];
}

void TableView::SetRelativeHeight( unsigned int rowIndex, float heightPercentage )
{
  DALI_ASSERT_ALWAYS( rowIndex < mRelativeHeights.size() );
  // add the relative height to the array of relative heights
  mRelativeHeights[ rowIndex ] = heightPercentage;
  // relayout all cells, no lock needed as nothing added or removed
  RelayoutRequest();
}

float TableView::GetRelativeHeight( unsigned int rowIndex ) const
{
  DALI_ASSERT_ALWAYS( rowIndex < mRelativeHeights.size() );

  return mRelativeHeights[ rowIndex ];
}

void TableView::SetFixedWidth( unsigned int columnIndex, float width )
{
  DALI_ASSERT_ALWAYS( columnIndex < mFixedWidths.size() );
  // add the fixed width to the array of fixed column widths
  mFixedWidths[ columnIndex ] = width;
  // relayout all cells, no lock needed as nothing added or removed
  RelayoutRequest();
}

float TableView::GetFixedWidth( unsigned int columnIndex ) const
{
  DALI_ASSERT_ALWAYS( columnIndex < mFixedWidths.size() );

  return mFixedWidths[ columnIndex ];
}

void TableView::SetRelativeWidth( unsigned int columnIndex, float widthPercentage )
{
  DALI_ASSERT_ALWAYS( columnIndex < mRelativeWidths.size() );
  // add the relative widths to the array of relative widths
  mRelativeWidths[ columnIndex ] = widthPercentage;
  // relayout all cells, no lock needed as nothing added or removed
  RelayoutRequest();
}

float TableView::GetRelativeWidth( unsigned int columnIndex ) const
{
  DALI_ASSERT_ALWAYS( columnIndex < mRelativeWidths.size() );

  return mRelativeWidths[ columnIndex ];
}

void TableView::SetLayoutAnimationDuration( float duration )
{
  mConstraintDuration = duration;
}

float TableView::GetLayoutAnimationDuration()
{
  return mConstraintDuration;
}

void TableView::OnRelaidOut( Vector2 size, ActorSizeContainer& container )
{
  float fixedHeightsTotal = 0.0f;
  float fixedWidthsTotal = 0.0f;

  // 1. update the relative sizes and calculate total fixed height and width
  UpdateRelativeSizes( fixedHeightsTotal, fixedWidthsTotal );

  // 2. go through the layout data and create constraints
  float cumulatedFixedHeight = 0.0f;
  float cumulatedRelativeHeight = 0.0f;

  // iterate the table
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  // float versions of the count + 1 to keep precision
  const float maxRowPlusOne( rowCount + 1 );
  const float maxColumnPlusOne( columnCount + 1 );
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    // reset widths at the start of each row
    float cumulatedFixedWidth = 0.0f;
    float cumulatedRelativeWidth = 0.0f;
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      // check if this cell has an actor
      Actor actor = mCellData[ row ][ column ].actor;
      const Toolkit::TableView::CellPosition position = mCellData[ row ][ column ].position;
      // if there is an actor and this is the main cell of the actor
      // an actor can be in multiple cells if its row or columnspan is more than 1
      // we however must only lay out each actor only once
      if( ( actor )&&( position.rowIndex == row )&&( position.columnIndex == column ) )
      {
        // anchor actor correctly
        actor.SetAnchorPoint( AnchorPoint::TOP_LEFT );
        actor.SetParentOrigin( ParentOrigin::TOP_LEFT );
        // remove old constraints
        actor.RemoveConstraints();

        // 1. set position
        // get the row and column indices
        float rowPos( position.rowIndex );
        float colPos( position.columnIndex );
        // constrain the actor position to be relative to the width and height of table
        // minus the padding of course (padding is all around cells)
        Vector2 relativePosition( cumulatedRelativeWidth, cumulatedRelativeHeight );
        // fixed height rows and fixed width cells are considered as padding so
        // they are removed from the total size for relative
        // for position only consider cumulated fixed rows and columns from top and left
        Vector2 positionPadding( maxColumnPlusOne * mPadding.width + fixedWidthsTotal,
                                 maxRowPlusOne * mPadding.height + fixedHeightsTotal );
        Vector2 fixedPosition( ( colPos + 1.0f ) * mPadding.width + cumulatedFixedWidth,
                                 ( rowPos + 1.0f ) * mPadding.height + cumulatedFixedHeight );

        Constraint widthConstraint = Constraint::New<float>( Actor::POSITION_X,
                                                             ParentSource( Actor::SIZE_WIDTH ),
                                                             RelativeToWidthOrHeight( relativePosition.x, positionPadding.x, fixedPosition.x ) );

        Constraint heightConstraint = Constraint::New<float>( Actor::POSITION_Y,
                                                              ParentSource( Actor::SIZE_HEIGHT ),
                                                              RelativeToWidthOrHeight( relativePosition.y, positionPadding.y, fixedPosition.y ) );

        widthConstraint.SetApplyTime( mConstraintDuration );
        heightConstraint.SetApplyTime( mConstraintDuration );

        // bake constrained position value if constraint is removed
        widthConstraint.SetRemoveAction( Constraint::Bake );
        heightConstraint.SetRemoveAction( Constraint::Bake );

        actor.ApplyConstraint( widthConstraint );
        actor.ApplyConstraint( heightConstraint );

        // 2. set size
        // constrain the actor size to be relative to the size of table
        // get the relative size for this cell
        Vector2 relativeSize( mRelativeSizes[ row ][ column ] );
        Vector2 fixedSize( mFixedWidths[ column ], mFixedHeights[ row ] );
        // if we span multiple cells, need to sum them all up, both fixed and relative parts
        if( position.rowSpan > 1 )
        {
          for( unsigned int i = 1; i < position.rowSpan; ++i )
          {
            // accumulate the height only
            relativeSize.height += mRelativeSizes[ row + i ][ column ].height;
            fixedSize.height += mFixedHeights[ row + i ];
          }
        }
        if( position.columnSpan > 1 )
        {
          for( unsigned int i = 1; i < position.columnSpan; ++i )
          {
            // accumulate the width only
            relativeSize.width += mRelativeSizes[ row ][ column + i ].width;
            fixedSize.width += mFixedWidths[ column + i ];
          }
        }
        // minus the padding from size (padding is all around cells)
        // if item spans multiple columns or rows then less padding is added (default span is 1)
        // fixed height rows and fixed width cells are considered as padding so they are removed
        // from the total available size for relative cells
        Vector2 sizePadding( maxColumnPlusOne * mPadding.width + fixedWidthsTotal,
                             maxRowPlusOne * mPadding.height + fixedHeightsTotal );
        // and added to the fixed size multiplied by the span of rows and columns
        fixedSize.width += ( position.columnSpan - 1.0f ) * mPadding.width;
        fixedSize.height += ( position.rowSpan - 1.0f ) * mPadding.height;

        RelativeToWidthOrHeight relativeWidthFunctor( relativeSize.x, sizePadding.x, fixedSize.x );
        RelativeToWidthOrHeight relativeHeightFunctor( relativeSize.y, sizePadding.y, fixedSize.y );

        widthConstraint = Constraint::New<float>( Actor::SIZE_WIDTH,
                                                  ParentSource( Actor::SIZE_WIDTH ),
                                                  relativeWidthFunctor );

        heightConstraint = Constraint::New<float>( Actor::SIZE_HEIGHT,
                                                   ParentSource( Actor::SIZE_HEIGHT ),
                                                   relativeHeightFunctor );

        widthConstraint.SetApplyTime( mConstraintDuration );
        heightConstraint.SetApplyTime( mConstraintDuration );

        // bake constrained size value if constraint is removed
        widthConstraint.SetRemoveAction( Constraint::Bake );
        heightConstraint.SetRemoveAction( Constraint::Bake );

        actor.ApplyConstraint( widthConstraint );
        actor.ApplyConstraint( heightConstraint );

        // Relayout Children
        Relayout ( actor, Vector2( relativeWidthFunctor( size.width ), relativeHeightFunctor( size.height ) ), container );
      }
      // for position we need to keep track of current fixed width and relative width
      // increase for next column
      cumulatedFixedWidth += mFixedWidths[ column ];
      cumulatedRelativeWidth += mRelativeSizes[ row ][ column ].width;
    }
    // for position we need to keep track of current fixed height and relative height
    // increase for next row
    cumulatedFixedHeight += mFixedHeights[ row ];
    cumulatedRelativeHeight += mRelativeSizes[ row ][ 0 ].height; // all columns share same height
  }
}

unsigned int TableView::GetRows()
{
  return mCellData.GetRows();
}

unsigned int TableView::GetColumns()
{
  return mCellData.GetColumns();
}

void TableView::OnControlChildAdd( Actor& child )
{
  if( mLayoutingChild )
  {
    // we're in the middle of laying out children so no point doing anything here
    return;
  }
  // check if we're already laying out this child somewhere on the table
  // walk through the layout data
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  // child not yet laid out, find the first free slot
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      // no actor means free cell
      if( !(mCellData[ row ][ column ].actor) )
      {
        // put the actor in the cell
        CellData data;
        data.actor = child;
        data.position.columnIndex = column;
        data.position.rowIndex = row;
        mCellData[ row ][ column ] = data;
        RelayoutRequest();
        // don' continue
        return;
      }
    }
  }
  // still here, no room for the poor child so increase the array. Need a new row
  ResizeContainers( rowCount + 1, columnCount );
  // put the actor to the first cell of the new row
  CellData data;
  data.actor = child;
  data.position.rowIndex = rowCount;
  data.position.columnIndex = 0;
  mCellData[ rowCount ][ 0 ] = data;
  // finally relayout the table
  RelayoutRequest();
}

void TableView::OnControlChildRemove( Actor& child )
{
  // dont process if we're in the middle of bigger operation like delete row, column or resize
  if( !mLayoutingChild )
  {
    // relayout the table only if instances were found
    if( RemoveAllInstances( child ) )
    {
      RelayoutRequest();
    }
  }
}

TableView::TableView( unsigned int initialRows, unsigned int initialColumns )
: ControlImpl( true ),  // requires touch
  mCellData( initialRows, initialColumns ),
  mLayoutingChild( false ),
  mConstraintDuration( DEFAULT_CONSTRAINT_DURATION )
{
  SetKeyboardNavigationSupport( true );
  ResizeContainers( initialRows, initialColumns );
}

void TableView::OnInitialize()
{
  // Make self as keyboard focusable and focus group
  Actor self = Self();
  self.SetKeyboardFocusable(true);
  SetAsKeyboardFocusGroup(true);
}

void TableView::ResizeContainers( unsigned int rows, unsigned int columns )
{
  vector<CellData> ignored;
  ResizeContainers( rows, columns, ignored );
}

void TableView::ResizeContainers( unsigned int rows, unsigned int columns, vector<CellData>& removed )
{
  mCellData.Resize( rows, columns, removed );
  // we dont care if these go smaller, data will be regenerated or is not needed anymore
  mRelativeSizes.Resize( rows, columns );
  mFixedHeights.resize( rows );
  mRelativeHeights.resize( rows );
  mFixedWidths.resize( columns );
  mRelativeWidths.resize( columns );
}

void TableView::RemoveAndGetLostActors( const vector<CellData>& lost, vector<Actor>& removed,
                                        unsigned int rowsRemoved, unsigned int columnsRemoved )
{
  // iterate through all lost cells
  vector< CellData >::const_iterator iter = lost.begin();
  for( ; iter != lost.end(); ++iter )
  {
    // if it is a valid actor
    if( (*iter).actor )
    {
      // is this actor still somewhere else in the table
      Toolkit::TableView::CellPosition position;
      if( FindChildPosition( (*iter).actor, position ) )
      {
        // it must be spanning multiple cells, position contains the top left most one
        // check if position is left of the removed location
        if( position.columnIndex < (*iter).position.columnIndex )
        {
          // if column span is greater than 1
          if( mCellData[ position.rowIndex ][ position.columnIndex ].position.columnSpan > 1 )
          {
            // decrease column span
            mCellData[ position.rowIndex ][ position.columnIndex ].position.columnSpan -= columnsRemoved;
          }
        }
        // check if position is left of the removed location
        if( position.rowIndex < (*iter).position.rowIndex )
        {
          // if row span is greater than 1
          if( mCellData[ position.rowIndex ][ position.columnIndex ].position.rowSpan > 1 )
          {
            // decrease row span
            mCellData[ position.rowIndex ][ position.columnIndex ].position.rowSpan -= rowsRemoved;
          }
        }
      }
      else
      {
        // this actor is gone for good
        // add actor to removed container
        removed.push_back( (*iter).actor );
        // we dont want the child actor anymore
        Self().Remove( (*iter).actor );
      }
    }
  }
}

bool TableView::RemoveAllInstances( Actor child )
{
  bool found = false;
  // walk through the layout data
  const unsigned int rowCount = mCellData.GetRows();
  const unsigned int columnCount = mCellData.GetColumns();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      if( mCellData[ row ][ column ].actor == child )
      {
        // clear the cell, NOTE that the cell might be spanning multiple cells
        mCellData[ row ][ column ] = CellData();
        found = true;
      }
    }
  }
  return found;
}

void TableView::UpdateRelativeSizes( float& fixedHeightsTotal, float& fixedWidthsTotal )
{
  // 1. check all the fixed heights and widths to know how much size they take in total
  // as well as the relative heights and widths to know how much is left for the 'fill' cells
  unsigned int fixedRowCount = 0;
  unsigned int relativeRowCount = 0;
  float relativeHeightsTotal = 0.0f;
  const unsigned int rowCount = mCellData.GetRows();
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    if( mFixedHeights[ row ] > 0.0f )
    {
      ++fixedRowCount;
      fixedHeightsTotal += mFixedHeights[ row ];
    }
    if( mRelativeHeights[ row ] > 0.0f )
    {
      ++relativeRowCount;
      relativeHeightsTotal += mRelativeHeights[ row ];
    }
  }
  unsigned int fixedColumnCount = 0;
  unsigned int relativeColumnCount = 0;
  const unsigned int columnCount = mCellData.GetColumns();
  float relativeWidthsTotal = 0.0f;
  for( unsigned int column = 0; column < columnCount; ++column )
  {
    if( mFixedWidths[ column ] > 0.0f )
    {
      ++fixedColumnCount;
      fixedWidthsTotal += mFixedWidths[ column ];
    }
    if( mRelativeWidths[ column ] > 0.0f )
    {
      ++relativeColumnCount;
      relativeWidthsTotal += mRelativeWidths[ column ];
    }
  }

  // 2. cap the relative width and height totals to 100%
  if( relativeHeightsTotal > 1.0f )
  {
    relativeHeightsTotal = 1.0f;
  }
  if( relativeWidthsTotal > 1.0f )
  {
    relativeWidthsTotal = 1.0f;
  }

  // 3. create a table of relative sizes so we can lookup for cells that span multiple rows & colums
  const float fillRowCount( rowCount - relativeRowCount - fixedRowCount );
  const float fillColumnCount( columnCount - relativeColumnCount - fixedColumnCount );

  // walk through the data containers
  for( unsigned int row = 0; row < rowCount; ++row )
  {
    float relativeHeight = 0.0f;
    // if we have a fixed height, relative height is 0
    if( mFixedHeights[ row ] > 0.0f )
    {
      relativeHeight = 0.0f;
    }
    // else if we're given a specific row height %, use that
    else if( mRelativeHeights[ row ] > 0.0f )
    {
      relativeHeight = mRelativeHeights[ row ];
    }
    // else if there are fill rows
    else if( fillRowCount > 0 )
    {
      // this is a 'fill' row. it gets the remainder of the 100% divided evenly between 'fill' rows
      relativeHeight = (1.0f - relativeHeightsTotal ) / fillRowCount;
    }
    for( unsigned int column = 0; column < columnCount; ++column )
    {
      float relativeWidth = 0.0f;
      // if we have a fixed width, relative width is 0
      if( mFixedWidths[ column ] > 0.0f )
      {
        relativeWidth = 0.0f;
      }
      // else if we're given a specific column width %, use that
      else if( mRelativeWidths[ column ] > 0.0f )
      {
        relativeWidth = mRelativeWidths[ column ];
      }
      // else if there are fill columns
      else if( fillColumnCount > 0 )
      {
        // this is a 'fill' column. it gets the remainder of the 100% divided evenly between 'fill' columns
        relativeWidth = (1.0f - relativeWidthsTotal ) / fillColumnCount;
      }
      // store the value
      mRelativeSizes[ row ][ column ] = Size( relativeWidth, relativeHeight );
    }
  }
}

TableView::~TableView()
{
  // nothing to do
}

Actor TableView::GetNextKeyboardFocusableActor(Actor currentFocusedActor, Control::KeyboardFocusNavigationDirection direction, bool loopEnabled)
{
  Actor nextFocusableActor;

  if ( !currentFocusedActor )
  {
    // Nothing is currently focused, so the child in the first cell should be focused.
    nextFocusableActor = GetChildAt(Toolkit::TableView::CellPosition(0, 0));
  }
  else
  {
    Toolkit::TableView::CellPosition position;
    if( FindChildPosition( currentFocusedActor, position ) )
    {
      // The current focused actor is a child of TableView
      bool focusLost = false;
      int currentRow = position.rowIndex;
      int currentColumn = position.columnIndex;
      int numberOfColumns = GetColumns();
      int numberOfRows = GetRows();

      switch ( direction )
      {
        case Control::Left:
        {
          if(--currentColumn < 0)
          {
            currentColumn = numberOfColumns - 1;
            if(--currentRow < 0)
            {
              currentRow = loopEnabled ? numberOfRows - 1 : 0;
              focusLost = (currentRow == 0);
            }
          }
          break;
        }
        case Control::Right:
        {
          if(++currentColumn > numberOfColumns - 1)
          {
            currentColumn = 0;
            if(++currentRow > numberOfRows - 1)
            {
              currentRow = loopEnabled ? 0 : numberOfRows - 1;
              focusLost = (currentRow == numberOfRows - 1);
            }
          }
          break;
        }
        case Control::Up:
        {
          if(--currentRow < 0)
          {
            currentRow = loopEnabled ? numberOfRows - 1 : 0;
            focusLost = (currentRow == 0);
          }
          break;
        }
        case Control::Down:
        {
          if(++currentRow > numberOfRows - 1)
          {
            currentRow = loopEnabled ? 0 : numberOfRows - 1;
            focusLost = (currentRow == numberOfRows - 1);
          }
          break;
        }
      }

      // Move the focus if we haven't lost it.
      if(!focusLost)
      {
        nextFocusableActor = GetChildAt(Toolkit::TableView::CellPosition(currentRow, currentColumn));
      }
    }
    else
    {
      // The current focused actor is not within table view, so the child in the first cell should be focused.
      nextFocusableActor = GetChildAt(Toolkit::TableView::CellPosition(0, 0));
    }
  }

  return nextFocusableActor;
}

} // namespace Internal

} // namespace Toolkit

} // namespace Dali
