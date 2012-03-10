#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char *createdoc()
{
	static char *c = "<?xml version=\"1.0\"?>\n \
<googleauth>\n\
  <googleauthinfo>\n\
    <author>John Fleck</author>\n\
     <garbage>this is garbage and will get deleted</garbage>\n\
    <datewritten>June 2, 2002</datewritten>\n\
    <keyword  mtag='contents of m'>example keyword</keyword>\n\
    <link rel='alternate' type='text/html'>Special Link</link>\n\
    <stuff>This is stuff <more> Here </more> </stuff>\n\
  </googleauthinfo>\n\
<junk   bug=\"bugstuff to get removed\">\n\
This is junk stuff\n\
</junk>\n\
</googleauth>\n\
";
	return c;
}



void parseStory(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	xmlAttrPtr newattr;
	xmlNodePtr newnode;
	xmlNodePtr next;

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "author"))) {
			key =
			    xmlNodeListGetString(doc, cur->xmlChildrenNode,
						 1);
			fprintf(stderr, "key = %s\n", key);
			xmlFree(key);

			/* Example of adding an attribute */
			newnode =
			    xmlNewTextChild(cur, NULL, "reference",
					    "Contents of Reference");
			newattr = xmlNewProp(newnode, "uri", "uristuff");
			newattr =
			    xmlNewProp(newnode, "stuff",
				       "***some stuff here****");


		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *) "garbage"))) {

				  next = cur->next;
				   xmlUnlinkNode(cur);
				   xmlFreeNode(cur);
				  cur=next;
		
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
		if ((!xmlStrcmp
		     (cur->name, (const xmlChar *) "googleauthinfo"))) {
			parseStory(doc, cur);
		}
		cur = cur->next;
	}
	xmlSaveFormatFile("googleauthouttest.xml", doc, 1);

	xmlFreeDoc(doc);
	xmlCleanupParser();

}
