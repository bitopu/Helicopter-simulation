function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/Constant8 */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1072"] = "MainRotor.c:303,308,311,314&MainRotor.h:88,89&MainRotor_data.c:66";
	/* <S1>/Display */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1074"] = "msg=rtwMsg_reducedBlock&block=test_HelicopterModelingSimulation_disc_copy:1074";
	/* <S1>/Display1 */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1075"] = "msg=rtwMsg_reducedBlock&block=test_HelicopterModelingSimulation_disc_copy:1075";
	/* <S1>/Rotor1 */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1078"] = "MainRotor.c:151,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,184,185,186,188,191,192,193,195,198,199,200,201,202,203,204,205,206,207,208,210,215,216,219,222,223,224,225,228,229,230,232,233,235,236,238,239,240,241,248,249,252,253,254,257,262,265,266,267,268,271,279,280,282,283,284,288,289,290,291,292,293,294,295,296,297,298,299,300,318,321,327,330,333,339,342,345,351&MainRotor.h:53,54,55,61,62,64,65,67,68,70,71,73,74,76,77,79,80,82,83,85,86&MainRotor_data.c:21,26,31,36,41,46,51,56,61";
	/* <S1>/Scope2 */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1081"] = "msg=rtwMsg_reducedBlock&block=test_HelicopterModelingSimulation_disc_copy:1081";
	/* <S1>/Sum1 */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1082"] = "MainRotor.c:324,327,336,339,348,351";
	/* <S2>/Element
Product */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1073:38"] = "MainRotor.c:305,307,308,309,310,311,312,313,314,315";
	/* <S2>/Sum */
	this.urlHashMap["test_HelicopterModelingSimulation_disc_copy:1073:41"] = "MainRotor.c:302,317,318,320,321,325,329,330,332,333,337,341,342,344,345,349&MainRotor.h:56";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "MainRotor"};
	this.sidHashMap["MainRotor"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1062"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1062"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S1>/SpeedM"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1063"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1063"] = {rtwname: "<S1>/SpeedM"};
	this.rtwnameHashMap["<S1>/CollectiveM"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1064"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1064"] = {rtwname: "<S1>/CollectiveM"};
	this.rtwnameHashMap["<S1>/CyclicLat"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1065"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1065"] = {rtwname: "<S1>/CyclicLat"};
	this.rtwnameHashMap["<S1>/CyclicLon"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1066"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1066"] = {rtwname: "<S1>/CyclicLon"};
	this.rtwnameHashMap["<S1>/rho"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1589"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1589"] = {rtwname: "<S1>/rho"};
	this.rtwnameHashMap["<S1>/wb"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1067"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1067"] = {rtwname: "<S1>/wb"};
	this.rtwnameHashMap["<S1>/Vb"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1068"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1068"] = {rtwname: "<S1>/Vb"};
	this.rtwnameHashMap["<S1>/Constant8"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1072"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1072"] = {rtwname: "<S1>/Constant8"};
	this.rtwnameHashMap["<S1>/Cross Product1"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073"] = {rtwname: "<S1>/Cross Product1"};
	this.rtwnameHashMap["<S1>/Display"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1074"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1074"] = {rtwname: "<S1>/Display"};
	this.rtwnameHashMap["<S1>/Display1"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1075"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1075"] = {rtwname: "<S1>/Display1"};
	this.rtwnameHashMap["<S1>/Rotor1"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1078"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1078"] = {rtwname: "<S1>/Rotor1"};
	this.rtwnameHashMap["<S1>/Scope2"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1081"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1081"] = {rtwname: "<S1>/Scope2"};
	this.rtwnameHashMap["<S1>/Sum1"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1082"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1082"] = {rtwname: "<S1>/Sum1"};
	this.rtwnameHashMap["<S1>/Fm"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1083"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1083"] = {rtwname: "<S1>/Fm"};
	this.rtwnameHashMap["<S1>/Mm"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1084"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1084"] = {rtwname: "<S1>/Mm"};
	this.rtwnameHashMap["<S2>/a"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:36"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:36"] = {rtwname: "<S2>/a"};
	this.rtwnameHashMap["<S2>/b"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:37"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:37"] = {rtwname: "<S2>/b"};
	this.rtwnameHashMap["<S2>/Element Product"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:38"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:38"] = {rtwname: "<S2>/Element Product"};
	this.rtwnameHashMap["<S2>/Selector2"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:39"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:39"] = {rtwname: "<S2>/Selector2"};
	this.rtwnameHashMap["<S2>/Selector3"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:40"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:40"] = {rtwname: "<S2>/Selector3"};
	this.rtwnameHashMap["<S2>/Sum"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:41"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:41"] = {rtwname: "<S2>/Sum"};
	this.rtwnameHashMap["<S2>/a elements"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:42"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:42"] = {rtwname: "<S2>/a elements"};
	this.rtwnameHashMap["<S2>/b elements"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:43"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:43"] = {rtwname: "<S2>/b elements"};
	this.rtwnameHashMap["<S2>/y"] = {sid: "test_HelicopterModelingSimulation_disc_copy:1073:44"};
	this.sidHashMap["test_HelicopterModelingSimulation_disc_copy:1073:44"] = {rtwname: "<S2>/y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
