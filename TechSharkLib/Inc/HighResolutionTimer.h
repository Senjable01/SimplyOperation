#ifndef INCLUDED_INC_HIGH_RESOLUTION_TIMER_H
#define INCLUDED_INC_HIGH_RESOLUTION_TIMER_H

//------< pragma >------------------------------------------------------------------------
#pragma once

//------< include >-----------------------------------------------------------------------
#include <winbase.h>
#include "Configulation.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //========================================================================================
	// 
	//      HighResolutionTimer
	// 
	//========================================================================================
    class HighResolutionTimer
    {
        //                     |<--pausedInterval-->|
        // ----*---------------*--------------------*------------*--------------> Frequency
        //  baseFrequency    stopFrequency   (startFrequency)   currentFrequency

    private:
        double secondPerFrequency;
        double deltaTime; // in Second

        LONGLONG baseFrequency;
        LONGLONG stopFrequency;
        LONGLONG tortalPausedInterval;

        LONGLONG lastFrequency; // lastTickedFrequency
        LONGLONG currentFrequency;

		#if FIXED_LENGTH_FRAME
		LONGLONG countsPerFrame; // 1フレームあたりのカウント数

		#endif // FIXED_LENGTH_FRAME

        bool stopped;

	public:
		HighResolutionTimer() :
			secondPerFrequency{0.0}, deltaTime{0.0},
			baseFrequency{0LL}, tortalPausedInterval{0LL}, stopFrequency{0LL},
			lastFrequency{0LL}, currentFrequency{0LL},
			#if FIXED_LENGTH_FRAME
			countsPerFrame{0LL},

			#endif // FIXED_LENGTH_FRAME
			stopped{false}
		{
			LONGLONG countsPerSec; // システムの一秒間あたりのカウント数(周波数)
			/* (Windows環境でないとfalse) */
			QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
			secondPerFrequency = 1.0 / static_cast<double>(countsPerSec);

			#if FIXED_LENGTH_FRAME
			static_assert(0 < FIXED_LENGTH_FRAME && FIXED_LENGTH_FRAME < 9'223'372'036'854'775'808, L"FIXED_LENGTH_FRAMEが不正な値です。");
			countsPerFrame = countsPerSec / FIXED_LENGTH_FRAME; // ---> (1 / FIXED_LENGTH_FRAME)秒当たりのカウント数

			#endif // FIXED_LENGTH_FRAME

			/* 構築した瞬間のカウント数を取得(timeGetTime関数より高精度) */
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrequency));
			baseFrequency = currentFrequency;
			lastFrequency = currentFrequency;

		}
		HighResolutionTimer(const HighResolutionTimer&) = delete;
		HighResolutionTimer& operator=(const HighResolutionTimer&) = delete;
		HighResolutionTimer(HighResolutionTimer&&) noexcept = delete;
		HighResolutionTimer& operator=(HighResolutionTimer&&) noexcept = delete;
		~HighResolutionTimer() {}

		// Returns the total time elapsed since Reset() was called, NOT counting any
		// time when the clock is stopped.
		float TimeStamp() const;
		// Call before message loop.
		void Reset();
		// Call when unpaused. (pause -> unpause)
		void Start();
		// Call when paused. (unpause->pause)
		void Stop();
		// Call every frame.
		bool Tick();

		// in Second
		float DeltaTime() const { return static_cast<float>(deltaTime); }

    };

	//---------------------------------------------------------------------------------
	// member functions
	//---------------------------------------------------------------------------------

	inline float HighResolutionTimer::TimeStamp() const
	{
		if (stopped)
		{
			//                     |<--pausedInterval-->|
			// ----*---------------*--------------------*------------*----------------*----------> time
			//  baseFrequency  stopFrequency  (startFrequency)  stopFrequency(latest)  currentFrequency
			return static_cast<float>(((stopFrequency - tortalPausedInterval) - baseFrequency) * secondPerFrequency);
		}
		else
		{
			//                     |<--pausedInterval-->|
			// ----*---------------*--------------------*----------------*----------> time
			//  baseFrequency  stopFrequency(latest)  (startFrequency)    currentFrequency
			return static_cast<float>(((currentFrequency - tortalPausedInterval) - baseFrequency) * secondPerFrequency);
		}

	}

	inline void HighResolutionTimer::Reset()
	{
		/* 現在のカウント数を取得 */
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrequency));
		baseFrequency = currentFrequency;
		lastFrequency = currentFrequency;

		stopFrequency	= 0;
		stopped			= false;
	}

	inline void HighResolutionTimer::Start()
	{
		if (stopped)
		{
			LONGLONG StartFrequency; // 再開する瞬間のカウント数
			/* 再開する瞬間のカウント数を取得 */
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&StartFrequency));

			//                     |<---------d---------->|
			// ----*---------------*----------------------*--------> time
			//  baseFrequency  stopFrequency(latest)  startFrequency(now)
			tortalPausedInterval += (StartFrequency - stopFrequency);
			lastFrequency	= StartFrequency;
			stopFrequency	= 0;
			stopped			= false;
		}
	}
	inline void HighResolutionTimer::Stop()
	{
		if (!stopped)
		{
			/* ポーズした瞬間のカウント数を記録 */
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&stopFrequency));
			stopped = true;
		}
	}
	inline bool HighResolutionTimer::Tick()
	{
		if (stopped)
		{
			deltaTime = 0.0;
			return true;
		}

		/* 現在のカウント数を更新 */
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentFrequency));

		#if FIXED_LENGTH_FRAME
		/* フレーム制限 */
		if (currentFrequency < lastFrequency + countsPerFrame)
		{
			return false;
		}

		#endif // FIXED_LENGTH_FRAME

		/* 現在フレームと一つ前のフレームとの時間差を記録 */
		deltaTime = (currentFrequency - lastFrequency) * secondPerFrequency;

		#if FIXED_LENGTH_FRAME
		//lastFrequency += countsPerFrame;
		//if (deltaTime > 40000)
		//{
		//	lastFrequency = currentFrequency;
		//}

		#endif // FIXED_LENGTH_FRAME

		if (deltaTime < 0.0)
		{
			deltaTime = 0.0;
		}

		/* 次回フレームの準備 */
		lastFrequency = currentFrequency;

		return true;
	}
}

#endif // !INCLUDED_INC_HIGH_RESOLUTION_TIMER_H