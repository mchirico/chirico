package main

import (
	"encoding/xml"
	"fmt"
)

func main() {
	type Email struct {
		Where string `xml:"where,attr"`
		Addr  string
	}
	// <Email where='work'>

	type TS struct {
		XMLName   xml.Name `xml:"log4j\:event"`
		Logger    string   `xml:"logger,attr"`
		Timestamp string   `xml:"timestamp,attr"`
		Epoch     string   `xml:"timestampepoch,attr"`
		Level     string   `xml:"level,attr"`
		Thread    string   `xml:"thread,attr"`
	}

	type Address struct {
		City, State string
	}
	type Result struct {
		TS
		Name   string `xml:"log4j\:message"`
		Phone  string
		Email  []Email
		Groups []string `xml:"Group>Value"`
		Address
	}
	v := Result{Name: "none", Phone: "none"}

	data := `

<log4j:event logger="gov.faa.tfms.domain.DelayProgramManagementService.DelayProgramManagementServiceBean" timestamp="13/07/02 22:00:37" timestampepoch="1372802437354" level="INFO" thread="WorkExecutorWorkerThread-72">

<log4j:message><![CDATA[Description: Exiting DelayProgramManagementService.assessFlightUpdate(Collection<Flight>)]]></log4j:message>
<FullName>Grace R. Emlin</FullName>
<Company>Example Inc.</Company>
<Email where="home">
<Addr>gre@example.com</Addr>
</Email>
<Email where='work'>
<Addr>gre@work.com</Addr>
</Email>
<Group>
<Value>Friends</Value>
<Value>Squash</Value>
</Group>
<City>Hanga Roa</City>
<State>Easter Island</State>
</log4j:event>

`
	err := xml.Unmarshal([]byte(data), &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	//fmt.Printf("XMLName: %v\n", v.XMLName)
	fmt.Printf("v: %#v\n", v.Timestamp)
	fmt.Printf("Name: %q\n", v.Name)
	fmt.Printf("Phone: %q\n", v.Phone)
	fmt.Printf("Email: %v\n", v.Email)
	fmt.Printf("Groups: %v\n", v.Groups)
	fmt.Printf("Address: %v\n", v.Address)
}
