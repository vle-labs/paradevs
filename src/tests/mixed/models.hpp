/**
 * @file tests/mixed/models.hpp
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

#ifndef TESTS_MIXED_MODELS_HPP
#define TESTS_MIXED_MODELS_HPP 1

#include <common/time/DoubleTime.hpp>
#include <common/Trace.hpp>

#include <dtss/Dynamics.hpp>

#include <pdevs/Dynamics.hpp>

namespace paradevs { namespace tests { namespace mixed {

template < class SchedulerHandle>
class A1 :
        public paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                           paradevs::common::NoParameters >
{
public:
    A1(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(
                                        name, parameters)
    { }
    virtual ~A1()
    { }

    void dint(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace() <<
            common::TraceElement < common::DoubleTime >(get_name(), t,
                                            common::DELTA_INT);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename common::DoubleTime::type t,
              typename common::DoubleTime::type /* e */,
              const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename common::DoubleTime::type t,
               typename common::DoubleTime::type /* e */,
               const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif
    }

    typename common::DoubleTime::type start(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::START);
        common::Trace < common::DoubleTime >::trace().flush();
#endif
        _phase = WAIT;
        return 0;
    }

    typename common::DoubleTime::type ta(
        typename common::DoubleTime::type t) const
    {
#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::TA);
        common::Trace < common::DoubleTime >::trace().flush();
#endif
        if (_phase == WAIT) {
            return 1;
        } else {
            return 0;
        }
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < common::DoubleTime,
                                               SchedulerHandle >("out", 0.));

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

template < class SchedulerHandle>
class B1 :
        public paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                           paradevs::common::NoParameters >
{
public:
    B1(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(
                                        name, parameters)
    { }
    virtual ~B1()
    { }

    void dint(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_INT);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename common::DoubleTime::type t,
              typename common::DoubleTime::type /* e */,
              const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename common::DoubleTime::type t,
               typename common::DoubleTime::type /* e */,
               const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

    }

    typename common::DoubleTime::type start(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::START);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        _phase = WAIT;
        return std::numeric_limits < double >::max();
    }

    typename common::DoubleTime::type ta(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::TA);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        if (_phase == WAIT) {
            return std::numeric_limits < double >::max();
        } else {
            return 0;
        }
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < common::DoubleTime,
                                               SchedulerHandle >("out", t));

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

template < class SchedulerHandle >
class A2 :
        public paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle >
{
public:
    A2(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                   paradevs::common::NoParameters >(
                                       name, parameters)
    { }
    virtual ~A2()
    { }

    void transition(
        const common::Bag < common::DoubleTime, SchedulerHandle >& x,
        typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)x;
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

    }

    typename common::DoubleTime::type start(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::START);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return 0;
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(
            common::ExternalEvent < common::DoubleTime,
                                    SchedulerHandle >( "out", 0.));

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return msgs;
    }
};

template < class SchedulerHandle >
class B2 :
        public paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle >
{
public:
    B2(const std::string& name,
       const paradevs::common::NoParameters& parameters) :
        paradevs::dtss::Dynamics < common::DoubleTime, SchedulerHandle,
                                   paradevs::common::NoParameters >(
                                       name, parameters)
    { }
    virtual ~B2()
    { }

    void transition(
        const common::Bag < common::DoubleTime, SchedulerHandle >& x,
        typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)x;
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_INT)
            << "x = " << x.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

    }

    typename common::DoubleTime::type start(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::START);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return 0;
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(
            common::ExternalEvent < common::DoubleTime,
                                    SchedulerHandle >("out", 0.));

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return msgs;
    }
};

template < class SchedulerHandle>
class Beep :
        public paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                           paradevs::common::NoParameters >
{
public:
    Beep(const std::string& name,
         const paradevs::common::NoParameters& parameters) :
        paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                    paradevs::common::NoParameters >(name,
                                                                     parameters)
    { }
    virtual ~Beep()
    { }

    void dint(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace() <<
            common::TraceElement < common::DoubleTime >(get_name(), t,
                                                        common::DELTA_INT);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        if (_phase == SEND) {
            _phase = WAIT;
        }
    }

    void dext(typename common::DoubleTime::type t,
              typename common::DoubleTime::type /* e */,
              const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_EXT)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        _phase = SEND;
    }

    void dconf(typename common::DoubleTime::type t,
               typename common::DoubleTime::type /* e */,
               const common::Bag < common::DoubleTime, SchedulerHandle >& msgs)
    {

#ifndef WITH_TRACE
        (void)t;
        (void)msgs;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::DELTA_CONF)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

    }

    typename common::DoubleTime::type start(typename common::DoubleTime::type t)
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::START);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        _phase = WAIT;
        return 0;
    }

    typename common::DoubleTime::type ta(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::TA);
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        if (_phase == WAIT) {
            return (rand() % 100) / 10.;
        } else {
            return 0;
        }
    }

    common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type t) const
    {

#ifndef WITH_TRACE
        (void)t;
#endif
        common::Bag < common::DoubleTime, SchedulerHandle > msgs;

        msgs.push_back(common::ExternalEvent < common::DoubleTime,
                                               SchedulerHandle >("out", 0.));

#ifdef WITH_TRACE
        common::Trace < common::DoubleTime >::trace()
            << common::TraceElement < common::DoubleTime >(get_name(), t,
                                                           common::LAMBDA)
            << "messages = " << msgs.to_string();
        common::Trace < common::DoubleTime >::trace().flush();
#endif

        return msgs;
    }

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

} } } // namespace paradevs tests mixed

#endif
