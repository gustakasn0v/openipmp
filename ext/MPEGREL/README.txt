/*********************************************************************
COPYRIGHT AND LICENSE

Copyright (c) 2003, ContentGuard Holdings, Inc.


 ****	****

 ****	ContentGuard OPEN MPEG REL LICENSE AGREEMENT
 ****	FOR INFORMATION REGARDING COPYING, REDISTRIBUTION, AND LICENSING, 
 ****	PLEASE SEE THE FILE NAMED LICENSE

 ****	****

README for MPEG-21 REL REFERENCE IMPLEMENTATION, MICROSOFT WINDOWS VERSION 
============================================================================

PREREQUISITES & SUPPORTED PLATFORMS:

1. This release is based on the specification and schemas released as in MPEG-21 REL FCD dated February 2003.

PREREQUISITES & SUPPORTED PLATFORMS:
- Must have the Microsoft MSXML 4.0 Parser installed
You can obtain it at:
http://msdn.microsoft.com/downloads/default.asp?url=/downloads/sample.asp?url=/msdn-files/027/001/766/msdncompositedoc.xml

- Supported platforms: Windows XP, Windows 2000 Server, Windows ME, Windows NT 4.0 Workstation, Windows 98 SE.

FILE ORGANIZATION:
=================
Files organized as follows:
	- bin/Release: RELLicAuthz.dll, RELLicAuthzDriver.dll, RELExLimitService.dll, RELLicAuthzWinGUI.exe and the local state reference file ExerciseLimit.cfg.
	- common: CGUtil class with utility functions used by the dlls and the gui app, and the file 
          CGTime.h that defines the structure tm used by RELLicAuthz.dll.
	- Examples: Sample REL license files and sample XML query files.
	- lib/Release: RELLicAuthz.lib and RELLicAuthzDriver.lib.
	- RELLicAuthz: The source code for the reference interpreter for MPEG-21 REL (RELLicAuthz.dll).
	- RELLicAuthzDriver: The source code for the reference driver for MPEG-21 REL (RELLicAuthzDriver.dll)
	  which makes use of the reference interpreter.
	- RELLicAuthzWinGUI: The source code for the gui that helps access the reference driver and the reference
          interpreter.
	- RELExLimitService: The source code for the local exercise limit service (RELExLimitService.dll) that keeps state in a local file (ExerciseLimit.cfg).
	- schemas: XML Schemas referenced by the sample licenses.
        - SuperWsp: The super workspace containing the four projects.


RUNNING THE PROGRAM:
===========================
1. Using the windows explorer, navigate to the directory that the program RELLicAuthzWinGUI.exe is copied and double click on the program to launch it.

2. The program displays a dialog box for selecting a REL license file. Click on the 'Browse' button next to the 'Select License File' edit control to display the 'open file dialog'.  Navigate to the 'Examples' directory under the directory where the package was unzipped. (Eg., if the folder the package was unzipped was c:\program files\XrML Reference Implementations, please navigate to c:\program files\XrML Reference Implementations\Examples).  On the list of files shown, select a license file (e.g., 'License_SimplewithCond.xml').  The name of the selected file will appear in the adjacent edit box.

3. Using the procedure described above, select a query file (e.g., 'Query_exampleInput.xml').

4. In the 'Options' section, click 'Log Authorization Session' to turn log on.  Check on 'Log Issuers and Conditions' if you want to log the issuers and conditions returned by 'validateRequest' (this option appears once the 'Log Authorization Session' option is selected). The log file 'AuthorizationSession.log' is saved in the directory containing the application.  Please note that the log files for the previous sessions are renamed and saved in the same directory.  Please select the 'Validate' option to validate the license file during loading.

5. Click on the 'Authorize' button. The application tries to authorize the request against the licenses in the selected license file. A pop-up message box will display the status of the authorization request (success or failure) and the error code returned if it is a failure.  The log file for the session is displayed in the 'Results' window.

6. Go to step 2 if you want to perform authorization for a different license/query pair.  Please note that the results will continue to get appended to the existing log file. If you only want to view the current results or if you want to conserve resources, delete the existing log file by clicking on the 'Clear Log' button.  Please note that this will not clear log files for the previous sessions.

PROGRAM EXECUTION FLOW:
=======================
1. The user selects a REL license file name and a query file name.

2. RELLicAuthzCEGUI calls the relAuthorizeRight function passing in the license file name and the query file name.

3. relAuthorizeRight loads the selected REL license file and the query file.

4. relAuthorizeRight calls validateRequest passing a licenseGroup, user, right and an array of resources.  This array can contain either a digitalResource or a diReference or one of each kind.  Any other combination of resources is unsupported at present.

5. validateRequest checks for unsupported items upon which it exits.

6. If no unsupported items are found, validateRequest loops through all the grants in all the licenses.  If at least one matching grant is found, it will return a positive result. Any conditions found are also returned.

7. If the call to validateRequest failed, the function RELAuthorizeRight exits.

8. If the call to validateRequest was successful, validateCondition will be called.

9. validateCondition loops through the conditions to find at least one that is satisfied.

10. If we meet at least one condition, it means that the specified user is allowed to exercise the right on the given resource.

11. The user is informed of the success/failure of the authorization.

12. The user can get further information from the log file 'AuthorizationSession.log' at the directory which contains the application.
   (if 'Log Authorization Session' option was selected).


QUERY FILE STRUCTURE:
=====================
A query file contains what we're querying for in a license. It contains four things:
	- The RSA modulus and exponent for a keyHolder principal
	- A right to be exercised 
	- A resource URI
	- A time to check against the validityInterval. This time represents the expected exercise time.
        - A count indicating the intended usage count for the right.

The query question asked would be:
        Can the <principal> exercise the <right> <count> times on the <resource> at <time>?  
This could be a question about the past, this is why we allow the user to pass in the reference time.

Note that this sample file is not REL syntax.

A sample query file is as follows:

<?xml version="1.0"?>
<query xmlns="http://www.contentguard.com/2002/exampleQueryNS">
	<goalToCheck>
		<principalToCheck rsaModulus="Fa7wo6NYfmvGqy4ACSWcNmuQfbejSZx7aCibIgkYswUeTCrmS0h27GJrA15SS7TYZzSfaS0xR9lZdUEF0ThO4w==" rsaExponent="AQABAA=="/>
		<rightToCheck>
			<cx:print xmlns:mx="urn:mpeg:mpeg21:2002:01-REL-NS"/>
		</rightToCheck>
		<resourceToCheck uri="http://www.contentguard.com/sampleBook.spd"/>
	</goalToCheck>
	<simulationExerciseEnvironment>
		<time>2001-12-23T01:30:00</time>
		<exerciseCountToCheck update="true">2</exerciseCountToCheck>
	</simulationExerciseEnvironment>
</query>

Please note:
--The query element "exerciseCountToCheck" indicating the intended usage count of the right is not mandatory.  It is defaulted to '1' if it is not present.
--The attribute "update" of the query element "exerciseCountToCheck" (if the element is present) is defaulted to "false" if not specified.


RELLicAuthzDriver PUBLIC API:
==============================
RELLicAuthzDriver exports one public API relAuthorizeRight. 
--This function takes int the REL license file and the XML query file as input.  It uses the functions in this module for parsing the input files, then calls the CRELLicAuthz module for validating the request and the condition.
--Parameters:
		TCHAR *tLicenseFileName		  ->the REL input license document
		TCHAR *tQueryFileName		  ->the XML query file
		TCHAR *tTimeToCheck			  ->the reference time to validate the conditions against
		bool bIssuerAndConditionPrint ->If true, the issuer and condition list will be logged
--The function returns the following HRESULT values:
	S_OK	if at least one matching grant was found and the conditions are satisfied
	S_FALSE if no matching grants were found and/or the conditions are not satisfied
	E_FAIL  if an error condition was encountered (an unsupported attribute for example).

--C/C++ Syntax:
	HRESULT relAuthorizeRight(
			TCHAR *tLicenseFileName, 
			TCHAR *tQueryFileName,
			bool bIssuerAndConditionPrint);


KNOWN LIMITATIONS:
==================
1. The following REL statements are not supported and will cause the program to exit:
	- xsi:type attributes types
	- licensePartIdRef attribute types
	- varRef attribute types

2. The only conditions supported are validityInterval and exerciseLimit. If an unsupported condition is encountered, the containing grant will be skipped.

Note:
-- The exerciseLimit condition validator needs the following in the license:
----The URI attribute of sx:exerciseLimit/serviceReference/sx:wsdlAddress/sx:kind/sx:wsdl/nonSecureIndirect should equal 'http://www.contentguard.com/schema/2003/05/cgwsdl.xml'
----The value of sx:exerciseLimit/serviceReference/sx:wsdlAddress/sx:kind/sx:binding should equal cgwsdl:dllBinding.
----The URI attribute of sx:exerciseLimit/serviceReference/sx:wsdlAddress/sx:address/digitalResource/nonSecureIndirect should be of the format: 'file:///<full or relative path of the local service dll>?stateId=<state reference id>'.  For example, the value could be 'file:///./RELExLimitService.dll?stateId=StateId1'.

--The State reference file needs to be initialized with the StateId in the license before we can validate the exercise limit condition.  Any calls to authorize before initialization will result in the corresponding grant to be skipped.

