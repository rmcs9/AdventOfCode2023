#include "day20.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <tuple>

std::queue<std::tuple<std::string, std::string, int>> pulseQ;
int lowPulses = 0, highPulses = 0;

class module{
public:

	std::string tag;
	std::list<std::string> dests;

	char type;
	//for conjs
	std::unordered_map<std::string, int> lastSigIn = std::unordered_map<std::string, int>();

	//for flips
	bool on = false;

	void processSignal(std::string from, int pulse){
		int newpulse;
		if(type == '%'){
			if(pulse == 1){
				on = !on;
				newpulse = on ? 2 : 1;
				for(auto send : dests){
					pulseQ.push(std::make_tuple(send, tag, newpulse));
				}	
				if(newpulse == 2){
					highPulses += dests.size();
				}
				else{
					lowPulses += dests.size();
				}
			}
		}
		else{
			lastSigIn[from] = pulse;
			bool allHigh = std::all_of(lastSigIn.begin(), lastSigIn.end(), [](auto element){ return element.second == 2; });
			newpulse = allHigh ? 1 : 2; 
			for(auto send : dests){
				pulseQ.push(std::make_tuple(send, tag, newpulse));
			}	
			if(newpulse == 2){
				highPulses += dests.size();
			}
			else{
				lowPulses += dests.size();
			}

		}
	
	}

	module(std::string tg, char t, std::list<std::string> d){
		tag = tg;
		type = t;
		dests = d;
	}
};


void day20::signals(std::string fp){
	std::fstream data(fp);
	std::unordered_map<std::string, module*> modules;
	std::list<std::string> broadcasterSends;

	std::string line;
	getline(data, line);
	while(!data.eof()) {
		char type = line.at(0);

		std::string tag = line.substr(1, line.find(' ') - 1);
		
		line = line.substr(line.find('>') + 1);
		
		std::list<std::string> dests;
		while(!line.empty()){
			dests.push_back(line.substr(1, line.find(',') - 1));
			line = line.find(',') == std::string::npos ? "" : line.substr(line.find(',') + 1);
		}
		if(type == 'b'){
			broadcasterSends = dests;
		}
		else{
			auto current = new module(tag, type, dests);
			modules[tag] = current;
		}
		getline(data, line);
	}

	for(auto &module : modules){
		for(auto dest : module.second->dests){
			if(modules.find(dest) != modules.end() && modules[dest]->type == '&'){
				modules[dest]->lastSigIn[module.first] = 1;	
			}
		}
	}

	for(int i = 0; i < 1000; i++){
		for(auto send : broadcasterSends){
			pulseQ.push(std::make_tuple(send, "broadcaster", 1));
			lowPulses++;
		}
		lowPulses += 1;

		while(!pulseQ.empty()){
			auto current = pulseQ.front();
			pulseQ.pop();

			if(modules.find(std::get<0>(current)) != modules.end()){
				modules[std::get<0>(current)]->processSignal(std::get<1>(current), std::get<2>(current));
			}
		}
	 }

	std::cout << "p1 total: " << lowPulses * highPulses << '\n';
}
