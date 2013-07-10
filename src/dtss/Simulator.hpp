/**
 * @file Simulator.hpp
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

#ifndef DTSS_SIMULATOR
#define DTSS_SIMULATOR 1

#include <common/Links.hpp>
#include <common/Node.hpp>
#include <common/Simulator.hpp>

#include <dtss/Dynamics.hpp>

namespace paradevs { namespace dtss {

class Simulator : public common::Simulator
{
public :
    Simulator(Dynamics* dynamics, common::Time time_step);
    virtual ~Simulator();

    virtual void observation(std::ostream& file) const;
    virtual void output(common::Time /* t */);
    virtual void post_message(common::Time /* t */,
                              const common::ExternalEvent& /* message */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Time transition(common::Time /* t */);

    virtual Dynamics* get_dynamics() const
    { return _dynamics; }

private :
    Dynamics*    _dynamics;
    common::Time _time_step;
};

} } // namespace paradevs dtss

#endif