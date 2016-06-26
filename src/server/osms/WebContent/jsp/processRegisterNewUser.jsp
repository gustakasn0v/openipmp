<%@ page import = "com.mutable.osmsOnline.server.Global" %>

<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/>
<jsp:useBean id="reqMsg" class="com.mutable.osms.common.io.message.osmsMessageRegisterUserRequest"   scope="page"/>
<jsp:useBean id="prc"    class="com.mutable.osmsOnline.server.app.ProcessMessageRegisterUserRequest" scope="page"/>
<jsp:setProperty name="reqMsg" property="*"/>

<% String errMsg = prc.process(reqMsg,user);%>

<% if (!user.isLoggedIn() ){ %>
	<jsp:forward page="registerNewUser.jsp" >
	<jsp:param name="errorMessage" value="<%=errMsg%>" />
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% }else{ %>
	<jsp:forward page="UserKeyStore.jsp" >
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% } %>

