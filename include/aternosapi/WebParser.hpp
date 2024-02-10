#pragma once
#include <optional>
#include <libxml2/libxml/xpath.h>
#include <string>

class WebParser{
	public:
	WebParser(std::string);
	void cleanWebParser();
	std::optional<xmlNodeSetPtr> EvalXPath(std::string);
	private:
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlXPathContextPtr xpathctx;
	xmlXPathObjectPtr xpathobj;
};