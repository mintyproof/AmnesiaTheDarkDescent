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

	cVector3f cVirtualReality::GetHMDPosition() {
		return mpLowLevelVirtualReality->GetHMDPosition();
	}

	//-----------------------------------------------------------------------

	cVector3f cVirtualReality::GetHMDRotation() {
		return mpLowLevelVirtualReality->GetHMDRotation();
	}

	//-----------------------------------------------------------------------

	void cVirtualReality::Update(float afTimeStep) {
		mpLowLevelVirtualReality->Update();
	}

	//-----------------------------------------------------------------------

	void cVirtualReality::Init(cResources* apResources) {
		Log("Initializing Virtual Reality Module\n");
		Log("--------------------------------------------------------\n");

		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

}