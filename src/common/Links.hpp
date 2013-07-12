/**
 * @file Links.hpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_LINKS
#define COMMON_LINKS 1

#include <common/Node.hpp>

#include <map>

namespace paradevs { namespace common {

class Node;

class Links : public std::multimap < Node, Node >
{
public:

    typedef std::pair < common::Links::iterator,
                        common::Links::iterator > Result;

    Links()
    { }
    virtual ~Links()
    { }

    void add(Model* out_model, const std::string& out_port_name,
             Model* in_model, const std::string& in_port_name);

    Result find(Model* out_model, const std::string& out_port_name);

    std::string to_string() const;
};

} } // namespace paradevs common

#endif
