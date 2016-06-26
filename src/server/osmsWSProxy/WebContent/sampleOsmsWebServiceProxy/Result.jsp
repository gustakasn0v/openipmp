<%@page contentType="text/html;charset=UTF-8"%><HTML>
<HEAD>
<TITLE>Result</TITLE>
</HEAD>
<BODY>
<H1>Result</H1>

<jsp:useBean id="sampleOsmsWebServiceProxyid" scope="session" class="com.mutable.osms.server.ws.OsmsWebServiceProxy" />
<%
if (request.getParameter("endpoint") != null && request.getParameter("endpoint").length() > 0)
sampleOsmsWebServiceProxyid.setEndpoint(request.getParameter("endpoint"));
%>

<%
String method = request.getParameter("method");
int methodID = 0;
if (method == null) methodID = -1;

if(methodID != -1) methodID = Integer.parseInt(method);
boolean gotMethod = false;

try {
switch (methodID){ 
case 2:
        gotMethod = true;
        java.lang.String getEndpoint2mtemp = sampleOsmsWebServiceProxyid.getEndpoint();
if(getEndpoint2mtemp == null){
%>
<%=getEndpoint2mtemp %>
<%
}else{
        String tempResultreturnp3 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(getEndpoint2mtemp));
        %>
        <%= tempResultreturnp3 %>
        <%
}
break;
case 5:
        gotMethod = true;
        String endpoint_0id=  request.getParameter("endpoint8");
        java.lang.String endpoint_0idTemp  = endpoint_0id;
        sampleOsmsWebServiceProxyid.setEndpoint(endpoint_0idTemp);
break;
case 10:
        gotMethod = true;
        com.mutable.osms.server.ws.OsmsWebService getOsmsWebService10mtemp = sampleOsmsWebServiceProxyid.getOsmsWebService();
if(getOsmsWebService10mtemp == null){
%>
<%=getOsmsWebService10mtemp %>
<%
}else{
        if(getOsmsWebService10mtemp!= null){
        String tempreturnp11 = getOsmsWebService10mtemp.toString();
        %>
        <%=tempreturnp11%>
        <%
        }}
break;
case 13:
        gotMethod = true;
        String type_2id=  request.getParameter("type24");
        java.lang.String type_2idTemp  = type_2id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsQueryRequest_1id" scope="session" class="com.mutable.osms.server.ws.message.OsmsQueryRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsQueryRequest_1id.setType(type_2idTemp);
        com.mutable.osms.server.ws.message.OsmsQueryResponse query13mtemp = sampleOsmsWebServiceProxyid.query(com1mutable1osms1server1ws1message1OsmsQueryRequest_1id);
if(query13mtemp == null){
%>
<%=query13mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">results:</TD>
<TD>
<%
if(query13mtemp != null){
java.lang.String typeresults16 = query13mtemp.getResults();
        String tempResultresults16 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeresults16));
        %>
        <%= tempResultresults16 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">length:</TD>
<TD>
<%
if(query13mtemp != null){
%>
<%=query13mtemp.getLength()
%><%}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">heading:</TD>
<TD>
<%
if(query13mtemp != null){
java.lang.String typeheading20 = query13mtemp.getHeading();
        String tempResultheading20 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeheading20));
        %>
        <%= tempResultheading20 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 26:
        gotMethod = true;
        String rightsInfo_4id=  request.getParameter("rightsInfo33");
        java.lang.String rightsInfo_4idTemp  = rightsInfo_4id;
        String contentId_5id=  request.getParameter("contentId35");
        java.lang.String contentId_5idTemp  = contentId_5id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsLicenseRequest_3id" scope="session" class="com.mutable.osms.server.ws.message.OsmsLicenseRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsLicenseRequest_3id.setRightsInfo(rightsInfo_4idTemp);
        com1mutable1osms1server1ws1message1OsmsLicenseRequest_3id.setContentId(contentId_5idTemp);
        com.mutable.osms.server.ws.message.OsmsLicenseResponse license26mtemp = sampleOsmsWebServiceProxyid.license(com1mutable1osms1server1ws1message1OsmsLicenseRequest_3id);
