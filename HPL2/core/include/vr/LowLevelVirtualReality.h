#ifndef HPL_LOW_LEVEL_VIRTUAL_REALITY_H
#define HPL_LOW_LEVEL_VIRTUAL_REALITY_H

#ifdef USE_VR

namespace hpl {
	class iLowLevelVirtualReality {
	public:
		virtual ~iLowLevelVirtualReality() {}
	};
}

#endif // USE_VR

#endif // HPL_LOW_LEVEL_VIRTUAL_REALITY_H