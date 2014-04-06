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
	type Address struct {
		City, State string
	}
	type Result struct {
		XMLName xml.Name `xml:"Person"`
		Name    string   `xml:"FullName"`
		T       []string `xml:"Thing>one"`
		T2      []string `xml:"Thing>more"`
		T3      []string `xml:"Thing>special>little"`
		Company string
		Phone   string
		Email   []Email
		Groups  []string `xml:"Group>Value"`
		Address
	}
	v := Result{Name: "none", Phone: "none"}

	data := `
<Person>
<FullName>Grace R. Emlin</FullName>
<Company>Example Inc.</Company>
<Thing> 
<one>one</one>
             <one>two</one>
             <more>more</more>
        <more>here</more>
        <special>  <little>hidden</little></special>
</Thing>
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
</Person>
`
	err := xml.Unmarshal([]byte(data), &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	fmt.Printf("XMLName: %#v\n", v.XMLName)
	fmt.Printf("Name: %q\n", v.Name)
	fmt.Printf("Company: %q\n", v.Company)
	fmt.Printf("Phone: %q\n", v.Phone)
	fmt.Printf("T: %q\n", v.T)
	fmt.Printf("T2: %q\n", v.T2)
	fmt.Printf("T3: %q\n", v.T3)
	fmt.Printf("Email: %v\n", v.Email)
	fmt.Printf("Groups: %v\n", v.Groups)
	fmt.Printf("Address: %v\n", v.Address)
	fmt.Printf("v=, %v\n", v)
}
