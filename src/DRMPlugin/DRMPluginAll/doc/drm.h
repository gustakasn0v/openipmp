/** \mainpage DRM plugin SDK

    Here we present DRM plugin SDK for protecting media content
    and playing protected media content.
    
    Basis of the DRM plugin SDK are the plugins independent of the
    media format. These plugins perform all the DRM related stuff. To
    support different media formats (currently supported are mpeg4 and mpeg2
    formats), there are additional plugins which handle specific format.
    
    For mpeg4 format, DRM plugin SDK implements standard defined protection,
    via mpeg4 DRM atoms which carry all necessary DRM informations. Basic
    DRM atom is an mpeg4 atom with "sinf" 4CC code, standing for (protection)
    scheme information atom. One can look at the mpeg4 documentation
    for further details on the protection architecture.
    
    For mpeg2 format, DRM plugin SDK implements standard defined protection,
    via IPMPX system. It is based on DRM informations being carried in IPMP
    control info structures, and messaging system which recognizes and
    connects DRM tools capable of handling specific protection scheme. One can
    look at the mpeg2 documentation for further details on the protection
    architecture.
    
    To integrate applications with DRM plugin SDK, one must implement certain
    interfaces required by the SDK. For mpeg4 support, one must implement all
    the interfaces given in IMPEG4DRMAtom.h. For mpeg2 support, one must
    implement all the interfaces given in IIPMPControlInfoPart.h, IIPMPDescriptor.h,
    IIPMPStreamDataUpdate.h, ISigCertContainer.h and IMPEG2IPMPXEncoder.h. It is
    expected that the implementations of these interfaces rely on an already
    existing architecture, so implementations should need only
    inherit-and-provide-members approach.
    
    One important part of the SDK usage is passing certain parameters to
    SDK routines. DRMLogger is used to log SDK activity and possible errors. It
    saves the log in DRMPlugin.log file in the runtime directory. One can look
    at the log file to see the messages. IXMLElement is used to pass specific
    information needed by the SDK. For the most part, these informations need
    not be kept secret, so they can reside in a configuration file (see
    <a href="EncoderInfo.xml">EncoderInfo</a> and
    <a href="PlayerInfo.xml">PlayerInfo</a>). Some informations though, need
    to be kept secret and thus keeping them in a configuration file could reveal
    them to an unauthorized user. These informations should be passed to the
    encoding/decoding applications via command line (or somehow else), and then
    added up in the IXMLElement via its interface function IXMLElement::AddChildElement.
    Typically, these are user name and password to access DRM server. These
    informations are needed by SDK plugins, as one can see in the documentation
    for a specific plugin.

    <h3><b>Sample code</b></h3>
    
    Usage of the DRM plugin SDK consists of two parts: encoding (protecting)
    media content and decoding (playing) protected media content. We provide
    basic usage explanations of the DRM plugin SDK in these two cases.
    
    For sample DRM encoder code (mpeg4 format), see \ref mpeg4drmencoder
    
    For sample DRM player code (mpeg4 format), see \ref mpeg4drmplayer

    For sample DRM encoder code (mpeg2 format), see \ref mpeg2drmencoder
    
    For sample DRM player code (mpeg2 format), see \ref mpeg2drmplayer

    <h3><b>Building and installing DRM plugin SDK</b></h3>

    On all platforms, one must first go to openipmp2/ext directory and unpack axis-c/axis-c.rar,
    Crypto++/Crypto++.rar, openssl/openssl.rar, srtp/srtp.rar and xerces/xerces.rar, to the same
    directories where these archives reside, including full paths contained in the archives.

    On windows platform, one can then build DRM plugin SDK either with Microsoft Visual
    Studio 6 or Microsoft Visual Studio .NET. In directory src/DRMPlugin/DRMPluginAll,
    there are DRMPluginAll.dsw (Visual Studio 6 workspace) and DRMPluginAll.sln
    (Visual Studio .NET solution). Use the DRMPluginAll project to build all the code for the SDK.
    After the build is completed, all libraries and headers are copied to
    src/DRMPlugin/DRMPluginAll/DRMPlugin directory. Headers are copied to
    include directory. DRMPluginAll.dsw copies all binaries to lib/win32/VC6/debug directory
    for Debug configuration and to lib/win32/VC6/release directory for Release configuration.
    DRMPluginAll.sln copies all binaries to lib/win32/VC7/debug directory for Debug
    configuration and to lib/win32/VC7/release directory for Release configuration. After
    that one can use the code to build and link his own applications.

    On linux platform, one needs aclocal, autoconf, automake and libtool tools to build
    DRM plugin SDK. Run src/DRMPlugin/autogen.sh script to create the makefiles. Then
    from src/DRMPlugin directory, run make sdk_install (needs root privileges).
    Installing copies the headers to /usr/local/include/DRMPlugin directory and
    the binaries to /usr/local/lib/DRMPlugin directory. After that one can use the code to
    build and link his own applications.
    To uninstall DRM plugin SDK, from src/DRMPlugin directory run make sdk_uninstall (needs root
    privileges).
    
    <h3><b>Necessary stuff for DRM protection</b></h3>

    DRM plugin SDK communicates with DRM server to get protection information, keys, handle users etc.
    Thus for DRM plugin SDK to work properly, one needs to install DRM server, or use one already
    installed. See DRM server documentation for details on building and installing it.<br>
    
    DRM plugin SDK authenticates users using p12 files, protected with user name and password.<br>
    To register a new user, go to the page "http://<IP>:<Port>/openipmp/jsp/login.jsp" and follow the
    link <em>REGISTER New User</em>, assuming that IP and Port are the IP address and port where
    DRM server is installed and running.<br>
    Registered user can get a p12 file via the same page. Login with the user name and password,
    follow the <em>Keystore</em> link and save the p12 file to a desired directory.<br>
    
    For OMA DRM support, additional files are needed. Because of OMA DRM requirements, one needs
    certificate files for authentication and identification. Thus to use OMA DRM, one must have his
    own X509 certificate file and a CA X509 certificate file, both DER encoded. Also, one must
    have his own DER encoded PKCS8 private key file. All these files can be created using for
    example openssl.<br>

    
    
*/
