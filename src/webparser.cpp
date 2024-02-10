#include <string>
#include <libxml2/libxml/HTMLparser.h>
#include <libxml2/libxml/xpath.h>
#include "aternosapi/WebParser.hpp"

WebParser::WebParser(std::string html) {
	doc = htmlReadDoc((const xmlChar*)html.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
	root = xmlDocGetRootElement(doc);
	xpathctx = xmlXPathNewContext(doc);
}

std::optional<xmlNodeSetPtr> WebParser::EvalXPath(std::string XPath) {
	xpathobj = xmlXPathEvalExpression((const xmlChar*)XPath.c_str(), xpathctx);
	if (xpathobj) {
		xmlNodeSetPtr nodes = xpathobj->nodesetval;
		if (!xmlXPathNodeSetIsEmpty(nodes)) { return nodes; }
	}
	return {};
}

void WebParser::cleanWebParser() {
	if (xpathobj) { xmlXPathFreeObject(xpathobj); }
	if (xpathctx) { xmlXPathFreeContext(xpathctx); }
    if (doc) { xmlFreeDoc(doc); }
    xmlCleanupParser();
}