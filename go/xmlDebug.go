/*
  Take a look at the following
  http://blog.davidsingleton.org/parsing-huge-xml-files-with-go/

*/


package main

import (
	"encoding/xml"
	"fmt"
)

func main() {

	type TS struct {
		XMLName   xml.Name `xml:"log4j\:event"`
		Logger    string   `xml:"logger,attr"`
		Timestamp string   `xml:"timestamp,attr"`
		Epoch     string   `xml:"timestampepoch,attr"`
		Level     string   `xml:"level,attr"`
		Thread    string   `xml:"thread,attr"`
	}
	type MSG struct {
		MS string `xml:"message"`
	}
	type NDC struct {
		Data string `xml:"NDC"`
	}

	type Result struct {
		TS
		MSG
		NDC
	}

	v := Result{}

	data := `


<log4j:event logger="gov.faa.tfms.domain.FXAManagementService.IFXAManagementService" timestamp="13/07/02 22:00:00" 
timestampepoch="1372802400389"
 level="DEBUG" thread="WorkExecutorWorkerThread-107">^M
<log4j:message><![CDATA[Description: FXAAnalysisService: Primary filter check 
performed, Flight UAL750 passed filtering check for 8 FXAs. Intersections will be computed 
for these FXAs. The FXAs are as follows in the format [<name>, <fxa idfr>, <definition idfr>]: [FEA_MCO, 993501262, 2265501581] [FCAJX1, 1114501201, 2270501552] [FCAJX7, 1114501301, 2261501502] [FCAJX2, 1114501501, 2261501604] [FCAMCO, 1115001262, 2275501557]
 [FCAJX5, 1115501406, 2262501690] [NE_2_FL_RERTE, 1116001330, 2273501578] [MCO_EAST, 1117001277, 2276501526] ]]></log4j:message>^M
<log4j:NDC><![CDATA[MessageUUID=54329344-6812-46aa-a463-59364032f2a2 
EdgeClass=ManageNCSMFlightUpdatesMDB UUID=8f84578f-0dcb-4be3-a04b-a849cbe040bf InTFMSSoftwareScope=true]]></log4j:NDC>^M


</log4j:event>^

`
	err := xml.Unmarshal([]byte(data), &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}

	fmt.Printf("v: %v\n", v.Timestamp)
	fmt.Printf("v: %v\n", v.MSG)
	fmt.Printf("v: %v\n", v.Data)

}
