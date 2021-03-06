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
#include <dali/internal/render/gl-resources/texture.h>

// EXTERNAL INCLUDES
#include <math.h>
#include <memory.h>

// INTERNAL INCLUDES
#include <dali/integration-api/debug.h>
#include <dali/internal/render/common/vertex.h>
#include <dali/internal/render/gl-resources/context.h>

namespace Dali
{

namespace Internal
{

using Dali::Internal::Vertex2D;
using Dali::Internal::Vertex3D;

using namespace Dali::Pixel;

Texture::Texture(Context&      context,
                 unsigned int  width,
                 unsigned int  height,
                 unsigned int  imageWidth,
                 unsigned int  imageHeight,
                 Pixel::Format pixelFormat)
: mContext(context),
  mId(0),
  mWidth(width),
  mHeight(height),
  mImageWidth(imageWidth),
  mImageHeight(imageHeight),
  mPixelFormat(pixelFormat),
  mDiscarded(false)
{
  mContext.AddObserver(*this);
}

Texture::~Texture()
{
  mContext.RemoveObserver(*this);
  // GlCleanup() should already have been called by TextureCache ensuring the resource is destroyed
  // on the render thread. (And avoiding a potentially problematic virtual call in the destructor)
}

void Texture::SetTextureId(GLuint id)
{
  mId=id;
}

void Texture::Update(Integration::Bitmap* bitmap)
{
  DALI_ASSERT_DEBUG( "Updating incorrect texture type" == NULL );
}

void Texture::UpdateArea( const RectArea& area )
{
  DALI_ASSERT_DEBUG( "Updating incorrect texture type" == NULL );
}

bool Texture::UpdateOnCreate()
{
  return false;
}

bool Texture::Bind(GLenum target, GLenum textureunit )
{
  // This is the only supported type at the moment
  DALI_ASSERT_DEBUG( target == GL_TEXTURE_2D );
  bool created = false;

  if( mId == 0 )
  {
    if( CreateGlTexture() )
    {
      created = true;
    }
  }

  // Bind the texture id
  mContext.ActiveTexture(textureunit);
  mContext.Bind2dTexture(mId);

  return created;
}

void Texture::GlCleanup()
{
  // otherwise, delete the gl texture
  if (mId != 0)
  {
    mContext.DeleteTextures(1,&mId);
    mId = 0;
  }
}

void Texture::MapUV(unsigned int numVerts,Vertex2D *verts, const PixelArea* pixelArea)
{
  MapUV(numVerts, (float*)(&verts->mU), sizeof(Vertex2D)/sizeof(float), pixelArea);
}

void Texture::MapUV(unsigned int numVerts,Vertex3D *verts, const PixelArea* pixelArea)
{
  MapUV(numVerts, (float*)(&verts->mU), sizeof(Vertex3D)/sizeof(float), pixelArea);
}

void Texture::MapUV(unsigned int numVerts, float* verts, unsigned int stride, const PixelArea* pixelArea)
{
  UvRect uv;

  GetTextureCoordinates(uv, pixelArea);

  float uScale = fabsf(uv.u2 - uv.u0);
  float vScale = fabsf(uv.v2 - uv.v0);

  for (unsigned int i = 0; i < numVerts; ++i)
  {
    verts[0] = uv.u0 + verts[0] * uScale;
    verts[1] = uv.v0 + verts[1] * vScale;
    verts += stride;
  }
}

unsigned int Texture::GetWidth() const
{
  return mWidth;
}

unsigned int Texture::GetHeight() const
{
  return mHeight;
}

Pixel::Format Texture::GetPixelFormat() const
{
  return mPixelFormat;
}

/*
 * When an OpenGL context is created and made active we don't
 * do anything, because we use lazy binding.
 * This means when a texture is required that's when it's loaded
 * into OpenGL.
 */
void Texture::GlContextCreated()
{
}

/*
 * From Context::Observer, called just before the OpenGL context is destroyed.
 */
void Texture::GlContextToBeDestroyed()
{
  GlCleanup();
}

void Texture::GetTextureCoordinates(UvRect& uv, const PixelArea* pixelArea)
{
  if( pixelArea == NULL )
  {
     GetDefaultTextureCoordinates(uv);
     return;
  }

  // pre-calulate the normalized values

  const float uScale = 1.0f / float(mWidth);
  const float vScale = 1.0f / float(mHeight);
  const float x = uScale * float(pixelArea->x);
  const float y = vScale * float(pixelArea->y);
  const float width  = uScale * float(pixelArea->width);
  const float height = vScale * float(pixelArea->height);


  // bottom left
  uv.u0 = x;
  uv.v0 = y;

  // top right
  uv.u2 = x + width;
  uv.v2 = y + height;

};

void Texture::GetDefaultTextureCoordinates(UvRect& uv) const
{
  if ((mWidth == mImageWidth) && (mHeight == mImageHeight))
  {
    // set the uv's to display 0,0 to 1,1
    uv.Reset();
    return;
  }

  // the texture co-ordinates go from 0 to 1. But the image is smaller than the
  // texture, so we need to adjust the uv values.
  float uScale = float(mImageWidth)  / float(mWidth);
  float vScale = float(mImageHeight) / float(mHeight);

  // bottom left
  uv.u0 = 0.0f;
  uv.v0 = 0.0f;

  // top right
  uv.u2 = uScale;
  uv.v2 = vScale;

}

} // namespace Internal

} // namespace Dali
