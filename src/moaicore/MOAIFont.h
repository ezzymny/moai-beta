// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFONT_H
#define	MOAIFONT_H

class MOAIData;

//================================================================//
// MOAIFont
//================================================================//
/**	@brief Font class.
*/
class MOAIFont :
	public virtual USLuaData,
	public USFont {
private:

	USTexture	mTexture;

	//----------------------------------------------------------------//
	static int	_getScale			( lua_State* L );
	static int	_load				( lua_State* L );
	static int	_loadFromTTF		( lua_State* L );

public:

	DECL_LUA_DATA ( MOAIFont )
	
	//----------------------------------------------------------------//
	USFont*			Bind				();
					MOAIFont			();
					~MOAIFont			();
	void			LoadFont			( MOAIData& fontImageData, cc8* charCodes );
	void			LoadFont			( cc8* fontImageFileName, cc8* charCodes );
	void			LoadFontFromTTF		( cc8* filename, cc8* charCodes, float points, u32 dpi );
	void			RegisterLuaClass	( USLuaState& state );
	void			RegisterLuaFuncs	( USLuaState& state );
	void			Render				();
	STLString		ToString			();
};

#endif