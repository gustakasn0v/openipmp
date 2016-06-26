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
<jsp:useBean id="user"   class="com.mutable.osms.server.bo.osmsUsers" scope="session"/>
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
		<TD VALIGN="BOTTOM" COLSPAN="3"><A HREF="http://www.openipmp.com" TARGET="_blank" TITLE="http://www.openipmp.com">
			<IMG SRC="logo.gif" WIDTH="222" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></A></TD>
		<TD WIDTH="390">
			<TABLE BORDER="0" CELLPADDING="0" CELLSPACING="0">
				<TR>
					<TD><IMG SRC="spacer.gif" WIDTH="29" HEIGHT="22" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD VALIGN="TOP" ROWSPAN="2"><IMG SRC="login_register.gif" WIDTH="102" HEIGHT="54" ALIGN="BOTTOM" BORDER="0" USEMAP="#login_register" ISMAP></TD>
					<TD VALIGN="BOTTOM" CLASS="bodycopy">user name:</TD>
					<TD><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="22" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD VALIGN="BOTTOM" CLASS="bodycopy">password:</TD>
					<TD><IMG SRC="spacer.gif" WIDTH="10" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
					<TD><IMG SRC="spacer.gif" WIDTH="29" HEIGHT="22" ALIGN="BOTTOM" BORDER="0"></TD>
				</TR>
				<TR>
					<FORM METHOD=POST ACTION=processLogin.jsp>
						<TD><IMG SRC="spacer.gif" WIDTH="29" HEIGHT="22" ALIGN="BOTTOM" BORDER="0"></TD>
						<TD VALIGN="TOP"><INPUT TYPE="TEXT" NAME="userName" SIZE="10" style="background-color:#CCCCCC"></TD>
						<TD><IMG SRC="spacer.gif" WIDTH="11" HEIGHT="22" ALIGN="BOTTOM" BORDER="0"></TD>
						<TD VALIGN="TOP"><INPUT TYPE="PASSWORD" NAME="password" SIZE="10" style="background-color:#CCCCCC"></TD>
						<TD><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
						<TD VALIGN="TOP">
							<INPUT TYPE="HIDDEN" NAME="loginSubmit" VALUE="nothing">
							<INPUT TYPE="SUBMIT" NAME="Submit" VALUE=">>" style="font-size:10px">
						</TD>
					</FORM>
				</TR>
			</TABLE>
		</TD>
		<TD WIDTH="89" VALIGN="BOTTOM"><IMG SRC="images/open_ipmp_manage_30.jpg" WIDTH="89" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13" VALIGN="BOTTOM"><IMG SRC="images/open_ipmp_manage_31.jpg" WIDTH="13" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="52" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_36.jpg" WIDTH="1" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_37.jpg" WIDTH="14" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD VALIGN="TOP" ROWSPAN="3" COLSPAN="4" background="login_cover.jpg">
			<P ALIGN="CENTER"><BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<BR>
			<FONT CLASS="error"><%=(request.getParameter("errorMessage")==null?"":request.getParameter("errorMessage"))%></FONT><BR>
		</TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_42.jpg" WIDTH="13" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="70" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1" BGCOLOR="#EEEEEE"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14" VALIGN="TOP" BGCOLOR="#BBBBBB"><IMG SRC="images/open_ipmp_manage_48.jpg" WIDTH="14" HEIGHT="373" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="13" VALIGN="TOP" BGCOLOR="#DDDDDD"><IMG SRC="images/open_ipmp_manage_53.jpg" WIDTH="13" HEIGHT="373" ALIGN="BOTTOM"
			BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1" BGCOLOR="#EEEEEE"><IMG SRC="images/open_ipmp_manage_58.jpg" WIDTH="1" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_59.jpg" WIDTH="14" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="13"><IMG SRC="images/open_ipmp_manage_64.jpg" WIDTH="13" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="15" BGCOLOR="#FFFFFF"><IMG SRC="spacer.gif" WIDTH="15" HEIGHT="9" ALIGN="BOTTOM" BORDER="0"></TD>
	</TR>
	<TR>
		<TD WIDTH="14"><IMG SRC="spacer.gif" WIDTH="14" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="spacer.gif" WIDTH="1" HEIGHT="1" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="14"><IMG SRC="images/open_ipmp_manage_70.jpg" WIDTH="14" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="1"><IMG SRC="images/open_ipmp_manage_71.jpg" WIDTH="1" HEIGHT="50" ALIGN="BOTTOM" BORDER="0"></TD>
		<TD WIDTH="207"><IMG SRC="images/open_ipmp_manage_72.jpg" WIDTH="207" HEIGHT="50" ALIGN="BOTTOM"
			BORDER="0"></TD>
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
			<DIV ALIGN="RIGHT">
			<P><A HREF="http://mutablemedia.com/" target="_blank"><IMG SRC="mutable_logo.gif"
			WIDTH="221" HEIGHT="44" ALIGN="BOTTOM" BORDER="0"></A>
</DIV>
		</TD>
		<TD WIDTH="15" BGCOLOR="#000000"></TD>
	</TR>
</TABLE>

</CENTER>
<P>

<MAP Name="login_register">
	<AREA Shape="Rect" coords = "17,0,72,19"  HREF="registerNewUser.jsp?date=<%= Global.getTime() %>" > 
</MAP>

</BODY>

</HTML>