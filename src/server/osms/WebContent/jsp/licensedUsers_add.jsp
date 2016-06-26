<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">
<HTML>

<HEAD>
<style type="text/css">
<!--

BODY { font-family: arial, sans-serif}

A:link, A:visited { font-size: 13px; line-height: 16px; color: #000000; text-decoration: none; font-weight: normal}
A:link.nav, A:visited.nav { font-size: 16px; line-height: 12px; color: #FFFFFF; font-weight: bold}
A:hover { font-size: 13px; line-height: 16px; text-decoration: underline; font-weight: normal}
A:hover.nav { font-size: 16px; line-height: 12px; color: #FFFFFF; font-weight: bold; text-decoration: underline}
A:active { color: #000000}

.bodycopy { font-size: 13px; color: #000000; text-decoration: none; line-height: 18px; letter-spacing: -0.02; text-align: left}
.bodycopyitalic { font-size: 13px; color: #000000; line-height: 18px; font-weight: bold; font-style:italic; letter-spacing: -0.02; text-align: left}
.bodycopywhite { font-size: 13px; color: #ffffff; text-decoration: none; line-height: 18px; letter-spacing: -0.02; text-align: left}
.tablehead { font-size: 15px; color: #000000; text-decoration: none; line-height: 18px; letter-spacing: -0.02; text-align: left}
.nav_on { font-size: 16px; line-height: 12px; color: #777777; font-weight: bold}
.error { font-size: 16px; line-height: 18px; color: #FF0000; font-weight: bold}

-->
</style>


	<META HTTP-EQUIV="Content-Type" CONTENT="text/html;CHARSET=iso-8859-1">
	<TITLE>openIPMP</TITLE>
</HEAD>

<BODY BGCOLOR="#000000" LEFTMARGIN="0" TOPMARGIN="0" MARGINWIDTH="0" MARGINHEIGHT="0">

<CENTER>
<P><BR>
<BR>

<%@ page import = "com.mutable.osmsOnline.server.Global" %>
<%@ page import = "com.mutable.osmsOnline.server.app.DateTool" %>
<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/>
<% if (!user.isLoggedIn() ){ %>
	<jsp:forward page="login.jsp" >
	<jsp:param name="errorMessage" value="User Not Logged In!" />
	<jsp:param name="date" value="<%= Global.getTime() %>" />
	</jsp:forward>
<% }%>
<%com.mutable.osms.server.db.osmsDatabase db=com.mutable.osms.server.app.osmsGlobalObjectManager.getInstance().getDatabase();%>
<%com.mutable.osms.server.bo.osmsUsers[] users=db.getUsers();%>
<TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0" BGCOLOR="#FFFFFF">
	<TR>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_13.jpg" WIDTH="14" HEIGHT="11" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_15.jpg" WIDTH="14" HEIGHT="11" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><IMG SRC="images/open_ipmp_manage_17.jpg" WIDTH="207" HEIGHT="11" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="390"><IMG SRC="images/open_ipmp_manage_18.jpg" WIDTH="390" HEIGHT="11" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_19.jpg" WIDTH="89" HEIGHT="11" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_20.jpg" WIDTH="13" HEIGHT="11" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#000000"><IMG SRC="images/open_ipmp_manage_21.jpg" WIDTH="15" HEIGHT="11" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_25.jpg" WIDTH="1" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD VALIGN="TOP" COLSPAN="3"><A HREF="http://www.openipmp.com" TARGET="_blank" TITLE="http://www.openipmp.com">
			<IMG SRC="logo.gif" WIDTH="222" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></A></TD>
		<TD WIDTH="390"><IMG SRC="images/open_ipmp_manage_29.jpg" WIDTH="390" HEIGHT="52" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_30.jpg" WIDTH="89" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_31.jpg" WIDTH="13" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_36.jpg" WIDTH="1" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_37.jpg" WIDTH="14" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_38.jpg" WIDTH="1" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><IMG SRC="images/open_ipmp_manage_39.jpg" WIDTH="207" HEIGHT="70" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="390" VALIGN="TOP" background="key.gif"><IMG SRC="spacer.gif" WIDTH="390" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"><BR>
			<IMG SRC="spacer.gif" WIDTH="63" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"><IMG SRC="arrow_off.gif"
			WIDTH="12" HEIGHT="13" ALIGN="BOTTOM" BORDER="0"><A HREF="UserKeyStore.jsp?date=<%= Global.getTime() %>" CLASS="nav">Keystore</A>
			<IMG SRC="spacer.gif" WIDTH="35" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"><IMG SRC="arrow_off.gif"
			WIDTH="12" HEIGHT="13" ALIGN="BOTTOM" BORDER="0"><A HREF="registeredContent.jsp?date=<%= Global.getTime() %>" CLASS="nav">Content</A>
			<IMG SRC="spacer.gif" WIDTH="35" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"><IMG SRC="arrow_on.gif"
			WIDTH="12" HEIGHT="13" ALIGN="BOTTOM" BORDER="0"><FONT CLASS="nav_on">Licenses</TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_41.jpg" WIDTH="89" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_42.jpg" WIDTH="13" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1" BGCOLOR="#EEEEEE"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14" VALIGN="TOP" BGCOLOR="#BBBBBB"><IMG SRC="images/open_ipmp_manage_48.jpg" WIDTH="14" HEIGHT="373" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="1" BGCOLOR="#000000"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD VALIGN="TOP" COLSPAN="3" BGCOLOR="#FFFFFF">
			<TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0" WIDTH="686">
				<TR>
					<TD><IMG SRC="spacer.gif" WIDTH="16" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD WIDTH="655"><IMG SRC="spacer.gif" WIDTH="655" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
				</TR>
				<TR>
					<TD><IMG SRC="spacer.gif" WIDTH="16" HEIGHT="23" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD WIDTH="655"><IMG SRC="add_user.gif" WIDTH="268" HEIGHT="23" ALIGN="BOTTOM" BORDER="0">
						<FONT CLASS="bodycopyitalic"> for <%= request.getParameter("primaryTitle")%> (<%= request.getParameter("doiIdentifier")%>)</FONT><BR>
						<IMG SRC="666666.gif" WIDTH="655" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="23" ALIGN="BOTTOM" BORDER="0"></TD>
				</TR>
				<TR>
					<TD><IMG SRC="spacer.gif" WIDTH="16" HEIGHT="341" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD WIDTH="655" VALIGN="TOP"><BR>

						<TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0">
							<TR>
								<TD><FONT CLASS="error"><%=(request.getParameter("errorMessage")==null?"":request.getParameter("errorMessage"))%> </FONT></TD>
							</TR>
							<FORM METHOD=POST ACTION=processLicensedUsersAddUser.jsp>
								<TR>
									<TD VALIGN="TOP" CLASS="bodycopy">username:<BR>
										<SELECT NAME=userName style="background-color:#CCCCCC">>
											<%for (int i=0;users!=null && i<users.length; i++) {%>
							 					<OPTION VALUE="<%=users[i].getUserName()%>"><%=users[i].getUserName()%></OPTION>
											<% } %>
										</SELECT>
									</TD>
								</TR>
								<TR>
									<TD><IMG SRC="spacer.gif" WIDTH="20" HEIGHT="6" ALIGN="BOTTOM" BORDER="0"></TD>
								</TR>
								<TR>
									<TD VALIGN="TOP" CLASS="bodycopy">start date:<BR>
										<INPUT TYPE="TEXT" NAME="startDate" value="<%=com.mutable.osmsOnline.server.app.DateTool.currentStringDate()%>" SIZE="17" style="background-color:#CCCCCC"></TD>
								</TR>
								<TR>
									<TD><IMG SRC="spacer.gif" WIDTH="20" HEIGHT="6" ALIGN="BOTTOM" BORDER="0"></TD>
								</TR>
								<TR>
									<TD CLASS="bodycopy">end date:<BR>
										<INPUT TYPE="TEXT" NAME="endDate" SIZE="17" style="background-color:#CCCCCC"></TD>
								</TR>
								<TR>
									<TD><IMG SRC="spacer.gif" WIDTH="20" HEIGHT="10" ALIGN="BOTTOM" BORDER="0"></TD>
								</TR>
								<TR>
									<TD VALIGN="TOP" CLASS="bodycopy">license Type:<BR>
										<SELECT NAME=licenseType style="background-color:#CCCCCC">>
							 					<OPTION VALUE="ODRL">ODRL</OPTION>
							 					<OPTION VALUE="MPEGREL">MPEGREL</OPTION>
										</SELECT>
									</TD>
								</TR>
								<TR>
									<TD><IMG SRC="spacer.gif" WIDTH="20" HEIGHT="10" ALIGN="BOTTOM" BORDER="0"></TD>
								</TR>
								<TR>
									<TD>
										<DIV ALIGN="RIGHT">
											<P><INPUT TYPE="HIDDEN" NAME="contentId" VALUE=<%=request.getParameter("contentId")%>>
							                  	<INPUT TYPE="HIDDEN" NAME="doiIdentifier" VALUE=<%= request.getParameter("doiIdentifier")%>>
						                 			<INPUT TYPE="HIDDEN" NAME="primaryTitle" VALUE="<%=request.getParameter("primaryTitle")%>" >
						                        	<INPUT TYPE="HIDDEN" NAME="date" VALUE=<%= Global.getTime() %> >
											<INPUT TYPE="SUBMIT" NAME="Submit" VALUE="Add" style="font-size:10px">
										</DIV>
							</FORM>
										<DIV ALIGN="RIGHT">
											<FORM METHOD=POST ACTION=licensedUsers.jsp>
												<INPUT TYPE="HIDDEN" NAME="contentId" VALUE=<%=request.getParameter("contentId")%>>
							      				<INPUT TYPE="HIDDEN" NAME="doiIdentifier" VALUE=<%= request.getParameter("doiIdentifier")%>>
						            				<INPUT TYPE="HIDDEN" NAME="primaryTitle" VALUE="<%=request.getParameter("primaryTitle")%>" >
						            				<INPUT TYPE="HIDDEN" NAME="date" VALUE=<%= Global.getTime() %> >
												<INPUT TYPE="SUBMIT" NAME="Cancel" VALUE="Cancel" style="font-size:10px">
											</FORM>
										</DIV>
									</TD>
								</TR>
						</TABLE>
					</TD>
					<TD><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="341" ALIGN="BOTTOM" BORDER="0"></TD>
				</TR>
			</TABLE>
		</TD>
		<TD WIDTH="13" VALIGN="TOP" BGCOLOR="#DDDDDD"><IMG SRC="images/open_ipmp_manage_53.jpg" WIDTH="13" HEIGHT="373" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1" BGCOLOR="#EEEEEE"><IMG SRC="images/open_ipmp_manage_58.jpg" WIDTH="1" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_59.jpg" WIDTH="14" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_60.jpg" WIDTH="1" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><IMG SRC="images/open_ipmp_manage_61.jpg" WIDTH="207" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="390"><IMG SRC="images/open_ipmp_manage_62.jpg" WIDTH="390" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_63.jpg" WIDTH="89" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_64.jpg" WIDTH="13" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_70.jpg" WIDTH="14" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_71.jpg" WIDTH="1" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><A HREF="processLogout.jsp"><IMG SRC="images/open_ipmp_manage_logout.jpg" WIDTH="207" HEIGHT="50" ALIGN="BOTTOM"
			BORDER="0"></A></TD>
		<TD WIDTH="390"><IMG SRC="images/open_ipmp_manage_73.jpg" WIDTH="390" HEIGHT="50" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_74.jpg" WIDTH="89" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_75.jpg" WIDTH="13" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_79.jpg" WIDTH="14" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_80.jpg" WIDTH="1" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_81.jpg" WIDTH="14" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_82.jpg" WIDTH="1" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><IMG SRC="images/open_ipmp_manage_83.jpg" WIDTH="207" HEIGHT="15" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="390"><IMG SRC="images/open_ipmp_manage_84.jpg" WIDTH="390" HEIGHT="15" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="89"><IMG SRC="images/open_ipmp_manage_85.jpg" WIDTH="89" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_86.jpg" WIDTH="13" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#000000"><IMG SRC="images/open_ipmp_manage_87.jpg" WIDTH="15" HEIGHT="15" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD VALIGN="TOP" COLSPAN="5" BGCOLOR="#000000"></TD>
		<TD VALIGN="TOP" COLSPAN="3" BGCOLOR="#000000">
			<DIV ALIGN="RIGHT"><P><A HREF="http://mutablemedia.com/" target="_blank"><IMG SRC="mutable_logo.gif"
			WIDTH="221" HEIGHT="44" ALIGN="BOTTOM" BORDER="0"></A></DIV>
		</TD>
		<TD WIDTH="15" BGCOLOR="#000000"></TD>
	</TR>
</TABLE>

</CENTER>
<P>

</BODY>

</HTML>
