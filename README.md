# Hash table

## Info

Full info [here](https://nbviewer.org/github/Matvey787/hashTable/blob/main/info.ipynb)

## Small guides

### How to use VTune

1. Download [VTune](https://www.intel.com/content/www/us/en/developer/tools/oneapi/vtune-profiler-download.html?operatingsystem=linux&linux-install-type=online)
2. From the console, locate the downloaded install file.
3. Use `$ sudo sh ./<installer>.sh` to launch the GUI Installer as the root.  
Optionally, use `$ sh ./<installer>.sh` to launch the GUI Installer as the current user.  
4. Convert `perf.data` to `.vtune` (I installed Vtune to home) 

```bash
cd ~
/opt/intel/oneapi/vtune/2025.1/bin64/vtune -import "path/to/perf.data" -r "path/where/you/waant/to/save/file.vtune"  
```

5. Run `vtune-gui` from the console 

```bash
/opt/intel/oneapi/vtune/2025.1/bin64/vtune-gui 
```

### How to use Perf

1. Download perf

```bash
sudo apt-get install linux-tools
```

2. Collect perf data of your program

```bash
perf record -e cycles --call-graph dwarf ./out
```

- `-e cycles` - параметр -e задает событие, которое будет отслеживаться. В данном случае cycles указывает на сбор данных о процессорных циклах (CPU clock cycles).
- `--call-graph dwarf` - включает запись стеков вызовов (call stacks), чтобы можно было анализировать, какие функции вызывали друг друга во время выполнения программы.

>[!NOTE]  
>If you get message:
>
>Access to performance monitoring and observability operations is limited.  
>Consider adjusting /proc/sys/kernel/perf_event_paranoid setting to open  
>access to performance monitoring and observability operations for processes  
>without CAP_PERFMON, CAP_SYS_PTRACE or CAP_SYS_ADMIN Linux capability.  
>More information can be found at 'Perf events and tool security' document:  
>https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html  
>perf_event_paranoid setting is 4:  
>  -1: Allow use of (almost) all events by all users  
>      Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK  
>= 0: Disallow raw and ftrace function tracepoint access  
>= 1: Disallow CPU event access  
>= 2: Disallow kernel profiling  
>To make the adjusted perf_event_paranoid setting permanent preserve it  
>in /etc/sysctl.conf (e.g. kernel.perf_event_paranoid = <setting>)  
>
>Just use it:
>
>```bash
>sudo sysctl -w kernel.perf_event_paranoid=-1  
>```
