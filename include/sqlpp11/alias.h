/*
 * Copyright (c) 2013-2014, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 *   Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 *   Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SQLPP_ALIAS_H
#define SQLPP_ALIAS_H

#include <sqlpp11/type_traits.h>
#include <sqlpp11/vendor/serializer.h>

namespace sqlpp
{
	template<typename Expression, typename AliasProvider>
		struct expression_alias_t
		{
			using _traits = make_traits<value_type_of<Expression>, tag::named_expression>;
			using _recursive_traits = make_recursive_traits<Expression>;

			static_assert(is_expression_t<Expression>::value, "invalid argument for an expression alias");
			static_assert(not is_alias_t<Expression>::value, "cannot create an alias of an alias");

			using _name_t = typename AliasProvider::_name_t;

			Expression _expression;
		};

	namespace vendor
	{
		template<typename Context, typename Expression, typename AliasProvider>
			struct serializer_t<Context, expression_alias_t<Expression, AliasProvider>>
			{
				using T = expression_alias_t<Expression, AliasProvider>;

				static Context& _(const T& t, Context& context)
				{
					context << '(';
					serialize(t._expression, context);
					context << ") AS ";
					context << T::_name_t::_get_name();
					return context;
				}
			};

	}
}

#endif
