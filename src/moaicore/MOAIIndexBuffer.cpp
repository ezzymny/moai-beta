// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIIndexBuffer.h>
#include <moaicore/MOAILogMessages.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	release
	@text	Release any memory held by this index buffer.
	
	@in		MOAIIndexBuffer self
	@out	nil
*/
int	MOAIIndexBuffer::_release ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIIndexBuffer, "U" )
	
	self->Clear ();
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reserve
	@text	Set capacity of buffer.
	
	@in		MOAIIndexBuffer self
	@in		number nIndices
	@out	nil
*/
int	MOAIIndexBuffer::_reserve ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIIndexBuffer, "UN" )
	
	u32 indexCount = state.GetValue < u32 >( 2, 0 );
	self->ReserveIndices ( indexCount );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setIndex
	@text	Initialize an index.
	
	@in		MOAIIndexBuffer self
	@in		number idx
	@in		number value
	@out	nil
*/
int	MOAIIndexBuffer::_setIndex ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIIndexBuffer, "UNN" )
	
	u32 idx		= state.GetValue < u32 >( 2, 1 ) - 1;
	u16 value	= state.GetValue < u16 >( 3, 0 );
	
	self->SetIndex ( idx, value );
	
	return 0;
}

//================================================================//
// MOAIGfxQuadListDeck2D
//================================================================//

//----------------------------------------------------------------//
bool MOAIIndexBuffer::Bind () {

	if ( this->mBuffer ) {
	
		this->Release ();
		
		glGenBuffers ( 1, &this->mGLBufferID );
		if ( !this->mGLBufferID ) return false;
		
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, this->mGLBufferID );
		glBufferData ( GL_ELEMENT_ARRAY_BUFFER, this->mIndexCount * sizeof ( u16 ), this->mBuffer, this->mHint );
		
		this->ClearBuffer ();
	}
	
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, this->mGLBufferID );
	return true;
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::Clear () {

	this->ClearBuffer ();
	if ( this->mGLBufferID ) {
		glDeleteBuffers ( 1, &this->mGLBufferID );
		this->mGLBufferID = 0;
	}
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::ClearBuffer () {

	if ( this->mBuffer ) {
		free ( this->mBuffer );
		this->mBuffer = 0;
	}
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::DrawElements ( GLenum mode, GLsizei count, u32 offset ) {

	glDrawElements ( mode, count, GL_UNSIGNED_SHORT, ( GLvoid* )offset );
}

//----------------------------------------------------------------//
MOAIIndexBuffer::MOAIIndexBuffer () :
	mBuffer ( 0 ),
	mIndexCount ( 0 ),
	mGLBufferID ( 0 ),
	mHint ( GL_STATIC_DRAW ) {
	
	RTTI_SINGLE ( MOAIIndexBuffer )
}

//----------------------------------------------------------------//
MOAIIndexBuffer::~MOAIIndexBuffer () {

	this->Clear ();
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::RegisterLuaFuncs ( USLuaState& state ) {

	luaL_Reg regTable [] = {
		{ "release",			_release },
		{ "reserve",			_reserve },
		{ "setIndex",			_setIndex },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::ReserveIndices ( u32 indexCount ) {

	this->ClearBuffer ();
	
	this->mIndexCount = indexCount;
	this->mBuffer = ( u16* )malloc ( indexCount * sizeof ( u16 ));
}

//----------------------------------------------------------------//
void MOAIIndexBuffer::SetIndex ( u32 idx, u16 value ) {

	if ( idx < this->mIndexCount ) {
		this->mBuffer [ idx ] = value;
	}
}
