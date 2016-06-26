/** \file RO.cpp

    OMA DRM rights object classes.

    The Initial Developer of the Original Code is Mutable, Inc. <br>
    Portions created by Mutable, Inc. are <br>
    Copyright (C) Mutable, Inc. 2002-2006.  All Rights Reserved. <p>

	  
*/

#include "RO.h"

//! DRMPlugin namespace. All DRM plugin code resides in it.
namespace DRMPlugin {

/*! \brief  Version.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDVersion::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("version"): (varName));
	return "<" + vName + ">" + vstring + "</" + vName + ">";
}

/*! \brief  (Unique) identifier.
*/
/*! \brief  (Unique) identifier used in rights context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RightsODDUID::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("uid"): (varName));
	return "<" + vName + ">" + uid + "</" + vName + ">";
}

/*! \brief  (Unique) identifier.
*/
/*! \brief  (Unique) identifier used in asset context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AssetODDUID::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("uid"): (varName));
	return "<" + vName + ">" + uid + "</" + vName + ">";
}

/*! \brief  (Unique) identifier.
*/
/*! \brief  (Unique) identifier used in individual context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string IndividualODDUID::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("uid"): (varName));
	return "<" + vName + ">" + uid + "</" + vName + ">";
}

/*! \brief  (Unique) identifier.
*/
/*! \brief  (Unique) identifier used in system context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SystemODDUID::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("uid"): (varName));
	return "<" + vName + ">" + uid + "</" + vName + ">";
}

/*! \brief  (Unique) identifier.
*/
/*! \brief  (Unique) identifier used in inherit context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InheritODDUID::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("uid"): (varName));
	return "<" + vName + ">" + uid + "</" + vName + ">";
}

/*! \brief  Context.
*/
/*! \brief  Rights context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string RightsOEXContext::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("context"): (varName));
  if ((version == 0) && (uid == 0)) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  if (version != 0) {
    ret = ret + version->XmlEncode();
  }
  if (uid != 0) {
    ret = ret + uid->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Context.
*/
/*! \brief  Asset context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AssetOEXContext::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("context"): (varName));
  if ((version == 0) && (uid == 0)) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  if (version != 0) {
    ret = ret + version->XmlEncode();
  }
  if (uid != 0) {
    ret = ret + uid->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Context.
*/
/*! \brief  Individual context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string IndividualOEXContext::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("context"): (varName));
  if ((version == 0) && (uids.size() == 0)) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  if (version != 0) {
    ret = ret + version->XmlEncode();
  }
  for (unsigned int i = 0; i < uids.size(); i++) {
    ret = ret + uids[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Context.
*/
/*!	\brief  System context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string SystemOEXContext::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("context"): (varName));
  if ((version == 0) && (uids.size() == 0)) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  if (version != 0) {
    ret = ret + version->XmlEncode();
  }
  for (unsigned int i = 0; i < uids.size(); i++) {
    ret = ret + uids[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Context.
*/
/*! \brief  Inherit context.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string InheritOEXContext::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("context"): (varName));
  if ((version == 0) && (uid == 0)) {
    return "<" + vName + "/>";
  }
  std::string ret("<" + vName + ">");
  if (version != 0) {
    ret = ret + version->XmlEncode();
  }
  if (uid != 0) {
    ret = ret + uid->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Inherit.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXInherit::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("inherit"): (varName));
	return "<" + vName + ">" + context->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Digest definition.

    Digest method algorithm is fixed to http://www.w3.org/2000/09/xmldsig#sha1.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXDigest::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("digest"): (varName));
	return "<" + vName  + ">" + dMethod->XmlEncode() + dValue->XmlEncode() +
    "</" + vName + ">";
}

/*! \brief  Key info contained in asset.

    \todo:  Documentation indicates that this is derived from DSKeyInfo,
            but DSKeyInfo doesn't contain encrypted key (see DSKeyInfo).
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXAssetKeyInfo::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("ds:KeyInfo"): (varName));
	return "<" + vName + ">" + encKey->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Asset used in agreement.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string AgreementOEXAsset::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("asset"): (varName));
  std::string ret("<" + vName);
  if (assetID != 0) {
    ret = ret + " id=\"" + assetID->GetIDValue()->Get() + "\"";
  }
  if ((context == 0) && (inherit == 0) && (digest == 0) && (keyInfo == 0)) {
    return ret + "/>";
  }
  ret = ret + ">";
  if (context != 0) {
    ret = ret + context->XmlEncode();
  }
  if (inherit != 0) {
    ret = ret + inherit->XmlEncode();
  }
  if (digest != 0) {
    ret = ret + digest->XmlEncode();
  }
  if (keyInfo != 0) {
    ret = ret + keyInfo->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Asset used in permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string PermissionOEXAsset::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("asset"): (varName));
  std::string ret("<" + vName);
  if (idRef != 0) {
    ret = ret + " idref=\"" + idRef->Get() + "\"";
  }
	return ret + "/>";
}

/*! \brief  Count constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDCountConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("count"): (varName));
	return "<" + vName + ">" + IntToString(count) + "</" + vName + ">";
}

/*! \brief  Timed count constraint.
*/
/*! \brief  Timed count constraint with timer.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string TimerOMADDTimedCountConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("timed-count"): (varName));
	return "<" + vName + " timer=\"" + IntToString(timer) + "\">" +
    IntToString(count) + "</" + vName + ">";
}

/*! \brief  Timed count constraint.
*/
/*! \brief  Timed count constraint without timer.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string NTimerOMADDTimedCountConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("timed-count"): (varName));
	return "<" + vName + ">" + IntToString(count) + "</" + vName + ">";
}

/*! \brief  Start time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDStart::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("start"): (varName));
	return "<" + vName + ">" + GetTime().Get() + "</" + vName + ">";
}

/*! \brief  End time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDEnd::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("end"): (varName));
	return "<" + vName + ">" + GetTime().Get() + "</" + vName + ">";
}

/*! \brief  Datetime constraint.
*/
/*! \brief  Empty datetime constraint. No start time and no end time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string EmptyODDDatetimeConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("datetime"): (varName));
	return "<" + vName + "></" + vName + ">";
}

/*! \brief  Datetime constraint.
*/
/*! \brief  Datetime constraint with start time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string StartODDDatetimeConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("datetime"): (varName));
	return "<" + vName + ">" + start->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Datetime constraint.
*/
/*! \brief  Datetime constraint with end time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string EndODDDatetimeConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("datetime"): (varName));
	return "<" + vName + ">" + end->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Datetime constraint.
*/
/*! \brief  Datetime constraint with both start and end time.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string StartEndODDDatetimeConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("datetime"): (varName));
	return "<" + vName + ">" + start->XmlEncode() + end->XmlEncode() +
    "</" + vName + ">";
}

/*! \brief  Interval constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDIntervalConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("interval"): (varName));
	return "<" + vName + ">" + interval + "</" + vName + ">";
}

/*! \brief  Accumulated constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDAccumulatedConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("accumulated"): (varName));
	return "<" + vName + ">" + interval + "</" + vName + ">";
}

/*! \brief  Individual constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDIndividualConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("individual"): (varName));
	return "<" + vName + ">" + context->XmlEncode() + "</" + vName + ">";
}

/*! \brief  System constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OMADDSystemConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("system"): (varName));
	return "<" + vName + ">" + context->XmlEncode() + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  General constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string GeneralOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (timedcount != 0) {
    ret = ret + timedcount->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  if (accumulated != 0) {
    ret = ret + accumulated->XmlEncode();
  }
  if (individual != 0) {
    ret = ret + individual->XmlEncode();
  }
  for (unsigned int i = 0; i < systems.size(); i++) {
    ret = ret + systems[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Play constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string PlayOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (timedcount != 0) {
    ret = ret + timedcount->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  if (accumulated != 0) {
    ret = ret + accumulated->XmlEncode();
  }
  if (individual != 0) {
    ret = ret + individual->XmlEncode();
  }
  for (unsigned int i = 0; i < systems.size(); i++) {
    ret = ret + systems[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Display constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string DisplayOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (timedcount != 0) {
    ret = ret + timedcount->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  if (accumulated != 0) {
    ret = ret + accumulated->XmlEncode();
  }
  if (individual != 0) {
    ret = ret + individual->XmlEncode();
  }
  for (unsigned int i = 0; i < systems.size(); i++) {
    ret = ret + systems[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Execute constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ExecuteOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (timedcount != 0) {
    ret = ret + timedcount->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  if (accumulated != 0) {
    ret = ret + accumulated->XmlEncode();
  }
  if (individual != 0) {
    ret = ret + individual->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Print constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string PrintOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  if (accumulated != 0) {
    ret = ret + accumulated->XmlEncode();
  }
  if (individual != 0) {
    ret = ret + individual->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Export constraint.
*/
/*! \brief  Move export constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string MoveExportOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  for (unsigned int i = 0; i < systems.size(); i++) {
    ret = ret + systems[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Constraint.
*/
/*! \brief  Export constraint.
*/
/*! \brief  Copy export constraint.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string CopyExportOEXConstraint::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("constraint"): (varName));
  std::string ret("<" + vName + ">");
  if (count != 0) {
    ret = ret + count->XmlEncode();
  }
  if (datetime != 0) {
    ret = ret + datetime->XmlEncode();
  }
  if (interval != 0) {
    ret = ret + interval->XmlEncode();
  }
  for (unsigned int i = 0; i < systems.size(); i++) {
    ret = ret + systems[i]->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Play permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDPlayPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("play"): (varName));
  std::string ret("<" + vName + ">");
  if (constraint != 0) {
    ret = ret + constraint->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Display permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDDisplayPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("display"): (varName));
  std::string ret("<" + vName + ">");
  if (constraint != 0) {
    ret = ret + constraint->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Execute permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDExecutePermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("execute"): (varName));
  std::string ret("<" + vName + ">");
  if (constraint != 0) {
    ret = ret + constraint->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Print permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string ODDPrintPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("print"): (varName));
  std::string ret("<" + vName + ">");
  if (constraint != 0) {
    ret = ret + constraint->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Export permission.
*/
/*! \brief  Move export permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string MoveOMADDExportPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("export"): (varName));
  return "<" + vName + " mode=\"move\">" + constraint->XmlEncode() +
    "</" + vName + ">";
}

/*! \brief  Basic permission.
*/
/*! \brief  Export permission.
*/
/*! \brief  Copy export permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string CopyOMADDExportPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("export"): (varName));
  return "<" + vName + " mode=\"copy\">" + constraint->XmlEncode() +
    "</" + vName + ">";
}

/*! \brief  Rights permission.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXPermission::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("permission"): (varName));
  std::string ret("<" + vName + ">");
  if (general != 0) {
    ret = ret + general->XmlEncode();
  }
  for (unsigned int i = 0; i < assets.size(); i++) {
    ret = ret + assets[i]->XmlEncode();
  }
  if (play != 0) {
    ret = ret + play->XmlEncode();
  }
  if (display != 0) {
    ret = ret + display->XmlEncode();
  }
  if (execute != 0) {
    ret = ret + execute->XmlEncode();
  }
  if (print != 0) {
    ret = ret + print->XmlEncode();
  }
  if (eexport != 0) {
    ret = ret + eexport->XmlEncode();
  }
	return ret + "</" + vName + ">";
}

/*! \brief  Rights agreement.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXAgreement::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("agreement"): (varName));
  std::string ret("<" + vName + ">");
  unsigned int i = 0;
  for (i = 0; i < assets.size(); i++) {
    ret = ret + assets[i]->XmlEncode();
  }
  for (i = 0; i < permissions.size(); i++) {
    ret = ret + permissions[i]->XmlEncode();
  }
	return ret  + "</" + vName + ">";
}

/*! \brief  Rights.
*/
/*! \brief  Encode as XML string.

    \param  varName         input, if != "" then XML header field is set
                            to varName, otherwise the namespace is set
                            as XML header field.

    \returns  Encoded XML string.
*/
std::string OEXRights::XmlEncode(const std::string& varName) const {
  std::string vName = ((varName == "")? ("rights"): (varName));
	return "<" + vName + ">" + context->XmlEncode() + agreement->XmlEncode() +
    "</" + vName + ">";
}

} // namespace DRMPlugin
