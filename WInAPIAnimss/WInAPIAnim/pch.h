#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>

#include <corecrt_math.h>

#include "Time.h"
#include "ConsoleRenderer.h"


#include <string> 
using std::string;
using std::wstring;

#include "Vector2.h"




//// 병목 현상, 원인 모르는 오류 나옴 , 쓰레드 하나가 뒤짐 , 갑자기 코드가 안 켜짐. 
//
//#include <thread>  // 멀티 쓰레드를 쓸 수 있도록 해주는 헤더 파일 
//#include <chrono>  
//#include <memory>