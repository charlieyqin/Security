// ======================================================================
//	File:		KCAPI_Keychain.cpp
//
//	Operation classes for core KC APIs:
//		- KCMakeKCRefFromFSRef
//		- KCMakeKCRefFromFSSpec
//		- KCMakeKCRefFromAlias
//		- KCMakeAliasFromKCRef
//		- KCReleaseKeychain
//		- KCUnlockNoUI
//		- KCUnlock
//		- KCUnlockWithInfo
//		- KCLock
//		- KCLockNoUI
//		- KCGetDefaultKeychain
//		- KCSetDefaultKeychain
//		- KCCreateKeychain
//		- KCCreateKeychainNoUI
//		- KCGetStatus
//		- KCChangeSettingsNoUI
//		- KCGetKeychain
//		- KCGetKeychainName
//		- KCChangeSettings
//		- KCCountKeychains
//		- KCGetIndKeychain
//		- KCAddCallback
//		- KCRemoveCallback
//		- KCSetInteractionAllowed
//		- KCIsInteractionAllowed
//
//	Copyright:	Copyright (c) 2000,2003 Apple Computer, Inc. All Rights Reserved.
//
//	Change History (most recent first):
//
//		 <1>	2/25/00	em		Created.
// ======================================================================
#include "KCAPI_Keychain.h"

#if TARGET_RT_MAC_MACHO
	#include <OSServices/KeychainCorePriv.h>
#endif

