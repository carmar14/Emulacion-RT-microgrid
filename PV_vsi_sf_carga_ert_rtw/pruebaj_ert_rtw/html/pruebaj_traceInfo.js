function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/In1 */
	this.urlHashMap["pruebaj:306"] = "pruebaj.c:151&pruebaj.h:81";
	/* <Root>/VSI  line Z1 */
	this.urlHashMap["pruebaj:302"] = "pruebaj.c:117,150,211&pruebaj.h:55,60,65";
	/* <Root>/Out1 */
	this.urlHashMap["pruebaj:304"] = "pruebaj.c:116&pruebaj.h:86";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "pruebaj"};
	this.sidHashMap["pruebaj"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/In1"] = {sid: "pruebaj:306"};
	this.sidHashMap["pruebaj:306"] = {rtwname: "<Root>/In1"};
	this.rtwnameHashMap["<Root>/VSI  line Z1"] = {sid: "pruebaj:302"};
	this.sidHashMap["pruebaj:302"] = {rtwname: "<Root>/VSI  line Z1"};
	this.rtwnameHashMap["<Root>/Out1"] = {sid: "pruebaj:304"};
	this.sidHashMap["pruebaj:304"] = {rtwname: "<Root>/Out1"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
