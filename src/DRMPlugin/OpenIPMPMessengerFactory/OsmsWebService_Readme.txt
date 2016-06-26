C++ Client OsmsWebService Readme
================================

Project OsmsWebService has the following external dependency:
    openipmp2\ext\axis-c-1-5-win32
    (Axis C++ version 1.5 and Xerces 2.2.0 DLLs)

To build OsmsWebService.lib static library openipmp2\ext\axis-c-1-5-win32\include
has to be used as an additional include directory.

When using OsmsWebService.lib, it is also necessary to link 
AxisClient.lib located in openipmp2\ext\axis-c-1-5-win32\lib.

In runtime, openipmp2\ext\axis-c-1-5-win32\bin has to be put
in the system environment variable PATH, i.e.
SET PATH=%PATH%;D:\swordfish\openipmp2\ext\axis-c-1-5-win32\bin

Remarks:
-------

1.]
Dinamic library xerces-c_2_2_0.dll is needed for axis-c-1-5-win32 
(version 1.5). Axis C++ version 1.6 (to be released soon) will use
xerces-c_2_6_0.dll.

2.]
To avoid Axis warning "The configuration file was not found (/axiscpp.conf)."
file axiscpp.conf (located in openipmp2\ext\axis-c-1-5-win32\bin) 
has to be put in the root directory.

3.]
There is a problem with deserialization in Axis C++ API when receiving Java WS server responses containing href/multiref.

Solution #1: Disable href/multiref in Axis Java on the server.
server-config.wsdd: <parameter name="sendMultiRefs" value="false"/>

Solution #2: The href/multiref error is due to rpc encoded WS style.
             WS-I recommends doc/lit. Switching to doc/lit should
             solve the problem as it does not support multiref.
