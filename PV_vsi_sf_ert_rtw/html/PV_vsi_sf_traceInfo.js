function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Vload */
	this.urlHashMap["PV_vsi_sf:289"] = "PV_vsi_sf.c:188,282,304&PV_vsi_sf.h:123";
	/* <Root>/Ipv */
	this.urlHashMap["PV_vsi_sf:291"] = "PV_vsi_sf.c:295&PV_vsi_sf.h:124";
	/* <Root>/1-D Lookup
Table2 */
	this.urlHashMap["PV_vsi_sf:164"] = "PV_vsi_sf.c:283&PV_vsi_sf.h:111,116&PV_vsi_sf_data.c:22,27";
	/* <Root>/Derivative */
	this.urlHashMap["PV_vsi_sf:146"] = "PV_vsi_sf.c:246,269,324,341,481&PV_vsi_sf.h:70,71,72,73";
	/* <Root>/Derivative1 */
	this.urlHashMap["PV_vsi_sf:154"] = "PV_vsi_sf.c:187,212,303,322,474&PV_vsi_sf.h:66,67,68,69";
	/* <Root>/Gain */
	this.urlHashMap["PV_vsi_sf:147"] = "PV_vsi_sf.c:272";
	/* <Root>/Gain1 */
	this.urlHashMap["PV_vsi_sf:150"] = "PV_vsi_sf.c:279";
	/* <Root>/Gain2 */
	this.urlHashMap["PV_vsi_sf:155"] = "PV_vsi_sf.c:215";
	/* <Root>/Gain4 */
	this.urlHashMap["PV_vsi_sf:259"] = "PV_vsi_sf.c:280";
	/* <Root>/Integrator */
	this.urlHashMap["PV_vsi_sf:161"] = "PV_vsi_sf.c:222,233,381,392,478&PV_vsi_sf.h:79,86,93";
	/* <Root>/MATLAB Function SOC  */
	this.urlHashMap["PV_vsi_sf:292"] = "PV_vsi_sf.c:232";
	/* <Root>/Product2 */
	this.urlHashMap["PV_vsi_sf:151"] = "PV_vsi_sf.c:284";
	/* <Root>/Sine Wave */
	this.urlHashMap["PV_vsi_sf:145"] = "PV_vsi_sf.c:242&PV_vsi_sf.h:58";
	/* <Root>/Sum2 */
	this.urlHashMap["PV_vsi_sf:148"] = "PV_vsi_sf.c:273";
	/* <Root>/Sum3 */
	this.urlHashMap["PV_vsi_sf:149"] = "PV_vsi_sf.c:271&PV_vsi_sf.h:59";
	/* <Root>/Sum4 */
	this.urlHashMap["PV_vsi_sf:152"] = "PV_vsi_sf.c:278&PV_vsi_sf.h:60";
	/* <Root>/Sum5 */
	this.urlHashMap["PV_vsi_sf:157"] = "PV_vsi_sf.c:214";
	/* <Root>/Sum7 */
	this.urlHashMap["PV_vsi_sf:280"] = "PV_vsi_sf.c:294&PV_vsi_sf.h:61";
	/* <Root>/VSI  line Z */
	this.urlHashMap["PV_vsi_sf:156"] = "PV_vsi_sf.c:184,376,471&PV_vsi_sf.h:78,85,92";
	/* <Root>/i3 */
	this.urlHashMap["PV_vsi_sf:288"] = "PV_vsi_sf.c:219&PV_vsi_sf.h:129";
	/* <Root>/SOC */
	this.urlHashMap["PV_vsi_sf:290"] = "PV_vsi_sf.c:239&PV_vsi_sf.h:130";
	/* <S1>/Constant2 */
	this.urlHashMap["PV_vsi_sf:135"] = "msg=rtwMsg_CodeGenerationReducedBlock&block=PV_vsi_sf:135";
	/* <S1>/Gain2 */
	this.urlHashMap["PV_vsi_sf:136"] = "PV_vsi_sf.c:281";
	/* <S1>/Sum5 */
	this.urlHashMap["PV_vsi_sf:137"] = "PV_vsi_sf.c:285";
	/* <S1>/Sum9 */
	this.urlHashMap["PV_vsi_sf:138"] = "msg=rtwMsg_CodeGenerationReducedBlock&block=PV_vsi_sf:138";
	/* <S1>/Transfer Fcn2 */
	this.urlHashMap["PV_vsi_sf:139"] = "PV_vsi_sf.c:286,394,485&PV_vsi_sf.h:80,87,94";
	/* <S2>:1 */
	this.urlHashMap["PV_vsi_sf:292:1"] = "PV_vsi_sf.c:235";
	/* <S2>:1:3 */
	this.urlHashMap["PV_vsi_sf:292:1:3"] = "PV_vsi_sf.c:236";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "PV_vsi_sf"};
	this.sidHashMap["PV_vsi_sf"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "PV_vsi_sf:142"};
	this.sidHashMap["PV_vsi_sf:142"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "PV_vsi_sf:292"};
	this.sidHashMap["PV_vsi_sf:292"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<Root>/Vload"] = {sid: "PV_vsi_sf:289"};
	this.sidHashMap["PV_vsi_sf:289"] = {rtwname: "<Root>/Vload"};
	this.rtwnameHashMap["<Root>/Ipv"] = {sid: "PV_vsi_sf:291"};
	this.sidHashMap["PV_vsi_sf:291"] = {rtwname: "<Root>/Ipv"};
	this.rtwnameHashMap["<Root>/1-D Lookup Table2"] = {sid: "PV_vsi_sf:164"};
	this.sidHashMap["PV_vsi_sf:164"] = {rtwname: "<Root>/1-D Lookup Table2"};
	this.rtwnameHashMap["<Root>/Control PR VSI"] = {sid: "PV_vsi_sf:142"};
	this.sidHashMap["PV_vsi_sf:142"] = {rtwname: "<Root>/Control PR VSI"};
	this.rtwnameHashMap["<Root>/Derivative"] = {sid: "PV_vsi_sf:146"};
	this.sidHashMap["PV_vsi_sf:146"] = {rtwname: "<Root>/Derivative"};
	this.rtwnameHashMap["<Root>/Derivative1"] = {sid: "PV_vsi_sf:154"};
	this.sidHashMap["PV_vsi_sf:154"] = {rtwname: "<Root>/Derivative1"};
	this.rtwnameHashMap["<Root>/From5"] = {sid: "PV_vsi_sf:160"};
	this.sidHashMap["PV_vsi_sf:160"] = {rtwname: "<Root>/From5"};
	this.rtwnameHashMap["<Root>/From6"] = {sid: "PV_vsi_sf:162"};
	this.sidHashMap["PV_vsi_sf:162"] = {rtwname: "<Root>/From6"};
	this.rtwnameHashMap["<Root>/Gain"] = {sid: "PV_vsi_sf:147"};
	this.sidHashMap["PV_vsi_sf:147"] = {rtwname: "<Root>/Gain"};
	this.rtwnameHashMap["<Root>/Gain1"] = {sid: "PV_vsi_sf:150"};
	this.sidHashMap["PV_vsi_sf:150"] = {rtwname: "<Root>/Gain1"};
	this.rtwnameHashMap["<Root>/Gain2"] = {sid: "PV_vsi_sf:155"};
	this.sidHashMap["PV_vsi_sf:155"] = {rtwname: "<Root>/Gain2"};
	this.rtwnameHashMap["<Root>/Gain4"] = {sid: "PV_vsi_sf:259"};
	this.sidHashMap["PV_vsi_sf:259"] = {rtwname: "<Root>/Gain4"};
	this.rtwnameHashMap["<Root>/Goto6"] = {sid: "PV_vsi_sf:158"};
	this.sidHashMap["PV_vsi_sf:158"] = {rtwname: "<Root>/Goto6"};
	this.rtwnameHashMap["<Root>/Goto7"] = {sid: "PV_vsi_sf:159"};
	this.sidHashMap["PV_vsi_sf:159"] = {rtwname: "<Root>/Goto7"};
	this.rtwnameHashMap["<Root>/Integrator"] = {sid: "PV_vsi_sf:161"};
	this.sidHashMap["PV_vsi_sf:161"] = {rtwname: "<Root>/Integrator"};
	this.rtwnameHashMap["<Root>/MATLAB Function SOC "] = {sid: "PV_vsi_sf:292"};
	this.sidHashMap["PV_vsi_sf:292"] = {rtwname: "<Root>/MATLAB Function SOC "};
	this.rtwnameHashMap["<Root>/Product2"] = {sid: "PV_vsi_sf:151"};
	this.sidHashMap["PV_vsi_sf:151"] = {rtwname: "<Root>/Product2"};
	this.rtwnameHashMap["<Root>/Sine Wave"] = {sid: "PV_vsi_sf:145"};
	this.sidHashMap["PV_vsi_sf:145"] = {rtwname: "<Root>/Sine Wave"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "PV_vsi_sf:148"};
	this.sidHashMap["PV_vsi_sf:148"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<Root>/Sum3"] = {sid: "PV_vsi_sf:149"};
	this.sidHashMap["PV_vsi_sf:149"] = {rtwname: "<Root>/Sum3"};
	this.rtwnameHashMap["<Root>/Sum4"] = {sid: "PV_vsi_sf:152"};
	this.sidHashMap["PV_vsi_sf:152"] = {rtwname: "<Root>/Sum4"};
	this.rtwnameHashMap["<Root>/Sum5"] = {sid: "PV_vsi_sf:157"};
	this.sidHashMap["PV_vsi_sf:157"] = {rtwname: "<Root>/Sum5"};
	this.rtwnameHashMap["<Root>/Sum7"] = {sid: "PV_vsi_sf:280"};
	this.sidHashMap["PV_vsi_sf:280"] = {rtwname: "<Root>/Sum7"};
	this.rtwnameHashMap["<Root>/VSI  line Z"] = {sid: "PV_vsi_sf:156"};
	this.sidHashMap["PV_vsi_sf:156"] = {rtwname: "<Root>/VSI  line Z"};
	this.rtwnameHashMap["<Root>/i3"] = {sid: "PV_vsi_sf:288"};
	this.sidHashMap["PV_vsi_sf:288"] = {rtwname: "<Root>/i3"};
	this.rtwnameHashMap["<Root>/SOC"] = {sid: "PV_vsi_sf:290"};
	this.sidHashMap["PV_vsi_sf:290"] = {rtwname: "<Root>/SOC"};
	this.rtwnameHashMap["<S1>/Ierror"] = {sid: "PV_vsi_sf:143"};
	this.sidHashMap["PV_vsi_sf:143"] = {rtwname: "<S1>/Ierror"};
	this.rtwnameHashMap["<S1>/Constant2"] = {sid: "PV_vsi_sf:135"};
	this.sidHashMap["PV_vsi_sf:135"] = {rtwname: "<S1>/Constant2"};
	this.rtwnameHashMap["<S1>/Gain2"] = {sid: "PV_vsi_sf:136"};
	this.sidHashMap["PV_vsi_sf:136"] = {rtwname: "<S1>/Gain2"};
	this.rtwnameHashMap["<S1>/Sum5"] = {sid: "PV_vsi_sf:137"};
	this.sidHashMap["PV_vsi_sf:137"] = {rtwname: "<S1>/Sum5"};
	this.rtwnameHashMap["<S1>/Sum9"] = {sid: "PV_vsi_sf:138"};
	this.sidHashMap["PV_vsi_sf:138"] = {rtwname: "<S1>/Sum9"};
	this.rtwnameHashMap["<S1>/Transfer Fcn2"] = {sid: "PV_vsi_sf:139"};
	this.sidHashMap["PV_vsi_sf:139"] = {rtwname: "<S1>/Transfer Fcn2"};
	this.rtwnameHashMap["<S1>/d"] = {sid: "PV_vsi_sf:144"};
	this.sidHashMap["PV_vsi_sf:144"] = {rtwname: "<S1>/d"};
	this.rtwnameHashMap["<S2>:1"] = {sid: "PV_vsi_sf:292:1"};
	this.sidHashMap["PV_vsi_sf:292:1"] = {rtwname: "<S2>:1"};
	this.rtwnameHashMap["<S2>:1:3"] = {sid: "PV_vsi_sf:292:1:3"};
	this.sidHashMap["PV_vsi_sf:292:1:3"] = {rtwname: "<S2>:1:3"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
