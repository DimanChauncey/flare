# Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
#
# Licensed under the BSD 3-Clause License (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of the
# License at
#
# https://opensource.org/licenses/BSD-3-Clause
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

cc_library(
  name = 'hbase',
  hdrs = [
    'hbase_channel.h',
    'hbase_client_controller.h',
    'hbase_server_controller.h',
    'hbase_service.h',
  ],
  deps = [
    ':hbase_client',
    ':hbase_server',
  ],
  visibility = 'PUBLIC',
)

cc_library(
  name = 'hbase_client',
  hdrs = [
    'hbase_channel.h',
    'hbase_client_controller.h',
  ],
  deps = [
    ':hbase_channel',
    ':hbase_client_controller',
    ':hbase_client_protocol',
  ],
  visibility = 'PUBLIC',
)

cc_library(
  name = 'hbase_server',
  hdrs = [
    'hbase_server_controller.h',
    'hbase_service.h',
  ],
  deps = [
    ':hbase_service',
    ':hbase_server_controller',
    ':hbase_server_protocol',
  ],
  visibility = 'PUBLIC',
)

cc_library(
  name = 'call_context',
  hdrs = 'call_context.h',
  srcs = 'call_context.cc',
  deps = [
    '//flare/rpc/protocol:controller',
    '//flare/net/hbase/proto:rpc_proto',
  ]
)

cc_library(
  name = 'call_context_factory',
  hdrs = 'call_context_factory.h',
  srcs = 'call_context_factory.cc',
  deps = [
    ':call_context',
    ':hbase_server_controller',
    '//flare/base:chrono',
    '//flare/rpc/protocol:controller',
  ]
)

cc_library(
  name = 'message',
  hdrs = 'message.h',
  srcs = 'message.cc',
  deps = [
    '//flare/base:buffer',
    '//flare/base:endian',
    '//flare/base:maybe_owning',
    '//flare/base/buffer:zero_copy_stream',
    '//flare/net/hbase/proto:constants',
    '//flare/net/hbase/proto:rpc_proto',
    '//flare/rpc/protocol:message',
    '//thirdparty/protobuf:protobuf',
  ]
)

cc_library(
  name = 'hbase_channel',
  hdrs = 'hbase_channel.h',
  srcs = 'hbase_channel.cc',
  deps = [
    ':hbase_client_controller',
    ':hbase_client_protocol',
    ':message',
    '//flare/base:callback',
    '//flare/base:down_cast',
    '//flare/base:random',
    '//flare/base:string',
    '//flare/base/net:endpoint',
    '//flare/fiber:fiber',
    '//flare/rpc/internal:correlation_id',
    '//flare/rpc/internal:stream_call_gate_pool',
    '//flare/rpc/internal:stream_call_gate',
    '//flare/rpc/name_resolver:list',
    '//flare/rpc/name_resolver:name_resolver',
    '//thirdparty/protobuf:protobuf',
  ],
  visibility = 'PUBLIC',
)

cc_test(
  name = 'hbase_channel_test',
  srcs = 'hbase_channel_test.cc',
  deps = [
    ':hbase_channel',
    ':hbase_service',
    ':hbase_server_controller',
    ':hbase_client_controller',
    '//flare/rpc:rpc',
    '//flare/testing:rpc_mock',
    '//flare/testing:echo_service_proto_flare',
    '//flare/testing:endpoint',
    '//flare/testing:main',
  ]
)

cc_library(
  name = 'hbase_controller_common',
  hdrs = 'hbase_controller_common.h',
  srcs = 'hbase_controller_common.cc',
  deps = [
    '//flare/base:buffer',
    '//flare/base:logging',
    '//flare/base/internal:time_view',
    '//flare/base/net:endpoint',
    '//flare/net/hbase/proto:constants',
    '//flare/net/hbase/proto:rpc_proto',
    '//thirdparty/googletest:gtest_prod',
    '//thirdparty/protobuf:protobuf',
  ]
)

