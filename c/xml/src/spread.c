#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *createdoc()
{
	static char *c = "<?xml version='1.0' encoding='utf-8'?>\
<feed xmlns='http://www.w3.org/2005/Atom'\
xmlns:openSearch='http://a9.com/-/spec/opensearchrss/1.0/'\
xmlns:gs='http://schemas.google.com/spreadsheets/2006'\
xmlns:batch='http://schemas.google.com/gdata/batch'>\
  <id>\
  http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full</id>\
  <updated>2008-07-09T17:29:46.585Z</updated>\
  <category scheme='http://schemas.google.com/spreadsheets/2006'\
  term='http://schemas.google.com/spreadsheets/2006#cell' />\
  <title type='text'>Sheet2</title>\
  <link rel='alternate' type='text/html'\
  href='http://spreadsheets.google.com/ccc?key=o02033738628008092337.7901402712316103813' />\
  <link rel='http://schemas.google.com/g/2005#feed'\
  type='application/atom+xml'\
  href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full' />\
  <link rel='http://schemas.google.com/g/2005#post'\
  type='application/atom+xml'\
  href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full' />\
  <link rel='http://schemas.google.com/g/2005#batch'\
  type='application/atom+xml'\
  href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/batch' />\
  <link rel='self' type='application/atom+xml'\
  href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full' />\
  <author>\
    <name>dev.mchirico</name>\
    <email>dev.mchirico@gmail.com</email>\
  </author>\
  <openSearch:totalResults>3</openSearch:totalResults>\
  <openSearch:startIndex>1</openSearch:startIndex>\
  <gs:rowCount>27</gs:rowCount>\
  <gs:colCount>8</gs:colCount>\
  <entry>\
    <id>\
    http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R1C1</id>\
    <updated>2008-07-09T17:29:46.585Z</updated>\
    <category scheme='http://schemas.google.com/spreadsheets/2006'\
    term='http://schemas.google.com/spreadsheets/2006#cell' />\
    <title type='text'>A1</title>\
    <content type='text'>2.5</content>\
    <link rel='self' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R1C1' />\
    <link rel='edit' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R1C1/3bw6t5' />\
    <gs:cell row='1' col='1' inputValue='=average(1,2,3,4)'\
    numericValue='2.5'>2.5</gs:cell>\
  </entry>\
  <entry>\
    <id>\
    http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R2C1</id>\
    <updated>2008-07-09T17:29:46.585Z</updated>\
    <category scheme='http://schemas.google.com/spreadsheets/2006'\
    term='http://schemas.google.com/spreadsheets/2006#cell' />\
    <title type='text'>A2</title>\
    <content type='text'>22.3538906808508</content>\
    <link rel='self' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R2C1' />\
    <link rel='edit' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R2C1/rh5gx3' />\
    <gs:cell row='2' col='1'\
    inputValue='=stdev(1,2,3,4,34,34,45,56)'\
    numericValue='22.353890680850807'>22.3538906808508</gs:cell>\
  </entry>\
  <entry>\
    <id>\
    http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R3C1</id>\
    <updated>2008-07-09T17:29:46.585Z</updated>\
    <category scheme='http://schemas.google.com/spreadsheets/2006'\
    term='http://schemas.google.com/spreadsheets/2006#cell' />\
    <title type='text'>A3</title>\
    <content type='text'>Sample data</content>\
    <link rel='self' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R3C1' />\
    <link rel='edit' type='application/atom+xml'\
    href='http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R3C1/s1g4lc' />\
    <gs:cell row='3' col='1' inputValue='Sample data'>Sample\
    data</gs:cell>\
  </entry>\
</feed>";
	return c;
}



void parseStory(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	xmlChar *attrb[3];
	xmlAttrPtr newattr;
	xmlNodePtr newnode;
	xmlNodePtr next;

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "link"))) {
			attrb[0] = xmlGetProp(cur, "rel");
			if ((!xmlStrcmp
			     (attrb[0], (const xmlChar *) "edit"))) {
				printf("rel: %s\n", attrb[0]);
				attrb[1] = xmlGetProp(cur, "href");
				printf("href: %s\n", attrb[1]);
				xmlFree(attrb[1]);
			}
			xmlFree(attrb[0]);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *) "cell"))) {
			attrb[0] = xmlGetProp(cur, "row");
			attrb[1] = xmlGetProp(cur, "col");
			attrb[2] = xmlGetProp(cur, "inputValue");
			key =  xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
			printf("(row,col): (%s,%s) key=%s inputValue='%s'\n", attrb[0],attrb[1],key,attrb[2]);
			xmlFree(attrb[2]);
			xmlFree(key);
			xmlFree(attrb[1]);
			xmlFree(attrb[0]);
		}


		cur = cur->next;
	}
	return;


}


int main(void)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	char *docmem;

	docmem = createdoc();

	doc = xmlParseMemory(docmem, strlen(docmem));
	if (doc == NULL) {
		return;
	}

	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "entry"))) {
			parseStory(doc, cur);
		}
		cur = cur->next;
	}
	xmlSaveFormatFile("spread.xml", doc, 1);

	xmlFreeDoc(doc);
	xmlCleanupParser();

}
