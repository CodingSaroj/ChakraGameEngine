#ifndef CHAKRA_META_ASSETS_HPP
#define CHAKRA_META_ASSETS_HPP

#include "core/Common.hpp"

#include "core/Asset.hpp"

#include "xml/Node.hpp"

namespace Chakra
{
    class BinaryData : public Asset
    {
        public:
            BinaryData(const std::string & data);

            std::string getData();

        private:
            std::string m_Data;
    };

    class TextData : public Asset
    {
        public:
            TextData(const std::string & data);

            std::string getData();

        private:
            std::string m_Data;
    };

    class XMLTree : public Asset
    {
        public:
            XMLTree(const XML::Node & root);

            XML::Node getRoot();

        private:
            XML::Node m_Root;
    }; 
}

#endif
