# Balance (default profile)
   
   # Little CPU
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor thunderstorm
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq 234000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq 1586000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/go_hispeed_load
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/go_hispeed_load 87
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/above_hispeed_delay
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/above_hispeed_delay "50000 1066000:30000"
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_rate
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_rate 30000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/hispeed_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/hispeed_freq 754000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_slack
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_slack 20000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/target_loads
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/target_loads "75 1066000:85"
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/min_sample_time
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/min_sample_time 40000
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/mode
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/mode 0
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boost
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boost 0
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/io_is_busy
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/io_is_busy 0
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/param_index
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/param_index 0
   chmod 0644 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boostpulse_duration
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boostpulse_duration 30000
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/down_low_load_threshold 10

   # Big CPU
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor thunderstorm
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq 312000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq 2288000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/go_hispeed_load
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/go_hispeed_load 92
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/above_hispeed_delay
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/above_hispeed_delay "50000 1560000:49000 1664000:49000"
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_rate
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_rate 30000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/hispeed_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/hispeed_freq 1352000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_slack
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_slack 20000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/target_loads
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/target_loads "80 1040000:81 1352000:87 1664000:90"
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/min_sample_time
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/min_sample_time 40000
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/mode
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/mode 0
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boost
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boost 0
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/io_is_busy
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/io_is_busy 0
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/param_index
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/param_index 0
   chmod 0644 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boostpulse_duration
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boostpulse_duration 30000
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/down_low_load_threshold 5

   # CPU HOTPLUG
   write /sys/power/cpuhotplug/enabled 1
   write /sys/module/autosmp/parameters/enabled N
   write /sys/devices/system/cpu/cpufreq/mp-cpufreq/cluster1_all_cores_max_freq 0
   write /sys/module/workqueue/parameters/power_efficient N

   # Samsung Hotplug settings
   chmod 0664 /sys/power/cpuhotplug/max_online_cpu
   write /sys/power/cpuhotplug/max_online_cpu 8
   chmod 0664 /sys/power/cpuhotplug/min_online_cpu
   write /sys/power/cpuhotplug/min_online_cpu 1
   chmod 0644 /sys/power/cpuhotplug/governor/enabled
   write /sys/power/cpuhotplug/governor/enabled 1
   chmod 0664 /sys/power/cpuhotplug/governor/dual_change_ms
   # write /sys/power/cpuhotplug/governor/dual_change_ms 50
   chmod 0644 /sys/power/cpuhotplug/governor/lit_multi_ratio
   write /sys/power/cpuhotplug/governor/lit_multi_ratio 100
   chmod 0644 /sys/power/cpuhotplug/governor/to_dual_ratio
   write /sys/power/cpuhotplug/governor/to_dual_ratio 70
   chmod 0644 /sys/power/cpuhotplug/governor/to_quad_ratio
   write /sys/power/cpuhotplug/governor/to_quad_ratio 80

   # FINGERPRINT BOOST
   write /sys/kernel/fp_boost/enabled 0

   # INPUT BOOST CPU
   write /sys/module/cpu_boost/parameters/input_boost_enabled 0

   # HMP
   chmod 0644 /sys/kernel/hmp/up_threshold
   write /sys/kernel/hmp/up_threshold 524
   chmod 0644 /sys/kernel/hmp/down_threshold
   write /sys/kernel/hmp/down_threshold 214

   # GPU
   chmod 0644 /sys/devices/14ac0000.mali/max_clock
   write /sys/devices/14ac0000.mali/max_clock 650
   chmod 0644 /sys/devices/14ac0000.mali/min_clock
   write /sys/devices/14ac0000.mali/min_clock 112
   chmod 0644 /sys/devices/14ac0000.mali/power_policy
   write /sys/devices/14ac0000.mali/power_policy coarse_demand
   chmod 0644 /sys/devices/14ac0000.mali/dvfs_governor
   write /sys/devices/14ac0000.mali/dvfs_governor 1
   chmod 0644 /sys/devices/14ac0000.mali/highspeed_clock
   write /sys/devices/14ac0000.mali/highspeed_clock 419
   chmod 0644 /sys/devices/14ac0000.mali/highspeed_load
   write /sys/devices/14ac0000.mali/highspeed_load 92
   chmod 0644 /sys/devices/14ac0000.mali/highspeed_delay
   write /sys/devices/14ac0000.mali/highspeed_delay 1
   write /sys/devices/14ac0000.mali/throttling1 600
   write /sys/devices/14ac0000.mali/throttling2 546
   write /sys/devices/14ac0000.mali/throttling3 419
   write /sys/devices/14ac0000.mali/throttling4 338
   write /sys/devices/14ac0000.mali/trippimg 260
   chmod 0664 /sys/kernel/hmp/down_compensation_high_freq
   write /sys/kernel/hmp/down_compensation_high_freq 1170000
   chmod 0664 /sys/kernel/hmp/down_compensation_mid_freq
   write /sys/kernel/hmp/down_compensation_mid_freq 962000
   chmod 0664 /sys/kernel/hmp/down_compensation_low_freq
   write /sys/kernel/hmp/down_compensation_low_freq 858000
   write /proc/sys/kernel/random/write_wakeup_threshold 384
   write /proc/sys/kernel/random/read_wakeup_threshold 64

   # IO Scheduler
   write /sys/block/sda/queue/scheduler cfq
   write /sys/block/sda/queue/read_ahead_kb 512
   write /sys/block/mmcblk0/queue/scheduler cfq
   write /sys/block/mmcblk0/queue/read_ahead_kb 512

   # Wakelocks
   write /sys/module/wakeup/parameters/enable_sensorhub_wl 1
   write /sys/module/wakeup/parameters/enable_ssp_wl 1
   write /sys/module/wakeup/parameters/enable_bcmdhd4359_wl 0
   write /sys/module/wakeup/parameters/enable_bluedroid_timer_wl 1
   write /sys/module/wakeup/parameters/enable_wlan_wake_wl 1
   write /sys/module/sec_battery/parameters/wl_polling 5
   write /sys/module/sec_nfc/parameters/wl_nfc 1

   # Misc
   write /sys/module/sync/parameters/fsync_enabled 1
   write /sys/kernel/dyn_fsync/Dyn_fsync_active 0
   write /sys/kernel/sched/gentle_fair_sleepers 0
   write /sys/kernel/sched/arch_power 0
   write /sys/kernel/power_suspend/power_suspend_mode 3
   write /proc/sys/net/ipv4/tcp_congestion_control westwood

   # LMK
   write /sys/module/lowmemorykiller/parameters/minfree "18432,23040,27648,32256,56064,76152"
   write /proc/sys/vm/vfs_cache_pressure 70
   write /proc/sys/vm/swappiness 160

