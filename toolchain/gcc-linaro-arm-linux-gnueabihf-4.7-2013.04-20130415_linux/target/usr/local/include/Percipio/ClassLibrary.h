//
// ClassLibrary.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/ClassLibrary.h#1 $
//
// Library: Foundation
// Package: SharedLibrary
// Module:  ClassLoader
//
// Definitions for class libraries.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ClassLibrary_INCLUDED
#define Foundation_ClassLibrary_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Manifest.h"
#include <typeinfo>


#if defined(_WIN32)
	#define PERCIPIO_LIBRARY_API __declspec(dllexport)
#else
	#define PERCIPIO_LIBRARY_API
#endif


//
// the entry points for every class library
//
extern "C"
{
	bool PERCIPIO_LIBRARY_API percipioBuildManifest(Percipio::ManifestBase* pManifest);
	void PERCIPIO_LIBRARY_API percipioInitializeLibrary();
	void PERCIPIO_LIBRARY_API percipioUninitializeLibrary();
} 


//
// additional support for named manifests
//
#define PERCIPIO_DECLARE_NAMED_MANIFEST(name) \
extern "C"	\
{			\
	bool PERCIPIO_LIBRARY_API PERCIPIO_JOIN(percipioBuildManifest, name)(Percipio::ManifestBase* pManifest); \
}


//
// Macros to automatically implement percipioBuildManifest
//
// usage:
//
// PERCIPIO_BEGIN_MANIFEST(MyBaseClass)
//     PERCIPIO_EXPORT_CLASS(MyFirstClass)
//     PERCIPIO_EXPORT_CLASS(MySecondClass)
//     ...
// PERCIPIO_END_MANIFEST
//
#define PERCIPIO_BEGIN_MANIFEST_IMPL(fnName, base) \
	bool fnName(Percipio::ManifestBase* pManifest_)										\
	{																				\
		typedef base _Base;															\
		typedef Percipio::Manifest<_Base> _Manifest;									\
		std::string requiredType(typeid(_Manifest).name());							\
		std::string actualType(pManifest_->className());							\
		if (requiredType == actualType)												\
		{																			\
			Percipio::Manifest<_Base>* pManifest = static_cast<_Manifest*>(pManifest_);


#define PERCIPIO_BEGIN_MANIFEST(base) \
	PERCIPIO_BEGIN_MANIFEST_IMPL(percipioBuildManifest, base)


#define PERCIPIO_BEGIN_NAMED_MANIFEST(name, base)	\
	PERCIPIO_DECLARE_NAMED_MANIFEST(name)			\
	PERCIPIO_BEGIN_MANIFEST_IMPL(PERCIPIO_JOIN(percipioBuildManifest, name), base)


#define PERCIPIO_END_MANIFEST \
			return true;	\
		}					\
		else return false;	\
	}


#define PERCIPIO_EXPORT_CLASS(cls) \
    pManifest->insert(new Percipio::MetaObject<cls, _Base>(#cls));


#define PERCIPIO_EXPORT_SINGLETON(cls) \
	pManifest->insert(new Percipio::MetaSingleton<cls, _Base>(#cls));


#endif // Foundation_ClassLibrary_INCLUDED
