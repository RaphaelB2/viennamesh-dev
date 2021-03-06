/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR10_05042005_0257)
#define FUSION_VECTOR10_05042005_0257

#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/container/vector/detail/at_impl.hpp>
#include <boost/fusion/sequence/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/sequence/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/sequence/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_sequence_tag;

    struct vector0 : sequence_base<vector0>
    {
        typedef mpl::vector0<> types;
        typedef vector_tag ftag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef random_access_sequence_tag category;
        typedef mpl::int_<0> size;
    };

// expand vector1 to vector10
#define BOOST_PP_FILENAME_1 <boost/fusion/sequence/container/vector/detail/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, 10)
#include BOOST_PP_ITERATE()

}}

#endif

