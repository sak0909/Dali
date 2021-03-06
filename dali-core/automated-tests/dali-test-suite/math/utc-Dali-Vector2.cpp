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

#include <iostream>
#include <sstream>

#include <stdlib.h>
#include <tet_api.h>

#include <dali/public-api/dali-core.h>

#include <dali-test-suite-utils.h>

using namespace Dali;

static void Startup();
static void Cleanup();

extern "C" {
  void (*tet_startup)() = Startup;
  void (*tet_cleanup)() = Cleanup;
}

static void UtcDaliVector2Cons();

static void UtcDaliVector2FitInside();
static void UtcDaliVector2FitScaleToFill();
static void UtcDaliVector2ShrinkInside();

static void UtcDaliVector2Add();
static void UtcDaliVector2Subtract();
static void UtcDaliVector2Negate();
static void UtcDaliVector2Multiply();
static void UtcDaliVector2Divide();
static void UtcDaliVector2Scale();
static void UtcDaliVector2Equals();
static void UtcDaliVector2Length();
static void UtcDaliVector2LengthSquared();
static void UtcDaliVector2Max();
static void UtcDaliVector2Min();
static void UtcDaliVector2Clamp();
static void UtcDaliVector2ClampVector2();
static void UtcDaliVector2Normalize();

static void UtcDaliVector2OperatorSubscript();

static void UtcDaliVector2OStreamOperator();

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

// Add test functionality for all APIs in the class (Positive and Negative)
extern "C" {
  struct tet_testlist tet_testlist[] = {
    { UtcDaliVector2Cons, POSITIVE_TC_IDX },

    { UtcDaliVector2FitInside, POSITIVE_TC_IDX },
    { UtcDaliVector2FitScaleToFill, POSITIVE_TC_IDX },
    { UtcDaliVector2ShrinkInside, POSITIVE_TC_IDX },

    { UtcDaliVector2Add,               POSITIVE_TC_IDX },
    { UtcDaliVector2Subtract,          POSITIVE_TC_IDX },
    { UtcDaliVector2Negate,            POSITIVE_TC_IDX },
    { UtcDaliVector2Multiply,          POSITIVE_TC_IDX },
    { UtcDaliVector2Divide,            POSITIVE_TC_IDX },
    { UtcDaliVector2Scale,             POSITIVE_TC_IDX },
    { UtcDaliVector2Equals,            POSITIVE_TC_IDX },
    { UtcDaliVector2Length,            POSITIVE_TC_IDX },
    { UtcDaliVector2LengthSquared,     POSITIVE_TC_IDX },
    { UtcDaliVector2Max,               POSITIVE_TC_IDX },
    { UtcDaliVector2Min,               POSITIVE_TC_IDX },
    { UtcDaliVector2Clamp,             POSITIVE_TC_IDX },
    { UtcDaliVector2ClampVector2,      POSITIVE_TC_IDX },
    { UtcDaliVector2Normalize,         POSITIVE_TC_IDX },

    { UtcDaliVector2OperatorSubscript, POSITIVE_TC_IDX },

    { UtcDaliVector2OStreamOperator,   POSITIVE_TC_IDX },

    { NULL, 0 }
  };
}

// Called only once before first test is run.
static void Startup()
{
}

// Called only once after last test is run
static void Cleanup()
{
}


static void UtcDaliVector2Cons()
{
  Vector3 v3(1.0f, 2.0f, 3.0f);
  Vector2 va;
  Vector2 vb(v3);
  Vector2 vc(11.0f, 123.0f);

  DALI_TEST_EQUALS(va.x, 0.0f, 0.001f, TEST_LOCATION);
  DALI_TEST_EQUALS(va.y, 0.0f, 0.001f, TEST_LOCATION);

  DALI_TEST_EQUALS(vb.width, 1.0f, 0.001f, TEST_LOCATION);
  DALI_TEST_EQUALS(vb.height, 2.0f, 0.001f, TEST_LOCATION);

  DALI_TEST_EQUALS(vc.width,  11.0f, 0.001f, TEST_LOCATION);
  DALI_TEST_EQUALS(vc.y,     123.0f, 0.001f, TEST_LOCATION);

  Vector4 vec4(5.0f,6.0f,7.0f,8.0f);
  Vector2 vec2;
  vec2 = vec4;
  DALI_TEST_EQUALS(vec2.x, 5.0f, 0.001, TEST_LOCATION);
  DALI_TEST_EQUALS(vec2.y, 6.0f, 0.001, TEST_LOCATION);

  Vector3 vec3(5.0f,6.0f,7.0f);
  vec2 = vec3;
  DALI_TEST_EQUALS(vec2.x, 5.0f, 0.001, TEST_LOCATION);
  DALI_TEST_EQUALS(vec2.y, 6.0f, 0.001, TEST_LOCATION);

  Vector2 vec2b(vec4);
  DALI_TEST_EQUALS(vec2.x, 5.0f, 0.001, TEST_LOCATION);
  DALI_TEST_EQUALS(vec2.y, 6.0f, 0.001, TEST_LOCATION);
}


