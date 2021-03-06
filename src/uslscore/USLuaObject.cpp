// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <uslscore/USLog.h>
#include <uslscore/USLuaObject.h>
#include <uslscore/USLuaRef.h>
#include <uslscore/USLuaState.h>
#include <uslscore/USLuaRuntime.h>
#include <uslscore/USLuaSerializer.h>
#include <uslscore/USLuaState-impl.h>

//================================================================//
// USLuaLocal
//================================================================//
	
//----------------------------------------------------------------//
USLuaLocal::USLuaLocal () :
	mRef ( LUA_NOREF ) {
}

//----------------------------------------------------------------//
USLuaLocal::~USLuaLocal () {
}

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int USLuaObject::_gc ( lua_State* L ) {

	USLuaState state ( L );
	
	USLuaObject* data = ( USLuaObject* )state.GetPtrUserData ( 1 );

	bool cleanup = ( data->GetRefCount () == 0 ); // ready to cleanup if no references

	// in any event, let's get rid of the userdata and lua refs we know about
	data->ClearLocal ( data->mContain );
	data->mUserdata.Clear ();
	data->mPrivateTable.Clear ();
	data->mInstanceTable.Clear ();
	
	// check to see if gc is being invoked during finalization
	if ( USLuaRuntime::IsValid ()) {
		USLuaRuntime::Get ().ClearObjectStackTrace ( data );
	}

	// delete if no references
	if ( cleanup ) {
		delete data;
	}
	return 0;
}

