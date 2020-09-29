#ifdef USE_VR

#include "vr/VirtualReality.h"
#include "system/LowLevelSystem.h"
#include "vr/LowLevelVirtualReality.h"

namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cVirtualReality::cVirtualReality(iLowLevelVirtualReality* apLowLevelVirtualReality) : iUpdateable("HPL_VirtualReality") {
		mpLowLevelVirtualReality = apLowLevelVirtualReality;
		
	}

	//-----------------------------------------------------------------------

	cVirtualReality::~cVirtualReality() {
		Log("Exiting Virtual Reality Module\n");
		Log("--------------------------------------------------------\n");


		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void cVirtualReality::Update(float afTimeStep) {
	}

	//-----------------------------------------------------------------------

	void cVirtualReality::Init(cResources* apResources) {
		Log("Initializing Virtual Reality Module\n");
		Log("--------------------------------------------------------\n");

		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

}

#endif // USE_VR