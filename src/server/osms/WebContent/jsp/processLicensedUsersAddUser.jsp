<%@ page import = "com.mutable.osmsOnline.server.Global" %>

<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/>
<jsp:useBean id="prc"    class="com.mutable.osmsOnline.server.app.ProcessLicensedUsers_addUser" scope="page"/>
<jsp:setProperty name="prc" property="*"/>

<% if (!user.isLoggedIn() ){ %>
	<jsp:forward page="login.jsp" >
	<jsp:param name="errorMessage" value="User Not Logged In!" />
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% }else{ %>

	<% String errMsg = prc.process(user);%>
	<%if(errMsg==null){%>
		<jsp:forward page="licensedUsers.jsp" >
		<jsp:param name="errorMessage" value="<%=errMsg%>" />
		<jsp:param name="contentId" value="<%=prc.getContentId()%>" />
		<jsp:param name="primaryTitle" value="<%=prc.getPrimaryTitle()%>" />
		<jsp:param name="date" value="<%= Global.getTime() %>" />
		</jsp:forward>
	<%}else{%>
		<jsp:forward page="licensedUsers_add.jsp" >
		<jsp:param name="errorMessage" value="<%=errMsg%>" />
		<jsp:param name="contentId" value="<%=prc.getContentId()%>" />
		<jsp:param name="primaryTitle" value="<%=prc.getPrimaryTitle()%>" />
		<jsp:param name="date" value="<%= Global.getTime() %>" />
		</jsp:forward>
	<%}%>
<% } %>

