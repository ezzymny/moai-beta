// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#ifndef _WIN32

#include <uslsext/USMutex_posix.h>

//================================================================//
// USMutexImpl
//================================================================//

//----------------------------------------------------------------//
void USMutexImpl::Init () {

	pthread_mutex_init ( &this->mMutex, 0 );
}

//----------------------------------------------------------------//
void USMutexImpl::Lock () {

	pthread_mutex_lock ( &this->mMutex );
}

//----------------------------------------------------------------//
void USMutexImpl::Unlock () {

	pthread_mutex_unlock ( &this->mMutex );
}

//----------------------------------------------------------------//
USMutexImpl::USMutexImpl () {
}

//----------------------------------------------------------------//
USMutexImpl::~USMutexImpl () {

	pthread_mutex_destroy ( &this->mMutex );
}

#endif
