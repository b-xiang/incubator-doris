// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef DORIS_BE_SRC_OLAP_ROWSET_ALPHA_ROWSET_META_H
#define DORIS_BE_SRC_OLAP_ROWSET_ALPHA_ROWSET_META_H

#include "olap/rowset/rowset_meta.h"

#include <memory>
#include <vector>
#include <string>

namespace doris {

class AlphaRowsetMeta;
using AlphaRowsetMetaSharedPtr = std::shared_ptr<AlphaRowsetMeta>;

class AlphaRowsetMeta : public RowsetMeta {
public:
    bool deserialize_extra_properties() override;

    void get_segment_groups(std::vector<SegmentGroupPB>* segment_groups);

    void add_segment_group(const SegmentGroupPB& segment_group);

    void get_pending_segment_groups(std::vector<PendingSegmentGroupPB>* pending_segment_groups);

    void add_pending_segment_group(const PendingSegmentGroupPB& pending_segment_group);

    void clear_pending_segment_group();

private:
    void _serialize_extra_meta_pb();

private:
    AlphaRowsetExtraMetaPB _extra_meta_pb;
};

typedef std::shared_ptr<AlphaRowsetMeta> AlphaRowsetMetaSharedPtr;

}

#endif // DORIS_BE_SRC_OLAP_ROWSET_ALPHA_ROWSET_META_H