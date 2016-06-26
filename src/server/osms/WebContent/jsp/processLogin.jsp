<%@ page import = "com.mutable.osmsOnline.server.Global" %>

<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/>
<jsp:useBean id="reqMsg" class="com.mutable.osms.common.io.message.osmsMessageUserLoginRequest"   scope="page"/>
<jsp:useBean id="prc"    class="com.mutable.osmsOnline.server.app.ProcessMessageUserLoginRequest" scope="page"/>
<jsp:setProperty name="reqMsg" property="*"/>

<% String error = prc.process(reqMsg,user);%>

<% if (!user.isLoggedIn() ){ %>
	<jsp:forward page="login.jsp" >
	<jsp:param name="errorMessage" value="<%=error%>" />
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% }else{ %>
	<jsp:forward page="registeredContent.jsp" >
	<jsp:param name="userName" value="<%= user.getUserName() %>" />
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% } %>

