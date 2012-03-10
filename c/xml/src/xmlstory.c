/*

gcc `xml2-config --cflags --libs` -o xmlstory xmlstory.c
./xmlstory story.xml 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void parseStory(xmlDocPtr doc, xmlNodePtr cur)
{

	xmlChar *v = NULL;

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {


		fprintf(stderr, "cur->name=%s\n", cur->name);
		/*
		   This will be the contents of the mtag. See story.xml
		 */
		v = xmlGetProp(cur, "mtag");
		if (v != NULL)
			fprintf(stderr, "\nv=%s\n", v);


		if ((!xmlStrcmp(cur->name, (const xmlChar *) "keyword"))) {
			v = xmlNodeListGetString(doc, cur->xmlChildrenNode,
						 1);
			printf("keyword: %s\n", v);
			xmlFree(v);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "author"))) {
			v = xmlNodeListGetString(doc, cur->xmlChildrenNode,
						 1);
			printf("author: %s\n", v);
			xmlFree(v);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "link"))) {
			v = xmlNodeListGetString(doc, cur->xmlChildrenNode,
						 1);
			printf("link: %s\n", v);
			xmlFree(v);
		}
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "stuff"))) {
			v = xmlNodeListGetString(doc, cur->xmlChildrenNode,
						 1);
			printf("stuff: %s\n", v);
			xmlFree(v);
		}
		cur = cur->next;
	}
	return;
}

static void parseDoc(char *docname)
{

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "story")) {
		fprintf(stderr,
			"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return;
	}

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "storyinfo"))) {
			parseStory(doc, cur);
		}

		cur = cur->next;
	}

	xmlFreeDoc(doc);
	return;
}

int main(int argc, char **argv)
{

	char *docname;

	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return (0);
	}

	docname = argv[1];
	parseDoc(docname);

	return (1);
}