static void UtcDaliVector2FitInside()
{
  DALI_TEST_EQUALS( Vector2(  1.0f,  2.0f ), FitInside( Vector2(   1.0f,  2.0f ), Vector2( 10.0f, 20.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  1.0f,  0.5f ), FitInside( Vector2(   1.0f,  2.0f ), Vector2( 20.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f, 20.0f ), FitInside( Vector2(  10.0f, 20.0f ), Vector2(  1.0f,  2.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f, 10.0f ), FitInside( Vector2( 100.0f, 10.0f ), Vector2( 10.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 20.0f, 10.0f ), FitInside( Vector2(  20.0f, 20.0f ), Vector2( 10.0f,  5.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f, 20.0f ), FitInside( Vector2(  20.0f, 20.0f ), Vector2(  5.0f, 10.0f ) ), TEST_LOCATION );
}

static void UtcDaliVector2FitScaleToFill()
{
  DALI_TEST_EQUALS( Vector2(  1.0f,  2.0f ), FitScaleToFill( Vector2(   1.0f,  2.0f ), Vector2( 10.0f, 20.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  1.0f,  2.0f ), FitScaleToFill( Vector2(  10.0f, 20.0f ), Vector2(  1.0f,  2.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f,  1.0f ), FitScaleToFill( Vector2( 100.0f, 10.0f ), Vector2( 10.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  5.0f,  5.0f ), FitScaleToFill( Vector2(  20.0f, 20.0f ), Vector2( 10.0f,  5.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  5.0f,  5.0f ), FitScaleToFill( Vector2(  20.0f, 20.0f ), Vector2(  5.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 20.0f, 40.0f ), FitScaleToFill( Vector2(  20.0f,  0.0f ), Vector2(  5.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f, 20.0f ), FitScaleToFill( Vector2(   0.0f, 20.0f ), Vector2(  5.0f, 10.0f ) ), TEST_LOCATION );
}

static void UtcDaliVector2ShrinkInside()
{
  DALI_TEST_EQUALS( Vector2(  1.0f,  2.0f ), ShrinkInside( Vector2(   1.0f,  2.0f ), Vector2( 10.0f, 20.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  1.0f,  2.0f ), ShrinkInside( Vector2(  10.0f, 20.0f ), Vector2(  1.0f,  2.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f, 10.0f ), ShrinkInside( Vector2( 100.0f, 10.0f ), Vector2( 10.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f,  5.0f ), ShrinkInside( Vector2(  20.0f, 20.0f ), Vector2( 10.0f,  5.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  5.0f, 10.0f ), ShrinkInside( Vector2(  20.0f, 20.0f ), Vector2(  5.0f, 10.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2(  5.0f, 10.0f ), ShrinkInside( Vector2(  10.0f, 10.0f ), Vector2( 10.0f, 20.0f ) ), TEST_LOCATION );
  DALI_TEST_EQUALS( Vector2( 10.0f,  5.0f ), ShrinkInside( Vector2(  10.0f, 10.0f ), Vector2( 20.0f, 10.0f ) ), TEST_LOCATION );
}




static void UtcDaliVector2Add()
{
  Vector2 v0(1.0f, 2.0f);
  Vector2 v1(10.0f, 20.0f);
  Vector2 r0(11.0f, 22.0f);

  Vector2 v2 = v0+v1;
  DALI_TEST_EQUALS(v2, r0, TEST_LOCATION);

  v0 += v1;
  DALI_TEST_EQUALS(v0, r0, TEST_LOCATION);
}


// Subtract
static void UtcDaliVector2Subtract()
{
  Vector2 v0(11.0f, 22.0f);
  Vector2 v1(10.0f, 20.0f);
  Vector2 r0(1.0f, 2.0f);

  Vector2 v2 = v0-v1;
  DALI_TEST_EQUALS(v2, r0, TEST_LOCATION);

  v0 -= v1;
  DALI_TEST_EQUALS(v0, r0, TEST_LOCATION);
}


static void UtcDaliVector2Negate()
{
  Vector2 v1(10.0f, 20.0f);
  Vector2 r0(-10.0f, -20.0f);

  Vector2 v2 = -v1;
  DALI_TEST_EQUALS(v2, r0, TEST_LOCATION);
}


// Multiply
static void UtcDaliVector2Multiply()
{
  Vector2 v0(2.0f, 3.0f);
  Vector2 v1(10.0f, 20.0f);
  Vector2 r0(20.0f, 60.0f);

  Vector2 v2 = v0 * v1;
  DALI_TEST_EQUALS(v2, r0, TEST_LOCATION);

  v0 *= v1;
  DALI_TEST_EQUALS(v0, r0, TEST_LOCATION);
}

// Divide
static void UtcDaliVector2Divide()
{
  Vector2 v0(1.0f, 1.0f);
  Vector2 v1(2.0f, 3.0f);
  Vector2 v2(4.0f, 9.0f);

  DALI_TEST_EQUALS( v0/v0, v0, TEST_LOCATION);
  DALI_TEST_EQUALS( v1/v0, v1, TEST_LOCATION);
  DALI_TEST_EQUALS( v1/v1, v0, TEST_LOCATION);
  DALI_TEST_EQUALS( v2/v1, v1, TEST_LOCATION);

  Vector2 v4(v0);
  v4 /= v0;
  DALI_TEST_EQUALS(v4, v0, TEST_LOCATION);

  Vector2 v5(v1);
  v5 /= v0;
  DALI_TEST_EQUALS(v5, v1, TEST_LOCATION);

  Vector2 v6(v1);
  v6 /= v6;
  DALI_TEST_EQUALS(v6, v0, TEST_LOCATION);

  v2 /= v1;
  DALI_TEST_EQUALS(v2, v1, TEST_LOCATION);

}

static void UtcDaliVector2Scale()
{
  Vector2 v0(2.0f, 4.0f);
  const Vector2 r0(20.0f, 40.0f);
  const Vector2 r1(10.0f, 20.0f);
  const Vector2 r2( 1.0f,  2.0f);
  const Vector2 r3(2.0f, 4.0f);

  Vector2 v2 = v0 * 10.0f;
  DALI_TEST_EQUALS(v2, r0, TEST_LOCATION);

  v0 *= 5.0f;
  DALI_TEST_EQUALS(v0, r1, TEST_LOCATION);

  v2 = r0 / 10.0f;
  DALI_TEST_EQUALS(v2, r3, TEST_LOCATION);

  v2 = r1;
  v2 /= 10.0f;
  DALI_TEST_EQUALS(v2, r2, TEST_LOCATION);
}

// Equals
static void UtcDaliVector2Equals()
{
  Vector2 v0(1.0f, 2.0f);
  Vector2 v1(1.0f, 2.0f);

  DALI_TEST_CHECK(v0 == v1);

  Vector2 v2 = Vector2(0.0f, 2.0f);
  DALI_TEST_CHECK(v0 != v2);

  v2 = Vector2(1.0f, 0.0f);
  DALI_TEST_CHECK(v0 != v2);

  v2 = Vector2(1.0f, 77.0f);
  DALI_TEST_CHECK(v0 != v2);

  v2 = Vector2(33.0f, 44.0f);
  DALI_TEST_CHECK(v0 != v2);
}

// Length
static void UtcDaliVector2Length()
{
  Vector2 v(1.0f, 2.0f);
  DALI_TEST_EQUALS(v.Length(), sqrtf(v.x*v.x + v.y*v.y), 0.001f, TEST_LOCATION);

  Vector2 v1(0.0f, 0.0f);
  DALI_TEST_EQUALS(v1.Length(), 0.0f, TEST_LOCATION);
}

// Length squared
static void UtcDaliVector2LengthSquared()
{
  Vector2 v(1.0f, 2.0f);
  DALI_TEST_EQUALS(v.LengthSquared(), v.x*v.x + v.y*v.y, 0.001f, TEST_LOCATION);

  Vector2 v1(0.0f, 0.0f);
  DALI_TEST_EQUALS(v1.LengthSquared(), 0.0f, TEST_LOCATION);
}

// Max
static void UtcDaliVector2Max()
{
  Vector2 v0(2.0f, 1.0f);
  Vector2 v1(1.0f, 2.0f);

  DALI_TEST_EQUALS(Max(v0, v1), Vector2(2.0f, 2.0f), 0.01f, TEST_LOCATION);
}

// Min
static void UtcDaliVector2Min()
{
  Vector2 v0(2.0f, 1.0f);
  Vector2 v1(1.0f, 2.0f);

  DALI_TEST_EQUALS(Min(v0, v1), Vector2(1.0f, 1.0f), 0.01f, TEST_LOCATION);
}

static void UtcDaliVector2Clamp()
{
  tet_infoline("Testing Dali::Vector2::Clamp( const Vector2& v, const float& min, const float& max )");

  Vector2 v0(2.0f, 0.8f);
  Vector2 v1(-1.0f, 2.0f);

  DALI_TEST_EQUALS( Clamp( v0, 0.9f, 1.1f ), Vector2(1.1f, 0.9f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( Clamp( v1, 1.0f, 1.0f ), Vector2(1.0f, 1.0f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( Clamp( v1, 0.0f, 3.0f ), Vector2(0.0f, 2.0f), 0.01f, TEST_LOCATION );
}

static void UtcDaliVector2ClampVector2()
{
  tet_infoline("Testing Dali::Vector2::Clamp( const Vector2& v, const Vector2& min, const Vector2& max )");

  Vector2 v0(2.0f, 0.8f);
  Vector2 v1(-1.0f, 2.0f);
  Vector2 v2(10.0f, 5.0f);
  Vector2 v3(8.0f, 10.0f);
  Vector2 v4(4.9f, 5.1f);
  Vector2 min(1.0f, 4.0f);
  Vector2 max(9.0f, 6.0f);

  v0.Clamp( min, max );
  v1.Clamp( min, max );
  v2.Clamp( min, max );
  v3.Clamp( min, max );
  v4.Clamp( min, max );

  DALI_TEST_EQUALS( v0, Vector2(2.0f, 4.0f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( v1, Vector2(1.0f, 4.0f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( v2, Vector2(9.0f, 5.0f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( v3, Vector2(8.0f, 6.0f), 0.01f, TEST_LOCATION );
  DALI_TEST_EQUALS( v4, Vector2(4.9f, 5.1f), 0.01f, TEST_LOCATION );
}

// Normalize
static void UtcDaliVector2Normalize()
{
  for (float f=0.0f; f<6.0f; f+=1.0f)
  {
    Vector2 v(cosf(f)*10.0f, cosf(f+1.0f)*10.0f);
    v.Normalize();
    DALI_TEST_EQUALS(v.LengthSquared(), 1.0f, 0.001f, TEST_LOCATION);
  }

  Vector4 v(0.0f, 0.0f, 0.0f, 1.0f);
  v.Normalize();
  DALI_TEST_EQUALS(v.LengthSquared(), 0.0f, 0.00001f, TEST_LOCATION);
}

static void UtcDaliVector2OperatorSubscript()
{
  tet_infoline("Testing Dali::Vector2::operator[]()");

  Vector2 testVector(1.0f, 2.0f);

  // read array subscripts
  DALI_TEST_EQUALS( testVector[0], 1.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( testVector[1], 2.0f, TEST_LOCATION );

  // write array subscripts/read struct memebers
  testVector[0] = 3.0f;
  testVector[1] = 4.0f;

  DALI_TEST_EQUALS( testVector.x, 3.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( testVector.y, 4.0f, TEST_LOCATION );

  // write struct members/read array subscripts
  testVector.x = 5.0f;
  testVector.y = 6.0f;

  const Vector2 testVector2(3.0f, 4.0f);
  const float& x = testVector2[0];
  const float& y = testVector2[1];
  DALI_TEST_EQUALS( x, 3.0f, TEST_LOCATION );
  DALI_TEST_EQUALS( y, 4.0f, TEST_LOCATION );


  try
  {
    float& w = testVector[4];
    if(w==0.0f);
    tet_result(TET_FAIL);
  }
  catch (Dali::DaliException& e)
  {
    tet_printf("Assertion %s failed at %s\n", e.mCondition.c_str(), e.mLocation.c_str());
    DALI_TEST_ASSERT( e, "index < 2", TEST_LOCATION);
  }

  try
  {
    const float& w = testVector2[4];
    if(w==0.0f);
    tet_result(TET_FAIL);
  }
  catch (Dali::DaliException& e)
  {
    tet_printf("Assertion %s failed at %s\n", e.mCondition.c_str(), e.mLocation.c_str());
    DALI_TEST_ASSERT( e, "index < 2" , TEST_LOCATION);
  }


}

static void UtcDaliVector2OStreamOperator()
{
  std::ostringstream oss;

  Vector2 vector(1, 2);

  oss << vector;

  std::string expectedOutput = "[1, 2]";

  DALI_TEST_EQUALS( oss.str(), expectedOutput, TEST_LOCATION);
}
