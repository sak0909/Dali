#ifndef __DALI_INTERNAL_SCENE_GRAPH_TEXT_ATTACHMENT_H__
#define __DALI_INTERNAL_SCENE_GRAPH_TEXT_ATTACHMENT_H__

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
#include <dali/internal/common/event-to-update.h>
#include <dali/internal/common/owner-pointer.h>
#include <dali/internal/update/resources/resource-manager.h>
#include <dali/internal/update/node-attachments/scene-graph-renderable-attachment.h>

namespace Dali
{

namespace Internal
{

class TextParameters;

namespace SceneGraph
{

class TextRenderer;
class Shader;
class RenderQueue;

/**
 * An attachment for rendering text from a font atlas.
 */
class TextAttachment : public RenderableAttachment
{
public:

  /**
   * Construct a new TextAttachment.
   * @return a new TextAttachment
   */
  static TextAttachment* New();

  /**
   * Virtual destructor
   */
  virtual ~TextAttachment();

  /**
   * @copydoc RenderableAttachment::GetRenderer().
   */
  virtual Renderer& GetRenderer();

  /**
   * @copydoc RenderableAttachment::GetRenderer().
   */
  virtual const Renderer& GetRenderer() const;

  /**
   * Set the text vertex buffer; ownership is passed to the renderer.
   * This is to avoid duplicate data being held in the text-attachment and the scene-graph-text-attachment.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] vertexBuffer vertex buffer
   */
  void SetTextVertexBuffer( BufferIndex updateBufferIndex, TextVertexBuffer* vertexBuffer );

  /**
   * Set the color associated with the gradient end point.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] color The gradient color (end-point color)
   */
  void SetGradientColor( BufferIndex updateBufferIndex, const Vector4& color );

  /**
   * Set the gradient start point.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] position The relative position of the gradient start point.
   */
  void SetGradientStartPoint( BufferIndex updateBufferIndex, const Vector2& position );

  /**
   * Set the gradient end point.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] position The relative position of the gradient end point.
   */
  void SetGradientEndPoint( BufferIndex updateBufferIndex, const Vector2& position );

  /**
   * Set the text color.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] color The text color.
   */
  void SetTextColor( BufferIndex updateBufferIndex, const Vector4& color );

  /**
   * Set text outlining.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] enable Set to true to enable text outlining.
   * @param[in] color Outline color.
   * @param[in] thickness Thickness of outline.
   */
  void SetOutline( BufferIndex updateBufferIndex, bool enable, const Vector4& color, const Vector2& thickness );

  /**
   * Set text glow.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] enable Set to true to enable text outer glow.
   * @param[in] color Glow color.
   * @param[in] intensity Determines the amount of glow around text.
   */
  void SetGlow( BufferIndex updateBufferIndex, bool enable, const Vector4& color, float intensity );

  /**
   * Set text shadow.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] enable  Set to true to enable text drop shadow.
   * @param[in] color   Shadow color.
   * @param[in] offset  Offset in pixels. To avoid cropping of the drop shadow limit the offset to PointSize / 3.5.
   * @param[in] size    Size of shadow in pixels. 0 means the shadow is the same size as the text.
   */
  void SetDropShadow( BufferIndex updateBufferIndex, bool enable, const Vector4& color, const Vector2& offset, const float size );

  /**
   * Set soft edge smoothing.
   * @param[in] updateBufferIndex The current update buffer index.
   * @param[in] smoothEdge Specify the distance field value for the center of the text edge.
   */
  void SetSmoothEdge( BufferIndex updateBufferIndex, float smoothEdge );

  /**
   * @copydoc RenderableAttachment::ShaderChanged()
   */
  virtual void ShaderChanged( BufferIndex updateBufferIndex );

  /**
   * @copydoc RenderableAttachment::SizeChanged()
   */
  virtual void SizeChanged( BufferIndex updateBufferIndex );