#include <Carbon/Carbon.h>
#undef check
UInt32	COp_KCAddCallback::sCounter[] = {0,0,0,0,0,0,0,0,0,0,0};

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCMakeKCRefFromFSRef
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCMakeKCRefFromFSRef::COp_KCMakeKCRefFromFSRef()
	:mFSRef("FSRef")
{
	AddParam(mFSRef);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCMakeKCRefFromFSRef::Operate()
{
	throw("KCMakeKCRefFromFSRef is not implemented");
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCMakeKCRefFromFSSpec
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCMakeKCRefFromFSSpec::COp_KCMakeKCRefFromFSSpec()
    :mKeychainFile("KeychainFile")
{
	AddParam(mKeychainFile);
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCMakeKCRefFromFSSpec::Operate()
{
	KCRef	aKeychain = NULL;

	mStatus = ::KCMakeKCRefFromFSSpec(
					(FSSpec*)mKeychainFile, 
					&aKeychain);

	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCMakeKCRefFromAlias
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCMakeKCRefFromAlias::COp_KCMakeKCRefFromAlias()
{
	AddParam(mAliasIndex);
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCMakeKCRefFromAlias::Operate()
{
	KCRef	aKeychain = NULL;
    AliasHandle alias = GetAlias();
    
	mStatus = ::KCMakeKCRefFromAlias(alias, &aKeychain);
	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCMakeAliasFromKCRef
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCMakeAliasFromKCRef::COp_KCMakeAliasFromKCRef()
{
	AddParam(mKeychainIndex);
	AddResult(mAliasIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCMakeAliasFromKCRef::Operate()
{
	AliasHandle	alias = GetAlias();
	mStatus = ::KCMakeAliasFromKCRef(GetKeychain(), (AliasHandle*)&alias);
    AddAlias(alias);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCReleaseKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCReleaseKeychain::COp_KCReleaseKeychain()
{
	AddParam(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCReleaseKeychain::Operate()
{
	KCRef	aKeychain = GetKeychain();
	mStatus = ::KCReleaseKeychain(&aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCLogout
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCLogout::COp_KCLogout()
{
}

OSStatus
COp_KCLogout::Operate()
{
    mStatus = ::KCLogout();

	return(mStatus);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCLogin
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCLogin::COp_KCLogin()
	:mName("Name"),
	mPassword("Password")
{
	AddParam(mName);
	AddParam(mPassword);
}

OSStatus
COp_KCLogin::Operate()
{
    mStatus = ::KCLogin( (StringPtr)mName, (StringPtr)mPassword );

	return(mStatus);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCChangeLoginPassword
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCChangeLoginPassword::COp_KCChangeLoginPassword()
	:mOldPassword("OldPassword"),
	mNewPassword("NewPassword")
{
	AddParam(mOldPassword);
	AddParam(mNewPassword);
}

OSStatus
COp_KCChangeLoginPassword::Operate()
{
    mStatus = ::KCChangeLoginPassword( (StringPtr)mOldPassword, (StringPtr)mNewPassword );

	return(mStatus);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCUnlockNoUI
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCUnlockNoUI::COp_KCUnlockNoUI()
	:mPassword("Password")
{
	AddParam(mKeychainIndex);
	AddParam(mPassword);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCUnlockNoUI::Operate()
{
//#if TARGET_RT_MAC_MACHO
//%%%₯₯₯₯₯₯₯	
    KCRef	aKeychain = GetKeychain();
    mStatus = ::KCUnlockNoUI( aKeychain,  (StringPtr)mPassword);
//	throw("KCUnlockNoUI not implemented");
//#else
//	throw("KCUnlockNoUI not implemented");
//#endif
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCUnlock
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCUnlock::COp_KCUnlock()
	:mPassword("Password")
{
	AddParam(mKeychainIndex);
	AddParam(mPassword);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCUnlock::Operate()
{
	mStatus = ::KCUnlock(GetKeychain(), (StringPtr)mPassword);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCUnlockWithInfo
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCUnlockWithInfo::COp_KCUnlockWithInfo()
	:mPassword("Password"), mMessage("Mesage")
{
	AddParam(mKeychainIndex);
	AddParam(mPassword);
	AddParam(mMessage);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCUnlockWithInfo::Operate()
{
#if 0 //TARGET_RT_MAC_MACHO
	mStatus = ::KCUnlockWithInfo(GetKeychain(), (StringPtr)mPassword, (StringPtr)mMessage);
#else
	return unimpErr;
	//throw("KCUnlockWithInfo is not implemented");
#endif
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCLock
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCLock::COp_KCLock()
{
	AddParam(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCLock::Operate()
{
	mStatus = ::KCLock(GetKeychain());
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCLockNoUI
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
/*
COp_KCLockNoUI::COp_KCLockNoUI()
{
	AddParam(mKeychainIndex);
}
*/
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
/*
OSStatus
COp_KCLockNoUI::Operate()
{
#if TARGET_RT_MAC_MACHO
	mStatus = ::KCLockNoUI(GetKeychain());
#else
	throw("KCLockNoUI not implemented");
#endif
	return(mStatus);
}
#pragma mark -
*/
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCGetDefaultKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCGetDefaultKeychain::COp_KCGetDefaultKeychain()
{
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCGetDefaultKeychain::Operate()
{
	KCRef	aKeychain = NULL;
	mStatus = ::KCGetDefaultKeychain(&aKeychain);
	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCSetDefaultKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCSetDefaultKeychain::COp_KCSetDefaultKeychain()
{
	AddParam(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCSetDefaultKeychain::Operate()
{
	mStatus = ::KCSetDefaultKeychain(GetKeychain());
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCCreateKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCCreateKeychain::COp_KCCreateKeychain()
	:mPassword("Password")
{
	AddParam(mKeychainIndex);
	AddParam(mPassword);
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCCreateKeychain::Operate()
{
	KCRef	aKeychain = GetKeychain();
	mStatus = ::KCCreateKeychain((StringPtr)mPassword, &aKeychain);
	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCCreateKeychainNoUI
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCCreateKeychainNoUI::COp_KCCreateKeychainNoUI()
    : mPassword("Password")
{
	AddParam(mKeychainIndex);
    AddParam(mPassword);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCCreateKeychainNoUI::Operate()
{
//#if TARGET_RT_MAC_MACHO

	KCRef	aKeychain = GetKeychain();

	mStatus = ::KCCreateKeychainNoUI(aKeychain, (StringPtr)mPassword);
//#else
//	throw("KCCreateKeychainNoUI not implemented");
//#endif
	return(mStatus);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Callback
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCCreateKeychainNoUI::Callback(
    KCRef			*outKeychain, 
    StringPtr		*outPassword, 
    void			*inContext)
{    										
/*    COp_KCCreateKeychainNoUI	*thisObject = static_cast<COp_KCCreateKeychainNoUI*>(inContext);
    if(thisObject == NULL) return -1;
    
//    FSSpec		*aFileSpec = thisObject->GetKeychainFile();
    KCRef		*aKeychain = thisObject->GetKeychainInCallback();
    StringPtr	aPassword = thisObject->GetPassword();
 //   OSStatus	aStatus = ::KCMakeKCRefFromFSSpec(aFileSpec, aKeychain);
    if(aStatus == noErr){
        *outKeychain = *aKeychain;
        *outPassword = aPassword;
    }
	else{
        *outKeychain = NULL;
        *outPassword = NULL;
	}
			
    return aStatus;
*/
return noErr;
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCGetStatus
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCGetStatus::COp_KCGetStatus()
	:mKeychainStatus("KeychainStatus")
{
	AddParam(mKeychainIndex);
	AddResult(mKeychainStatus);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCGetStatus::Operate()
{
	mStatus = ::KCGetStatus(
					GetKeychain(), 
					(UInt32*)mKeychainStatus);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCChangeSettingsNoUI
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCChangeSettingsNoUI::COp_KCChangeSettingsNoUI()
	:mLockOnSleep("LockOnSleep"),
	mUseKCGetDataSound("UseKCGetDataSound"),
	mUseKCGetDataAlert("UseKCGetDataAlert"),
	mUseLockInterval("UseLockInterval"),
	mLockInterval("LockInterval"),
	mNewPassword("NewPassword"),
	mOldPassword("OldPassword")
{
	AddParam(mLockOnSleep);
	AddParam(mUseKCGetDataSound);
	AddParam(mUseKCGetDataAlert);
	AddParam(mUseLockInterval);
	AddParam(mLockInterval);
	AddParam(mNewPassword);
	AddParam(mOldPassword);
	AddParam(mKeychainIndex);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCChangeSettingsNoUI::Operate()
{
#if TARGET_RT_MAC_MACHO

	mChangeSettingsInfo.lockOnSleep = (Boolean)mLockOnSleep;
//	mChangeSettingsInfo.useKCGetDataSound = (Boolean)mUseKCGetDataSound;
//	mChangeSettingsInfo.useKCGetDataAlert = (Boolean)mUseKCGetDataAlert;
	mChangeSettingsInfo.useLockInterval = (Boolean)mUseLockInterval;
	mChangeSettingsInfo.lockInterval = (UInt32)mLockInterval;
//	mChangeSettingsInfo.newPassword = (StringPtr)mNewPassword;
//	mChangeSettingsInfo.oldPassword = (StringPtr)mOldPassword;
	mChangeSettingsInfo.keychain = GetKeychain();
	
//	mStatus = ::KCChangeSettingsNoUI(
//					COp_KCChangeSettingsNoUI::Callback, 
//					this);
	throw("KCChangeSettingsNoUI not implemented");
#else
	throw("KCChangeSettingsNoUI not implemented");
#endif
	return(mStatus);
}

#if TARGET_RT_MAC_MACHO
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Callback
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCChangeSettingsNoUI::Callback(
    KCChangeSettingsInfo	* outSettings, 
    void					* inContext)
{
    COp_KCChangeSettingsNoUI	*thisObject = static_cast<COp_KCChangeSettingsNoUI*>(inContext);
    if(thisObject == NULL) return -1;

										// #2462430 - this should be :
										// 		*outSettings = thisObject->GetSettingsInfoPtr();
										// where KCChangeSettingsInfo **outSettings
										//
	outSettings = thisObject->GetChangeSettingsInfoPtr();
    return noErr;
}
#endif

#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCGetKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCGetKeychain::COp_KCGetKeychain()
{
	AddParam(mItemIndex);
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCGetKeychain::Operate()
{
	KCRef	aKeychain;
	mStatus = ::KCGetKeychain(
					GetItem(), 
					&aKeychain);
	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCGetKeychainName
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCGetKeychainName::COp_KCGetKeychainName()
	:mKeychainName("KeychainName")
{
	AddParam(mKeychainIndex);
	AddResult(mKeychainName);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCGetKeychainName::Operate()
{
	mStatus = ::KCGetKeychainName(
					GetKeychain(), 
					(StringPtr)mKeychainName);
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCChangeSettings
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCChangeSettings::COp_KCChangeSettings()
{
	AddParam(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCChangeSettings::Operate()
{
	mStatus = ::KCChangeSettings(GetKeychain());
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCCountKeychains
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCCountKeychains::COp_KCCountKeychains()
	:mCount("Count")
{
	AddResult(mCount);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCCountKeychains::Operate()
{
	mStatus = noErr;
	mCount = ::KCCountKeychains();
	return(mStatus);
}
#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCGetIndKeychain
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCGetIndKeychain::COp_KCGetIndKeychain()
	:mIndex("Index")
{
	AddParam(mIndex);
	AddResult(mKeychainIndex);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCGetIndKeychain::Operate()
{
	KCRef	aKeychain = NULL;
	mStatus = ::KCGetIndKeychain(mIndex, &aKeychain);
	AddKeychain(aKeychain);
	return(mStatus);
}
#pragma mark -
KCCallbackUPP	COp_KCAddCallback::sCallbacks[] =
	{	NewKCCallbackUPP(COp_KCAddCallback::Callback0),
		NewKCCallbackUPP(COp_KCAddCallback::Callback1),
		NewKCCallbackUPP(COp_KCAddCallback::Callback2),
		NewKCCallbackUPP(COp_KCAddCallback::Callback3),
		NewKCCallbackUPP(COp_KCAddCallback::Callback4),
		NewKCCallbackUPP(COp_KCAddCallback::Callback5),
		NewKCCallbackUPP(COp_KCAddCallback::Callback6),
		NewKCCallbackUPP(COp_KCAddCallback::Callback7),
		NewKCCallbackUPP(COp_KCAddCallback::Callback8),
		NewKCCallbackUPP(COp_KCAddCallback::Callback9),
		NewKCCallbackUPP(COp_KCAddCallback::Callback10) };
		
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCAddCallback
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCAddCallback::COp_KCAddCallback()
	:mEvent("KCEvent")
{
	AddParam(mEvent);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCAddCallback::Operate()
{
	mStatus = ::KCAddCallback(
					COp_KCAddCallback::sCallbacks[mEvent],
					(KCEventMask)(1 << (KCEvent)mEvent),
					(void *)this);
	return(mStatus);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
#define KCADDCALLBACK(N) \
OSStatus \
COp_KCAddCallback::Callback ## N( \
	KCEvent			inKeychainEvent, \
	KCCallbackInfo	*inInfo, \
	void			*inContext) \
{ \
	COp_KCAddCallback::sCounter[inKeychainEvent]++; \
	return noErr; \
}

KCADDCALLBACK(0)
KCADDCALLBACK(1)
KCADDCALLBACK(2)
KCADDCALLBACK(3)
KCADDCALLBACK(4)
KCADDCALLBACK(5)
KCADDCALLBACK(6)
KCADDCALLBACK(7)
KCADDCALLBACK(8)
KCADDCALLBACK(9)
KCADDCALLBACK(10)

#undef KCADDCALLBACK

#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCRemoveCallback
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCRemoveCallback::COp_KCRemoveCallback()
	:mEvent("KCEvent"),
	mIdleCount("IdleCount"),
	mLockCount("LockCount"),
	mUnlockCount("UnlockCount"),
	mAddCount("AddCount"),
	mDeleteCount("DeleteCount"),
	mUpdateCount("UpdateCount"),
	mChangeIdentityCount("ChangeIdentityCount"),
	mFindCount("FindCount"),
	mSystemCount("SystemCount"),
	mDefaultChangedCount("DefaultChangedCount"),
	mDataAccessCount("DataAccessCount")
{
	AddParam(mEvent);
	
	AddResult(mIdleCount);
	AddResult(mLockCount);
	AddResult(mUnlockCount);
	AddResult(mAddCount);
	AddResult(mDeleteCount);
	AddResult(mUpdateCount);
	AddResult(mChangeIdentityCount);
	AddResult(mFindCount);
	AddResult(mSystemCount);
	AddResult(mDefaultChangedCount);
	AddResult(mDataAccessCount);
}

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCRemoveCallback::Operate()
{
	// Receive a few events so we make sure we get all pending notifications (callbacks)
	EventRecord er;
	for (int ix = 0; ix < 142; ix++)
		GetNextEvent(0, &er);

	mStatus = ::KCRemoveCallback(
					COp_KCAddCallback::sCallbacks[mEvent]);

										// Copy the current results
	UInt16						i = 0;
	tParamList::iterator		aIterator = mResultList.begin();
    CParamUInt32 *				aParam = static_cast<CParamUInt32 *>(*aIterator);
    while(aIterator != mResultList.end()){
    	if(aParam){
			*aParam = COp_KCAddCallback::sCounter[i];
			i++;
		}
        aParam = static_cast<CParamUInt32 *>(*(++aIterator));
    }

										// reset the counter
	COp_KCAddCallback::sCounter[mEvent] = 0;

	return(mStatus);
}

#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCSetInteractionAllowed
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCSetInteractionAllowed::COp_KCSetInteractionAllowed()
	:mAllow("AllowInteraction")
{
	AddParam(mAllow);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCSetInteractionAllowed::Operate()
{
	mStatus = ::KCSetInteractionAllowed(mAllow);
	return(mStatus);
}

#pragma mark -
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ COp_KCIsInteractionAllowed
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
COp_KCIsInteractionAllowed::COp_KCIsInteractionAllowed()
	:mAllow("AllowInteraction")
{
	AddResult(mAllow);
}
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
// 	₯ Operate
// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ
OSStatus
COp_KCIsInteractionAllowed::Operate()
{
	mStatus = noErr;
	mAllow = ::KCIsInteractionAllowed();
	return(mStatus);
}
