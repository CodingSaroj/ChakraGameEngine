#include "Reader.hpp"

namespace Chakra
{
    namespace XML
    {
        Reader::Reader(const std::string & rawData)
        {
            xmlParserCtxtPtr ctxt = xmlCreateDocParserCtxt((const xmlChar *)"reader");
            xmlInitParserCtxt(ctxt);
        
            xmlDocPtr doc = xmlCtxtReadMemory(ctxt, rawData.c_str(), rawData.size(), nullptr, nullptr, XML_PARSE_DTDATTR | XML_PARSE_DTDVALID);
        
            xmlValidCtxtPtr vctxt = xmlNewValidCtxt();
        
            if (xmlValidateDocument(vctxt, doc) != 1)
            {
                Logger::LogError("XML::Reader", "XML validation failed");
                xmlFreeValidCtxt(vctxt);
                xmlFreeDoc(doc);
                xmlFreeParserCtxt(ctxt);
                exit(-1);
            }
        
            xmlFreeValidCtxt(vctxt);
        
        
            xmlNodePtr root = xmlDocGetRootElement(doc);
        
            processNode(&m_Root, root);
        
            xmlFreeDoc(doc);
            xmlFreeParserCtxt(ctxt);
        }
        
        void Reader::processNode(Node ** target, xmlNodePtr node)
        {
            std::unordered_map<std::string, Attribute> attributes;
        
            _xmlAttr * attr  = node->properties;
        
            while (true)
            {
                if (!attr)
                {
                    break;
                }
        
                attributes.emplace((const char *)attr->name, Attribute((const char *)attr->children->content));
        
                attr = attr->next;
            }
        
            std::unordered_map<std::string, Node *> children;
        
            xmlNodePtr child  = node->children->next;
        
            while (true)
            {
                if (!child)
                {
                    break;
                }
        
                Node * target = nullptr;
                processNode(&target, child);
        
                children[(const char *)child->name] = target;
        
                if (!child->next)
                {
                    break;
                }
                child = child->next->next;
            }
        
            *target = new Node((const char *)node->name, attributes, (const char *)node->children->content, children);
        }
        
        Node Reader::getRootNode()
        {
            return *m_Root;
        }
    }
}
