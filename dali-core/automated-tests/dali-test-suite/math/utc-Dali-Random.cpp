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

static void UtcDaliRandomRangeMethod();
static void UtcDaliRandomAxisMethod();
static void UtcDaliRandomChanceMethod();

enum {
  POSITIVE_TC_IDX = 0x01,
  NEGATIVE_TC_IDX,
};

// Add test functionality for all APIs in the class (Positive and Negative)
extern "C" {
  struct tet_testlist tet_testlist[] = {
    { UtcDaliRandomRangeMethod,  POSITIVE_TC_IDX },
    { UtcDaliRandomAxisMethod,   POSITIVE_TC_IDX },
    { UtcDaliRandomChanceMethod, POSITIVE_TC_IDX },
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


static void UtcDaliRandomRangeMethod()
{
  TestApplication application; // Reset all test adapter return codes

  float a=0, b=1;
  for(size_t i=0; i<100; i++)
  {
    float r = Dali::Random::Range(a, b);
    DALI_TEST_CHECK(r >= a && r <= b);
  }

  a=100; b=-100;
  for(size_t i=0; i<100; i++)
  {
    float r = Dali::Random::Range(a, b);
    DALI_TEST_CHECK(r >= b && r <= a);
  }
}


static void UtcDaliRandomAxisMethod()
{
  TestApplication application; // Reset all test adapter return codes

  for(size_t i=0; i<100; i++)
  {
    Vector4 axis = Dali::Random::Axis();
    DALI_TEST_EQUALS(axis.Length(), 1.0f, 0.0001f, TEST_LOCATION);
  }
}

static void UtcDaliRandomChanceMethod()
{
  int bin_zero=0, bin_one=0;

  for(size_t i=0; i<100000; i++)
  {
    bool chance = Dali::Random::Chance();
    if(chance)
    {
      bin_one++;
    }
    else
    {
      bin_zero++;
    }
  }
  // Check distribution
  DALI_TEST_EQUALS((float)bin_zero / (float)bin_one, 1.0f, 0.1f, TEST_LOCATION);

  bin_zero=0; bin_one = 0;
  for(size_t i=0; i<100000; i++)
  {
    bool chance = Dali::Random::Chance(0.25);
    if(chance) {bin_one++;} else {bin_zero++;}
  }
  // Check distribution
  DALI_TEST_EQUALS((float)bin_zero / (float)bin_one, 3.0f, 0.1f, TEST_LOCATION);

  bin_zero=0; bin_one = 0;
  for(size_t i=0; i<100000; i++)
  {
    bool chance = Dali::Random::Chance(0.1);
    if(chance) {bin_one++;} else {bin_zero++;}
  }
  // Check distribution
  DALI_TEST_EQUALS((float)bin_zero / (float)bin_one, 9.0f, 0.1f, TEST_LOCATION);
}
