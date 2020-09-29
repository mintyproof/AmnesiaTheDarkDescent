#ifndef HPL_LOW_LEVEL_VIRTUAL_REALITY_H
#define HPL_LOW_LEVEL_VIRTUAL_REALITY_H

#include "math/MathTypes.h"

namespace hpl {
	class iLowLevelVirtualReality {
	public:
		virtual ~iLowLevelVirtualReality() {}

		virtual void Update() = 0;
		virtual cVector3f GetHMDPosition() = 0;
		virtual cVector3f GetHMDRotation() = 0;
	};
}

#endif // HPL_LOW_LEVEL_VIRTUAL_REALITY_H