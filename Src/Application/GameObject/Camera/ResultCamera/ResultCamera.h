#pragma once

#include "../CameraBase.h"

class ResultCamera : public CameraBase
{
public:
	ResultCamera() {}
	~ResultCamera()			override {}

	void Init()				override;
	void PostUpdate()		override;

};


