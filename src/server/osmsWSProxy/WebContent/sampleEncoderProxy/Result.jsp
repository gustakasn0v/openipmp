<%@page contentType="text/html;charset=UTF-8"%><HTML>
<HEAD>
<TITLE>Result</TITLE>
</HEAD>
<BODY>
<H1>Result</H1>

<jsp:useBean id="sampleEncoderProxyid" scope="session" class="com.mutable.ws.EncoderProxy" />
<%
if (request.getParameter("endpoint") != null && request.getParameter("endpoint").length() > 0)
sampleEncoderProxyid.setEndpoint(request.getParameter("endpoint"));
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
        java.lang.String getEndpoint2mtemp = sampleEncoderProxyid.getEndpoint();
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
        sampleEncoderProxyid.setEndpoint(endpoint_0idTemp);
break;
case 10:
        gotMethod = true;
        com.mutable.ws.Encoder getEncoder10mtemp = sampleEncoderProxyid.getEncoder();
if(getEncoder10mtemp == null){
%>
<%=getEncoder10mtemp %>
<%
}else{
        if(getEncoder10mtemp!= null){
        String tempreturnp11 = getEncoder10mtemp.toString();
        %>
        <%=tempreturnp11%>
        <%
        }}
break;
case 13:
        gotMethod = true;
        String username_1id=  request.getParameter("username16");
        java.lang.String username_1idTemp  = username_1id;
        String password_2id=  request.getParameter("password18");
        java.lang.String password_2idTemp  = password_2id;
        String inFile_3id=  request.getParameter("inFile20");
        java.lang.String inFile_3idTemp  = inFile_3id;
        String outFile_4id=  request.getParameter("outFile22");
        java.lang.String outFile_4idTemp  = outFile_4id;
        int encode13mtemp = sampleEncoderProxyid.encode(username_1idTemp,password_2idTemp,inFile_3idTemp,outFile_4idTemp);
        String tempResultreturnp14 = org.eclipse.jst.ws.util.JspUtils.markup(String.valueOf(encode13mtemp));
        %>
        <%= tempResultreturnp14 %>
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