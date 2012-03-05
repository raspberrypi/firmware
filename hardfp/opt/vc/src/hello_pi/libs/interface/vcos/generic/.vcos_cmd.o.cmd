cmd_drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o := bcm2708-gcc -Wp,-MD,drivers/misc/vc04_services/interface/vcos/generic/.vcos_cmd.o.d  -nostdinc -isystem /home/suse/released/tools/arm-bcm2708/linux-x86/bin/../lib/gcc/arm-bcm2708-linux-gnueabi/4.5.1/include -I/home/dc4/raspberry/arm_linux/linux/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/dc4/raspberry/arm_linux/linux/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-bcm2708/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=6 -march=armv6 -mtune=arm1136j-s -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -DVCOS_VERIFY_BKPTS=1 -Idrivers/misc/vc04_services -Idrivers/misc/vc04_services/interface/vcos/linuxkernel    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(vcos_cmd)"  -D"KBUILD_MODNAME=KBUILD_STR(vchiq)" -c -o drivers/misc/vc04_services/interface/vcos/generic/.tmp_vcos_cmd.o drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.c

source_drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o := drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.c

deps_drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o := \
  /home/dc4/raspberry/arm_linux/linux/include/linux/kconfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/foo.h) \
  drivers/misc/vc04_services/interface/vcos/vcos.h \
  drivers/misc/vc04_services/interface/vcos/vcos_assert.h \
  drivers/misc/vc04_services/interface/vcos/vcos_types.h \
  drivers/misc/vc04_services/interface/vcos/linuxkernel/vcos_platform_types.h \
  /home/suse/released/tools/arm-bcm2708/linux-x86/bin/../lib/gcc/arm-bcm2708-linux-gnueabi/4.5.1/include/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/posix_types.h \
  include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
  drivers/misc/vc04_services/interface/vcos/vcos_types.h \
  drivers/misc/vc04_services/interface/vcos/linuxkernel/vcos_platform.h \
  include/linux/semaphore.h \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/const.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/typecheck.h \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  include/linux/bitops.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/bitops.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/system.h \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/linux/linkage.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/linkage.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/irqflags.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/hwcap.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/suse/released/tools/arm-bcm2708/linux-x86/bin/../lib/gcc/arm-bcm2708-linux-gnueabi/4.5.1/include/stdarg.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/div64.h \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  include/linux/spinlock_up.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_up.h \
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/atomic.h \
  include/asm-generic/atomic-long.h \
  include/asm-generic/atomic64.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/kthread.h \
  include/linux/err.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/mm/owner.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/capability.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/timex.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/seqlock.h \
  include/linux/math64.h \
  include/linux/param.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/timex.h \
  arch/arm/mach-bcm2708/include/mach/timex.h \
  include/linux/jiffies.h \
  include/linux/rbtree.h \
  include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/string.h \
  include/linux/errno.h \
  include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/cmpxchg/local.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  include/linux/auxvec.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/completion.h \
  include/linux/wait.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/current.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/glue.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  arch/arm/mach-bcm2708/include/mach/memory.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/sizes.h \
  include/asm-generic/sizes.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/getorder.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/ipcbuf.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/sembuf.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/preempt/rt.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/rcutiny.h \
  include/linux/signal.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/sigcontext.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/pid.h \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/pfn.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/srcu.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rculist.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/sysctl.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/aio.h \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/vmalloc.h \
  include/linux/delay.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/delay.h \
  include/linux/interrupt.h \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/irqnr.h \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/hardirq.h \
    $(wildcard include/config/local/timers.h) \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/irq.h \
  arch/arm/mach-bcm2708/include/mach/irqs.h \
  arch/arm/mach-bcm2708/include/mach/platform.h \
  arch/arm/mach-bcm2708/include/mach/arm_control.h \
  include/linux/irq_cpustat.h \
  include/linux/kref.h \
  include/trace/events/irq.h \
  include/linux/tracepoint.h \
    $(wildcard include/config/tracepoints.h) \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  include/trace/define_trace.h \
    $(wildcard include/config/event/tracing.h) \
  include/linux/random.h \
  include/linux/ioctl.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/ctype.h \
  include/linux/uaccess.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/uaccess.h \
  /home/dc4/raspberry/arm_linux/linux/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  include/linux/gfp.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/slab_def.h \
  include/trace/events/kmem.h \
  include/trace/events/gfpflags.h \
  include/linux/kmalloc_sizes.h \
  drivers/misc/vc04_services/interface/vcos/generic/vcos_generic_event_flags.h \
  drivers/misc/vc04_services/interface/vcos/generic/vcos_mem_from_malloc.h \
  drivers/misc/vc04_services/interface/vcos/generic/vcos_joinable_thread_from_plain.h \
  drivers/misc/vc04_services/interface/vcos/vcos_semaphore.h \
  drivers/misc/vc04_services/interface/vcos/vcos_lowlevel_thread.h \
  drivers/misc/vc04_services/interface/vcos/vcos_timer.h \
  drivers/misc/vc04_services/interface/vcos/generic/vcos_common.h \
  drivers/misc/vc04_services/interface/vcos/vcos_init.h \
  drivers/misc/vc04_services/interface/vcos/vcos_thread.h \
  drivers/misc/vc04_services/interface/vcos/vcos_mutex.h \
  drivers/misc/vc04_services/interface/vcos/vcos_mem.h \
  drivers/misc/vc04_services/interface/vcos/vcos_logging.h \
  drivers/misc/vc04_services/interface/vcos/vcos_cmd.h \
  drivers/misc/vc04_services/interface/vcos/vcos_stdint.h \
  drivers/misc/vc04_services/interface/vcos/linuxkernel/stdint.h \
  drivers/misc/vc04_services/interface/vcos/vcos_string.h \
  drivers/misc/vc04_services/interface/vcos/vcos_event.h \
  drivers/misc/vc04_services/interface/vcos/vcos_thread_attr.h \
  drivers/misc/vc04_services/interface/vcos/vcos_event_flags.h \
  drivers/misc/vc04_services/interface/vcos/vcos_atomic_flags.h \
  drivers/misc/vc04_services/interface/vcos/vcos_once.h \
  drivers/misc/vc04_services/interface/vcos/vcos_cfg.h \

drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o: $(deps_drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o)

$(deps_drivers/misc/vc04_services/interface/vcos/generic/vcos_cmd.o):