if(license26mtemp == null){
%>
<%=license26mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">license:</TD>
<TD>
<%
if(license26mtemp != null){
java.lang.String typelicense29 = license26mtemp.getLicense();
        String tempResultlicense29 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typelicense29));
        %>
        <%= tempResultlicense29 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 37:
        gotMethod = true;
        String password_7id=  request.getParameter("password44");
        java.lang.String password_7idTemp  = password_7id;
        String userName_8id=  request.getParameter("userName46");
        java.lang.String userName_8idTemp  = userName_8id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsUserLoginRequest_6id" scope="session" class="com.mutable.osms.server.ws.message.OsmsUserLoginRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsUserLoginRequest_6id.setPassword(password_7idTemp);
        com1mutable1osms1server1ws1message1OsmsUserLoginRequest_6id.setUserName(userName_8idTemp);
        com.mutable.osms.server.ws.message.OsmsUserLoginResponse userLogin37mtemp = sampleOsmsWebServiceProxyid.userLogin(com1mutable1osms1server1ws1message1OsmsUserLoginRequest_6id);
if(userLogin37mtemp == null){
%>
<%=userLogin37mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">responseString:</TD>
<TD>
<%
if(userLogin37mtemp != null){
java.lang.String typeresponseString40 = userLogin37mtemp.getResponseString();
        String tempResultresponseString40 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeresponseString40));
        %>
        <%= tempResultresponseString40 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 48:
        gotMethod = true;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsUserLogoutRequest_9id" scope="session" class="com.mutable.osms.server.ws.message.OsmsUserLogoutRequest" />
        <%
        com.mutable.osms.server.ws.message.OsmsUserLogoutResponse userLogout48mtemp = sampleOsmsWebServiceProxyid.userLogout(com1mutable1osms1server1ws1message1OsmsUserLogoutRequest_9id);
