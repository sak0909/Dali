#ifndef __DALI_INTERNAL_PROGRAM_H__
#define __DALI_INTERNAL_PROGRAM_H__

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

// EXTERNAL INCLUDES
#include <string>

// INTERNAL INCLUDES
#include <dali/public-api/common/vector-wrapper.h>
#include <dali/public-api/object/ref-object.h>
#include <dali/internal/render/gl-resources/context.h>
#include <dali/internal/render/gl-resources/context-observer.h>
#include <dali/integration-api/resource-cache.h>

namespace Dali
{

class Matrix;

namespace Integration
{
class GlAbstraction;
class ShaderData;
}

namespace Internal
{

class Context;

/*
 * A program contains a vertex & fragment shader.
 *
 * A program will contain vertex attributes and uniform variables
 * E.g. inside the code for our text fragment shaders we have the line:
 * \code
 * uniform lowp vec4  uColor
 * \endcode
 *
 * This describes a variable used to color text as it is drawn.
 *
 * uColor is set to the value specified by Actor::SetColor and is
 * animatable through the property Actor::COLOR
 */
class Program : public ContextObserver
{
public:

  /**
   * Size of the uniform cache per program
   * GLES specification states that minimum uniform count for fragment shader
   * is 16 and for vertex shader 128. We're caching the 16 common ones for now
   */
  static const int MAX_UNIFORM_CACHE_SIZE = 16;

  /**
   * Constant for uniform / attribute not found
   */
  static const int NOT_FOUND = -1;

  /**
   * Vertex attributes
   */
  enum AttribType
  {
    ATTRIB_UNKNOWN = -1,
    ATTRIB_POSITION,
    ATTRIB_NORMAL,
    ATTRIB_TEXCOORD,
    ATTRIB_COLOR,
    ATTRIB_BONE_WEIGHTS,
    ATTRIB_BONE_INDICES,
    ATTRIB_TYPE_LAST
  };

  /**
   * Common shader uniform names
   */
  enum UniformType
  {
    UNIFORM_NOT_QUERIED = -2,
    UNIFORM_UNKNOWN = -1,
    UNIFORM_MVP_MATRIX,
    UNIFORM_MODELVIEW_MATRIX,
    UNIFORM_PROJECTION_MATRIX,
    UNIFORM_MODEL_MATRIX,
    UNIFORM_VIEW_MATRIX,
    UNIFORM_NORMAL_MATRIX,
    UNIFORM_COLOR,
    UNIFORM_CUSTOM_TEXTURE_COORDS,
    UNIFORM_SAMPLER,
    UNIFORM_SAMPLER_RECT,
    UNIFORM_EFFECT_SAMPLER,
    UNIFORM_EFFECT_SAMPLER_RECT,
    UNIFORM_TIME_DELTA,
    UNIFORM_SAMPLER_OPACITY,
    UNIFORM_SAMPLER_NORMAL_MAP,

    UNIFORM_TEXT_COLOR,
    UNIFORM_SMOOTHING,
    UNIFORM_OUTLINE,
    UNIFORM_OUTLINE_COLOR,
    UNIFORM_GLOW,
    UNIFORM_GLOW_COLOR,
    UNIFORM_SHADOW,
    UNIFORM_SHADOW_COLOR,
    UNIFORM_SHADOW_SMOOTHING,
    UNIFORM_GRADIENT_COLOR,
    UNIFORM_GRADIENT_LINE,
    UNIFORM_INVERSE_TEXT_SIZE,

    UNIFORM_TYPE_LAST
  };

  /**
   * Creates a new program, or returns a copy of an existing program in the program cache
   * maintained by Context
   * @param [in] resourceId ResourceManager resourceId for the shader source and binary.
   *                        Used as a lookup key in the program cache
   * @param[in] shaderData  A pointer to a data structure containing the program source
   *                        and optionally precompiled binary. If the binary is empty the program bytecode
   *                        is copied into it after compilation and linking)
   * @param [in] context    GL context
   * @return pointer to the program
   */
  static Program* New( const Integration::ResourceId& resourceId, Integration::ShaderData* shaderData, Context& context );

  /**
   * Takes this program into use
   */
  void Use();

  /**
   * @return true if this program is used currently
   */
  bool IsUsed();

  /**
   * @param [in] type of the attribute
   * @return the index of the attribute
   */
  GLint GetAttribLocation( AttribType type );

  /**
   * Register a uniform name in our local cache
   * @param [in] name uniform name
   * @return the index of the uniform name in local cache
   */
  unsigned int RegisterUniform( const std::string& name );

