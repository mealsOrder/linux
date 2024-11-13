#include <cstdint>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>

#include "tinyxml/tinyxml.h"
#include "config.hpp"
#include <iostream>

namespace config {
    void SDV::Load(TiXmlElement* sub) {
        assert(sub != nullptr);
        TiXmlElement* elem = nullptr;
        elem = sub->FirstChildElement("qamIp");
        if (elem && elem->GetText()) {
            qam_ip = elem->GetText();
        }

        elem = sub->FirstChildElement("qamPort");
        if(elem && elem->GetText()) {
            qam_port = std::stoi(elem->GetText());
        }

        
    }
}