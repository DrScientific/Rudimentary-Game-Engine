#pragma once

#include <SDKDDKVer.h>

// Headers for CppUnitTest
#include "CppUnitTest.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif