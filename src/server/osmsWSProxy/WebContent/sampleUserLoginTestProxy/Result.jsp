<%@page contentType="text/html;charset=UTF-8"%><HTML>
<HEAD>
<TITLE>Result</TITLE>
</HEAD>
<BODY>
<H1>Result</H1>

<jsp:useBean id="sampleUserLoginTestProxyid" scope="session" class="com.mutable.ws.UserLoginTestProxy" />
<%
if (request.getParameter("endpoint") != null && request.getParameter("endpoint").length() > 0)
sampleUserLoginTestProxyid.setEndpoint(request.getParameter("endpoint"));
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
        java.lang.String getEndpoint2mtemp = sampleUserLoginTestProxyid.getEndpoint();
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
        sampleUserLoginTestProxyid.setEndpoint(endpoint_0idTemp);
break;
case 10:
        gotMethod = true;
        com.mutable.ws.UserLoginTest getUserLoginTest10mtemp = sampleUserLoginTestProxyid.getUserLoginTest();
if(getUserLoginTest10mtemp == null){
%>
<%=getUserLoginTest10mtemp %>
<%
}else{
        if(getUserLoginTest10mtemp!= null){
        String tempreturnp11 = getUserLoginTest10mtemp.toString();
        %>
        <%=tempreturnp11%>
        <%
        }}
break;
case 13:
        gotMethod = true;
        String userName_1id=  request.getParameter("userName16");
        java.lang.String userName_1idTemp  = userName_1id;
        String password_2id=  request.getParameter("password18");
        java.lang.String password_2idTemp  = password_2id;
        java.lang.String login13mtemp = sampleUserLoginTestProxyid.login(userName_1idTemp,password_2idTemp);
if(login13mtemp == null){
%>
<%=login13mtemp %>
<%
}else{
        String tempResultreturnp14 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(login13mtemp));
        %>
        <%= tempResultreturnp14 %>
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