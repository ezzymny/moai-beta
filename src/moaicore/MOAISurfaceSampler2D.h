#ifndef MOAISURFACESAMPLER2D_H
#define MOAISURFACESAMPLER2D_H

class MOAITransform;

//================================================================//
// MOAISurface2D
//================================================================//
class MOAISurface2D :
	public USSurface2D {
public:

	MOAITransform*	mSourcePrim;
};

//================================================================//
// MOAISurfaceSampler2D
//================================================================//
class MOAISurfaceSampler2D {
private:

	USRect				mWorldRect;
	USRect				mLocalRect;

	USAffine2D			mWorldToSampleMtx;
	USAffine2D			mLocalToSampleMtx;

	MOAITransform*	mSourcePrim;

public:

	enum {
		kMaxSurfaces = 256,
	};

	MOAISurface2D mSurfaces [ kMaxSurfaces ];
	u32 mTop;

	//----------------------------------------------------------------//
	void		AddSurfaceFromLocal			( USVec2D v0, USVec2D v1 );
	void		AddSurfaceFromWorld			( USVec2D v0, USVec2D v1 );
	void		Clear						();
	USRect		GetLocalRect				();
	void		Init						( const USAffine2D& worldToSampleMtx, const USRect& worldRect );
				MOAISurfaceSampler2D		();
				~MOAISurfaceSampler2D		();
	void		SetObjectMtx				();
	void		SetObjectMtx				( const USAffine2D& localToWorld, const USAffine2D& worldToLocal );
	void		SetSourcePrim				( MOAITransform* sourcePrim );
};

#endif
