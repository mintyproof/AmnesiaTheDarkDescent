#ifndef HPL_VIRTUAL_REALITY_H
#define HPL_VIRTUAL_REALITY_H

#ifdef USE_VR

#include "engine/Updateable.h"

namespace hpl {
	class iLowLevelVirtualReality;
	class cResources;

	class cVirtualReality : public iUpdateable {
	public:
		cVirtualReality(iLowLevelVirtualReality* apLowLevelVirtualReality);
		~cVirtualReality();
		
		void Update(float afTimeStep);
		void Init(cResources* apResources);
	protected:
		iLowLevelVirtualReality* mpLowLevelVirtualReality;
	};
}

#endif // USE_VR

#endif // HPL_VIRTUAL_REALITY_H