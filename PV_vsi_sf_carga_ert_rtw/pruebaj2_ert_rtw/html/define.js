function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["pruebaj2_B"] = {file: "pruebaj2_c.html",line:20,type:"var"};
this.def["pruebaj2_X"] = {file: "pruebaj2_c.html",line:23,type:"var"};
this.def["pruebaj2_Y"] = {file: "pruebaj2_c.html",line:26,type:"var"};
this.def["pruebaj2_M_"] = {file: "pruebaj2_c.html",line:29,type:"var"};
this.def["pruebaj2_M"] = {file: "pruebaj2_c.html",line:30,type:"var"};
this.def["rt_ertODEUpdateContinuousStates"] = {file: "pruebaj2_c.html",line:36,type:"fcn"};
this.def["pruebaj2_step"] = {file: "pruebaj2_c.html",line:103,type:"fcn"};
this.def["pruebaj2_derivatives"] = {file: "pruebaj2_c.html",line:153,type:"fcn"};
this.def["pruebaj2_initialize"] = {file: "pruebaj2_c.html",line:170,type:"fcn"};
this.def["pruebaj2_terminate"] = {file: "pruebaj2_c.html",line:233,type:"fcn"};
this.def["B_pruebaj2_T"] = {file: "pruebaj2_h.html",line:57,type:"type"};
this.def["X_pruebaj2_T"] = {file: "pruebaj2_h.html",line:63,type:"type"};
this.def["XDot_pruebaj2_T"] = {file: "pruebaj2_h.html",line:69,type:"type"};
this.def["XDis_pruebaj2_T"] = {file: "pruebaj2_h.html",line:75,type:"type"};
this.def["ODE4_IntgData"] = {file: "pruebaj2_h.html",line:84,type:"type"};
this.def["ExtY_pruebaj2_T"] = {file: "pruebaj2_h.html",line:91,type:"type"};
this.def["RT_MODEL_pruebaj2_T"] = {file: "pruebaj2_types_h.html",line:20,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:78,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:83,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:95,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:102,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:109,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:116,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:123,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:130,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:148,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["pruebaj2_c.html"] = "../pruebaj2.c";
	this.html2Root["pruebaj2_c.html"] = "pruebaj2_c.html";
	this.html2SrcPath["pruebaj2_h.html"] = "../pruebaj2.h";
	this.html2Root["pruebaj2_h.html"] = "pruebaj2_h.html";
	this.html2SrcPath["pruebaj2_private_h.html"] = "../pruebaj2_private.h";
	this.html2Root["pruebaj2_private_h.html"] = "pruebaj2_private_h.html";
	this.html2SrcPath["pruebaj2_types_h.html"] = "../pruebaj2_types.h";
	this.html2Root["pruebaj2_types_h.html"] = "pruebaj2_types_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","pruebaj2_c.html","pruebaj2_h.html","pruebaj2_private_h.html","pruebaj2_types_h.html","rtwtypes_h.html"];
