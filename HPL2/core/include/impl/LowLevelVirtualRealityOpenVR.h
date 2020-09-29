#ifndef HPL_LOW_LEVEL_VIRTUAL_REALITY_OPENVR_H
#define HPL_LOW_LEVEL_VIRTUAL_REALITY_OPENVR_H

#include "vr/LowLevelVirtualReality.h"

#include <openvr.h>
#include "math/MathTypes.h"

namespace hpl {
	class cLowLevelVirtualRealityOpenVR : public iLowLevelVirtualReality {
	public:
		cLowLevelVirtualRealityOpenVR();
		~cLowLevelVirtualRealityOpenVR();

		void Update();
		cVector3f GetHMDPosition();
		cVector3f GetHMDRotation();
	private:
		void ProcessEvent(vr::VREvent_t event);
        cVector3f GetRotationFromVRMatrix(vr::HmdMatrix34_t mMatrix);
        cVector3f GetPositionFromVRMatrix(vr::HmdMatrix34_t mMatrix);

		cVector3f vHMDPosition;
		cVector3f vHMDRotation;

		vr::IVRSystem* mpHMD = NULL;
		vr::TrackedDevicePose_t mrTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
		cMatrixf mmDevicePose[vr::k_unMaxTrackedDeviceCount];
	};
}

#endif // HPL_LOW_LEVEL_VIRTUAL_REALITY_OPENVR_H