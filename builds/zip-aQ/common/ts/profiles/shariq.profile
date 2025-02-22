#  Thunderstorms - Shariq v5

   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor thunderstorm
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq 130000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq 1690000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/go_hispeed_load
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/go_hispeed_load 98
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/above_hispeed_delay
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/above_hispeed_delay "40000 754000:30000 858000:27000 962000:25000"
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_rate
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_rate 24000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/hispeed_freq
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/hispeed_freq 858000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_slack
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/timer_slack 24000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/target_loads
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/target_loads "75 1066000:85"
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/min_sample_time
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/min_sample_time 20000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/mode
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/mode 0
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boost
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boost 0
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/io_is_busy
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/io_is_busy 0
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/param_index
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/param_index 0
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boostpulse_duration
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/boostpulse_duration 80000
   chmod 0664 /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/down_low_load_threshold
   write /sys/devices/system/cpu/cpu0/cpufreq/thunderstorm/down_low_load_threshold 25

   # Big CPU
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor thunderstorm
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq 208000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq 1664000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/go_hispeed_load
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/go_hispeed_load 98
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/above_hispeed_delay
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/above_hispeed_delay "85000 728000:40000 1040000:30000 1144000:30000"
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_rate
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_rate 24000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/hispeed_freq
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/hispeed_freq 1040000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_slack
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/timer_slack 24000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/target_loads
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/target_loads "80 1040000:81 1248000:87 1456000:90"
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/min_sample_time
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/min_sample_time 20000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/mode
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/mode 0
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boost
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boost 0
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/io_is_busy
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/io_is_busy 0
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/param_index
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/param_index 0
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boostpulse_duration
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/boostpulse_duration 60000
   chmod 0664 /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/down_low_load_threshold
   write /sys/devices/system/cpu/cpu4/cpufreq/thunderstorm/down_low_load_threshold 25

   # CPU HOTPLUG MAIN SETTINGS
   write /sys/power/cpuhotplug/enabled 1
   write /sys/module/autosmp/parameters/enabled N
   write /sys/devices/system/cpu/cpufreq/mp-cpufreq/cluster1_all_cores_max_freq 0
   write /sys/module/workqueue/parameters/power_efficient N

   # Samsung Hotplug settings
   chmod 0664 /sys/power/cpuhotplug/max_online_cpu
   write /sys/power/cpuhotplug/max_online_cpu 8
   chmod 0664 /sys/power/cpuhotplug/min_online_cpu
   write /sys/power/cpuhotplug/min_online_cpu 1
   chmod 0664 /sys/power/cpuhotplug/governor/dual_change_ms
   write /sys/power/cpuhotplug/governor/dual_change_ms 60
   chmod 0644 /sys/power/cpuhotplug/governor/enabled
   write /sys/power/cpuhotplug/governor/enabled 1
   chmod 0644 /sys/power/cpuhotplug/governor/lit_multi_ratio
   write /sys/power/cpuhotplug/governor/lit_multi_ratio 40
   chmod 0644 /sys/power/cpuhotplug/governor/to_dual_ratio
   write /sys/power/cpuhotplug/governor/to_dual_ratio 40
   chmod 0644 /sys/power/cpuhotplug/governor/to_quad_ratio
   write /sys/power/cpuhotplug/governor/to_quad_ratio 100

   # FINGERPRINT BOOST
   write /sys/kernel/fp_boost/enabled 0

   # INPUT BOOST CPU
   write /sys/module/cpu_boost/parameters/input_boost_enabled 0

   # HMP
   chmod 0664 /sys/kernel/hmp/up_threshold
   write /sys/kernel/hmp/up_threshold 825
   chmod 0664 /sys/kernel/hmp/down_threshold
   write /sys/kernel/hmp/down_threshold 380
   chmod 0644 /sys/kernel/hmp/down_compensation_enabled 
   write /sys/kernel/hmp/down_compensation_enabled 1
   chmod 0644 /sys/kernel/hmp/down_compensation_threshold
   write /sys/kernel/hmp/down_compensation_threshold 162
   chmod 0644 /sys/kernel/hmp/down_compensation_timeout
   write /sys/kernel/hmp/down_compensation_timeout 30
   chmod 0644 /sys/kernel/hmp/sb_up_threshold
   write /sys/kernel/hmp/sb_up_threshold 254
   chmod 0644 /sys/kernel/hmp/sb_down_threshold
   write /sys/kernel/hmp/sb_down_threshold 163
   chmod 0664 /sys/kernel/hmp/down_compensation_high_freq
   write /sys/kernel/hmp/down_compensation_high_freq 754000
   chmod 0664 /sys/kernel/hmp/down_compensation_mid_freq
   write /sys/kernel/hmp/down_compensation_mid_freq 650000
   chmod 0664 /sys/kernel/hmp/down_compensation_low_freq
   write /sys/kernel/hmp/down_compensation_low_freq 546000

   # GPU
   write /sys/devices/14ac0000.mali/throttling1 546
   write /sys/devices/14ac0000.mali/throttling2 419
   write /sys/devices/14ac0000.mali/throttling3 338
   write /sys/devices/14ac0000.mali/throttling4 260
   write /sys/devices/14ac0000.mali/trippimg 112
   chmod 0664 /sys/devices/14ac0000.mali/max_clock
   write /sys/devices/14ac0000.mali/max_clock 650
   chmod 0664 /sys/devices/14ac0000.mali/min_clock
   write /sys/devices/14ac0000.mali/min_clock 112
   chmod 0664 /sys/devices/14ac0000.mali/power_policy
   write /sys/devices/14ac0000.mali/power_policy coarse_demand
   chmod 0664 /sys/devices/14ac0000.mali/dvfs_governor
   write /sys/devices/14ac0000.mali/dvfs_governor 1
   chmod 0664 /sys/devices/14ac0000.mali/highspeed_clock
   write /sys/devices/14ac0000.mali/highspeed_clock 419
   chmod 0664 /sys/devices/14ac0000.mali/highspeed_load
   write /sys/devices/14ac0000.mali/highspeed_load 90
   chmod 0664 /sys/devices/14ac0000.mali/highspeed_delay
   write /sys/devices/14ac0000.mali/highspeed_delay 1

   # IO Scheduler
   write /sys/block/sda/queue/scheduler sioplus
   write /sys/block/sda/queue/read_ahead_kb 128
   write /sys/block/mmcblk0/queue/scheduler sioplus
   write /sys/block/mmcblk0/queue/read_ahead_kb 128
   write /sys/block/sda/queue/iostats 0
   write /sys/block/mmcblk0/queue/iostats 0
   write /sys/block/sda/queue/rq_affinity 1
   write /sys/block/mmcblk0/queue/rq_affinity 1
   write /sys/block/sda/queue/nr_requests 128
   write /sys/block/mmcblk0/queue/nr_requests 256

   # Wakelocks
   write /sys/module/wakeup/parameters/enable_sensorhub_wl 0
   write /sys/module/wakeup/parameters/enable_ssp_wl 0
   write /sys/module/wakeup/parameters/enable_bcmdhd4359_wl 1
   write /sys/module/wakeup/parameters/enable_bluedroid_timer_wl 0
   write /sys/module/wakeup/parameters/enable_wlan_wake_wl 1
   write /sys/module/sec_battery/parameters/wl_polling 3
   write /sys/module/sec_nfc/parameters/wl_nfc 1

   # Misc
   write /sys/module/sync/parameters/fsync_enabled 1
   write /sys/kernel/dyn_fsync/Dyn_fsync_active 0
   write /sys/kernel/sched/gentle_fair_sleepers 0
   write /sys/kernel/sched/arch_power 1
   write /sys/kernel/power_suspend/power_suspend_mode 3

   write /proc/sys/net/ipv4/tcp_congestion_control bic

