// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAICPSPACE_H
#define	MOAICPSPACE_H
#if USE_CHIPMUNK

#include <moaicore/MOAIAction.h>

struct cpBody;
struct cpSpace;
class MOAICpArbiter;
class MOAICpBody;
class MOAICpSpace;
class MOAICpCollisionHandler;

//================================================================//
// MOAICpPrim
//================================================================//
class MOAICpPrim :
	public virtual USLuaData  {
protected:

	USLeanLink < MOAICpPrim* > mLinkInSpace;
	MOAICpSpace* mSpace;

	//----------------------------------------------------------------//
	virtual void	CpAddToSpace			( cpSpace* space ) = 0;
	virtual void	CpRemoveFromSpace		( cpSpace* space ) = 0;
	
public:

	friend class MOAICpSpace;

	//----------------------------------------------------------------//
	virtual void	DoRemove				();
					MOAICpPrim				();
					~MOAICpPrim				();
	void			Remove					();
};

//================================================================//
// MOAICpSpace
//================================================================//
/**	@brief Chipmunk Space.
*/
class MOAICpSpace :
	public MOAIAction {
private:

	cpSpace*					mSpace;
	USRef < MOAICpBody >		mStaticBody;
	USRef < MOAICpArbiter >		mArbiter;
	
	MOAICpCollisionHandler*	mCollisionHandlers;
	MOAICpCollisionHandler* mDefaultHandler;
	
	typedef USLeanList < MOAICpPrim* >::Iterator PrimIt;
	USLeanList < MOAICpPrim* > mPrims;

	//----------------------------------------------------------------//
	static int	_activateShapesTouchingShape	( lua_State* L );
	static int	_getDamping						( lua_State* L );
	static int	_getGravity						( lua_State* L );
	static int	_getIdleSpeedThreshold			( lua_State* L );
	static int	_getIterations					( lua_State* L );
	static int	_getSleepTimeThreshold			( lua_State* L );
	static int	_getStaticBody					( lua_State* L );
	static int	_insertPrim						( lua_State* L );
	static int	_rehashShape					( lua_State* L );
	static int	_rehashStatic					( lua_State* L );
	static int	_removePrim						( lua_State* L );
	static int	_resizeActiveHash				( lua_State* L );
	static int	_resizeStaticHash				( lua_State* L );
	static int	_setCollisionHandler			( lua_State* L );
	static int	_setDamping						( lua_State* L );
	static int	_setGravity						( lua_State* L );
	static int	_setIdleSpeedThreshold			( lua_State* L );
	static int	_setIterations					( lua_State* L );
	static int	_setSleepTimeThreshold			( lua_State* L );
	static int	_shapeForPoint					( lua_State* L );
	static int	_shapeForSegment				( lua_State* L );
	static int	_shapeListForPoint				( lua_State* L );
	static int	_shapeListForRect				( lua_State* L );
	static int	_shapeListForSegment			( lua_State* L );
	
	//----------------------------------------------------------------//

public:
	
	enum {
		BEGIN			= 0x00000001,
		PRE_SOLVE		= 0x00000002,
		POST_SOLVE		= 0x00000004,
		SEPARATE		= 0x00000008,
		ALL				= 0x0000000f,
	};
	
	friend class MOAICpBody;
	friend class MOAICpConstraint;
	friend class MOAICpShape;
	
	DECL_LUA_DATA ( MOAICpSpace )
	
	//----------------------------------------------------------------//
	void			DrawDebug				();
	MOAICpArbiter*	GetArbiter				();
	void			InsertPrim				( MOAICpPrim& prim );
	bool			IsBusy					();
					MOAICpSpace				();
					~MOAICpSpace			();
	void			OnUpdate				( float step );
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
	void			RemovePrim				( MOAICpPrim& prim );
	STLString		ToString				();
};

#endif
#endif