#ifndef _AKSI_MATH_CH_
#define _AKSI_MATH_CH_

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Vector2Int.h"
#include "Vector3Int.h"
#include "Vector4Int.h"

#include <iosfwd>
#include <cmath>
#include <limits>
#include <algorithm>

class AMath {
public:
    bool static ReliableFloatComp(float i, float j);

    bool static Swap(float i, float j);
};

#endif