## Virtual Memory Settings | Zram
   #echo "N" > /sys/module/zswap/parameters/enabled;
   # Y - enable, N - disable
   
   setprop persist.vnswap.enabled false
   
   chmod 0644 /sys/module/zswap/parameters/enable;
   echo 0 > /sys/module/zswap/parameters/enable;
   chmod 0444 /sys/module/zswap/parameters/enable;
   swapoff /dev/block/zram0 > /dev/null 2>&1;
   echo 1 >/sys/block/zram0/reset;
   echo 2899312640 > /sys/block/zram0/disksize;
   chmod 0644 /dev/block/zram0;
   mkswap /dev/block/zram0 > /dev/null 2>&1;
   swapon /dev/block/zram0 > /dev/null 2>&1;
   
   # ENTROPY
   write /proc/sys/kernel/random/write_wakeup_threshold 384
   write /proc/sys/kernel/random/read_wakeup_threshold 64

   # SWAP
   write /proc/sys/vm/swappiness 60
   write /proc/sys/vm/vfs_cache_pressure 45
   write /proc/sys/vm/dirty_expire_centisecs 1500
   write /proc/sys/vm/dirty_writeback_centisecs 3000

   # WiFi
   setprop wifi.supplicant_scan_interval 550

   # Boeffla wakelocks
   write /sys/devices/virtual/misc/boeffla_wakelock_blocker/wakelock_blocker 'wlan_rx_wake;wlan_wake;wlan_ctrl_wake;wlan_txfl_wake;BT_bt_wake;BT_host_wake;mmc0_detect;nfc_wake_lock;grip_wake_lock;13960000.decon_f;rmnet0;GPSD;umts_ipc0;NETLINK'

   ## END
