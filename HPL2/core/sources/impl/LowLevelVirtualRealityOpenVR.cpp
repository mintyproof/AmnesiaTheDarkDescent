#include "vr/VirtualReality.h"
#include "system/LowLevelSystem.h"
#include "vr/LowLevelVirtualReality.h"
#include "impl/LowLevelVirtualRealityOpenVR.h"
#include "math/Math.h"

namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cLowLevelVirtualRealityOpenVR::cLowLevelVirtualRealityOpenVR() {
		Log("Initializing OpenVR...");

		vr::EVRInitError eError = vr::VRInitError_None;
		mpHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

		if (eError != vr::VRInitError_None) {
			mpHMD = NULL;
			Log("Initializating VR runtime failed! VR functions won't behave correctly. Error: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
			exit(EXIT_FAILURE);
		}

		if (!vr::VRCompositor()) {
			printf("Failed to initialize VR compositor!\n");
		}

		Log("OpenVR initialized!");
	}

	//-----------------------------------------------------------------------

	cLowLevelVirtualRealityOpenVR::~cLowLevelVirtualRealityOpenVR() {
		if (mpHMD != NULL) {
			vr::VR_Shutdown();
			mpHMD = NULL;
		}
	}
	
	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////
	
	//-----------------------------------------------------------------------

	void cLowLevelVirtualRealityOpenVR::Update() {
		vr::VREvent_t event;
		while (mpHMD->PollNextEvent(&event, sizeof(event))) {
			ProcessEvent(event);
		}

		for (vr::TrackedDeviceIndex_t iDeviceIndex = 0; iDeviceIndex < vr::k_unMaxTrackedDeviceCount; iDeviceIndex++) {
			if (!mpHMD->IsTrackedDeviceConnected(iDeviceIndex))
				continue;

			vr::VRControllerState_t state;
			if (mpHMD->GetControllerState(iDeviceIndex, &state, sizeof(state))) {
				vr::TrackedDevicePose_t vTrackedDevicePose, vTrackedControllerPose;
				vr::VRControllerState_t vControllerState;
				vr::HmdMatrix34_t mPoseMatrix;
				vr::ETrackedDeviceClass eTrackedDeviceClass = vr::VRSystem()->GetTrackedDeviceClass(iDeviceIndex);

				switch (eTrackedDeviceClass) {
				case vr::ETrackedDeviceClass::TrackedDeviceClass_HMD:
					vr::VRSystem()->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, &vTrackedDevicePose, 1);
					mPoseMatrix = vTrackedDevicePose.mDeviceToAbsoluteTracking;
					vHMDPosition = GetPositionFromVRMatrix(mPoseMatrix);
					vHMDRotation = GetRotationFromVRMatrix(mPoseMatrix);
					fprintf(stderr, "pos %.3f, %.3f, %.3f : rot %.3f, %.3f, %.3f\n", vHMDPosition.x, vHMDPosition.y, vHMDPosition.z, vHMDRotation.x, vHMDRotation.y, vHMDRotation.z);
					break;
				}
			}
		}
	}

	//-----------------------------------------------------------------------

	void cLowLevelVirtualRealityOpenVR::ProcessEvent(vr::VREvent_t event) {

	}

	//-----------------------------------------------------------------------

	cVector3f cLowLevelVirtualRealityOpenVR::GetHMDPosition() {
		return vHMDPosition;
	}

	//-----------------------------------------------------------------------

	cVector3f cLowLevelVirtualRealityOpenVR::GetHMDRotation() {
		return vHMDRotation;
	}

	//-----------------------------------------------------------------------

	cVector3f cLowLevelVirtualRealityOpenVR::GetRotationFromVRMatrix(vr::HmdMatrix34_t mMatrix) {
		vr::HmdQuaternion_t qQuaternion;

		qQuaternion.w = std::sqrt(std::fmax(0, 1 + mMatrix.m[0][0] + mMatrix.m[1][1] + mMatrix.m[2][2])) / 2;
		qQuaternion.x = std::sqrt(std::fmax(0, 1 + mMatrix.m[0][0] - mMatrix.m[1][1] - mMatrix.m[2][2])) / 2;
		qQuaternion.y = std::sqrt(std::fmax(0, 1 - mMatrix.m[0][0] + mMatrix.m[1][1] - mMatrix.m[2][2])) / 2;
		qQuaternion.z = std::sqrt(std::fmax(0, 1 - mMatrix.m[0][0] - mMatrix.m[1][1] + mMatrix.m[2][2])) / 2;
		qQuaternion.x = std::copysign(qQuaternion.x, mMatrix.m[2][1] - mMatrix.m[1][2]);
		qQuaternion.y = std::copysign(qQuaternion.y, mMatrix.m[0][2] - mMatrix.m[2][0]);
		qQuaternion.z = std::copysign(qQuaternion.z, mMatrix.m[1][0] - mMatrix.m[0][1]);

		cVector3f vRotation;

		// it's midnight and I don't feel like figuring this math out quite yet..
		// sourced from the Wikipedia article "Conversion between quaternions and Euler angles"

		double sinr_cosp = 2 * (qQuaternion.w * qQuaternion.x + qQuaternion.y * qQuaternion.z);
		double cosr_cosp = 1 - 2 * (qQuaternion.x * qQuaternion.x + qQuaternion.y * qQuaternion.y);
		vRotation.x = std::atan2(sinr_cosp, cosr_cosp);

		double sinp = 2 * (qQuaternion.w * qQuaternion.y - qQuaternion.z * qQuaternion.x);
		if (std::abs(sinp) >= 1)
			vRotation.y = std::copysign(kPif / 2, sinp); // use 90 degrees if out of range
		else
			vRotation.y = std::asin(sinp);

		double siny_cosp = 2 * (qQuaternion.w * qQuaternion.z + qQuaternion.x * qQuaternion.y);
		double cosy_cosp = 1 - 2 * (qQuaternion.y * qQuaternion.y + qQuaternion.z * qQuaternion.z);
		vRotation.z = std::atan2(siny_cosp, cosy_cosp);

		return cVector3f(cMath::ToDeg(vRotation.x), cMath::ToDeg(vRotation.y), cMath::ToDeg(vRotation.z));
	}

	//-----------------------------------------------------------------------

	cVector3f cLowLevelVirtualRealityOpenVR::GetPositionFromVRMatrix(vr::HmdMatrix34_t mMatrix) {
		return cVector3f(mMatrix.m[0][3], mMatrix.m[1][3], mMatrix.m[2][3]);
	}

	//-----------------------------------------------------------------------

}