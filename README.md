# CPU scheduling simulator (with raylib)
 Update: 31/05/2023   
 If you want [TUI version](https://github.com/minsubak/cpu_scheduling_simulator/tree/tui) <== here   
 ## INDEX   
   [How to Download](#how-to-download)   
   [How to run](#how-to-run)   
   [Algorithm list](#algorithm-list)   
   [Anything else](#anything-else)   
   [Contributor or Referencer](#contributor-or-referencer)

 ## How to Download
   - click the download button at the top of the page or run this command on a terminal that supports git
   ```
   git clone github.com/minsubak/cpu_scheduling_simulator.git
   ```

 ## How to run
   - run this command on a terminal (recommanded MSYS2)
   
   library build
   ```
   cd lib/raylib-slim/src
   cd ../../..
   make -j`nproc`
   ```
   make execute file
   ```
   make clean
   make
   ./bin/play.exe
   ```
   
 ## Algorithm List

  ### FCFS (First Come First Served)
  - [FCFS](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/FCFS.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/0cbd3542-b6d2-4a98-90fe-778d3f125e8c)

  ### SJF (Shortest Job First)
  - [SJF](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/SJF.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/bf78ef42-60cc-4064-9708-1e13807a24f3)

  ### HRN (Hightest Response-ratio Next)
  - [HRN](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/HRN.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/78c1ff16-41ee-41bb-83af-57592484bbe6)

  ### NPP (Non-Preemption Priority)
  - [NPP](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/NPP.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/a71d95b1-c7a0-4b5c-bf6b-a4ba55a8ef85)

  ### PP (Preemption Priority)
  - [PP](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/PP.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/4b58ead0-c425-42bc-be1a-5f7afe9e664c)

  ### RR (Round-Robin)
  - [RR](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/RR.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/c626af01-4c6a-4457-9bc1-d48f33d73a6f)

  ### SRT (Shortest Remaining Time)
  - [SRT](https://github.com/minsubak/cpu_scheduling_simulator/blob/main/include/SRT.h) run screen capture

  ![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/f30202b4-d196-438a-9eae-214b172d4a81)

 ## Anything else
 - IDE: Visual Studio Code, MSYS2
 - encoding: UTF-8

 ## Contributor or referencer   
 Personal: Contributor
 + [Jaedeok Kim](https://github.com/jdeokkim)
 + [Dennis Ko](https://github.com/dennis0324)

 Organization: Referencer
 + [6PM](https://github.com/6pm-crew)
 + [Raylib](https://www.raylib.com/index.html)
