<%@page contentType="text/html;charset=UTF-8"%><HTML>
<HEAD>
<TITLE>Result</TITLE>
</HEAD>
<BODY>
<H1>Result</H1>

<jsp:useBean id="sampleOpenIPMPWSProxyid" scope="session" class="com.mutable.osms.server.app.service.OpenIPMPWSProxy" />
<%
if (request.getParameter("endpoint") != null && request.getParameter("endpoint").length() > 0)
sampleOpenIPMPWSProxyid.setEndpoint(request.getParameter("endpoint"));
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
        java.lang.String getEndpoint2mtemp = sampleOpenIPMPWSProxyid.getEndpoint();
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
        sampleOpenIPMPWSProxyid.setEndpoint(endpoint_0idTemp);
break;
case 10:
        gotMethod = true;
        com.mutable.osms.server.app.service.OpenIPMPWS getOpenIPMPWS10mtemp = sampleOpenIPMPWSProxyid.getOpenIPMPWS();
if(getOpenIPMPWS10mtemp == null){
%>
<%=getOpenIPMPWS10mtemp %>
<%
}else{
        if(getOpenIPMPWS10mtemp!= null){
        String tempreturnp11 = getOpenIPMPWS10mtemp.toString();
        %>
        <%=tempreturnp11%>
        <%
        }}
break;
case 13:
        gotMethod = true;
        sampleOpenIPMPWSProxyid.ping();
break;
case 16:
        gotMethod = true;
        String userName_1id=  request.getParameter("userName19");
        java.lang.String userName_1idTemp  = userName_1id;
        String passwd_2id=  request.getParameter("passwd21");
        java.lang.String passwd_2idTemp  = passwd_2id;
        int login16mtemp = sampleOpenIPMPWSProxyid.login(userName_1idTemp,passwd_2idTemp);
        String tempResultreturnp17 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(login16mtemp));
        %>
        <%= tempResultreturnp17 %>
        <%
break;
case 23:
        gotMethod = true;
        String agentUserName_3id=  request.getParameter("agentUserName26");
        java.lang.String agentUserName_3idTemp  = agentUserName_3id;
        String agentPassword_4id=  request.getParameter("agentPassword28");
        java.lang.String agentPassword_4idTemp  = agentPassword_4id;
        String sourceFileURL_5id=  request.getParameter("sourceFileURL30");
        java.lang.String sourceFileURL_5idTemp  = sourceFileURL_5id;
        String destinationFileURL_6id=  request.getParameter("destinationFileURL32");
        java.lang.String destinationFileURL_6idTemp  = destinationFileURL_6id;
        String contentOwnerAppId_7id=  request.getParameter("contentOwnerAppId34");
        java.lang.String contentOwnerAppId_7idTemp  = contentOwnerAppId_7id;
        String contentOwnerUserId_8id=  request.getParameter("contentOwnerUserId36");
        java.lang.String contentOwnerUserId_8idTemp  = contentOwnerUserId_8id;
        String transactionID_9id=  request.getParameter("transactionID38");
        java.lang.String transactionID_9idTemp  = transactionID_9id;
        String validityStartDate_10id=  request.getParameter("validityStartDate40");
        java.lang.String validityStartDate_10idTemp  = validityStartDate_10id;
        String validityEndDate_11id=  request.getParameter("validityEndDate42");
        java.lang.String validityEndDate_11idTemp  = validityEndDate_11id;
        String validityDays_12id=  request.getParameter("validityDays44");
        int validityDays_12idTemp  = Integer.parseInt(validityDays_12id);
        String validityPlaycount_13id=  request.getParameter("validityPlaycount46");
        int validityPlaycount_13idTemp  = Integer.parseInt(validityPlaycount_13id);
        String grantUser_14id=  request.getParameter("grantUser48");
        java.lang.String grantUser_14idTemp  = grantUser_14id;
        int packageSecureContentWithParamsForSingleUser23mtemp = sampleOpenIPMPWSProxyid.packageSecureContentWithParamsForSingleUser(agentUserName_3idTemp,agentPassword_4idTemp,sourceFileURL_5idTemp,destinationFileURL_6idTemp,contentOwnerAppId_7idTemp,contentOwnerUserId_8idTemp,transactionID_9idTemp,validityStartDate_10idTemp,validityEndDate_11idTemp,validityDays_12idTemp,validityPlaycount_13idTemp,grantUser_14idTemp);
        String tempResultreturnp24 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(packageSecureContentWithParamsForSingleUser23mtemp));
        %>
        <%= tempResultreturnp24 %>
        <%
break;
case 50:
        gotMethod = true;
        String agentUserName_15id=  request.getParameter("agentUserName53");
        java.lang.String agentUserName_15idTemp  = agentUserName_15id;
        String agentPassword_16id=  request.getParameter("agentPassword55");
        java.lang.String agentPassword_16idTemp  = agentPassword_16id;
        String contentOwnerAppId_17id=  request.getParameter("contentOwnerAppId57");
        java.lang.String contentOwnerAppId_17idTemp  = contentOwnerAppId_17id;
        String contentOwnerUserId_18id=  request.getParameter("contentOwnerUserId59");
        java.lang.String contentOwnerUserId_18idTemp  = contentOwnerUserId_18id;
        String transactionID_19id=  request.getParameter("transactionID61");
        java.lang.String transactionID_19idTemp  = transactionID_19id;
        String mpegREL_20id=  request.getParameter("mpegREL63");
        java.lang.String mpegREL_20idTemp  = mpegREL_20id;
        int packageSecureContentWithMPEG_REL50mtemp = sampleOpenIPMPWSProxyid.packageSecureContentWithMPEG_REL(agentUserName_15idTemp,agentPassword_16idTemp,contentOwnerAppId_17idTemp,contentOwnerUserId_18idTemp,transactionID_19idTemp,mpegREL_20idTemp);
        String tempResultreturnp51 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(packageSecureContentWithMPEG_REL50mtemp));
        %>
        <%= tempResultreturnp51 %>
        <%
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