const sin_lookup_fp8_8[32] = { 
	0x0000,0x0032,0x0062,0x008e,0x00b5,0x00d5,0x00ed,0x00fb,0x0100,0x00fb,0x00ed,0x00d5,0x00b5,0x008e,0x0062,0x0032,0x0000,0xffce,0xff9e,0xff72,0xff4b,0xff2b,0xff13,0xff05,0xff00,0xff05,0xff13,0xff2b,0xff4b,0xff72,0xff9e,0xffce,};
const cos_lookup_fp8_8[32] = { 
	0x0100,0x00fb,0x00ed,0x00d5,0x00b5,0x008e,0x0062,0x0032,0x0000,0xffce,0xff9e,0xff72,0xff4b,0xff2b,0xff13,0xff05,0xff00,0xff05,0xff13,0xff2b,0xff4b,0xff72,0xff9e,0xffce,0x0000,0x0032,0x0062,0x008e,0x00b5,0x00d5,0x00ed,0x00fb,};
// start: 28
// radius: 90.509668
const xpos_diff[32] = { 
	-64,-50,-34,-17,0  ,17 ,34 ,50 ,64 ,75 ,83 ,88 ,90 ,88 ,83 ,75 ,64 ,50 ,34 ,17 ,0  ,-17,-34,-50,-64,-75,-83,-88,-90,-88,-83,-75,};
const ypos_diff[32] = { 
	-63,-75,-83,-88,-90,-88,-83,-75,-64,-50,-34,-17,0  ,17 ,34 ,50 ,64 ,75 ,83 ,88 ,90 ,88 ,83 ,75 ,64 ,50 ,34 ,17 ,0  ,-17,-34,-50,};