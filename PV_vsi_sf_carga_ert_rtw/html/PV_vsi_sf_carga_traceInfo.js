function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Vload */
	this.urlHashMap["PV_vsi_sf_carga:289"] = "PV_vsi_sf_carga.h:128";
	/* <Root>/Ipv */
	this.urlHashMap["PV_vsi_sf_carga:291"] = "PV_vsi_sf_carga.h:129";
	/* <Root>/1-D Lookup
Table2 */
	this.urlHashMap["PV_vsi_sf_carga:164"] = "PV_vsi_sf_carga.c:289&PV_vsi_sf_carga.h:116,121&PV_vsi_sf_carga_data.c:22,27";
	/* <Root>/Current Panel */
	this.urlHashMap["PV_vsi_sf_carga:297"] = "PV_vsi_sf_carga.c:302";
	/* <Root>/Derivative */
	this.urlHashMap["PV_vsi_sf_carga:146"] = "PV_vsi_sf_carga.c:253,276,329,347,502&PV_vsi_sf_carga.h:72,73,74,75";
	/* <Root>/Derivative1 */
	this.urlHashMap["PV_vsi_sf_carga:154"] = "PV_vsi_sf_carga.c:193,216,310,327,495&PV_vsi_sf_carga.h:68,69,70,71";
	/* <Root>/Gain */
	this.urlHashMap["PV_vsi_sf_carga:147"] = "PV_vsi_sf_carga.c:279";
	/* <Root>/Gain1 */
	this.urlHashMap["PV_vsi_sf_carga:150"] = "PV_vsi_sf_carga.c:286";
	/* <Root>/Gain2 */
	this.urlHashMap["PV_vsi_sf_carga:155"] = "PV_vsi_sf_carga.c:219";
	/* <Root>/Gain4 */
	this.urlHashMap["PV_vsi_sf_carga:259"] = "PV_vsi_sf_carga.c:287";
	/* <Root>/Integrator */
	this.urlHashMap["PV_vsi_sf_carga:161"] = "PV_vsi_sf_carga.c:226,237,399,410,499&PV_vsi_sf_carga.h:82,90,98";
	/* <Root>/MATLAB Function SOC  */
	this.urlHashMap["PV_vsi_sf_carga:292"] = "PV_vsi_sf_carga.c:236";
	/* <Root>/Product2 */
	this.urlHashMap["PV_vsi_sf_carga:151"] = "PV_vsi_sf_carga.c:290";
	/* <Root>/Sine Wave */
	this.urlHashMap["PV_vsi_sf_carga:145"] = "PV_vsi_sf_carga.c:249&PV_vsi_sf_carga.h:60";
	/* <Root>/Sum2 */
	this.urlHashMap["PV_vsi_sf_carga:148"] = "PV_vsi_sf_carga.c:280";
	/* <Root>/Sum3 */
	this.urlHashMap["PV_vsi_sf_carga:149"] = "PV_vsi_sf_carga.c:278&PV_vsi_sf_carga.h:61";
	/* <Root>/Sum4 */
	this.urlHashMap["PV_vsi_sf_carga:152"] = "PV_vsi_sf_carga.c:285&PV_vsi_sf_carga.h:62";
	/* <Root>/Sum5 */
	this.urlHashMap["PV_vsi_sf_carga:157"] = "PV_vsi_sf_carga.c:218&PV_vsi_sf_carga.h:59";
	/* <Root>/Sum7 */
	this.urlHashMap["PV_vsi_sf_carga:280"] = "PV_vsi_sf_carga.c:301&PV_vsi_sf_carga.h:63";
	/* <Root>/Transfer Fcn3 */
	this.urlHashMap["PV_vsi_sf_carga:293"] = "PV_vsi_sf_carga.c:186,389,506,512&PV_vsi_sf_carga.h:58,81,89,97";
	/* <Root>/VSI  line Z */
	this.urlHashMap["PV_vsi_sf_carga:156"] = "PV_vsi_sf_carga.c:183,383,492&PV_vsi_sf_carga.h:80,88,96";
	/* <Root>/i3 */
	this.urlHashMap["PV_vsi_sf_carga:288"] = "PV_vsi_sf_carga.c:223&PV_vsi_sf_carga.h:134";
	/* <Root>/SOC */
	this.urlHashMap["PV_vsi_sf_carga:290"] = "PV_vsi_sf_carga.c:243&PV_vsi_sf_carga.h:135";
	/* <Root>/vload */
	this.urlHashMap["PV_vsi_sf_carga:299"] = "PV_vsi_sf_carga.c:246&PV_vsi_sf_carga.h:136";
	/* <S1>/Constant2 */
	this.urlHashMap["PV_vsi_sf_carga:135"] = "msg=rtwMsg_CodeGenerationReducedBlock&block=PV_vsi_sf_carga:135";
	/* <S1>/Gain2 */
	this.urlHashMap["PV_vsi_sf_carga:136"] = "PV_vsi_sf_carga.c:288";
	/* <S1>/Sum5 */
	this.urlHashMap["PV_vsi_sf_carga:137"] = "PV_vsi_sf_carga.c:291";
	/* <S1>/Sum9 */
	this.urlHashMap["PV_vsi_sf_carga:138"] = "msg=rtwMsg_CodeGenerationReducedBlock&block=PV_vsi_sf_carga:138";
	/* <S1>/Transfer Fcn2 */
	this.urlHashMap["PV_vsi_sf_carga:139"] = "PV_vsi_sf_carga.c:292,412,509,515&PV_vsi_sf_carga.h:83,91,99";
	/* <S2>:1 */
	this.urlHashMap["PV_vsi_sf_carga:292:1"] = "PV_vsi_sf_carga.c:239";
	/* <S2>:1:3 */
	this.urlHashMap["PV_vsi_sf_carga:292:1:3"] = "PV_vsi_sf_carga.c:240";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "PV_vsi_sf_carga"};
	this.sidHashMap["PV_vsi_sf_carga"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "PV_vsi_sf_carga:142"};
	this.sidHashMap["PV_vsi_sf_carga:142"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "PV_vsi_sf_carga:292"};
	this.sidHashMap["PV_vsi_sf_carga:292"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<Root>/Vload"] = {sid: "PV_vsi_sf_carga:289"};
	this.sidHashMap["PV_vsi_sf_carga:289"] = {rtwname: "<Root>/Vload"};
	this.rtwnameHashMap["<Root>/Ipv"] = {sid: "PV_vsi_sf_carga:291"};
	this.sidHashMap["PV_vsi_sf_carga:291"] = {rtwname: "<Root>/Ipv"};
	this.rtwnameHashMap["<Root>/1-D Lookup Table2"] = {sid: "PV_vsi_sf_carga:164"};
	this.sidHashMap["PV_vsi_sf_carga:164"] = {rtwname: "<Root>/1-D Lookup Table2"};
	this.rtwnameHashMap["<Root>/Control PR VSI"] = {sid: "PV_vsi_sf_carga:142"};
	this.sidHashMap["PV_vsi_sf_carga:142"] = {rtwname: "<Root>/Control PR VSI"};
	this.rtwnameHashMap["<Root>/Current Panel"] = {sid: "PV_vsi_sf_carga:297"};
	this.sidHashMap["PV_vsi_sf_carga:297"] = {rtwname: "<Root>/Current Panel"};
	this.rtwnameHashMap["<Root>/Derivative"] = {sid: "PV_vsi_sf_carga:146"};
	this.sidHashMap["PV_vsi_sf_carga:146"] = {rtwname: "<Root>/Derivative"};
	this.rtwnameHashMap["<Root>/Derivative1"] = {sid: "PV_vsi_sf_carga:154"};
	this.sidHashMap["PV_vsi_sf_carga:154"] = {rtwname: "<Root>/Derivative1"};
	this.rtwnameHashMap["<Root>/From"] = {sid: "PV_vsi_sf_carga:296"};
	this.sidHashMap["PV_vsi_sf_carga:296"] = {rtwname: "<Root>/From"};
	this.rtwnameHashMap["<Root>/From1"] = {sid: "PV_vsi_sf_carga:294"};
	this.sidHashMap["PV_vsi_sf_carga:294"] = {rtwname: "<Root>/From1"};
	this.rtwnameHashMap["<Root>/From5"] = {sid: "PV_vsi_sf_carga:160"};
	this.sidHashMap["PV_vsi_sf_carga:160"] = {rtwname: "<Root>/From5"};
	this.rtwnameHashMap["<Root>/From6"] = {sid: "PV_vsi_sf_carga:162"};
	this.sidHashMap["PV_vsi_sf_carga:162"] = {rtwname: "<Root>/From6"};
	this.rtwnameHashMap["<Root>/Gain"] = {sid: "PV_vsi_sf_carga:147"};
	this.sidHashMap["PV_vsi_sf_carga:147"] = {rtwname: "<Root>/Gain"};
	this.rtwnameHashMap["<Root>/Gain1"] = {sid: "PV_vsi_sf_carga:150"};
	this.sidHashMap["PV_vsi_sf_carga:150"] = {rtwname: "<Root>/Gain1"};
	this.rtwnameHashMap["<Root>/Gain2"] = {sid: "PV_vsi_sf_carga:155"};
	this.sidHashMap["PV_vsi_sf_carga:155"] = {rtwname: "<Root>/Gain2"};
	this.rtwnameHashMap["<Root>/Gain4"] = {sid: "PV_vsi_sf_carga:259"};
	this.sidHashMap["PV_vsi_sf_carga:259"] = {rtwname: "<Root>/Gain4"};
	this.rtwnameHashMap["<Root>/Goto6"] = {sid: "PV_vsi_sf_carga:158"};
	this.sidHashMap["PV_vsi_sf_carga:158"] = {rtwname: "<Root>/Goto6"};
	this.rtwnameHashMap["<Root>/Goto7"] = {sid: "PV_vsi_sf_carga:159"};
	this.sidHashMap["PV_vsi_sf_carga:159"] = {rtwname: "<Root>/Goto7"};
	this.rtwnameHashMap["<Root>/Goto8"] = {sid: "PV_vsi_sf_carga:295"};
	this.sidHashMap["PV_vsi_sf_carga:295"] = {rtwname: "<Root>/Goto8"};
	this.rtwnameHashMap["<Root>/Integrator"] = {sid: "PV_vsi_sf_carga:161"};
	this.sidHashMap["PV_vsi_sf_carga:161"] = {rtwname: "<Root>/Integrator"};
	this.rtwnameHashMap["<Root>/MATLAB Function SOC "] = {sid: "PV_vsi_sf_carga:292"};
	this.sidHashMap["PV_vsi_sf_carga:292"] = {rtwname: "<Root>/MATLAB Function SOC "};
	this.rtwnameHashMap["<Root>/Product2"] = {sid: "PV_vsi_sf_carga:151"};
	this.sidHashMap["PV_vsi_sf_carga:151"] = {rtwname: "<Root>/Product2"};
	this.rtwnameHashMap["<Root>/Sine Wave"] = {sid: "PV_vsi_sf_carga:145"};
	this.sidHashMap["PV_vsi_sf_carga:145"] = {rtwname: "<Root>/Sine Wave"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "PV_vsi_sf_carga:148"};
	this.sidHashMap["PV_vsi_sf_carga:148"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<Root>/Sum3"] = {sid: "PV_vsi_sf_carga:149"};
	this.sidHashMap["PV_vsi_sf_carga:149"] = {rtwname: "<Root>/Sum3"};
	this.rtwnameHashMap["<Root>/Sum4"] = {sid: "PV_vsi_sf_carga:152"};
	this.sidHashMap["PV_vsi_sf_carga:152"] = {rtwname: "<Root>/Sum4"};
	this.rtwnameHashMap["<Root>/Sum5"] = {sid: "PV_vsi_sf_carga:157"};
	this.sidHashMap["PV_vsi_sf_carga:157"] = {rtwname: "<Root>/Sum5"};
	this.rtwnameHashMap["<Root>/Sum7"] = {sid: "PV_vsi_sf_carga:280"};
	this.sidHashMap["PV_vsi_sf_carga:280"] = {rtwname: "<Root>/Sum7"};
	this.rtwnameHashMap["<Root>/Transfer Fcn3"] = {sid: "PV_vsi_sf_carga:293"};
	this.sidHashMap["PV_vsi_sf_carga:293"] = {rtwname: "<Root>/Transfer Fcn3"};
	this.rtwnameHashMap["<Root>/VSI  line Z"] = {sid: "PV_vsi_sf_carga:156"};
	this.sidHashMap["PV_vsi_sf_carga:156"] = {rtwname: "<Root>/VSI  line Z"};
	this.rtwnameHashMap["<Root>/i3"] = {sid: "PV_vsi_sf_carga:288"};
	this.sidHashMap["PV_vsi_sf_carga:288"] = {rtwname: "<Root>/i3"};
	this.rtwnameHashMap["<Root>/SOC"] = {sid: "PV_vsi_sf_carga:290"};
	this.sidHashMap["PV_vsi_sf_carga:290"] = {rtwname: "<Root>/SOC"};
	this.rtwnameHashMap["<Root>/vload"] = {sid: "PV_vsi_sf_carga:299"};
	this.sidHashMap["PV_vsi_sf_carga:299"] = {rtwname: "<Root>/vload"};
	this.rtwnameHashMap["<S1>/Ierror"] = {sid: "PV_vsi_sf_carga:143"};
	this.sidHashMap["PV_vsi_sf_carga:143"] = {rtwname: "<S1>/Ierror"};
	this.rtwnameHashMap["<S1>/Constant2"] = {sid: "PV_vsi_sf_carga:135"};
	this.sidHashMap["PV_vsi_sf_carga:135"] = {rtwname: "<S1>/Constant2"};
	this.rtwnameHashMap["<S1>/Gain2"] = {sid: "PV_vsi_sf_carga:136"};
	this.sidHashMap["PV_vsi_sf_carga:136"] = {rtwname: "<S1>/Gain2"};
	this.rtwnameHashMap["<S1>/Sum5"] = {sid: "PV_vsi_sf_carga:137"};
	this.sidHashMap["PV_vsi_sf_carga:137"] = {rtwname: "<S1>/Sum5"};
	this.rtwnameHashMap["<S1>/Sum9"] = {sid: "PV_vsi_sf_carga:138"};
	this.sidHashMap["PV_vsi_sf_carga:138"] = {rtwname: "<S1>/Sum9"};
	this.rtwnameHashMap["<S1>/Transfer Fcn2"] = {sid: "PV_vsi_sf_carga:139"};
	this.sidHashMap["PV_vsi_sf_carga:139"] = {rtwname: "<S1>/Transfer Fcn2"};
	this.rtwnameHashMap["<S1>/d"] = {sid: "PV_vsi_sf_carga:144"};
	this.sidHashMap["PV_vsi_sf_carga:144"] = {rtwname: "<S1>/d"};
	this.rtwnameHashMap["<S2>:1"] = {sid: "PV_vsi_sf_carga:292:1"};
	this.sidHashMap["PV_vsi_sf_carga:292:1"] = {rtwname: "<S2>:1"};
	this.rtwnameHashMap["<S2>:1:3"] = {sid: "PV_vsi_sf_carga:292:1:3"};
	this.sidHashMap["PV_vsi_sf_carga:292:1:3"] = {rtwname: "<S2>:1:3"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
