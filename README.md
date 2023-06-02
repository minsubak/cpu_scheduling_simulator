# CPU scheduling simulator 
update: 02/06/2023

## INDEX
[How to Download](#how-to-download)   
[How to run](#how-to-run)   
[Run screen](#run-screen)
[Anything else](#anything-else)
[Contributor](#contributor)

## How to Download
 - click the download button at the top of the page or run this command on a terminal that supports git
 ```
 git clone github.com/minsubak/cpu_scheduling_simulator.git
 git switch tui
 ```

## How to run
 - run this command to operate the makefile (recommanded MSYS2)
 ```
 make clean
 clean
 ./main.exe
 ```

## Run screen
![image](https://github.com/minsubak/cpu_scheduling_simulator/assets/54968879/3a76b07c-af9d-4a38-9456-eddd1d5560db)   

## Anything else
 - IDE: Visual Studio Code, MSYS2
 - encoding: UTF-8

## Contributor

 - 사용한 스케줄링 기법:   
   FCFS, SJF, Non-Preemption Priority, Preemption Priority, RR, SRT, HRN

 - 입력(순서 고정):    
   프로세스 인덱스, 프로세스ID, 도착시간, 서비스시간, 우선순위, 시간할당량

 - 출력(순서 고정):    
   간트 차트, 각 프로세스 별 대기시간, 평균 대기 시간, 각 프로세스 별 응답시간, 
   평균 응답 시간, 각 프로세스 별 반환 시간, 평균 반환 시간

 - 제출 기한:   
   6/4

 - 보고서 내용:    
   팀 구성, 팀원 역할, 개발언어, UI, 함수/클래스 다이어그램, 개발일정 등

 - 제출 파일:   
   최종 보고서, 소스코드, 실행파일 제출
   팀 구성, 님원 역할, 개발언어, 함수/클래스 구성도/다이어그램, 자료구조/주요변수 설명, 
   각 알고리즘 핵심 부분코드 설명, 개발한 UI 특징, 각 알고리즘 실행 결과 캡쳐 및 설명

 - 기타:   
   해당 소스 코드, 파일은 VScode, UTF-8 환경에서 작성
   폰트 오류 발생 시 인코딩을 UTF-8로 변경

 - 제작자: 민도우(박민수)