if(userLogout48mtemp == null){
%>
<%=userLogout48mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">responseString:</TD>
<TD>
<%
if(userLogout48mtemp != null){
java.lang.String typeresponseString51 = userLogout48mtemp.getResponseString();
        String tempResultresponseString51 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeresponseString51));
        %>
        <%= tempResultresponseString51 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 55:
        gotMethod = true;
        String organizationName_11id=  request.getParameter("organizationName62");
        java.lang.String organizationName_11idTemp  = organizationName_11id;
        String addressLine3_12id=  request.getParameter("addressLine364");
        java.lang.String addressLine3_12idTemp  = addressLine3_12id;
        String firstName_13id=  request.getParameter("firstName66");
        java.lang.String firstName_13idTemp  = firstName_13id;
        String addressLine2_14id=  request.getParameter("addressLine268");
        java.lang.String addressLine2_14idTemp  = addressLine2_14id;
        String password_15id=  request.getParameter("password70");
        java.lang.String password_15idTemp  = password_15id;
        String addressLine1_16id=  request.getParameter("addressLine172");
        java.lang.String addressLine1_16idTemp  = addressLine1_16id;
        String suffix_17id=  request.getParameter("suffix74");
        java.lang.String suffix_17idTemp  = suffix_17id;
        String secretQuestion_18id=  request.getParameter("secretQuestion76");
        java.lang.String secretQuestion_18idTemp  = secretQuestion_18id;
        String emailAddress_19id=  request.getParameter("emailAddress78");
        java.lang.String emailAddress_19idTemp  = emailAddress_19id;
        String state_20id=  request.getParameter("state80");
        java.lang.String state_20idTemp  = state_20id;
        String zipCode_21id=  request.getParameter("zipCode82");
        java.lang.String zipCode_21idTemp  = zipCode_21id;
        String faxPhoneNumber_22id=  request.getParameter("faxPhoneNumber84");
        java.lang.String faxPhoneNumber_22idTemp  = faxPhoneNumber_22id;
        String userName_23id=  request.getParameter("userName86");
        java.lang.String userName_23idTemp  = userName_23id;
        String salutation_24id=  request.getParameter("salutation88");
        java.lang.String salutation_24idTemp  = salutation_24id;
        String mainPhoneNumber_25id=  request.getParameter("mainPhoneNumber90");
        java.lang.String mainPhoneNumber_25idTemp  = mainPhoneNumber_25id;
        String organizationUnit_26id=  request.getParameter("organizationUnit92");
        java.lang.String organizationUnit_26idTemp  = organizationUnit_26id;
        String lastName_27id=  request.getParameter("lastName94");
        java.lang.String lastName_27idTemp  = lastName_27id;
        String country_28id=  request.getParameter("country96");
        java.lang.String country_28idTemp  = country_28id;
        String altPhoneNumber_29id=  request.getParameter("altPhoneNumber98");
        java.lang.String altPhoneNumber_29idTemp  = altPhoneNumber_29id;
        String city_30id=  request.getParameter("city100");
        java.lang.String city_30idTemp  = city_30id;
        String secretAnswer_31id=  request.getParameter("secretAnswer102");
        java.lang.String secretAnswer_31idTemp  = secretAnswer_31id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id" scope="session" class="com.mutable.osms.server.ws.message.OsmsCreateUserRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setOrganizationName(organizationName_11idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setAddressLine3(addressLine3_12idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setFirstName(firstName_13idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setAddressLine2(addressLine2_14idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setPassword(password_15idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setAddressLine1(addressLine1_16idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setSuffix(suffix_17idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setSecretQuestion(secretQuestion_18idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setEmailAddress(emailAddress_19idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setState(state_20idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setZipCode(zipCode_21idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setFaxPhoneNumber(faxPhoneNumber_22idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setUserName(userName_23idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setSalutation(salutation_24idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setMainPhoneNumber(mainPhoneNumber_25idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setOrganizationUnit(organizationUnit_26idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setLastName(lastName_27idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setCountry(country_28idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setAltPhoneNumber(altPhoneNumber_29idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setCity(city_30idTemp);
        com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id.setSecretAnswer(secretAnswer_31idTemp);
        com.mutable.osms.server.ws.message.OsmsCreateUserResponse createUser55mtemp = sampleOsmsWebServiceProxyid.createUser(com1mutable1osms1server1ws1message1OsmsCreateUserRequest_10id);
if(createUser55mtemp == null){
%>
<%=createUser55mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">responseString:</TD>
<TD>
<%
if(createUser55mtemp != null){
java.lang.String typeresponseString58 = createUser55mtemp.getResponseString();
        String tempResultresponseString58 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeresponseString58));
        %>
        <%= tempResultresponseString58 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 104:
        gotMethod = true;
        String metadataType_33id=  request.getParameter("metadataType113");
        java.lang.String metadataType_33idTemp  = metadataType_33id;
        String digitalItemInstanceId_34id=  request.getParameter("digitalItemInstanceId115");
        java.lang.String digitalItemInstanceId_34idTemp  = digitalItemInstanceId_34id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsGetContentKeyRequest_32id" scope="session" class="com.mutable.osms.server.ws.message.OsmsGetContentKeyRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsGetContentKeyRequest_32id.setMetadataType(metadataType_33idTemp);
        com1mutable1osms1server1ws1message1OsmsGetContentKeyRequest_32id.setDigitalItemInstanceId(digitalItemInstanceId_34idTemp);
        com.mutable.osms.server.ws.message.OsmsGetContentKeyResponse getContentKey104mtemp = sampleOsmsWebServiceProxyid.getContentKey(com1mutable1osms1server1ws1message1OsmsGetContentKeyRequest_32id);
if(getContentKey104mtemp == null){
%>
<%=getContentKey104mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">auxDataXml:</TD>
<TD>
<%
if(getContentKey104mtemp != null){
java.lang.String typeauxDataXml107 = getContentKey104mtemp.getAuxDataXml();
        String tempResultauxDataXml107 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeauxDataXml107));
        %>
        <%= tempResultauxDataXml107 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">keyXml:</TD>
<TD>
<%
if(getContentKey104mtemp != null){
java.lang.String typekeyXml109 = getContentKey104mtemp.getKeyXml();
        String tempResultkeyXml109 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typekeyXml109));
        %>
        <%= tempResultkeyXml109 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 117:
        gotMethod = true;
        String metadataType_36id=  request.getParameter("metadataType126");
        java.lang.String metadataType_36idTemp  = metadataType_36id;
        String metadataXml_37id=  request.getParameter("metadataXml128");
        java.lang.String metadataXml_37idTemp  = metadataXml_37id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsRegisterContentAssignIdentifierRequest_35id" scope="session" class="com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsRegisterContentAssignIdentifierRequest_35id.setMetadataType(metadataType_36idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterContentAssignIdentifierRequest_35id.setMetadataXml(metadataXml_37idTemp);
        com.mutable.osms.server.ws.message.OsmsRegisterContentAssignIdentifierResponse registerContentAssignIdentifier117mtemp = sampleOsmsWebServiceProxyid.registerContentAssignIdentifier(com1mutable1osms1server1ws1message1OsmsRegisterContentAssignIdentifierRequest_35id);
if(registerContentAssignIdentifier117mtemp == null){
%>
<%=registerContentAssignIdentifier117mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">metadataType:</TD>
<TD>
<%
if(registerContentAssignIdentifier117mtemp != null){
java.lang.String typemetadataType120 = registerContentAssignIdentifier117mtemp.getMetadataType();
        String tempResultmetadataType120 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typemetadataType120));
        %>
        <%= tempResultmetadataType120 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">metadataXml:</TD>
<TD>
<%
if(registerContentAssignIdentifier117mtemp != null){
java.lang.String typemetadataXml122 = registerContentAssignIdentifier117mtemp.getMetadataXml();
        String tempResultmetadataXml122 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typemetadataXml122));
        %>
        <%= tempResultmetadataXml122 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 130:
        gotMethod = true;
        String metadataType_39id=  request.getParameter("metadataType137");
        java.lang.String metadataType_39idTemp  = metadataType_39id;
        String metadataXml_40id=  request.getParameter("metadataXml139");
        java.lang.String metadataXml_40idTemp  = metadataXml_40id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsRegisterContentExistingIdentifierRequest_38id" scope="session" class="com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsRegisterContentExistingIdentifierRequest_38id.setMetadataType(metadataType_39idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterContentExistingIdentifierRequest_38id.setMetadataXml(metadataXml_40idTemp);
        com.mutable.osms.server.ws.message.OsmsRegisterContentExistingIdentifierResponse registerContentExistingIdentifier130mtemp = sampleOsmsWebServiceProxyid.registerContentExistingIdentifier(com1mutable1osms1server1ws1message1OsmsRegisterContentExistingIdentifierRequest_38id);
if(registerContentExistingIdentifier130mtemp == null){
%>
<%=registerContentExistingIdentifier130mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">responseString:</TD>
<TD>
<%
if(registerContentExistingIdentifier130mtemp != null){
java.lang.String typeresponseString133 = registerContentExistingIdentifier130mtemp.getResponseString();
        String tempResultresponseString133 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeresponseString133));
        %>
        <%= tempResultresponseString133 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 141:
        gotMethod = true;
        String metadataType_42id=  request.getParameter("metadataType154");
        java.lang.String metadataType_42idTemp  = metadataType_42id;
        String auxDataXml_43id=  request.getParameter("auxDataXml156");
        java.lang.String auxDataXml_43idTemp  = auxDataXml_43id;
        String keyXml_44id=  request.getParameter("keyXml158");
        java.lang.String keyXml_44idTemp  = keyXml_44id;
        String metadataXml_45id=  request.getParameter("metadataXml160");
        java.lang.String metadataXml_45idTemp  = metadataXml_45id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id" scope="session" class="com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id.setMetadataType(metadataType_42idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id.setAuxDataXml(auxDataXml_43idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id.setKeyXml(keyXml_44idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id.setMetadataXml(metadataXml_45idTemp);
        com.mutable.osms.server.ws.message.OsmsRegisterDigitalItemInstanceResponse registerDigitalItemInstance141mtemp = sampleOsmsWebServiceProxyid.registerDigitalItemInstance(com1mutable1osms1server1ws1message1OsmsRegisterDigitalItemInstanceRequest_41id);
if(registerDigitalItemInstance141mtemp == null){
%>
<%=registerDigitalItemInstance141mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">metadataType:</TD>
<TD>
<%
if(registerDigitalItemInstance141mtemp != null){
java.lang.String typemetadataType144 = registerDigitalItemInstance141mtemp.getMetadataType();
        String tempResultmetadataType144 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typemetadataType144));
        %>
        <%= tempResultmetadataType144 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">signatureXml:</TD>
<TD>
<%
if(registerDigitalItemInstance141mtemp != null){
java.lang.String typesignatureXml146 = registerDigitalItemInstance141mtemp.getSignatureXml();
        String tempResultsignatureXml146 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typesignatureXml146));
        %>
        <%= tempResultsignatureXml146 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">auxDataXml:</TD>
<TD>
<%
if(registerDigitalItemInstance141mtemp != null){
java.lang.String typeauxDataXml148 = registerDigitalItemInstance141mtemp.getAuxDataXml();
        String tempResultauxDataXml148 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeauxDataXml148));
        %>
        <%= tempResultauxDataXml148 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">metadataXml:</TD>
<TD>
<%
if(registerDigitalItemInstance141mtemp != null){
java.lang.String typemetadataXml150 = registerDigitalItemInstance141mtemp.getMetadataXml();
        String tempResultmetadataXml150 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typemetadataXml150));
        %>
        <%= tempResultmetadataXml150 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 162:
        gotMethod = true;
        String password_47id=  request.getParameter("password171");
        java.lang.String password_47idTemp  = password_47id;
        String passwordConfirm_48id=  request.getParameter("passwordConfirm173");
        java.lang.String passwordConfirm_48idTemp  = passwordConfirm_48id;
        String userName_49id=  request.getParameter("userName175");
        java.lang.String userName_49idTemp  = userName_49id;
        String emailAddress_50id=  request.getParameter("emailAddress177");
        java.lang.String emailAddress_50idTemp  = emailAddress_50id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id" scope="session" class="com.mutable.osms.server.ws.message.OsmsRegisterUserRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id.setPassword(password_47idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id.setPasswordConfirm(passwordConfirm_48idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id.setUserName(userName_49idTemp);
        com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id.setEmailAddress(emailAddress_50idTemp);
        com.mutable.osms.server.ws.message.OsmsRegisterUserResponse registerUser162mtemp = sampleOsmsWebServiceProxyid.registerUser(com1mutable1osms1server1ws1message1OsmsRegisterUserRequest_46id);
if(registerUser162mtemp == null){
%>
<%=registerUser162mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">userSecurityStore:</TD>
<TD>
<%
if(registerUser162mtemp != null){
byte[] typeuserSecurityStore165 = registerUser162mtemp.getUserSecurityStore();
        String tempuserSecurityStore165 = "[";        for(int iuserSecurityStore165=0;iuserSecurityStore165< typeuserSecurityStore165.length;iuserSecurityStore165++){
            tempuserSecurityStore165 = tempuserSecurityStore165 + typeuserSecurityStore165[iuserSecurityStore165] + ",";
        }
        int lengthuserSecurityStore165 = tempuserSecurityStore165.length();
        tempuserSecurityStore165 = tempuserSecurityStore165.substring(0,(lengthuserSecurityStore165 - 1)) + "]";
        %>
        <%=tempuserSecurityStore165%>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">userName:</TD>
<TD>
<%
if(registerUser162mtemp != null){
java.lang.String typeuserName167 = registerUser162mtemp.getUserName();
        String tempResultuserName167 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeuserName167));
        %>
        <%= tempResultuserName167 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 179:
        gotMethod = true;
        String startDate_52id=  request.getParameter("startDate186");
        java.text.DateFormat dateFormatstartDate186 = java.text.DateFormat.getDateInstance();
        java.util.Date dateTempstartDate186  = dateFormatstartDate186.parse(startDate_52id);
        java.util.GregorianCalendar startDate_52idTemp = new java.util.GregorianCalendar();
        startDate_52idTemp.setTime(dateTempstartDate186);
        String licenseType_53id=  request.getParameter("licenseType188");
        java.lang.String licenseType_53idTemp  = licenseType_53id;
        String userName_54id=  request.getParameter("userName190");
        java.lang.String userName_54idTemp  = userName_54id;
        String endDate_55id=  request.getParameter("endDate192");
        java.text.DateFormat dateFormatendDate192 = java.text.DateFormat.getDateInstance();
        java.util.Date dateTempendDate192  = dateFormatendDate192.parse(endDate_55id);
        java.util.GregorianCalendar endDate_55idTemp = new java.util.GregorianCalendar();
        endDate_55idTemp.setTime(dateTempendDate192);
        String contentId_56id=  request.getParameter("contentId194");
        java.lang.String contentId_56idTemp  = contentId_56id;
        %>
        <jsp:useBean id="com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id" scope="session" class="com.mutable.osms.server.ws.message.OsmsRightsAuthorizationRequest" />
        <%
        com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id.setStartDate(startDate_52idTemp);
        com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id.setLicenseType(licenseType_53idTemp);
        com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id.setUserName(userName_54idTemp);
        com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id.setEndDate(endDate_55idTemp);
        com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id.setContentId(contentId_56idTemp);
        com.mutable.osms.server.ws.message.OsmsRightsAuthorizationResponse rightsAuthorization179mtemp = sampleOsmsWebServiceProxyid.rightsAuthorization(com1mutable1osms1server1ws1message1OsmsRightsAuthorizationRequest_51id);
if(rightsAuthorization179mtemp == null){
%>
<%=rightsAuthorization179mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">transactionId:</TD>
<TD>
<%
if(rightsAuthorization179mtemp != null){
java.lang.String typetransactionId182 = rightsAuthorization179mtemp.getTransactionId();
        String tempResulttransactionId182 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typetransactionId182));
        %>
        <%= tempResulttransactionId182 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
}
} catch (Exception e) { 
%>
exception: <%= e %>
<%
return;
}
if(!gotMethod){
%>
result: N/A
<%
}
%>
</BODY>
</HTML>