//----------------------------------------------------------------//
int USLuaObject::_getClass ( lua_State* L ) {

	USLuaState state ( L );
	USLuaObject* object = ( USLuaObject* )state.GetPtrUserData ( 1 );

	if ( object ) {
		object->PushLuaClassTable ( state );
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
int USLuaObject::_getClassName ( lua_State* L ) {

	USLuaState state ( L );
	USLuaObject* object = ( USLuaObject* )state.GetPtrUserData ( 1 );

	if ( object ) {
		lua_pushstring ( L, object->TypeName ());
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------//
int USLuaObject::_tombstone ( lua_State* L ) {

	USLuaState state ( L );
	
	USLog::Print ( "----------------------------------------------------------------\n" );
	USLog::Print ( "ERROR: Attempt to access missing object instance.\n" );
	state.PrintStackTrace ( USLog::CONSOLE, 0 );
	USLog::Print ( "\n" );
	
	return 0;
}

//----------------------------------------------------------------//
int USLuaObject::_tostring ( lua_State* L ) {

	USLuaState state ( L );

	USLuaObject* data = ( USLuaObject* )state.GetPtrUserData ( 1 );
	if ( data ) {
	
		STLString str;
		str.write ( "0x%p <%s>", data, data->TypeName ()); // TODO: 64-bit
		state.Push ( str );
		return 1;
	}
	return 0;
}

//================================================================//
// USLuaObject
//================================================================//

//----------------------------------------------------------------//
void USLuaObject::BindToLuaWithTable ( USLuaState& state ) {

	assert ( !this->mUserdata );
	assert ( state.IsType ( -1, LUA_TTABLE ));
	
	USLuaClass* type = this->GetLuaClass ();
	assert ( type );
	
	// create and initialize a new userdata
	state.PushPtrUserData ( this );

	// move the instance table to top; initialize it
	state.MoveToTop ( -2 );
	
	lua_pushvalue ( state, -1 );
	lua_setfield ( state, -2, "__index" );
	
	lua_pushvalue ( state, -1 );
	lua_setfield ( state, -2, "__newindex" );

	lua_pushcfunction ( state, USLuaObject::_gc );
	lua_setfield ( state, -2, "__gc" );
	
	lua_pushcfunction ( state, USLuaObject::_tostring );
	lua_setfield ( state, -2, "__tostring" );
	
	// create and initialize the private table
	lua_newtable ( state );
	
	// use the member table as the private table's __index
	type->PushMemberTable ( state );
	lua_setfield ( state, -2, "__index" );
	
	// and make the member table the private table's meta
	type->PushMemberTable ( state );
	lua_setmetatable ( state, -2 );
	
	// grab a ref to the private table; attach it to the instance table
	this->mPrivateTable = state.GetWeakRef ( -1 );
	lua_setmetatable ( state, -2 );

	// grab a ref to the instance table; attach it to the userdata
	this->mInstanceTable = state.GetWeakRef ( -1 );
	lua_setmetatable ( state, -2 );
	
	// and take a ref back to the userdata	
	if ( this->GetRefCount () == 0 ) {
		this->mUserdata.SetWeakRef ( state, -1 );
	}
	else {
		this->mUserdata.SetStrongRef ( state, -1 );
	}

	assert ( !lua_isnil ( state, -1 ));
}

//----------------------------------------------------------------//
void USLuaObject::ClearLocal ( USLuaLocal& ref ) {
	
	if ( USLuaRuntime::IsValid ()) {
		USLuaStateHandle state = USLuaRuntime::Get ().State ();
		
		if ( this->mPrivateTable.PushRef ( state )) {
		
			lua_pushnumber ( state, ref.mRef );
			lua_pushnil ( state );
			lua_settable ( state, -3 );
			lua_pop ( state, 1 );
		}
	}
	ref.mRef = LUA_NOREF;
}

//----------------------------------------------------------------//
USLuaClass* USLuaObject::GetLuaClass () {

	// no implementation
	assert ( false );
	return 0;
}

//----------------------------------------------------------------//
USLuaStateHandle USLuaObject::GetSelf () {

	USLuaStateHandle state = USLuaRuntime::Get ().State ();
	this->PushLuaUserdata ( state );
	return state;
}

//----------------------------------------------------------------//
bool USLuaObject::IsBound () {

	return ( this->mUserdata != 0 );
}

//----------------------------------------------------------------//
void USLuaObject::LockToRefCount () {

	this->mUserdata.MakeStrong ();
}

//----------------------------------------------------------------//
void USLuaObject::LuaRelease ( USLuaObject& object ) {

	if ( this->mContain && USLuaRuntime::IsValid ()) {
	
		USLuaStateHandle state = USLuaRuntime::Get ().State ();
	
		if ( this->PushLocal ( state, this->mContain )) {
			
			object.PushLuaUserdata ( state );
			lua_pushnil ( state );
			lua_rawset ( state, -3 );
		}
		lua_pop ( state, 1 );
	}
	object.Release ();
}

//----------------------------------------------------------------//
void USLuaObject::LuaRetain ( USLuaObject& object ) {

	if ( this->mPrivateTable ) {
		USLuaStateHandle state = USLuaRuntime::Get ().State ();

		// affirm container table
		if ( this->mContain ) {
			this->PushLocal ( state, this->mContain );
		}
		else {
			lua_newtable ( state );
			this->SetLocal ( state, -1, this->mContain );
		}
		
		lua_pop ( state, 1 );
		this->PushLocal ( state, this->mContain );
		
		object.PushLuaUserdata ( state );
		lua_pushvalue ( state, -1 );
		lua_rawset ( state, -3 );
		
		lua_pop ( state, 1 );
	}
	object.Retain ();
}

//----------------------------------------------------------------//
void USLuaObject::LuaUnbind () {
	
	if ( this->mUserdata && USLuaRuntime::IsValid ()) {
		
		USLuaStateHandle state = USLuaRuntime::Get ().State ();
		
		this->mUserdata.PushRef ( state );
		
		void* userdata = lua_touserdata ( state, -1 );
		memset ( userdata, 0, sizeof ( void* ));
		
		lua_newtable ( state );
		
		lua_pushvalue ( state, -1 );
		lua_setmetatable ( state, -2 );
		
		lua_pushcfunction ( state, USLuaObject::_tombstone );
		lua_setfield ( state, -2, "__index" );
		
		lua_pushcfunction ( state, USLuaObject::_tombstone );
		lua_setfield ( state, -2, "__newindex" );
		
		lua_pushcfunction ( state, USLuaObject::_tombstone );
		lua_setfield ( state, -2, "__tostring" );
		
		lua_setmetatable ( state, -2 );

		lua_pop ( state, 1 );

		this->mUserdata.Clear ();
	}
}

//----------------------------------------------------------------//
void USLuaObject::OnRelease ( u32 refCount ) {

	if ( refCount == 0 ) {
	
		if ( this->mUserdata ) {
			this->mUserdata.MakeWeak ();
		}
		else {
			// no Lua binding and no references, so
			// go ahead and kill this turkey
			delete this;
		}
	}
}

//----------------------------------------------------------------//
void USLuaObject::OnRetain ( u32 refCount ) {
	UNUSED ( refCount );
}

//----------------------------------------------------------------//
void USLuaObject::PushLuaClassTable ( USLuaState& state ) {

	USLuaClass* luaType = this->GetLuaClass ();
	luaType->mClassTable.PushRef ( state );
}

//----------------------------------------------------------------//
void USLuaObject::PushLuaUserdata ( USLuaState& state ) {

	// create the handle userdata for reference counting
	if ( !this->mUserdata.PushRef ( state )) {
		
		// pop the 'nil' pushed by PushRef
		state.Pop ( 1 );
		
		// create an empty instance table
		lua_newtable ( state );
		
		// initialize and bind the userdata
		this->BindToLuaWithTable ( state );
	}
	assert ( !lua_isnil ( state, -1 ));
}

//----------------------------------------------------------------//
bool USLuaObject::PushLocal ( USLuaState& state, USLuaLocal& ref ) {

	if ( ref ) {
		
		assert ( this->mPrivateTable );
		
		this->mPrivateTable.PushRef ( state );
		lua_rawgeti ( state, -1, ref.mRef );
		lua_replace ( state, -2 );
		return true;
	}
	lua_pushnil ( state );
	return false;
}

//----------------------------------------------------------------//
void USLuaObject::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void USLuaObject::RegisterLuaFuncs ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void USLuaObject::SerializeIn ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void USLuaObject::SerializeOut ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void USLuaObject::SetLocal ( USLuaState& state, int idx, USLuaLocal& ref ) {

	idx = state.AbsIndex ( idx );

	assert ( this->mPrivateTable );

	this->mPrivateTable.PushRef ( state );
	
	if ( ref ) {
		luaL_unref ( state, -1, ref.mRef );
		ref.mRef = LUA_NOREF;
	}
	
	state.CopyToTop ( idx );
	ref.mRef = luaL_ref ( state, -2 );
	
	lua_pop ( state, 1 );
}

//----------------------------------------------------------------//
USLuaObject::USLuaObject () {
	RTTI_SINGLE ( RTTIBase )
	
	if ( USLuaRuntime::IsValid ()) {
		USLuaRuntime::Get ().RegisterObject ( *this );
	}
}

//----------------------------------------------------------------//
USLuaObject::~USLuaObject () {
	
	if ( USLuaRuntime::IsValid ()) {
		
		USLuaRuntime::Get ().ClearObjectStackTrace ( this );
		
		this->LuaUnbind ();
		
		USLuaRuntime::Get ().DeregisterObject ( *this );
	}
}

//================================================================//
// USLuaClass
//================================================================//

//----------------------------------------------------------------//
USLuaObject* USLuaClass::GetSingleton () {
	return 0;
}

//----------------------------------------------------------------//
void USLuaClass::InitLuaFactoryClass ( USLuaObject& data, USLuaState& state ) {

	int top = lua_gettop ( state );

	lua_newtable ( state );
	
	lua_pushcfunction ( state, USLuaObject::_getClass );
	lua_setfield ( state, -2, "getClass" );
	
	lua_pushcfunction ( state, USLuaObject::_getClassName );
	lua_setfield ( state, -2, "getClassName" );

	data.RegisterLuaFuncs ( state );

	lua_pushvalue ( state, -1 );
	lua_setfield ( state, -2, "__index" );

	lua_pushnil ( state );
	lua_setfield ( state, -2, "__newindex" );

	this->mMemberTable = state.GetStrongRef ( -1 );
	
	lua_settop ( state, top );

	lua_newtable ( state );
	this->RegisterLuaClass ( state );
	data.RegisterLuaClass ( state );
	this->mClassTable = state.GetStrongRef ( -1 );

	lua_setglobal ( state, data.TypeName ());

	lua_settop ( state, top );
}

//----------------------------------------------------------------//
void USLuaClass::InitLuaSingletonClass ( USLuaObject& data, USLuaState& state ) {

	int top = lua_gettop ( state );

	state.PushPtrUserData ( &data );

	lua_newtable ( state );
	this->RegisterLuaClass ( state );
	data.RegisterLuaClass ( state );
	this->mClassTable = state.GetStrongRef ( -1 );
	
	lua_pushvalue ( state, -1 );
	lua_setfield ( state, -2, "__index" );

	lua_pushnil ( state );
	lua_setfield ( state, -2, "__newindex" );

	lua_setmetatable ( state, -2 );

	lua_setglobal ( state, data.TypeName ());

	// set up the private table so we can use lua retain/release
	lua_newtable ( state );
	data.mPrivateTable.SetStrongRef ( state, -1 );
	lua_pop ( state, 1 );

	lua_settop ( state, top );
}

//----------------------------------------------------------------//
bool USLuaClass::IsSingleton () {

	return ( this->GetSingleton () != 0 );
}

//----------------------------------------------------------------//
void USLuaClass::PushMemberTable ( USLuaState& state ) {

	state.Push ( this->mMemberTable );
}

//----------------------------------------------------------------//
USLuaClass::USLuaClass () {
}

//----------------------------------------------------------------//
USLuaClass::~USLuaClass () {
}