  /**
   * @copydoc RenderableAttachment::DoPrepareRender()
   */
  virtual void DoPrepareRender( BufferIndex updateBufferIndex );

  /**
   * @copydoc RenderableAttachment::IsFullyOpaque()
   */
  virtual bool IsFullyOpaque( BufferIndex updateBufferIndex )
  {
    return false; // false since drawing text requires alpha
  }

  /**
   * @copydoc RenderableAttachment::GetScaleForSize()
   */
  virtual void DoGetScaleForSize( const Vector3& nodeSize, Vector3& scaling );

protected:

  /**
   * Protected constructor. See New()
   */
  TextAttachment();

private:

  /**
   * @copydoc RenderableAttachment::ConnectToSceneGraph2().
   */
  virtual void ConnectToSceneGraph2( BufferIndex updateBufferIndex );

  /**
   * @copydoc RenderableAttachment::OnDestroy2().
   */
  virtual void OnDestroy2();

  /**
   * @copydoc RenderableAttachment::DoPrepareResources()
   */
  virtual bool DoPrepareResources( BufferIndex updateBufferIndex, ResourceManager& resourceManager );

  // Undefined
  TextAttachment(const TextAttachment&);

  // Undefined
  TextAttachment& operator=(const TextAttachment& rhs);

private:

  TextRenderer* mTextRenderer;    ///< Raw-pointers to renderer that is owned by RenderManager
  Vector2 mGeometrySize;          ///< used for geometry scaling
  Vector2 mGeometryScaling;       ///< used for geometry scaling

  unsigned int mAtlasId;          ///< atlas Id from last vertex buffer

};

inline void SetTextVertexBufferMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, TextVertexBuffer& buffer)
{
  typedef MessageDoubleBuffered1< TextAttachment, OwnerPointer< TextVertexBuffer> > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetTextVertexBuffer, &buffer );
}

inline void SetGradientColorMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, const Vector4& color )
{
  typedef MessageDoubleBuffered1< TextAttachment, Vector4 > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetGradientColor, color );
}

inline void SetGradientStartPointMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, const Vector2& position )
{
  typedef MessageDoubleBuffered1< TextAttachment, Vector2 > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetGradientStartPoint, position );
}

inline void SetGradientEndPointMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, const Vector2& position )
{
  typedef MessageDoubleBuffered1< TextAttachment, Vector2 > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetGradientEndPoint, position );
}

inline void SetTextColorMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, const Vector4& color )
{
  typedef MessageDoubleBuffered1< TextAttachment, Vector4 > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetTextColor, color );
}

inline void SetOutlineMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, bool enable, const Vector4& color, const Vector2& params )
{
  typedef MessageDoubleBuffered3< TextAttachment, bool, Vector4, Vector2 > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetOutline, enable, color, params );
}

inline void SetGlowMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, bool enable, const Vector4& color, float params )
{
  typedef MessageDoubleBuffered3< TextAttachment, bool, Vector4, float > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetGlow, enable, color, params );
}

inline void SetDropShadowMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, bool enable, const Vector4& color, const Vector2& offset, const float size )
{
  typedef MessageDoubleBuffered4< TextAttachment, bool, Vector4, Vector2, float > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetDropShadow, enable, color, offset, size );
}

inline void SetSmoothEdgeMessage( EventToUpdate& eventToUpdate, const TextAttachment& attachment, float params )
{
  typedef MessageDoubleBuffered1< TextAttachment, float > LocalType;

  // Reserve some memory inside the message queue
  unsigned int* slot = eventToUpdate.ReserveMessageSlot( sizeof( LocalType ) );

  // Construct message in the message queue memory; note that delete should not be called on the return value
  new (slot) LocalType( &attachment, &TextAttachment::SetSmoothEdge, params );
}

} // namespace SceneGraph

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_SCENE_GRAPH_TEXT_ATTACHMENT_H__
