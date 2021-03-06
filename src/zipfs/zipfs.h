// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef ZIPFS_H
#define ZIPFS_H

#include <stdarg.h>
#include <stdio.h>

//================================================================//
// zipfs_stat
//================================================================//
typedef struct zipfs_stat {

	int						mExists;
	int						mIsDir;
	
	unsigned long long		mTimeCreated;	// Time created (in seconds from cardinal date)
	unsigned long long		mTimeModified;	// Time last modified (in seconds from cardinal date)
	unsigned long long		mTimeViewed;	// Time last viewed (in seconds from cardinal date)
	size_t					mSize;			// Yeah, that

} zipfs_stat;


//================================================================//
// stdio
//================================================================//

typedef void ZIPFSFILE;

extern ZIPFSFILE* zipfs_stderr;
extern ZIPFSFILE* zipfs_stdin;
extern ZIPFSFILE* zipfs_stdout;

//----------------------------------------------------------------//
extern void					zipfs_clearerr				( ZIPFSFILE* fp );
extern int					zipfs_fclose				( ZIPFSFILE* fp );
extern int					zipfs_feof					( ZIPFSFILE* fp );
extern int					zipfs_ferror				( ZIPFSFILE* fp );
extern int					zipfs_fflush				( ZIPFSFILE* fp );
extern int					zipfs_fgetc					( ZIPFSFILE* fp );
extern int					zipfs_fgetpos				( ZIPFSFILE* fp, fpos_t* position );
extern char* 				zipfs_fgets					( char* string, int length, ZIPFSFILE* fp );
extern ZIPFSFILE* 			zipfs_fopen 				( const char* filename, const char* mode );
extern int					zipfs_fprintf				( ZIPFSFILE * fp, const char * format, ... );
extern int 					zipfs_fputc					( int c, ZIPFSFILE* fp );
extern int					zipfs_fputs					( const char* string, ZIPFSFILE* fp );
extern size_t				zipfs_fread					( void* buffer, size_t size, size_t count, ZIPFSFILE* fp );
extern ZIPFSFILE*			zipfs_freopen				( const char* filename, const char* mode, ZIPFSFILE* fp );
extern int					zipfs_fscanf				( ZIPFSFILE* fp, const char* format, ... );
extern int					zipfs_fseek					( ZIPFSFILE* fp, long offset, int origin );
extern int					zipfs_fsetpos				( ZIPFSFILE* fp, const fpos_t * pos );
extern long					zipfs_ftell					( ZIPFSFILE* fp );
extern size_t				zipfs_fwrite				( const void* data, size_t size, size_t count, ZIPFSFILE* fp );
extern int					zipfs_getc					( ZIPFSFILE* fp );
extern int					zipfs_remove				( const char* path );
extern int					zipfs_rename				( const char* oldname, const char* newname );
extern void					zipfs_rewind				( ZIPFSFILE* fp );
extern void					zipfs_setbuf				( ZIPFSFILE* fp, char* buffer );
extern int					zipfs_setvbuf				( ZIPFSFILE* fp, char* buffer, int mode, size_t size );
extern ZIPFSFILE*			zipfs_tmpfile				();
extern int					zipfs_ungetc				( int character, ZIPFSFILE* fp );
extern int					zipfs_vfprintf				( ZIPFSFILE* fp, const char* format, va_list arg );
extern int					zipfs_vfscanf				( ZIPFSFILE* fp, const char* format, va_list arg );

//================================================================//
// extra
//================================================================//

typedef void ZIPFSDIR;

//----------------------------------------------------------------//
extern int					zipfs_affirm_path				( const char* path );
extern char*				zipfs_basename					( const char* filename );
extern char*				zipfs_bless_path				( const char* path );
extern int					zipfs_chdir						( const char* path );
extern void					zipfs_cleanup					();
extern void					zipfs_dir_close					( ZIPFSDIR* dir );
extern char const*			zipfs_dir_entry_name			( ZIPFSDIR* dir );
extern int					zipfs_dir_entry_is_subdir		( ZIPFSDIR* dir );
extern ZIPFSDIR*			zipfs_dir_open					();
extern int					zipfs_dir_read_entry			( ZIPFSDIR* dir );
extern char*				zipfs_get_abs_dirpath			( const char* path );
extern char*				zipfs_get_abs_filepath			( const char* path );
extern char*				zipfs_get_rel_path				( const char* path );
extern int					zipfs_get_stat					( char const* path, zipfs_stat* filestat );
extern char*				zipfs_get_working_path			();
extern char*				zipfs_getcwd					( char* buffer, size_t length );
extern void					zipfs_init						();
extern int					zipfs_is_virtual_path			( const char* path );
extern int					zipfs_mkdir						( const char* path );
extern int					zipfs_mount_virtual				( const char* path, const char* archive );
extern char*				zipfs_normalize_path			( const char* path );
extern int					zipfs_rmdir						( const char* path );

#endif