cc_test(
  name = 'hbase_controller_common_test',
  srcs = 'hbase_controller_common_test.cc',
  deps = [
    ':hbase_controller_common',
  ]
)

cc_library(
  name = 'hbase_client_controller',
  hdrs = 'hbase_client_controller.h',
  srcs = 'hbase_client_controller.cc',
  deps = [
    ':call_context',
    ':hbase_controller_common',
  ],
  visibility = 'PUBLIC',
)

cc_test(
  name = 'hbase_client_controller_test',
  srcs = 'hbase_client_controller_test.cc',
  deps = [
    ':hbase_client_controller',
    '//flare/testing:main',
  ]
)

cc_library(
  name = 'hbase_server_controller',
  hdrs = 'hbase_server_controller.h',
  srcs = 'hbase_server_controller.cc',
  deps = [
    ':hbase_controller_common',
    '//flare/base/internal:early_init',
    '//thirdparty/googletest:gtest_prod',
  ],
  visibility = 'PUBLIC',
)

cc_test(
  name = 'hbase_server_controller_test',
  srcs = 'hbase_server_controller_test.cc',
  deps = [
    ':hbase_server_controller',
    '//flare/testing:main',
  ]
)

cc_library(
  name = 'hbase_client_protocol',
  hdrs = 'hbase_client_protocol.h',
  srcs = 'hbase_client_protocol.cc',
  deps = [
    ':call_context_factory',
    ':call_context',
    ':hbase_client_controller',
    ':message',
    '//flare/base:down_cast',
    '//flare/base:endian',
    '//flare/base:logging',
    '//flare/base/buffer:zero_copy_stream',
    '//flare/net/hbase/proto:rpc_proto',
    '//flare/rpc/protocol:controller',
    '//flare/rpc/protocol:message',
    '//flare/rpc/protocol:stream_protocol',
    '//thirdparty/googletest:gtest_prod',
  ]
)

cc_library(
  name = 'hbase_server_protocol',
  hdrs = 'hbase_server_protocol.h',
  srcs = 'hbase_server_protocol.cc',
  deps = [
    ':call_context_factory',
    ':call_context',
    ':hbase_server_controller',
    ':message',
    '//flare/base:logging',
    '//flare/base:down_cast',
    '//flare/base:endian',
    '//flare/base/buffer:zero_copy_stream',
    '//flare/net/hbase/proto:rpc_proto',
    '//flare/rpc/protocol:message',
    '//flare/rpc/protocol:stream_protocol',
    '//thirdparty/googletest:gtest_prod',
  ]
)

cc_test(
  name = 'hbase_protocol_test',
  srcs = 'hbase_protocol_test.cc',
  deps = [
    ':call_context',
    ':hbase_client_controller',
    ':hbase_client_protocol',
    ':hbase_server_controller',
    ':hbase_server_protocol',
    ':message',
    '//flare/base:down_cast',
    '//flare/init:on_init',
    '//flare/testing:echo_service_proto_flare',
    '//flare/testing:main',
  ]
)


cc_library(
  name = 'hbase_service',
  hdrs = 'hbase_service.h',
  srcs = 'hbase_service.cc',
  deps = [
    ':call_context',
    ':hbase_server_controller',
    ':hbase_server_protocol',
    ':message',
    '//flare/base:callback',
    '//flare/base:down_cast',
    '//flare/base/internal:lazy_init',
    '//flare/fiber:fiber',
    '//flare/rpc/internal:fast_latch',
    '//flare/rpc/internal:rpc_metrics',
    '//flare/rpc/protocol:stream_service',
    '//flare/net/hbase/proto:rpc_proto',
  ],
  visibility = 'PUBLIC',
)

cc_test(
  name = 'hbase_service_test',
  srcs = 'hbase_service_test.cc',
  deps = [
    ':call_context',
    ':message',
    ':hbase_service',
    ':hbase_server_controller',
    '//flare/base:down_cast',
    '//flare/testing:main',
    '//flare/testing:echo_service_proto_flare',
  ]
)
