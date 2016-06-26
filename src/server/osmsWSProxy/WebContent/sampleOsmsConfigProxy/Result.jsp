<%@page contentType="text/html;charset=UTF-8"%><HTML>
<HEAD>
<TITLE>Result</TITLE>
</HEAD>
<BODY>
<H1>Result</H1>

<jsp:useBean id="sampleOsmsConfigProxyid" scope="session" class="com.mutable.ws.OsmsConfigProxy" />
<%
if (request.getParameter("endpoint") != null && request.getParameter("endpoint").length() > 0)
sampleOsmsConfigProxyid.setEndpoint(request.getParameter("endpoint"));
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
        java.lang.String getEndpoint2mtemp = sampleOsmsConfigProxyid.getEndpoint();
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
        sampleOsmsConfigProxyid.setEndpoint(endpoint_0idTemp);
break;
case 10:
        gotMethod = true;
        com.mutable.ws.OsmsConfig getOsmsConfig10mtemp = sampleOsmsConfigProxyid.getOsmsConfig();
if(getOsmsConfig10mtemp == null){
%>
<%=getOsmsConfig10mtemp %>
<%
}else{
%>
<TABLE>
<TR>
<TD COLSPAN="3" ALIGN="LEFT">returnp:</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">rightsHostUrl:</TD>
<TD>
<%
if(getOsmsConfig10mtemp != null){
java.lang.String typerightsHostUrl13 = getOsmsConfig10mtemp.getRightsHostUrl();
        String tempResultrightsHostUrl13 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typerightsHostUrl13));
        %>
        <%= tempResultrightsHostUrl13 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">rightsHostPort:</TD>
<TD>
<%
if(getOsmsConfig10mtemp != null){
java.lang.String typerightsHostPort15 = getOsmsConfig10mtemp.getRightsHostPort();
        String tempResultrightsHostPort15 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typerightsHostPort15));
        %>
        <%= tempResultrightsHostPort15 %>
        <%
}%>
</TD>
<TR>
<TD WIDTH="5%"></TD>
<TD COLSPAN="2" ALIGN="LEFT">serverPort:</TD>
<TD>
<%
if(getOsmsConfig10mtemp != null){
java.lang.String typeserverPort17 = getOsmsConfig10mtemp.getServerPort();
        String tempResultserverPort17 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(typeserverPort17));
        %>
        <%= tempResultserverPort17 %>
        <%
}%>
</TD>
</TABLE>
<%
}
break;
case 19:
        gotMethod = true;
        java.lang.String getServerPort19mtemp = sampleOsmsConfigProxyid.getServerPort();
if(getServerPort19mtemp == null){
%>
<%=getServerPort19mtemp %>
<%
}else{
        String tempResultreturnp20 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(getServerPort19mtemp));
        %>
        <%= tempResultreturnp20 %>
        <%
}
break;
case 22:
        gotMethod = true;
        java.lang.String getRightsHostPort22mtemp = sampleOsmsConfigProxyid.getRightsHostPort();
if(getRightsHostPort22mtemp == null){
%>
<%=getRightsHostPort22mtemp %>
<%
}else{
        String tempResultreturnp23 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(getRightsHostPort22mtemp));
        %>
        <%= tempResultreturnp23 %>
        <%
}
break;
case 25:
        gotMethod = true;
        java.lang.String getRightsHostUrl25mtemp = sampleOsmsConfigProxyid.getRightsHostUrl();
if(getRightsHostUrl25mtemp == null){
%>
<%=getRightsHostUrl25mtemp %>
<%
}else{
        String tempResultreturnp26 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(getRightsHostUrl25mtemp));
        %>
        <%= tempResultreturnp26 %>
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