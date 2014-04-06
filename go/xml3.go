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

<log4j:event logger="tfms.interfacelog.FOS_INBOUND" timestamp="14/03/19 20:01:03" timestampepoch="1395259263190" level="INTERFACE" thread="WorkExecutorWorkerThread-80">
<log4j:message><![CDATA[Base64:
AAABTgAAAAAAAAB1AAADjgAAEmkAAAB1PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9InllcyI/Pgo8Rk9TX0lOUFVUPgogICAgPENUT1BfTElTVF9SRVE+PC9DVE9QX0xJU1RfUkVRPgo8L0ZPU19JTlBVVD4K]]></log4j:message>
<log4j:NDC><![CDATA[EdgeClass=FOSIncomingServiceMDB UUID=9868d245-055b-444a-b2bf-41f7d898fff4 InTFMSSoftwareScope=true]]></log4j:NDC>
</log4j:event>



`
	err := xml.Unmarshal([]byte(data), &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	//fmt.Printf("XMLName: %v\n", v.XMLName)
	fmt.Printf("v: %#v\n", v.Timestamp)
	fmt.Printf("timestampepoch: %q\n", v.Epoch)
	fmt.Printf("level: %q\n", v.Level)
	fmt.Printf("thread: %v\n", v.Thread)
	fmt.Printf("Groups: %v\n", v.Groups)
	fmt.Printf("Address: %v\n", v.Address)
}
