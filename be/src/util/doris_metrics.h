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

#ifndef DORIS_BE_SRC_COMMON_UTIL_DORIS_METRICS_H
#define DORIS_BE_SRC_COMMON_UTIL_DORIS_METRICS_H

#include <set>
#include <string>
#include <vector>

#include "util/metrics.h"

namespace doris {

class SystemMetrics;

class DorisMetrics {
public:
    // counters
    static IntCounter fragment_requests_total;
    static IntCounter fragment_request_duration_us;
    static IntCounter http_requests_total;
    static IntCounter http_request_duration_us;
    static IntCounter http_request_send_bytes;
    static IntCounter query_scan_bytes;
    static IntCounter query_scan_rows;
    static IntCounter ranges_processed_total;
    static IntCounter push_requests_success_total;
    static IntCounter push_requests_fail_total;
    static IntCounter push_request_duration_us;
    static IntCounter push_request_write_bytes;
    static IntCounter push_request_write_rows;
    static IntCounter create_tablet_requests_total;
    static IntCounter create_tablet_requests_failed;
    static IntCounter drop_tablet_requests_total;

    static IntCounter report_all_tablets_requests_total;
    static IntCounter report_all_tablets_requests_failed;
    static IntCounter report_tablet_requests_total;
    static IntCounter report_tablet_requests_failed;
    static IntCounter report_disk_requests_total;
    static IntCounter report_disk_requests_failed;
    static IntCounter report_task_requests_total;
    static IntCounter report_task_requests_failed;

    static IntCounter schema_change_requests_total;
    static IntCounter schema_change_requests_failed;
    static IntCounter create_rollup_requests_total;
    static IntCounter create_rollup_requests_failed;
    static IntCounter storage_migrate_requests_total;
    static IntCounter delete_requests_total;
    static IntCounter delete_requests_failed;
    static IntCounter cancel_delete_requests_total;
    static IntCounter clone_requests_total;
    static IntCounter clone_requests_failed;

    static IntCounter finish_task_requests_total;
    static IntCounter finish_task_requests_failed;

    static IntCounter base_compaction_request_total;
    static IntCounter base_compaction_request_failed;
    static IntCounter cumulative_compaction_request_total;
    static IntCounter cumulative_compaction_request_failed;

    static IntCounter base_compaction_deltas_total;
    static IntCounter base_compaction_bytes_total;
    static IntCounter cumulative_compaction_deltas_total;
    static IntCounter cumulative_compaction_bytes_total;

    static IntCounter alter_task_success_total;
    static IntCounter alter_task_failed_total;

    static IntCounter meta_write_request_total;
    static IntCounter meta_write_request_duration_us;
    static IntCounter meta_read_request_total;
    static IntCounter meta_read_request_duration_us;

    // Gauges
    static IntGauge memory_pool_bytes_total;
    static IntGauge process_thread_num;
    static IntGauge process_fd_num_used;
    static IntGauge process_fd_num_limit_soft;
    static IntGauge process_fd_num_limit_hard;

    ~DorisMetrics();
    // call before calling metrics
    void initialize(
        const std::string& name,
        bool init_system_metrics = false,
        const std::set<std::string>& disk_devices = std::set<std::string>(),
        const std::vector<std::string>& network_interfaces = std::vector<std::string>());

    static DorisMetrics* instance() { return &_s_doris_metrics; }
    static MetricRegistry* metrics() { return _s_doris_metrics._metrics; }
private:
    // Don't allow constrctor
    DorisMetrics();

    void update();
    void _update_process_thread_num();
    void _update_process_fd_num();

private:
    static const char* _s_hook_name;

    static DorisMetrics _s_doris_metrics;

    MetricRegistry* _metrics;
    SystemMetrics* _system_metrics;
};

};

#endif
