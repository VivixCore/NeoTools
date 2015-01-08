#pragma once
#ifndef nt_TIMER_H_INCLUDED
#define nt_TIMER_H_INCLUDED

struct ntTimer 
{ 
	//private: //The clock time when the timer started 
		int startTicks; //The ticks stored when the timer was paused 
		int pausedTicks; //The timer status 
		bool paused; 
		bool started; 
	//public: //Initializes variables 
		ntTimer(); //The various clock actions 
		ntTimer(const ntTimer&);
		ntTimer& operator = (const ntTimer&);
		void start(); 
		void stop(); 
		void pause(); 
		void unpause(); //Gets the timer's time 
		int get_ticks(); //Checks the status of the timer 
		bool is_started(); 
		bool is_paused(); 
};

#endif