  /**
   * Gets the location of a pre-registered uniform.
   * Uniforms in list UniformType are always registered and in the order of the enumeration
   * @param [in] uniformIndex of the uniform in local cache
   * @return the index of the uniform in the GL program
   */
  GLint GetUniformLocation( unsigned int uniformIndex );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as int
   */
  void SetUniform1i( GLint location, GLint value0 );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as int
   * @param [in] value1 as int
   * @param [in] value2 as int
   * @param [in] value3 as int
   */
  void SetUniform4i( GLint location, GLint value0, GLint value1, GLint value2, GLint value3 );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as float
   */
  void SetUniform1f( GLint location, GLfloat value0 );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as float
   * @param [in] value1 as float
   */
  void SetUniform2f( GLint location, GLfloat value0, GLfloat value1 );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as float
   * @param [in] value1 as float
   * @param [in] value2 as float
   */
  void SetUniform3f( GLint location, GLfloat value0, GLfloat value1, GLfloat value2 );

  /**
   * Sets the uniform value
   * @param [in] location of uniform
   * @param [in] value0 as float
   * @param [in] value1 as float
   * @param [in] value2 as float
   * @param [in] value3 as float
   */
  void SetUniform4f( GLint location, GLfloat value0, GLfloat value1, GLfloat value2, GLfloat value3 );

  /**
   * Sets the uniform value as matrix. NOTE! we never want GPU to transpose
   * so make sure your matrix is in correct order for GL.
   * @param [in] location Location of uniform
   * @param [in] count Count of matrices
   * @param [in] value values as float pointers
   */
  void SetUniformMatrix4fv( GLint location, GLsizei count, const GLfloat* value );

  /**
   * Sets the uniform value as matrix. NOTE! we never want GPU to transpose
   * so make sure your matrix is in correct order for GL.
   * @param [in] location Location of uniform
   * @param [in] count Count of matrices
   * @param [in] value values as float pointers
   */
  void SetUniformMatrix3fv( GLint location, GLsizei count, const GLfloat* value );

public: // From ContextObserver

  /**
   * @copydoc ContextObserver::GlContextCreated
   */
  virtual void GlContextCreated();          // From ContextObserver

  /**
   * @copydoc ContextObserver::GlContextToBeDestroyed
   */
  virtual void GlContextToBeDestroyed();   // From ContextObserver

private: // Implementation

  /**
   * Constructor, private so no direct instantiation
   * @param[in] shaderData A pointer to a data structure containing the program source and binary
   * @param[in] context    The GL context state cache.
   */
  Program( Integration::ShaderData* shaderData, Context& context );

public:

  /**
   * Destructor
   */
  virtual ~Program();

private:

  // default constructor, not defined
  Program();
  // assignment operator, not defined
  Program& operator=( const Program& );

  /**
   * Load the shader, from a precompiled binary if available, else from source code
   */
  void Load();

  /**
   * Unload the shader
   */
  void Unload();

  /**
   * Compile the shader
   * @param shaderType vertex or fragment shader
   * @param shaderId of the shader, returned
   * @param src of the shader
   * @return true if the compilation succeeded
   */
  bool CompileShader(GLenum shaderType, GLuint& shaderId, const char* src);

  /**
   * Links the shaders together to create program
   */
  void Link();

  /**
   * Frees the shader programs
   */
  void FreeShaders();

  /**
   * Resets caches
   */
  void ResetAttribsUniforms();

private:  // Data

  Context& mContext;                          ///< The GL context state cache
  Integration::GlAbstraction& mGlAbstraction; ///< The OpenGL Abstraction layer
  bool mLinked;                               ///< whether the program is linked
  GLuint mVertexShaderId;                     ///< GL identifier for vertex shader
  GLuint mFragmentShaderId;                   ///< GL identifier for fragment shader
  GLuint mProgramId;                          ///< GL identifier for program
  Integration::ShaderData* mProgramData;      ///< Shader program source and binary (when compiled & linked or loaded)

  // location caches
  GLint mAttribLocations[ ATTRIB_TYPE_LAST ]; ///< attribute location cache
  std::vector< std::pair< std::string, GLint > > mUniformLocations; ///< uniform location cache

  // uniform value caching
  GLint mUniformCacheInt[ MAX_UNIFORM_CACHE_SIZE ];         ///< Value cache for uniforms of single int
  GLfloat mUniformCacheFloat[ MAX_UNIFORM_CACHE_SIZE ];     ///< Value cache for uniforms of single float
  GLfloat mUniformCacheFloat4[ MAX_UNIFORM_CACHE_SIZE ][4]; ///< Value cache for uniforms of four float

};

} // namespace Internal

} // namespace Dali

#endif // __DALI_INTERNAL_PROGRAM_H__
