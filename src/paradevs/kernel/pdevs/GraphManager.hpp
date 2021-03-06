/**
 * @file kernel/pdevs/GraphManager.hpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013-2015 ULCO http://www.univ-litoral.fr
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

#ifndef PDEVS_GRAPH_MANANGER
#define PDEVS_GRAPH_MANANGER 1

#include <paradevs/common/Coordinator.hpp>
#include <paradevs/common/Links.hpp>
#include <paradevs/common/Model.hpp>
#include <paradevs/common/Parameters.hpp>
#include <paradevs/common/utils/String.hpp>

#include <sstream>

namespace paradevs { namespace pdevs {

template < class Time,
           class GraphParameters = common::NoParameters >
class GraphManager
{
public:
    GraphManager(common::Coordinator < Time >* coordinator,
                 const GraphParameters& /* parameters */) :
        _coordinator(coordinator)
    { }

    virtual ~GraphManager()
    { }

    void add_child(common::Model < Time >* child)
    {
        _child_list.push_back(child);
        child->set_parent(_coordinator);
    }

    void add_link(common::Model < Time >* src_model,
                  const std::string& src_port_name,
                  common::Model < Time >* dst_model,
                  const std::string& dst_port_name)
    {
        assert((src_model != _coordinator and
                dst_model != _coordinator and
                src_model->exist_out_port(src_port_name) and
                dst_model->exist_in_port(dst_port_name)) or
               (src_model == _coordinator and
                dst_model != _coordinator and
                src_model->exist_in_port(src_port_name) and
                dst_model->exist_in_port(dst_port_name)) or
               (src_model != _coordinator and
                dst_model == _coordinator and
                src_model->exist_out_port(src_port_name) and
                dst_model->exist_out_port(dst_port_name)));

        _link_list.add(src_model, src_port_name, dst_model, dst_port_name);
    }

    const common::Models < Time >& children() const
    { return _child_list; }

    void dispatch_events(common::Bag < Time > bag,
                         typename Time::type t)
    {
        for (auto & ymsg : bag) {
            typename common::Links < Time >::Result result_model =
                _link_list.find(ymsg.get_model(),
                                ymsg.get_port_name());

            for (typename common::Links < Time >::
                     const_iterator it = result_model.first;
                     it != result_model.second; ++it) {
                // event on output port of coupled Model
                if (it->second.get_model() == _coordinator) {
                    dispatch_events_to_parent(it->second, ymsg.get_content(),
                                              t);
                } else { // event on input port of internal model
                    it->second.get_model()->post_event(
                        t, common::ExternalEvent < Time >(
                            it->second, ymsg.get_content()));
                }
            }
        }
    }

    virtual void dispatch_events_to_parent(common::Node < Time > node,
                                           const common::Value& content,
                                           typename Time::type t)
    {
        common::Bag < Time > ymessages;

        ymessages.push_back(
            common::ExternalEvent <Time >(node, content));

        dynamic_cast < common::Coordinator < Time >* >(
            _coordinator->get_parent())->dispatch_events(
                ymessages, t);
    }

    bool exist_link(common::Model < Time >* src_model,
                    const std::string& src_port_name,
                    common::Model < Time >* dst_model,
                    const std::string& dst_port_name) const
    {
        return _link_list.exist(src_model, src_port_name, dst_model,
                                dst_port_name);
    }

    common::Coordinator < Time >* get_coordinator() const
    { return _coordinator; }

    void post_event(typename Time::type t,
                    const common::ExternalEvent < Time >& event)
    {
        typename common::Links < Time >::Result result =
            _link_list.find(_coordinator, event.get_port_name());

        for (typename common::Links < Time >::const_iterator it_r =
                 result.first; it_r != result.second; ++it_r) {
                 it_r->second.get_model()->post_event(
                     t, common::ExternalEvent < Time >(it_r->second,
                                                       event.get_content()));
        }
    }

    virtual std::string to_string(int level) const
    {
    	std::ostringstream ss;

    	ss << common::spaces(level * 2) << "Childs :" << std::endl;
        for (auto & child : _child_list) {
            ss << child->to_string(level + 1);
        }
        ss << _link_list.to_string(level);
        return ss.str();
    }

private:
    common::Links < Time >        _link_list;
    common::Models < Time >       _child_list;
    common::Coordinator < Time >* _coordinator;
};

} } // namespace paradevs pdevs

#endif
