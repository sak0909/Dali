#ifndef __DALI_INTERNAL_ACTOR_ATTACHMENT_DECLARATIONS_H__
#define __DALI_INTERNAL_ACTOR_ATTACHMENT_DECLARATIONS_H__

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
#include <dali/public-api/object/ref-object.h>

namespace Dali
{

namespace Internal
{

class ActorAttachment;
class CameraAttachment;
class ImageAttachment;
class LightAttachment;
class TextAttachment;
class MeshAttachment;

typedef IntrusivePtr<ActorAttachment>  ActorAttachmentPtr;
typedef IntrusivePtr<CameraAttachment> CameraAttachmentPtr;
typedef IntrusivePtr<ImageAttachment>  ImageAttachmentPtr;
typedef IntrusivePtr<LightAttachment>  LightAttachmentPtr;
typedef IntrusivePtr<MeshAttachment>   MeshAttachmentPtr;
typedef IntrusivePtr<TextAttachment>   TextAttachmentPtr;

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_ACTOR_ATTACHMENT_DECLARATIONS_H__
