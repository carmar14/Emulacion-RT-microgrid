function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Step */
	this.urlHashMap["pruebaj2:305"] = "pruebaj2.c:122&pruebaj2.h:55";
	/* <Root>/VSI  line Z1 */
	this.urlHashMap["pruebaj2:302"] = "pruebaj2.c:125,163,228&pruebaj2.h:56,62,68,74";
	/* <Root>/VSI  line Z2 */
	this.urlHashMap["pruebaj2:306"] = "pruebaj2.c:118,158,225&pruebaj2.h:61,67,73";
	/* <Root>/Out1 */
	this.urlHashMap["pruebaj2:304"] = "pruebaj2.c:117&pruebaj2.h:90";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "pruebaj2"};
	this.sidHashMap["pruebaj2"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Step"] = {sid: "pruebaj2:305"};
	this.sidHashMap["pruebaj2:305"] = {rtwname: "<Root>/Step"};
	this.rtwnameHashMap["<Root>/VSI  line Z1"] = {sid: "pruebaj2:302"};
	this.sidHashMap["pruebaj2:302"] = {rtwname: "<Root>/VSI  line Z1"};
	this.rtwnameHashMap["<Root>/VSI  line Z2"] = {sid: "pruebaj2:306"};
	this.sidHashMap["pruebaj2:306"] = {rtwname: "<Root>/VSI  line Z2"};
	this.rtwnameHashMap["<Root>/Out1"] = {sid: "pruebaj2:304"};
	this.sidHashMap["pruebaj2:304"] = {rtwname: "<Root>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
