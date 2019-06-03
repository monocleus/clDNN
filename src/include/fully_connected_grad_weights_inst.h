/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "api/CPP/fully_connected_grad_weights.hpp"
#include "primitive_inst.h"

namespace cldnn
{
template <>
struct typed_program_node<fully_connected_grad_weights> : public typed_program_node_base<fully_connected_grad_weights>
{
    using parent = typed_program_node_base<fully_connected_grad_weights>;

public:
    using parent::parent;

    program_node& input() const { return get_dependency(0); }
    program_node& weights() const { return get_dependency(2); }
    program_node& bias() const { return get_dependency(3); }
    program_node& prev_weights_grad() const { return bias_term() ? get_dependency(4) : get_dependency(3); }
    program_node& prev_bias_grad() const { return get_dependency(5); }
    bool use_momentum() const { return !get_primitive()->prev_weights_grad.empty(); }
    bool bias_term() const { return !get_primitive()->bias.empty(); }

};

using fully_connected_grad_weights_node = typed_program_node<fully_connected_grad_weights>;

template <>
class typed_primitive_inst<fully_connected_grad_weights> : public typed_primitive_inst_base<fully_connected_grad_weights>
{
    using parent = typed_primitive_inst_base<fully_connected_grad_weights>;

public:
    static layout calc_output_layout(fully_connected_grad_weights_node const& node);
    static std::string to_string(fully_connected_grad_weights_node const& node);

public:
    typed_primitive_inst(network_impl& network, fully_connected_grad_weights_node const& node);

    memory_impl& weights_memory() const { return dep_memory(2); }
    memory_impl& bias_memory() const { return dep_memory(3); }
    memory_impl& prev_weights_grad() const { return bias_term() ? dep_memory(4) : dep_memory(3); }
    memory_impl& prev_bias_grad() const { return dep_memory(5); }
    bool use_momentum() const { return !argument.prev_weights_grad.empty(); }
    bool bias_term() const { return !argument.bias.empty(); }
};

using fully_connected_grad_weights_inst = typed_primitive_inst<fully_connected_grad_weights>;

}
