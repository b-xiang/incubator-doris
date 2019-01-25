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

#ifndef DORIS_BE_SRC_OLAP_ROWSET_ROWSET_H
#define DORIS_BE_SRC_OLAP_ROWSET_ROWSET_H

#include "gen_cpp/olap_file.pb.h"
#include "olap/new_status.h"
#include "olap/rowset/rowset_reader.h"
#include "olap/rowset/rowset_meta.h"

#include <memory>

namespace doris {

class Rowset;
using RowsetSharedPtr = std::shared_ptr<Rowset>;

class RowsetWriter;

class Rowset {
public:
    static Rowset* create();
    virtual ~Rowset() { }

    virtual OLAPStatus init() = 0;

    virtual std::unique_ptr<RowsetReader> create_reader() = 0;

    virtual OLAPStatus copy(RowsetWriter* dest_rowset_writer) = 0;

    virtual OLAPStatus remove() = 0;

    virtual OLAPStatus to_rowset_pb(const RowsetMetaPB& rs_meta);

    virtual RowsetMetaSharedPtr rowset_meta() const = 0;

    virtual int data_disk_size() const = 0;

    virtual int index_disk_size() const = 0;

    virtual bool empty() const = 0;

    virtual bool zero_num_rows() const = 0;

    virtual size_t num_rows() const = 0;

    virtual Version version() const = 0;

    virtual int64_t end_version() const = 0;

    virtual int64_t start_version() const = 0;

    virtual VersionHash version_hash() const = 0;

    virtual bool in_use() const = 0;

    virtual RowsetId rowset_id() const = 0;

    virtual bool delete_files() const = 0;

    virtual void set_version(Version version) = 0;

    virtual void set_version_hash(VersionHash version_hash) = 0;

    virtual int64_t create_time() = 0;
};

} // namespace doris

#endif // DORIS_BE_SRC_OLAP_ROWSET_ROWSET_H