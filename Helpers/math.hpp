#pragma once

#include "../valve_sdk/sdk.hpp"

#include <DirectXMath.h>

namespace Math {
	void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
}