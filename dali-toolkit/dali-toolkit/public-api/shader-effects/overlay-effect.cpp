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
#include <dali-toolkit/public-api/shader-effects/overlay-effect.h>

namespace Dali
{

namespace Toolkit
{

OverlayEffect::OverlayEffect()
{
}

OverlayEffect::~OverlayEffect()
{
}

OverlayEffect OverlayEffect::New( Image overlayImage )
{
  // (Target > 0.5) * (1 - (1-2*(Target-0.5)) * (1-Blend)) + (Target <= 0.5) * ((2*Target) * Blend)
  const char* OVERLAY_FRAGMENT_SHADER_SOURCE =
  "void main()\n"
  "{\n"
  "  lowp vec4 target = texture2D(sTexture, vTexCoord);\n"
  "  lowp vec4 overlay = texture2D(sEffect, vTexCoord);\n"
  "  if ( length( target.rgb ) > 0.5 )\n"
  "  {\n"
  "    gl_FragColor = vec4( mix( target.rgb, 1.0 - ( 1.0 - 2.0 * ( target.rgb - 0.5 ) )  * ( 1.0 - overlay.rgb ), overlay.a ), min( 1.0, target.a + overlay.a ) );\n"
  "  }\n"
  "  else\n"
  "  {\n"
  "    gl_FragColor = vec4( mix( target.rgb, 2.0 * target.rgb * overlay.rgb, overlay.a ), target.a + overlay.a );\n"
  "  }\n"
  "}\n";

  ShaderEffect shader = ShaderEffect::New( "", // Use default
                                           OVERLAY_FRAGMENT_SHADER_SOURCE,
                                           GeometryType( GEOMETRY_TYPE_IMAGE ),
                                           ShaderEffect::GeometryHints( ShaderEffect::HINT_BLENDING ) );

  shader.SetEffectImage( overlayImage );

  return OverlayEffect( shader );
}

//Call the Parent copy constructor to add reference to the implementation for this object
OverlayEffect::OverlayEffect( ShaderEffect handle )
: ShaderEffect( handle )
{
}

} // namespace Toolkit

} // namespace Dali
