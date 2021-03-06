/*=============================================================================
    Copyright (c) 2001-2004 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PHOENIX_CORE_AS_ACTOR_HPP
#define PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/spirit/phoenix/core/actor.hpp>

namespace boost { namespace phoenix
{
    template <typename T>
    struct as_actor_base; // defined in value.hpp

    template <typename Base>
    struct as_actor_base<actor<Base> >
    {
        typedef Base type;

        static Base const&
        convert(actor<Base> const& x)
        {
            return x;
        }
    };

    template <>
    struct as_actor_base<void_type>
    {
        typedef void_type type;
        struct error_attempting_to_convert_void_type_to_an_actor {};

        static void
        convert(error_attempting_to_convert_void_type_to_an_actor);
    };

    template <>
    struct as_actor_base<void>
    {
        typedef void type;
        struct error_attempting_to_convert_void_type_to_an_actor {};

        static void
        convert(error_attempting_to_convert_void_type_to_an_actor);
    };

    template <typename T>
    struct as_actor
    {
        typedef actor<typename as_actor_base<T>::type> type;

        static type
        convert(T const& x)
        {
            return as_actor_base<T>::convert(x);
        }
    };
}}

#endif
