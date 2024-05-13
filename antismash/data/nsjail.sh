#!/bin/bash

mkdir /sys/fs/cgroup/{cpu,pids,memory}/NSJAIL

nsjail -v \
    -Ml --port 4444 \
    --user nobody:nobody \
    --group nogroup:nogroup \
    --hostname localhost \
    --cwd /app \
    -R /app/flag.txt \
    -R /app/antismash \
    -R /bin \
    -R /lib \
    -R /lib64 \
    -R /usr/lib \
    -R /app/libc.so.6 \
    -R /app/ld-linux-x86-64.so.2 \
    --detect_cgroupv2 \
    --time_limit 30 \
    --cgroup_pids_max 8 \
    --cgroup_mem_max 67108864 \
    --cgroup_cpu_ms_per_sec 100 \
    -- $@
