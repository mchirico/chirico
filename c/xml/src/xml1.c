#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



char * createdoc()
{
  static char *c=
"<?xml version=\"1.0\"?>\n \
<googleauth>\n\
  <googleauthinfo>\n\
    <author>John Fleck</author>\n\
    <datewritten>June 2, 2002</datewritten>\n\
    <keyword  mtag='contents of m'>example keyword</keyword>\n\
    <link rel='alternate' type='text/html'>Special Link</link>\n\
    <stuff>This is stuff <more> Here </more> </stuff>\n\
  </googleauthinfo>\n\
<junk   bug=\"bugstuff to get removed\">\n\
This is junk stuff\n\
</junk>\n\
<garbage>this is garbage and will get deleted</garbage>\n\
</googleauth>\n\
";
    return c;
}



void parseStory(xmlDocPtr doc, xmlNodePtr cur, char *keyword)
{

  fprintf(stderr,"in parseStory\n");

	xmlAttrPtr newattr;
	xmlNodePtr newnode;

	xmlNewTextChild(cur, NULL, "keyword", keyword);

	newnode =
	    xmlNewTextChild(cur, NULL, "reference",
			    "Contents of Reference");
	newattr = xmlNewProp(newnode, "uri", "uristuff");
	newattr = xmlNewProp(newnode, "stuff", "***some stuff here****");
	return;
}

xmlDocPtr parseDoc(char *docmem, char *uri)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlNodePtr next;

	xmlAttrPtr newattr;
	doc = xmlParseMemory(docmem,strlen(docmem));

	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully. \n");
		return (NULL);
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return (NULL);
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "googleauth")) {
		fprintf(stderr,
			"document of the wrong type, root node != googleauth");
		xmlFreeDoc(doc);
		return (NULL);
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		fprintf(stderr, "cur->name: %s\n", cur->name);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "googleauthinfo"))) {
			parseStory(doc, cur, "keyword");
		}


		if ((!xmlStrcmp(cur->name, (const xmlChar *) "junk"))) {
		  // Example of deleting an attribute
		  		  xmlUnsetProp(cur, (const xmlChar *) "bug");
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *) "garbage"))) {

				  //This will delete a complete node
				  next = cur->next;
				  xmlUnlinkNode(cur);
				   xmlFreeNode(cur);
				  cur=next;

		}
		cur = cur->next;
	}


	return (doc);
}

int main(int argc, char **argv)
{
	char *docmem;
	char *uri="attgarbo";
	xmlDocPtr doc;
	xmlChar *xmlbuff;
	int buffersize;

	docmem=createdoc();


	doc = parseDoc(docmem, uri);
	//	doc = xmlReadMemory(docmem, strlen(docmem), "include.xml", NULL, 0);



	if (doc != NULL) {
		xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
		fprintf(stderr, "Length=(%d)\n******\n%s\n******\n", buffersize,xmlbuff);
		xmlFree(xmlbuff);


		xmlSaveFormatFile("googleauthoutxml1.xml", doc, 1);
		xmlCleanupParser(); /* ? */
		xmlFreeDoc(doc);

	}

	return (1);
}
