# Microsoft Developer Studio Generated NMAKE File, Based on DRMPluginAll.dsp
!IF "$(CFG)" == ""
CFG=DRMPluginAll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DRMPluginAll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DRMPluginAll - Win32 Release" && "$(CFG)" != "DRMPluginAll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DRMPluginAll.mak" CFG="DRMPluginAll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DRMPluginAll - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "DRMPluginAll - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF  "$(CFG)" == "DRMPluginAll - Win32 Release"

ALL :
	@ECHO Creating directories...
	@IF NOT EXIST .\DRMPlugin @mkdir .\DRMPlugin
	@IF NOT EXIST .\DRMPlugin\include @mkdir .\DRMPlugin\include
	@IF NOT EXIST .\DRMPlugin\lib @mkdir .\DRMPlugin\lib
	@IF NOT EXIST .\DRMPlugin\lib\win32 @mkdir .\DRMPlugin\lib\win32
	@IF NOT EXIST .\DRMPlugin\lib\win32\VC6 @mkdir .\DRMPlugin\lib\win32\VC6
	@IF NOT EXIST .\DRMPlugin\lib\win32\VC6\release @mkdir .\DRMPlugin\lib\win32\VC6\release
	@del /Q .\DRMPlugin\*.*
	@del /Q .\DRMPlugin\include\*.*
	@del /Q .\DRMPlugin\lib\*.*
	@del /Q .\DRMPlugin\lib\win32\*.*
	@del /Q .\DRMPlugin\lib\win32\VC6\*.*
	@del /Q .\DRMPlugin\lib\win32\VC6\release\*.*
	@ECHO Done...
	@ECHO Copying include files...
	@copy ..\include\Value.h .\DRMPlugin\include
	@copy ..\include\UTCTime.h .\DRMPlugin\include
	@copy ..\include\BasicTypes.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\ContentInfoManager.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\ContentInfoManagerFactory.h .\DRMPlugin\include
	@copy ..\include\DRMLogger.h .\DRMPlugin\include
	@copy ..\include\ICipher.h .\DRMPlugin\include
	@copy  ..\DRMDecoderPlugin\include\IDRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IDRMEncManager.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IISMADRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMDecoderPlugin\DecryptorHolder\DecryptorHolder.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IISMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\include\IMPEG4DRMAtom.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IOMADRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IOMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IOpenIPMPDRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IOpenIPMPMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\include\IPublicCrypto.h .\DRMPlugin\include
	@copy  ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\ISMADRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\ISMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\include\IThreadSync.h .\DRMPlugin\include
	@copy ..\include\IXMLDocument.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\include\MPEG4DRMPluginException.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\OMADRMEncManagerFactory\OMADRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\OMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\OpenIPMPDRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\OpenIPMPMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\PublicCryptoFactory\PublicCryptoFactory.h .\DRMPlugin\include
	@copy ..\ThreadSyncFactory\ThreadSyncFactory.h .\DRMPlugin\include
	@copy ..\XMLFactory\XMLFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\DRMInfoException.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IISMADRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IISMADRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOMADRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOMADRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOpenIPMPDRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOpenIPMPDRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\ISMADRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\OMADRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\OpenIPMPDRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\ISMADRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\OMADRMDecManagerFactory\OMADRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\OpenIPMPDRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\openIPMP\OpenIPMP.h .\DRMPlugin\include
	@ECHO Done...
	@ECHO Copying libraries...
	@ECHO Copying externals...
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\AxisClient.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\AxisXMLParser.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\HTTPChannel.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\HTTPTransport.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\xerces\win32\lib\VC6\xerces-c_2_6.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\xerces\win32\lib\VC6\xerces-depdom_2_6.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\openssl\lib\win32\release\VC6\ssleay32.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\..\..\ext\openssl\lib\win32\release\VC6\libeay32.dll .\DRMPlugin\lib\win32\VC6\release
	@ECHO Copying DRM plugins...
	@copy ..\OMADRM\OMADRMDeviceIDCalc\Build\Win32\VC6\Release\OMADRMDeviceIDCalc.exe .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Release\ContentInfoManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\Build\Win32\VC6\Release\ISMADRMEncManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy  ..\DRMEncoderPlugin\OMADRMEncManagerFactory\Build\Win32\VC6\Release\OMADRMEncManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Release\OpenIPMPDRMEncManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\OMADRMEncCommHandlerFactory\Build\Win32\VC6\Release\OMADRMEncCommHandlerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\XMLFactory\Build\Win32\VC6\Release\XMLFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\PublicCryptoFactory\Build\Win32\VC6\Release\PublicCryptoFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\ThreadSyncFactory\Build\Win32\VC6\Release\ThreadSyncFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\OpenIPMPMessengerFactory\Build\Win32\VC6\Release\OpenIPMPMessengerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\Build\Win32\VC6\Release\ISMADRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMDecoderPlugin\OMADRMDecManagerFactory\Build\Win32\VC6\Release\OMADRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy  ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\Build\Win32\VC6\Release\OpenIPMPDRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMDecoderPlugin\OMADRMDecCommHandlerFactory\Build\Win32\VC6\Release\OMADRMDecCommHandlerFactory.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Release\ContentInfoManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\Build\Win32\VC6\Release\ISMADRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\OMADRMEncManagerFactory\Build\Win32\VC6\Release\OMADRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Release\OpenIPMPDRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\XMLFactory\Build\Win32\VC6\Release\XMLFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\PublicCryptoFactory\Build\Win32\VC6\Release\PublicCryptoFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\ThreadSyncFactory\Build\Win32\VC6\Release\ThreadSyncFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy  ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\Build\Win32\VC6\Release\ISMADRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMDecoderPlugin\OMADRMDecManagerFactory\Build\Win32\VC6\Release\OMADRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\Build\Win32\VC6\Release\OpenIPMPDRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\release
	@ECHO Copying MPEG4 DRM plugins...
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\ISMAMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\OMAMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\OpenIPMPMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\ISMAMPEG4SinfDRMEncryptor.lib  .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\OMAMPEG4SinfDRMEncryptor.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\Build\Win32\VC6\Release\OpenIPMPMPEG4SinfDRMEncryptor.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMDecoderPlugin\DecryptorHolder\Build\Win32\VC6\Release\DecryptorHolder.lib .\DRMPlugin\lib\win32\VC6\release
	@ECHO Done...
	@ECHO Copying MPEG2 DRM plugins...
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Release\MPEG2IPMPXDRMEncoder.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\OpenIPMPMPEG2IPMPXDRMEncryptor\Build\Win32\VC6\Release\OpenIPMPMPEG2IPMPXDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\MessageRouter\Build\Win32\VC6\Release\MessageRouter.dll .\DRMPlugin\lib\win32\VC6\release
	@copy  ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\OpenIPMPTool\Build\Win32\VC6\Release\OpenIPMPTool.dll .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Release\MPEG2IPMPXDRMEncoder.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\MessageRouter\Build\Win32\VC6\Release\MessageRouter.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\OpenIPMPTool\Build\Win32\VC6\Release\OpenIPMPTool.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPControlInfo\Build\Win32\VC6\Release\IPMPControlInfo.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPCrypto\Build\Win32\VC6\Release\IPMPCrypto.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPData\Build\Win32\VC6\Release\IPMPData.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\DecoderIPMPControlInfo\Build\Win32\VC6\Release\DecoderIPMPControlInfo.lib  .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\DecoderIPMPData\Build\Win32\VC6\Release\DecoderIPMPData.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPControlInfoParser\Build\Win32\VC6\Release\IPMPControlInfoParser.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPDataParser\Build\Win32\VC6\Release\IPMPDataParser.lib .\DRMPlugin\lib\win32\VC6\release
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPToolManager\Build\Win32\VC6\Release\IPMPToolManager.lib .\DRMPlugin\lib\win32\VC6\release
	@ECHO Done...

