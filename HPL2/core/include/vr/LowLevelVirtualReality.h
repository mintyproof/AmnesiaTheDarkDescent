#ifndef HPL_LOW_LEVEL_VIRTUAL_REALITY_H
#define HPL_LOW_LEVEL_VIRTUAL_REALITY_H

#ifdef USE_VR

namespace hpl {
	class iLowLevelVirtualReality {
	public:
		iLowLevelVirtualReality();
		virtual ~iLowLevelVirtualReality();

		void Update(float afTimeStep);
		bool Init(cResources* apResources);
	};
}

#endif // USE_VR

#endif // HPL_LOW_LEVEL_VIRTUAL_REALITY_H