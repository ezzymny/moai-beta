// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAILayer2D.h>
#include <moaicore/MOAILayerBridge2D.h>
#include <moaicore/MOAILogMessages.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@brief <tt>() init ( self, sourceLayer, targetLayer )</tt>\n
\n
	Initialize the bridge transform (map coordinates in one layer onto
	another; useful for rendering screen space objects tied to world
	space coordinates - map pins, for example).
	@param self (in)
	@param sourceLayer (in)
	@param targetLayer (in)
*/
int MOAILayerBridge2D::_init ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAILayerBridge2D, "UUU" );
	
	MOAILayer2D* sourceScene = state.GetLuaObject < MOAILayer2D >( 2 );
	if ( !sourceScene ) return 0;
	
	MOAILayer2D* targetScene = state.GetLuaObject < MOAILayer2D >( 3 );
	if ( !targetScene ) return 0;
	
	self->mSourceScene = sourceScene;
	self->mTargetScene = targetScene;
	
	return 0;
}

//================================================================//
// MOAILayerBridge2D
//================================================================//

//----------------------------------------------------------------//
MOAILayerBridge2D::MOAILayerBridge2D () {
	
	RTTI_SINGLE ( MOAITransform )
}

//----------------------------------------------------------------//
MOAILayerBridge2D::~MOAILayerBridge2D () {
}

//----------------------------------------------------------------//
void MOAILayerBridge2D::OnDepNodeUpdate () {
	
	if ( !( this->mSourceScene && this->mTargetScene )) return; 
	
	//this->mSourceScene->DepNodeUpdate ();
	//this->mTargetScene->DepNodeUpdate ();
	
	this->mSourceScene->GetWorldToWndMtx ( this->mLocalToWorldMtx );
	
	USAffine2D targetWndToWorld;
	this->mTargetScene->GetWndToWorldMtx ( targetWndToWorld );
	this->mLocalToWorldMtx.Append ( targetWndToWorld );
	
	this->mWorldToLocalMtx.Inverse ( this->mLocalToWorldMtx );
}

//----------------------------------------------------------------//
void MOAILayerBridge2D::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAILayerBridge2D::RegisterLuaFuncs ( USLuaState& state ) {
	
	MOAITransform::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "init",				_init },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