!ELSEIF  "$(CFG)" == "DRMPluginAll - Win32 Debug"

ALL :
	@ECHO Creating directories...
	@IF NOT EXIST .\DRMPlugin @mkdir .\DRMPlugin
	@IF NOT EXIST .\DRMPlugin\include @mkdir .\DRMPlugin\include
	@IF NOT EXIST .\DRMPlugin\lib @mkdir .\DRMPlugin\lib
	@IF NOT EXIST .\DRMPlugin\lib\win32 @mkdir .\DRMPlugin\lib\win32
	@IF NOT EXIST .\DRMPlugin\lib\win32\VC6 @mkdir .\DRMPlugin\lib\win32\VC6
	@IF NOT EXIST .\DRMPlugin\lib\win32\VC6\debug @mkdir .\DRMPlugin\lib\win32\VC6\debug
	@del /Q .\DRMPlugin\*.*
	@del /Q .\DRMPlugin\include\*.*
	@del /Q .\DRMPlugin\lib\*.*
	@del /Q .\DRMPlugin\lib\win32\*.*
	@del /Q .\DRMPlugin\lib\win32\VC6\*.*
	@del /Q .\DRMPlugin\lib\win32\VC6\debug\*.*
	@ECHO Done...
	@ECHO Copying include files...
	@copy ..\include\Value.h .\DRMPlugin\include
	@copy ..\include\UTCTime.h .\DRMPlugin\include
	@copy ..\include\BasicTypes.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\ContentInfoManager.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\ContentInfoManagerFactory.h .\DRMPlugin\include
	@copy ..\include\DRMLogger.h .\DRMPlugin\include
	@copy ..\include\ICipher.h .\DRMPlugin\include
	@copy  ..\DRMDecoderPlugin\include\IDRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IDRMEncManager.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IISMADRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMDecoderPlugin\DecryptorHolder\DecryptorHolder.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IISMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\include\IMPEG4DRMAtom.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IOMADRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IOMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\include\IOpenIPMPDRMEncManager.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\include\IOpenIPMPMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\include\IPublicCrypto.h .\DRMPlugin\include
	@copy  ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\ISMADRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\ISMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\include\IThreadSync.h .\DRMPlugin\include
	@copy ..\include\IXMLDocument.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\include\MPEG4DRMPluginException.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\OMADRMEncManagerFactory\OMADRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\OMAMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\OpenIPMPDRMEncManagerFactory.h .\DRMPlugin\include
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\OpenIPMPMPEG4SinfDRMEncryptor.h .\DRMPlugin\include
	@copy ..\PublicCryptoFactory\PublicCryptoFactory.h .\DRMPlugin\include
	@copy ..\ThreadSyncFactory\ThreadSyncFactory.h .\DRMPlugin\include
	@copy ..\XMLFactory\XMLFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\DRMInfoException.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IISMADRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IISMADRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOMADRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOMADRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOpenIPMPDRMDecManager.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\IOpenIPMPDRMDecryptor.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\ISMADRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\OMADRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\include\OpenIPMPDRMInfo.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\ISMADRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\OMADRMDecManagerFactory\OMADRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\OpenIPMPDRMDecManagerFactory.h .\DRMPlugin\include
	@copy ..\openIPMP\OpenIPMP.h .\DRMPlugin\include
	@ECHO Done...
	@ECHO Copying libraries...
	@ECHO Copying externals...
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\AxisClient_D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\AxisXMLParser_D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\HTTPChannel_D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\axis-c\lib\win32\VC6\HTTPTransport_D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\xerces\win32\lib\VC6\xerces-c_2_6D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\xerces\win32\lib\VC6\xerces-depdom_2_6D.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\openssl\lib\win32\debug\VC6\ssleay32.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\..\..\ext\openssl\lib\win32\debug\VC6\libeay32.dll .\DRMPlugin\lib\win32\VC6\debug
	@ECHO Copying DRM plugins...
	@copy ..\OMADRM\OMADRMDeviceIDCalc\Build\Win32\VC6\Debug\OMADRMDeviceIDCalc.exe .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Debug\ContentInfoManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\Build\Win32\VC6\Debug\ISMADRMEncManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\OMADRMEncManagerFactory\Build\Win32\VC6\Debug\OMADRMEncManagerFactory.dll  .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Debug\OpenIPMPDRMEncManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\OMADRMEncCommHandlerFactory\Build\Win32\VC6\Debug\OMADRMEncCommHandlerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\XMLFactory\Build\Win32\VC6\Debug\XMLFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\PublicCryptoFactory\Build\Win32\VC6\Debug\PublicCryptoFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\ThreadSyncFactory\Build\Win32\VC6\Debug\ThreadSyncFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\OpenIPMPMessengerFactory\Build\Win32\VC6\Debug\OpenIPMPMessengerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\Build\Win32\VC6\Debug\ISMADRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMDecoderPlugin\OMADRMDecManagerFactory\Build\Win32\VC6\Debug\OMADRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\Build\Win32\VC6\Debug\OpenIPMPDRMDecManagerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy  ..\DRMDecoderPlugin\OMADRMDecCommHandlerFactory\Build\Win32\VC6\Debug\OMADRMDecCommHandlerFactory.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\ContentInfoManagerFactory\Build\Win32\VC6\Debug\ContentInfoManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\ISMADRMEncManagerFactory\Build\Win32\VC6\Debug\ISMADRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\OMADRMEncManagerFactory\Build\Win32\VC6\Debug\OMADRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMEncoderPlugin\OpenIPMPDRMEncManagerFactory\Build\Win32\VC6\Debug\OpenIPMPDRMEncManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\XMLFactory\Build\Win32\VC6\Debug\XMLFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\PublicCryptoFactory\Build\Win32\VC6\Debug\PublicCryptoFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\ThreadSyncFactory\Build\Win32\VC6\Debug\ThreadSyncFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMDecoderPlugin\ISMADRMDecManagerFactory\Build\Win32\VC6\Debug\ISMADRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy  ..\DRMDecoderPlugin\OMADRMDecManagerFactory\Build\Win32\VC6\Debug\OMADRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\DRMDecoderPlugin\OpenIPMPDRMDecManagerFactory\Build\Win32\VC6\Debug\OpenIPMPDRMDecManagerFactory.lib .\DRMPlugin\lib\win32\VC6\debug
	@ECHO Copying MPEG4 DRM plugins...
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\ISMAMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\OMAMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\OpenIPMPMPEG4SinfDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\ISMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\ISMAMPEG4SinfDRMEncryptor.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OMAMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\OMAMPEG4SinfDRMEncryptor.lib  .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMEncoderPlugin\OpenIPMPMPEG4SinfDRMEncryptor\Build\Win32\VC6\Debug\OpenIPMPMPEG4SinfDRMEncryptor.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG4DRMPlugin\MPEG4SinfDRMPlugin\MPEG4SinfDRMDecoderPlugin\DecryptorHolder\Build\Win32\VC6\Debug\DecryptorHolder.lib .\DRMPlugin\lib\win32\VC6\debug
	@ECHO Done...
	@ECHO Copying MPEG2 DRM plugins...
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Debug\MPEG2IPMPXDRMEncoder.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\OpenIPMPMPEG2IPMPXDRMEncryptor\Build\Win32\VC6\Debug\OpenIPMPMPEG2IPMPXDRMEncryptor.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\MessageRouter\Build\Win32\VC6\Debug\MessageRouter.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\OpenIPMPTool\Build\Win32\VC6\Debug\OpenIPMPTool.dll .\DRMPlugin\lib\win32\VC6\debug
	@copy  ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMEncoderPlugin\MPEG2IPMPXDRMEncoder\Build\Win32\VC6\Debug\MPEG2IPMPXDRMEncoder.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\MessageRouter\Build\Win32\VC6\Debug\MessageRouter.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\OpenIPMPTool\Build\Win32\VC6\Debug\OpenIPMPTool.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPControlInfo\Build\Win32\VC6\Debug\IPMPControlInfo.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPCrypto\Build\Win32\VC6\Debug\IPMPCrypto.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\IPMPData\Build\Win32\VC6\Debug\IPMPData.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\DecoderIPMPControlInfo\Build\Win32\VC6\Debug\DecoderIPMPControlInfo.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\DecoderIPMPData\Build\Win32\VC6\Debug\DecoderIPMPData.lib  .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPControlInfoParser\Build\Win32\VC6\Debug\IPMPControlInfoParser.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPDataParser\Build\Win32\VC6\Debug\IPMPDataParser.lib .\DRMPlugin\lib\win32\VC6\debug
	@copy ..\MPEG2DRMPlugin\MPEG2IPMPXDRMPlugin\MPEG2IPMPXDRMDecoderPlugin\IPMPToolManager\Build\Win32\VC6\Debug\IPMPToolManager.lib .\DRMPlugin\lib\win32\VC6\debug
	@ECHO Done...

!ENDIF 

