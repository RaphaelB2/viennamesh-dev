/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_05052005_0733)
#define FUSION_NEXT_IMPL_05052005_0733

#include <boost/mpl/next.hpp>

namespace boost { namespace fusion
{
    struct mpl_iterator_tag;

    template <typename Iterator>
    struct mpl_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<mpl_iterator_tag>
        {
            template <typename Iterator>
            struct apply 
            {
                typedef mpl_iterator<
                    typename mpl::next<typename Iterator::iterator_type>::type
                > type;
    
                static type
                call(Iterator)
                {
                    return type();
                }
            };
        };
    }
}}

#endif


