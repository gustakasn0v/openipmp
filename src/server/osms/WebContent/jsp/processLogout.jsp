<%@ page import = "com.mutable.osmsOnline.server.Global" %>  

<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/> 
<jsp:useBean id="reqMsg" class="com.mutable.osms.common.io.message.osmsMessageUserLogoutRequest"   scope="page"/> 
<jsp:useBean id="prc"    class="com.mutable.osmsOnline.server.app.ProcessMessageUserLogoutRequest" scope="page"/>  	

<% String error = prc.process(reqMsg,user); %>
<% session.invalidate(); %>

<jsp:forward page="login.jsp" > 	
	<jsp:param name="date" value="<%= Global.getTime() %>" /> 
	<jsp:param name="errorMessage" value="<%=error%>" />
</jsp:forward>   