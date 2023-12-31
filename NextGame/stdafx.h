// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#include <iostream>
#include <limits>
#include <cmath>
#include "float3.h"
#include "float4x4.h"

#define F_EPSILON std::numeric_limits<float>::epsilon()
#define F_PI 3.14159265358979323846f
#define F_TAU PI*2.0f;
#define TO_RAD(degrees) ((degrees) * (F_PI / 180.0f))
#define TO_DEG(radians) ((radians) * (180.0f / F_PI))