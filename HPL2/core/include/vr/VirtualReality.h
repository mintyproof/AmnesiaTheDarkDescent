#ifndef HPL_VIRTUAL_REALITY_H
#define HPL_VIRTUAL_REALITY_H

#include "engine/Updateable.h"
#include "math/MathTypes.h"

namespace hpl {
	class iLowLevelVirtualReality;
	class cResources;

	class cVirtualReality : public iUpdateable {
	public:
		cVirtualReality(iLowLevelVirtualReality* apLowLevelVirtualReality);
		~cVirtualReality();
		
		cVector3f GetHMDPosition();
		cVector3f GetHMDRotation();

		void Update(float afTimeStep);
		void Init(cResources* apResources);
	protected:
		iLowLevelVirtualReality* mpLowLevelVirtualReality;
	};
}

#endif // HPL_VIRTUAL_REALITY_H