#ifndef __DALI_PROPERTY_INPUT_ACCESSOR_H__
#define __DALI_PROPERTY_INPUT_ACCESSOR_H__

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

// INTERNAL INCLUDES
#include <dali/public-api/object/property-types.h>
#include <dali/internal/event/common/property-input-impl.h>

namespace Dali
{

namespace Internal
{

class PropertyInputAccessor
{
public:

  /**
   * Create the PropertyInputAccessor.
   */
  PropertyInputAccessor()
  : mInput( NULL )
  {
  }

  /**
   * Create the PropertyInputAccessor.
   */
  PropertyInputAccessor( const PropertyInputImpl* input, int /*componentIndex*/ )
  : mInput( input )
  {
  }

  /**
   * Copy from a PropertyInputAccessor
   */
  PropertyInputAccessor( const PropertyInputAccessor& accessor )
  : mInput( accessor.mInput )
  {
  }

  /**
   * Set the property input.
   */
  void SetInput( const PropertyInputImpl& input, int componentIndex )
  {
    DALI_ASSERT_DEBUG( componentIndex < 0 && "Did not expect a valid component index" );
    mInput = &input;
  }

  /**
   * Retrieve the property input.
   */
  const PropertyInputImpl* GetInput() const
  {
    return mInput;
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetType()
   */
  Property::Type GetType() const
  {
    return mInput->GetType();
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputBoolean()
   */
  const bool& GetConstraintInputBoolean( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputBoolean( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputFloat()
   */
  const float& GetConstraintInputFloat( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputFloat( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector2()
   */
  const Vector2& GetConstraintInputVector2( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputVector2( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector3()
   */
  const Vector3& GetConstraintInputVector3( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputVector3( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector4()
   */
  const Vector4& GetConstraintInputVector4( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputVector4( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputQuaternion()
   */
  const Quaternion& GetConstraintInputQuaternion( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputQuaternion( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputMatrix3()
   */
  const Matrix3& GetConstraintInputMatrix3( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputMatrix3( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputMatrix()
   */
  const Matrix& GetConstraintInputMatrix( BufferIndex updateBufferIndex ) const
  {
    return mInput->GetConstraintInputMatrix( updateBufferIndex );
  }

public:

  const PropertyInputImpl* mInput;
};

class PropertyInputComponentAccessor
{
public:

  /**
   * Create the PropertyInputComponentAccessor.
   */
  PropertyInputComponentAccessor()
  : mInput( NULL ),
    mComponentIndex( 0 )
  {
  }

  /**
   * Create the PropertyInputComponentAccessor.
   */
  PropertyInputComponentAccessor( const PropertyInputImpl* input, int componentIndex )
  : mInput( input ),
    mComponentIndex( componentIndex )
  {
  }

  /**
   * Copy from a PropertyInputAccessor
   */
  PropertyInputComponentAccessor( const PropertyInputAccessor& accessor )
  : mInput( accessor.mInput ),
    mComponentIndex( -1 )
  {
  }

  /**
   * Copy from a PropertyInputComponentAccessor
   */
  PropertyInputComponentAccessor( const PropertyInputComponentAccessor& accessor )
  : mInput( accessor.mInput ),
    mComponentIndex( accessor.mComponentIndex )
  {
  }

  /**
   * Set the property input.
   */
  void SetInput( const PropertyInputImpl& input, int componentIndex )
  {
    mInput = &input;
    mComponentIndex = componentIndex;
  }

  /**
   * Retrieve the property input.
   */
  const PropertyInputImpl* GetInput() const
  {
    return mInput;
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetType()
   */
  Property::Type GetType() const
  {
    return mInput->GetType();
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputBoolean()
   */
  const bool& GetConstraintInputBoolean( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputBoolean( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputFloat()
   */
  const float& GetConstraintInputFloat( BufferIndex updateBufferIndex ) const
  {
    // Invalid index is ok
    if ( mComponentIndex < 0 )
    {
      // Not a Vector3 or Vector4 component, expecting float type
      return mInput->GetConstraintInputFloat( updateBufferIndex );
    }
    else if ( PropertyTypes::Get< Vector3 >() == mInput->GetType() )
    {
      if ( 0 == mComponentIndex )
      {
        return mInput->GetConstraintInputVector3( updateBufferIndex ).x;
      }
      else if ( 1 == mComponentIndex )
      {
        return mInput->GetConstraintInputVector3( updateBufferIndex ).y;
      }

      DALI_ASSERT_DEBUG( 2 == mComponentIndex && "Invalid Vector3 component index" );
      return mInput->GetConstraintInputVector3( updateBufferIndex ).z;
    }

    // Expecting Vector4
    if ( 0 == mComponentIndex )
    {
      return mInput->GetConstraintInputVector4( updateBufferIndex ).x;
    }
    else if ( 1 == mComponentIndex )
    {
      return mInput->GetConstraintInputVector4( updateBufferIndex ).y;
    }
    else if ( 2 == mComponentIndex )
    {
      return mInput->GetConstraintInputVector4( updateBufferIndex ).y;
    }

    DALI_ASSERT_DEBUG( 3 == mComponentIndex && "Invalid Vector4 component index" );
    return mInput->GetConstraintInputVector4( updateBufferIndex ).w;
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector2()
   */
  const Vector2& GetConstraintInputVector2( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputVector2( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector3()
   */
  const Vector3& GetConstraintInputVector3( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputVector3( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputVector4()
   */
  const Vector4& GetConstraintInputVector4( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputVector4( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputQuaternion()
   */
  const Quaternion& GetConstraintInputQuaternion( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputQuaternion( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputMatrix3()
   */
  const Matrix3& GetConstraintInputMatrix3( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputMatrix3( updateBufferIndex );
  }

  /**
   * @copydoc Dali::Internal::PropertyInputImpl::GetConstraintInputMatrix()
   */
  const Matrix& GetConstraintInputMatrix( BufferIndex updateBufferIndex ) const
  {
    DALI_ASSERT_DEBUG( mComponentIndex < 0 && "Did not expect valid component index" );

    return mInput->GetConstraintInputMatrix( updateBufferIndex );
  }

public:

  const PropertyInputImpl* mInput;
  int mComponentIndex;
};

} // namespace Internal

} // namespace Dali

#endif // __DALI_PROPERTY_INPUT_ACCESSOR_H__
