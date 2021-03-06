/*
    Copyright (C) 2019 gxb

    This file is part of gxb-core.

    gxb-core is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gxb-core is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gxb-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <graphene/chain/protocol/types.hpp>
#include <graphene/db/generic_index.hpp>

namespace graphene { namespace chain {

    /**
     *  @brief caculate Contribution ratio
     *  @ingroup object
     *  @ingroup protocol
     */
     class staking_object : public graphene::chain::abstract_object<staking_object>
     {
       public:
          static const uint8_t space_id = protocol_ids;
          static const uint8_t type_id = staking_object_type;

          account_id_type   owner;
          time_point_sec    create_date_time;
          uint32_t          staking_days;
          uint32_t          weight;
          fc::string        program_id;
          asset             amount;
          witness_id_type   trust_node;
          bool              is_valid;
     };
     struct by_owner;
     struct by_trust_node;

     /**
     * @ingroup object_index
     */
     using staking_multi_index_type = multi_index_container<
         staking_object, indexed_by<
                             ordered_unique<tag<by_id>, member<object, object_id_type, &object::id>>,
                             ordered_non_unique<tag<by_owner>, member<staking_object, account_id_type, &staking_object::owner>>,
                             ordered_non_unique<tag<by_trust_node>,
                                                composite_key<
                                                    staking_object,
                                                    member<staking_object, witness_id_type, &staking_object::trust_node>,
                                                    member<object, object_id_type, &object::id>>>>>;

     typedef generic_index<staking_object, staking_multi_index_type> staking_index;

 }}

 FC_REFLECT_DERIVED (graphene::chain::staking_object,
                     (graphene::chain::object),
                     (owner)(create_date_time)(staking_days)(weight)(program_id)(amount)(trust_node)(is_valid))
